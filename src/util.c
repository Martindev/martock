#include <martock.h>

/**
 *  Load Allegro and ENet, and initialize any modules that need it.
 *  
 *  @return: 0 no errors
 *           1 Allegro failed
 *           2 blocks failed
 */
int init ()
{
        if(!al_init())
                return 1;

        al_init_image_addon();
        al_install_keyboard();
        al_init_font_addon();
        al_init_ttf_addon();

        al_set_new_display_flags(ALLEGRO_OPENGL);
        al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);

        memset(save, 0, SAVE_LEN);
        tilepix = 60;
        width = 800;
        height = 600;
        world = NULL;

        /* Create the screen first because any bitmaps made before the screen
           will be memory bitmaps (aka "crawlers"). */
        queue = al_create_event_queue();
        screen = al_create_display(width, height);
        font = al_load_ttf_font("assets/font.ttf", 20, 0);

        al_register_event_source(queue,
                                 al_get_display_event_source(screen));
        al_register_event_source(queue,
                                 al_get_keyboard_event_source());

        block_init(NULL);

        return 0;
}

/**
 *  Set the global save profile.
 *
 *  @s: Save profile name.
 */
void set_save (const char *s)
{
        /* worlds/ = 7; /chunks = 7 */
        char loc[7 + strlen(s) + 7];
        memset(loc, 0, 7 + strlen(s) + 7);
        sprintf(loc, "worlds/%s", s);
        mkdir("worlds", 0777);
        mkdir(loc, 0777);
        sprintf(loc, "worlds/%s/chunks", s);
        mkdir(loc, 0777);
        memset(save, 0, SAVE_LEN);
        sprintf(save, "%s", s);
}

/**
 *  Open a file with its name.
 *
 *  @mode: the write mode to forward to fopen (e.g. "w", "r")
 *  @msg: the formatted string
 *  @...: the variable argument list
 */
FILE *vfopen (const char *mode, const char *msg, ...)
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
        al_destroy_display(screen);
        al_destroy_event_queue(queue);
        world_close(world);
        block_deinit();
}
