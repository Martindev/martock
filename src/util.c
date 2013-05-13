#include <martock.h>

/**
 *  Load Allegro and ENet, and initialize any modules that need it.
 *  
 *  @return: 0 no errors
 *           1 Allegro failed
 *           2 ENet failed
 *           3 blocks failed
 */
int init ()
{
        if(!al_init())
                return 1;

        al_init_image_addon();
        al_install_keyboard();
        al_init_font_addon();
        al_init_ttf_addon();

        if (enet_initialize())
                return 2;

        atexit(enet_deinitialize);

        return 0;
}

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

/**
 *  Close all the libraries and modules that were opened.
 */
void deinit ()
{
}