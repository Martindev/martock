#include <martock.h>

/**
 *  Generate a world of vertical chunks, stretching size chunks in either
 *  direction. Keep CHUNK_RENDER_DISTANCE chunks on either side of the origin
 *  in memory and close the others to file.
 *
 *  @size: chunks to expand from the origin
 *  @rules: rules of world generation (forward to chunk generation)
 *
 *  @return: pointer to the origin chunk
 */
chunk *world_generate (u16 size, u8 rules)
{
        if (size < CHUNK_RENDER_DISTANCE)
                return NULL;

        chunk *ch = chunk_generate(rules, NULL, 0);
        ch->position = 0 - size;

        chunk *ita = ch, *itb;

        /* Generate chunks. */
        for (int i = 1 - size; i <= size; i++) {
                itb = chunk_generate(rules, ita, CHUNK_LEFT);
                ita->right = itb;
                itb->left = ita;
                itb->position = i;
                ita = itb;
        }

        /* Save them to disk. */
        ita = ch;
        while (ita) {
                itb = ita;

                if (ita->right)
                        ita = ita->right;
                else
                        ita = NULL;

                chunk_close(itb);
        }

        ita = chunk_load(0 - CHUNK_RENDER_DISTANCE);
        for (int i = ita->position + 1; i <= CHUNK_RENDER_DISTANCE; i++) {
                itb = chunk_load(i);

                ita->right = itb;

                itb->left = ita;
                ita = itb;

                if (i == 0)
                        ch = itb;
        }

        return ch;
}

/**
 *  Save a world to disk and unload it from memory.
 *
 *  @ch: a chunk in the world
 */
void world_close (chunk *ch)
{
        if (!ch)
                return;

        chunk *edge = world_edge(ch, CHUNK_LEFT), *it;
        
        it = edge;
        while (it->right) {
                it = it->right;
                chunk_close(it->left);
        }

        if (it)
                chunk_close(it);
}

/**
 *  Search through the chunk list for the edge on the given side.
 *
 *  @ch: a chunk in the world
 *  @side: left or right
 *
 *  @return: outermost loaded chunk
 */
chunk *world_edge (chunk *ch, u8 side)
{
        chunk *it = ch;
        
        if (!ch)
                it = NULL;
        else if (side == CHUNK_LEFT)
                while (it->left)
                        it = it->left;
        else if (side == CHUNK_RIGHT)
                while (it->right) {
                        it = it->right;
                        fprintf(stderr, "IT: %d\n", it->position);
                }
        else
                it = NULL;

        return it;
}

/**
 *  Move the loaded window over to a new occupied chunk. Drop the one left
 *  behind and generate or load a new one.
 *
 *  @ch: current center chunk
 *  @side: left or right
 *
 *  @return: the new center chunk
 */
chunk *world_shift (chunk *ch, u8 side)
{
        chunk *drop, *new, *edge, *shift;

        clock_t start = clock();

        if (!ch)
                shift = NULL;
        else if (side == CHUNK_RIGHT) {
                drop = world_edge(ch, CHUNK_LEFT);
                drop->right->left = NULL;
                chunk_close(drop);

                edge = world_edge(ch, CHUNK_RIGHT);
                new = chunk_load(edge->position + 1);
                if (!new)
                        new = chunk_generate(ch->rules, edge, CHUNK_LEFT);
                new->position = edge->position + 1;
                new->left = edge;
                edge->right = new;
                shift = ch->right;
        } else if (side == CHUNK_LEFT) {
                drop = world_edge(ch, CHUNK_RIGHT);
                drop->left->right = NULL;
                chunk_close(drop);

                edge = world_edge(ch, CHUNK_LEFT);
                new = chunk_load(edge->position - 1);
                if (!new)
                        new = chunk_generate(ch->rules, edge, CHUNK_RIGHT);
                new->position = edge->position - 1;
                new->right = edge;
                edge->left = new;
                shift = ch->left;
        } else {
                shift = NULL;
        }

        clock_t end = clock();
        printf ("Shifted in %.3fs\n", ((double)end - (double)start)* 1.0e-6);

        return shift;
}

/**
 *  Generate a world and provide a navigatable view of it.
 */
void world_view ()
{
        chunk *ch = world_generate(20, CHUNK_FULL);

        int x = 0;
        int y = 100;

        int tiwi = 30;
        int tihi = 15;

        int scale = BLOCK_SIZE / BLOCK_SCALE;
        int running = 1;

        int height = tihi * scale;
        int width = tiwi * scale;

        ALLEGRO_EVENT event;
        ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
        ALLEGRO_DISPLAY *screen = al_create_display(tiwi * scale, tihi * scale);
        ALLEGRO_FONT *font = al_load_ttf_font("assets/font.ttf", 20, 0);
        ALLEGRO_TIMEOUT timeout;
        ALLEGRO_KEYBOARD_STATE state;

        block fg, bg;
        block_init(NULL);

        al_register_event_source(queue,
                                 al_get_display_event_source(screen));
        al_register_event_source(queue,
                                 al_get_keyboard_event_source());

        do {
                al_clear_to_color(al_map_rgb(0, 0, 0));

                al_hold_bitmap_drawing(true);
                for (int i = x; i < x + tiwi; i++)
                        for (int j = y; j < y + tihi; j++) {
                                if ((i < 0) && ch->left) {
                                        int ix = CHUNK_WIDTH - abs(i);
                                        fg = ch->left->fore[ix][j];
                                        bg = ch->left->back[ix][j];
                                } else if ((i >= CHUNK_WIDTH) && ch->right) {
                                        int ix = i % CHUNK_WIDTH;
                                        fg = ch->right->fore[ix][j];
                                        bg = ch->right->back[ix][j];
                                } else {
                                        fg = ch->fore[i][j];
                                        bg = ch->back[i][j];
                                }

                                block_draw(fg, bg, (i - x) * scale,
                                           (j - y) * scale, scale);
                        }
                al_hold_bitmap_drawing(false);

                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0,
                              "Viewing: (%d, %d, %d)", x, y, ch->position);

                al_flip_display();

                al_init_timeout(&timeout, 0.02);
                al_wait_for_event_until(queue, &event, &timeout);

                al_get_keyboard_state(&state);

                if (al_key_down(&state, ALLEGRO_KEY_ESCAPE)) {
                        running = 0;
                } else if (al_key_down(&state, ALLEGRO_KEY_W)) {
                        if (y > 0)
                                y--;
                } else if (al_key_down(&state, ALLEGRO_KEY_S)) {
                        if (y < CHUNK_HEIGHT)
                                y++;
                } else if (al_key_down(&state, ALLEGRO_KEY_A)) {
                        if (x > 0)
                                x--;
                        else {
                                ch = world_shift(ch, CHUNK_LEFT);
                                x += CHUNK_WIDTH;
                        }
                } else if (al_key_down(&state, ALLEGRO_KEY_D)) {
                        if (x < CHUNK_WIDTH - tiwi)
                                x++;
                        else {
                                ch = world_shift(ch, CHUNK_RIGHT);
                                x -= CHUNK_WIDTH;
                        }
                }

                if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {

                        al_acknowledge_resize(screen);
                        width = al_get_display_width(screen);
                        height = al_get_display_height(screen);
                        tiwi = width / scale;
                        tihi = height / scale;

                } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

                        running = 0;

                }

        } while (running);

        al_destroy_display(screen);
        al_destroy_event_queue(queue);
        world_close(ch);
        block_deinit();

}