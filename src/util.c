#include <stdio.h>
#include <stdarg.h>
#include <martock.h>

/**
 *  This functions as a proxy for fopen, which conveniently allows those who
 *  call it to use a formatted string, without having to use sprintf and make
 *  an array for it every time the name includes a variable.
 *
 *  @mode: the write mode to forward to fopen (e.g. "w", "r")
 *  @msg: the formatted string
 *  @...: the variable argument list
 */
FILE *vfopen(const char *mode, const char *msg, ...)
{
        va_list li;
        char temp[1024] = {0};

        va_start(li, msg);
        vsprintf(temp, msg, li);
        va_end(li);

        return fopen(temp, mode);
}
