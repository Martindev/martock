#include <martock.h>

char save[SAVE_LEN];
int tilepix = 60;
int width = 800;
int height = 600;
chunk *world = NULL;

ALLEGRO_BITMAP *buffer;
ALLEGRO_EVENT event;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_DISPLAY *screen;
ALLEGRO_FONT *font;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_KEYBOARD_STATE state;

int main (int argc, char **argv)
{
        init();

        world_view();

        deinit();

        return 0;
}

int loop ()
{
        int running = 1;
        int tiwi = width / tilepix;
        int tihi = height / tilepix;
        entity hero = entity_make(0, 0, 50, RACE_HERO);

        ALLEGRO_BITMAP *buffer = al_create_bitmap(width + tilepix,
                                                  height + tilepix);
        ALLEGRO_BITMAP *sprite = al_create_bitmap(tilepix,
                                                  (int)(tilepix * hero.h));

        ALLEGRO_BITMAP *tmp = al_get_target_bitmap();
        al_set_target_bitmap(sprite);
        al_clear_to_color(al_map_rgb(255, 0, 0));
        al_set_target_bitmap(tmp);

        world = world_generate("hero", 10, CHUNK_FULL);

        do {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                hero.dir = 0;

                world_get_img(hero.c, (int)hero.x - (tiwi / 2),
                              (int)hero.y - (tihi / 2), tiwi + 1, tihi + 1,
                              buffer);

                al_draw_bitmap_region(buffer, fmod(hero.x, 1) * tilepix,
                                      fmod(hero.y, 1) * tilepix, width, height,
                                      0, 0, 0);

                al_draw_bitmap(sprite, (width / 2) - hero.w,
                               ((hero.y < tihi / 2) ? hero.y * tilepix :
                               (height / 2) - hero.h), 0);

                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0,
                              "Viewing: (%2e, %2e, %d)", hero.x, hero.y,
                              world->position);

                al_flip_display();

                al_init_timeout(&timeout, 0.02);
                al_wait_for_event_until(queue, &event, &timeout);

                al_get_keyboard_state(&state);

                if (al_key_down(&state, ALLEGRO_KEY_ESCAPE)) {
                        running = 0;
                }
                
                if (al_key_down(&state, ALLEGRO_KEY_W)) {
                        hero.dir ^= DIR_UP;
                } 
                
                if (al_key_down(&state, ALLEGRO_KEY_A)) {
                        hero.dir ^= DIR_LEFT;
                } 
                
                if (al_key_down(&state, ALLEGRO_KEY_D)) {
                        hero.dir ^= DIR_RIGHT;
                }

                if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {

                        al_acknowledge_resize(screen);
                        width = al_get_display_width(screen);
                        height = al_get_display_height(screen);
                        buffer = al_create_bitmap(width + tilepix,
                                                  height + tilepix);
                        tiwi = width / tilepix;
                        tihi = height / tilepix;

                } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

                        running = 0;

                }

                entity_update(&hero);

                if (hero.c > world->position) {
                        world = world_shift(world, CHUNK_RIGHT);
                } else if (hero.c < world->position) {
                        fprintf(stderr, "Shiftin'\n");
                        world = world_shift(world, CHUNK_LEFT);
                }

        } while (running);

        return 0;
}