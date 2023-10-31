// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void *malloc(size_t size)
{
	// map a region of memory
	void* new_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new_ptr == MAP_FAILED) {
		return NULL;
	}

	// add element in mem_list
	mem_list_add(new_ptr, size);

	return new_ptr;
}

void *calloc(size_t nmemb, size_t size)
{
	// compute size
	size_t nr_alloc = nmemb * size;

	void* new_ptr = malloc(nr_alloc);
	if (new_ptr == MAP_FAILED) {
		return NULL;
	}

	// fill with 0
	memset(new_ptr, 0, nr_alloc);
	return new_ptr;
}

void free(void *ptr)
{
	if (ptr == NULL) {
		// nothing to free
		return;
	}

	// get length
	size_t length = mem_list_find(ptr)->len;
	// remove from mem_list
	mem_list_del(ptr);

	// delete mapping for ptr
	munmap(ptr, length);
}

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL) {
		return malloc(size);
	}

	if (size == 0) {
		free(ptr);
		return NULL;
	}

	size_t copy_len;
	struct mem_list *item = mem_list_find(ptr);
	if (item != NULL) {
		if (size > item->len) {
			copy_len = item->len;
		} else {
			copy_len = size;
		}
	}

	void* new_ptr = malloc(size);
	if (new_ptr == NULL) {
		return NULL;
	}

	memcpy(new_ptr, ptr, copy_len);

	// delete from list
	mem_list_del(ptr);

	return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (nmemb == 0 || size == 0) {
        free(ptr);
        return NULL;
    }

	// compute size
	size_t size_realloc = nmemb * size;

	// detect unsigned long overflow
	if (size_realloc / size != nmemb) {
		errno = ENOMEM;
		return NULL;
	}

	void* new_ptr = realloc(ptr, size_realloc);
	if (new_ptr == NULL) {
		return NULL;
	}

	return new_ptr;
}
