#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <internal/syscall.h>



int puts(const char *s) {
    // get string lenght
    size_t len = strlen(s);
    int return_value;

    for (size_t i = 0; i < len; i++) {
        // write each character
        return_value = write(1, &s[i], 1);

        // check if write was done succesfully
        if (return_value < 0) {
            errno = -return_value;
            return -1;
        }
    }

    // add \n at the end of string
    return_value = write(1, "\n", 1);

    if (return_value < 0) {
        errno = -return_value;
        return -1;
    }

    return 0;
}
