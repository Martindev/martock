#include <martock.h>

/**
 *  Supply the world or viewer with a new chunk to append to the given neighbor.
 *  Set the new chunk's position relative to the provided neighbor.
 *
 *  @neighbor: chunk this new one must be contiguous with
 *  @side: which side to append onto the neighbor
 *  @rules: generation rules
 *
 *  @return: created or loaded chunk
 */

chunk *chunk_request (chunk *neighbor, u8 side, u8 rules)
{
        int pos;
        chunk *ch;

        if (!neighbor)
                return NULL;

        if (side == CHUNK_LEFT) {
                pos = neighbor->position - 1;
        } else if (side == CHUNK_RIGHT) {
                pos = neighbor->position + 1;
        } else
                return NULL;

        ch = chunk_load(pos);

        if (!ch)
                /* chunk_generate uses "side" to describe the neighbor's position
                relative to the chunk it generates, where request is relative
                to the neighbor, so they must be switched.                     */
                ch = chunk_generate(rules, neighbor, (side == CHUNK_LEFT) ?
                                                  CHUNK_RIGHT : CHUNK_LEFT);
        
        /* Put the chunk in the world. */
        ch->position = pos;
        if (side == CHUNK_LEFT) {
                ch->right = neighbor;
                ch->right->left = ch;
        } else if (side == CHUNK_RIGHT) {
                ch->left = neighbor;
                ch->left->right = ch;
        }

        return ch;
}

/**
 *  Load a chunk from file if it exists.
 *
 *  @pos: the position of the chunk in the world
 *
 *  @return: the loaded chunk; NULL on failure
 */
chunk *chunk_load (u16 pos)
{
        chunk *ch = NULL;
        FILE *file = NULL;

        /* Return if the memory allocation fails. */
        if (!(ch = calloc(1, sizeof(chunk))))
                return NULL;

        /* Return if the file can't be found. */
        if (!(file = vfopen("rb", "world/chunks/%d.ch", pos)))
                return NULL;

        fread(ch, sizeof(chunk), 1, file);
        return ch;
}

/**
 *  Construct a new chunk according the provided rules using cellular automata.
 *  Give the chunk a position value relative to the neighbor, and assign the
 *  the neighbor pointer in the right place.
 *
 *  @rules: cellular automata rules
 *  @neighbor: the chunk this is appending to
 *  @side: which side it's appending to the neighbor
 *
 *  @return: the newly generated chunk; NULL on failure
 */
