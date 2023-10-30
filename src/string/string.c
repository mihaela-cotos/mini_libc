// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	// check if destination is allocated (is not NULL)
	if (destination == NULL) {
		return NULL;
	}

	for (size_t i = 0; i <= strlen(source); i++) {
		// copy characters one after another, including \0
		destination[i] = source[i];
	}

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* https://linux.die.net/man/3/strncpy */

	if (destination == NULL) {
		return NULL;
	}

	size_t i;

	for (i = 0; i < len && source[i] != '\0'; i++) {
		// copy 'len' number of characters one after another
		destination[i] = source[i];
	}

	// copy '\0' character
	destination[i] = source[i];
	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* https://man7.org/linux/man-pages/man3/strcat.3.html */

	size_t dest_len = strlen(destination);

	// concatenate strings using strcpy
	strcpy(&(destination[dest_len]), source);

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	size_t dest_len = strlen(destination);
	size_t i;

	for (i = 0; i < len && source[i] != '\0'; i++) {
		destination[dest_len + i] = source[i];
	}
	destination[dest_len + i] = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* https://www.techiedelight.com/implement-strcmp-function-c/ */
	size_t i;
	size_t str1_len = strlen(str1);

	for (i = 0; i < str1_len; i++) {
		// check if characters are different
		if (str1[i] != str2[i]) {
			break;
		}
	}

	// return the ASCII difference
	return *(const unsigned char*)(str1 + i)  - *(const unsigned char*)(str2 + i);
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	size_t i;

	for (i = 0; i < len && str1[i] != '\0' && str2[i] != '\0'; i++) {
		// check if characters are different
		if (str1[i] < str2[i]) {
			return -1;
		}

		if (str1[i] > str2[i]) {
			return 1;
		}
	}

	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	size_t len = strlen(str);
	size_t i;

	// iterate through array and search the char
	for (i = 0; i < len; i++) {
		if (str[i] == c) {
			// if found => return
			return str + i;
		}
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	size_t len = strlen(str);
	size_t i;

	// iterate from tail to head
	for (i = len; i > 0; i--) {
		if (str[i] == c) {
			// if char is found => return
			return str + i;
		}
	}

	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	size_t haystack_len = strlen(haystack);
	size_t needle_len = strlen(needle);
	size_t i;

	for (i = 0; i <= haystack_len - needle_len; i++) {
		// using previous functions to search needle in the haystack
		if (strncmp(haystack + i, needle, needle_len) == 0) {
			return haystack + i;
		}
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	size_t haystack_len = strlen(haystack);
	size_t needle_len = strlen(needle);
	size_t i, j;

	char* last = NULL;

	for (i = 0; i <= haystack_len - needle_len; i++) {
		// using previous functions to search needle in the haystack
		if (strncmp(haystack + i, needle, needle_len) == 0) {
			last = haystack + i;
		}
	}

	return last;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* https://www.geeksforgeeks.org/write-memcpy/ */

	// cast destination and source to char*
	char* dest = (char *)destination;
	char* src = (char *)source;

	for (size_t i = 0; i < num; i++) {
		// copy contents of source to destination
		dest[i] = src[i];
	}
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	// cast destination and source to char*
	char* dest = (char *)destination;
	char* src = (char *)source;

	/*  create a temporary array that stores source content
	in case source and destination addresses are overlapping */
	char tmp[(const)num];

	for (size_t i = 0; i < num; i++) {
		tmp[i] = src[i];
	}

	// copy content from the temporary array to dest
	for (size_t i = 0; i < num; i++) {
		dest[i] = tmp[i];
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	// cast ptr1 and ptr2 to char*
	char* first = (char *)ptr1;
	char* second = (char *)ptr2;

	for (size_t i = 0; i < num; i++) {
		if (first[i] < second[i]) {
			return -1;
		} else if (first[i] > second[i]) {
			return 1;
		}
	}

	return 0;
}

void *memset(void *source, int value, size_t num)
{
	// cast source to char*
	char* src = (char *)source;

	for (size_t i = 0; i < num; i++) {
		// fill source with the constant byte (int value)
		src[i] = (unsigned char)value;
	}

	return source;
}
