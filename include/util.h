#ifndef UTIL_H
#define UTIL_H

/* Open a file using a formatted string as a name. */
FILE *vfopen(const char *mode, const char *msg, ...);

#endif /* UTIL_H */