chunk *chunk_generate (u8 rules, const chunk *neighbor, u8 side)
{
        chunk *ch = NULL;

        /* Return if the memory allocation fails. */
        if (!(ch = calloc(1, sizeof(chunk))))
                return NULL;

        /* Set the defaults for each vertical level. */
        for (int i = 0; i < CHUNK_WIDTH; i++)
                for (int j = 0; j < CHUNK_SOIL; j++)
                        ch->fore[i][j].id = BLOCK_SKY;

        for (int i = 0; i < CHUNK_WIDTH; i++)
                for (int j = CHUNK_SOIL; j < CHUNK_MANTLE; j++)
                        ch->fore[i][j].id = BLOCK_SOIL;

        for (int i = 0; i < CHUNK_WIDTH; i++)
                for (int j = CHUNK_MANTLE; j < CHUNK_HEIGHT; j++)
                        ch->fore[i][j].id = BLOCK_STONE;

        /* If a flat chunk was requested, it's done. */
        if (rules & CHUNK_FLAT)
                return ch;

        /* Varying terrain (hills, valleys, mountains, etc.) */
        memset(ch->heights, CHUNK_HILL / 2, CHUNK_WIDTH);
        for (int i = 0; i < CHUNK_WIDTH; i++)
                ch->heights[i] = rand() % CHUNK_HILL;
        for (int i = 0; i < CHUNK_WIDTH; i++) {
                int average = ch->heights[i];
                int count = 0;
                for (int j = 1; j < CHUNK_SMOOTH_RADIUS; j++) {
                        if (i - j >= 0) {
                                average += ch->heights[i - j];
                                count++;
                        } else if (neighbor && (side == CHUNK_LEFT)) {
                                average += neighbor->heights[CHUNK_WIDTH -
                                                             abs(i - j)];
                                count++;
                        }

                        if (i + j < CHUNK_WIDTH) {
                                average += ch->heights[i + j];
                                count++;
                        } else if (neighbor && (side == CHUNK_RIGHT)) {
                                average += neighbor->heights[(i + j) %
                                                             CHUNK_WIDTH];
                                count++;
                        }
                }

                average /= count;
                ch->heights[i] = average;

                ch->fore[i][CHUNK_SOIL - ch->heights[i]].id = BLOCK_GRASS;
                for (int j = CHUNK_SOIL - ch->heights[i] + 1; j < CHUNK_SOIL; j++)
                        ch->fore[i][j].id = BLOCK_SOIL;
        }

        /* Gradient stone. */
        double total = CHUNK_MANTLE - CHUNK_SOIL;
        for (int i = 0; i < CHUNK_WIDTH; i++)
                for (int j = CHUNK_SOIL + 1; j < CHUNK_MANTLE; j++) {
                        int prop = ((j - CHUNK_SOIL) / total) * 100;
                        if ((rand() % 100) < prop)
                                ch->fore[i][j].id = BLOCK_STONE;
                }

        /* Solid background layer. */
        memcpy(ch->back, ch->fore, sizeof(block) * CHUNK_WIDTH * CHUNK_HEIGHT);

        /* Initial seeding. */
        double ytotal = CHUNK_CORE - CHUNK_MANTLE;
        double xtotal = CHUNK_WIDTH - CHUNK_BORDER;
        for (int i = CHUNK_BORDER; i < CHUNK_WIDTH - CHUNK_BORDER; i++)
                for (int j = CHUNK_MANTLE; j < CHUNK_CORE; j++) {
                        int yprop = ((j - CHUNK_MANTLE) / ytotal) * 100;
                        int xprop = ((i - CHUNK_BORDER) / xtotal) * 100;
                        yprop = (yprop > 50) ? 100 - yprop : yprop;
                        xprop = (xprop > 50) ? 100 - xprop : xprop;
                        if ((rand() % 100) < ((xprop + yprop) / 2))
                                ch->fore[i][j].id = BLOCK_SKY;
                }

        /* Cave automata. */
        chunk cmp;
        memcpy(&cmp, ch, sizeof(chunk));
        for (int i = CHUNK_BORDER; i < CHUNK_WIDTH - CHUNK_BORDER; i++)
                for (int j = CHUNK_MANTLE; j < CHUNK_CORE; j++) {
                        int t = 0;

                        t = (cmp.fore[i - 1][j - 1].id) ? (t + 1) : t;
                        t = (cmp.fore[i - 1][j    ].id) ? (t + 1) : t;
                        t = (cmp.fore[i - 1][j + 1].id) ? (t + 1) : t;

                        t = (cmp.fore[i    ][j - 1].id) ? (t + 1) : t;
                        t = (cmp.fore[i    ][j + 1].id) ? (t + 1) : t;

                        t = (cmp.fore[i + 1][j - 1].id) ? (t + 1) : t;
                        t = (cmp.fore[i + 1][j    ].id) ? (t + 1) : t;
                        t = (cmp.fore[i + 1][j + 1].id) ? (t + 1) : t;

                        if (ch->fore[i][j].id) {
                                if ((t < 3) || (t > 8))
                                        ch->fore[i][j].id = BLOCK_SKY;
                        } else
                                if ((t > 5) && (t < 9))
                                        ch->fore[i][j].id = BLOCK_STONE;
                }

        return ch;
}

/**
 *  Fetch a chunk's neighbor by sifting through links.
 *
 *  @ch: chunk to start from
 *  @d: displacement from start
 *
 *  @return: chunk d spaces from starter chunk
 */
chunk *chunk_left (chunk *ch, int d)
{
        if (!ch)
                return NULL;

        int i = 0;
        chunk *it = ch;

        while (it->left && (i < d)) {
                it = it->left;
                i++;
        }

        return it;
}

chunk *chunk_right (chunk *ch, int d)
{
        if (!ch)
                return NULL;

        int i = 0;
        chunk *it = ch;

        while (it->right && (i < d)) {
                it = it->right;
                i++;
        }

        return it;
}

/**
 *  Allow real-time browsing of the chunk, illustrated graphically.
 *
 *  @ch: chunk to view
 */
