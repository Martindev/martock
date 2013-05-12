#ifndef UTIL_H
#define UTIL_H

#include <martock.h>

/* Initialize all libraries and modules. */
int init ();

/* Open a file using a formatted string as a name. */
FILE *vfopen(const char *mode, const char *msg, ...);

/* Close all the libraries and modules that were opened. */
void deinit ();

#endif /* UTIL_H */