void chunk_view (chunk *ch)
{
        int x = 0;
        int y = 80;

        int height = 640;
        int width = 800;

        int scale = BLOCK_SIZE / BLOCK_SCALE;
        int running = 1;

        int tiwi = width / scale;
        int tihi = height / scale;

        chunk *left, *right;

        int world_width = CHUNK_WIDTH * CHUNK_RENDER_DISTANCE;

        ALLEGRO_EVENT event;
        ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
        ALLEGRO_DISPLAY *screen = al_create_display(800, 640);
        ALLEGRO_FONT *font = al_load_ttf_font("assets/font.ttf", 20, 0);

        block fg, bg;

        al_register_event_source(queue,
                                 al_get_display_event_source(screen));
        al_register_event_source(queue,
                                 al_get_keyboard_event_source());

        do {
                al_clear_to_color(al_map_rgb(0, 0, 0));

                for (int i = x; i < x + tiwi; i++)
                        for (int j = y; j < y + tihi; j++) {
                                int disp = 0;
                                if (i >= 0)
                                        disp = (i % CHUNK_WIDTH) ?
                                                i / CHUNK_WIDTH + 1 :
                                                i / CHUNK_WIDTH;
                                else
                                        disp = (abs(i) % CHUNK_WIDTH) ?
                                                abs(i) / CHUNK_WIDTH + 1 :
                                                abs(i) / CHUNK_WIDTH;

                                if ((i >= 0) && (i < CHUNK_WIDTH)) {
                                        fg = ch->fore[i][j];
                                        bg = ch->back[i][j];
                                } else if ((i < 0) &&
                                          (left = chunk_left(ch, disp))) {
                                        fg = left->fore[CHUNK_WIDTH -abs(i)][j];
                                        bg = left->back[CHUNK_WIDTH -abs(i)][j];
                                } else if ((i >= CHUNK_WIDTH) &&
                                          (right = chunk_right(ch, disp))) {
                                        fg = ch->left->fore[i % CHUNK_WIDTH][j];
                                        bg = ch->left->back[i % CHUNK_WIDTH][j];
                                }

                                block_draw(fg, bg, (i - x) * scale,
                                           (j - y) * scale, scale);
                        }

                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0,
                              "Viewing: (%d, %d)", x, y);

                al_flip_display();

                al_wait_for_event(queue, &event);

                while (!al_event_queue_is_empty(queue)) {
                        al_get_next_event(queue, &event);
                        if (event.type == ALLEGRO_EVENT_KEY_CHAR) {

                                int keycode = event.keyboard.keycode;

                                if (keycode == ALLEGRO_KEY_ESCAPE) {
                                        running = 0;
                                } else if (keycode == ALLEGRO_KEY_W) {
                                        if (y > 0)
                                                y--;
                                } else if (keycode == ALLEGRO_KEY_S) {
                                        if (y < CHUNK_HEIGHT)
                                                y++;
                                } else if (keycode == ALLEGRO_KEY_A) {
                                        if (x > 0 - (world_width))
                                                x--;
                                        else {
                                                ch = world_shift(ch,
                                                                 CHUNK_LEFT);
                                                x += CHUNK_WIDTH;
                                        }
                                } else if (keycode == ALLEGRO_KEY_D) {
                                        if (x < world_width)
                                                x++;
                                        else {
                                                ch = world_shift(ch,
                                                                 CHUNK_RIGHT);
                                                x -= CHUNK_WIDTH;
                                        }
                                }

                        } else if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {

                                al_acknowledge_resize(screen);
                                width = al_get_display_width(screen);
                                height = al_get_display_height(screen);
                                tiwi = width / scale;
                                tihi = height / scale;

                        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

                                running = 0;

                        }
                }

        } while (running);

        al_destroy_display(screen);
        al_destroy_event_queue(queue);
}

/**
 *  Render a chunk to an image file to preview it. This function is inexplicably
 *  slow. Leave it running overnight, or depend on the text render.
 *
 *  @ch: the chunk to preview
 */
void chunk_save_img (chunk *ch)
{
        if (!ch)
                return;

        int scale = BLOCK_SIZE / BLOCK_SCALE;
        int width = scale * CHUNK_WIDTH;
        int height = scale * CHUNK_HEIGHT;

        ALLEGRO_BITMAP *canvas = al_create_bitmap(width, height);

        if (!canvas)
                return;

        al_set_target_bitmap(canvas);

        for (int i = 0; i < CHUNK_WIDTH; i++)
                for (int j = 0; j < CHUNK_HEIGHT; j++) {
                        al_draw_scaled_bitmap(block_sprite(ch->fore[i][j].id),
                                              0, 0, BLOCK_SIZE, BLOCK_SIZE,
                                              i * scale, j * scale,
                                              scale, scale, 0);
                }

        char temp[100] = {0};
        sprintf(temp, "world/chunks/%d.png", ch->position);
        al_save_bitmap(temp, canvas);
        al_destroy_bitmap(canvas);
}

/**
 *  Create a lingual save representing the chunk visually with text.
 *
 *  @ch: pointer to the chunk to save
 */
void chunk_save_text (const chunk *ch)
{
        if (!ch)
                return;

        FILE *file = vfopen("w", "world/chunks/%d.txt", ch->position);

        if (file)
                for (int j = 0; j < CHUNK_HEIGHT; j++) {
                        for (int i = 0; i < CHUNK_WIDTH; i++)
                                switch (ch->fore[i][j].id) {
                                        case BLOCK_SKY:   fprintf(file, "  ");
                                                          break;
                                        case BLOCK_GRASS: fprintf(file, "--");
                                                          break;
                                        case BLOCK_SOIL:  fprintf(file, "..");
                                                          break;
                                        case BLOCK_STONE: fprintf(file, "##");
                                                          break;
                                        default:          fprintf(file, "%2d",
                                                          ch->fore[i][j].id);
                                }
                        fprintf(file, "\n");
                }
}

/**
 *  Save the data from the chunk if a save file structure is present, and then
 *  free the memory used by the chunk.
 *
 *  @ch: pointer to the chunk memory
 */
void chunk_close (chunk *ch)
{
        if (!ch)
                return;

        FILE *file = vfopen("wb", "world/chunks/%d.ch", ch->position);

        if (file)
                fwrite(ch, sizeof(chunk), 1, file);

        /* Tell the neighbors he's moved out. */
        if (ch->right)
                ch->right->left = NULL;

        if (ch->left)
                ch->left->right = NULL;

        free(ch);
}