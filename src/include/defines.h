#ifndef DEFINES_H
#define DEFINES_H

#include <martock.h>
#include <inttypes.h>

/* Global Constants. */
#define C 10000
#define SAVE_LEN 100

#define GRAVITY 0.15
#define TERMINAL 1

#define HERO_SPEED 0.05
#define HERO_WIDTH 1
#define HERO_HEIGHT 1.6

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef enum {
        DIR_LEFT  = 0x01,
        DIR_RIGHT = 0x02,
        DIR_UP    = 0x04,
        DIR_DOWN  = 0x08
} dir_t;

typedef enum {
        RACE_HERO = 0
} race_t;

typedef struct entity {
        int c, oc;
        double w, h;
        double x, y;
        double ox, oy;
        double velv;
        double velh;
        race_t race;
        dir_t dir;
} entity;

/* Block id's. */
enum {
        BLOCK_SKY     = 0,
        BLOCK_GRASS   = 1,
        BLOCK_SOIL    = 2,
        BLOCK_STONE   = 3,
        BLOCK_IRON    = 4,
        BLOCK_MITHRIL = 5,
        BLOCK_DIAMOND = 6,
        BLOCK_TRUNK   = 7,
        BLOCK_LEAVES  = 8
};

/* Frequency. */
enum {
        BLOCK_IRON_ODD    = 30,
        BLOCK_MITHRIL_ODD = 20,
        BLOCK_DIAMOND_ODD = 10
};

/* Block metadata. */
enum {
        BLOCK_COUNT = 9, /* Quantity of blocks. */
        BLOCK_SIZE = 60, /* Sprite resolution. */
        BLOCK_SCALE = 1, /* Render scale. */
};

/* Visibilities. */
enum {
        BLOCK_TRANSPARENT = 0,
        BLOCK_OPAQUE = 255
};

typedef struct block {
        u16 id;
} block;

typedef struct block_profile {
        u8 opacity; /* Render opacity. */
        u8 density; /* Difficulty to break. */
        u8 gravity; /* Does it fall? */
        u8 weight; /* Fall speed/pack weight. */
} block_profile;

/* Chunk dimensions. */
enum {
        CHUNK_WIDTH  = 500,
        CHUNK_HEIGHT = 500
};

/* Chunk level beginnings. */
enum {
        CHUNK_SOIL    = CHUNK_HEIGHT / 4,
        CHUNK_MANTLE  = CHUNK_HEIGHT / 3,
        CHUNK_CORE    = (CHUNK_HEIGHT / 4) * 3
};

/* Generator flags. */
enum {
        CHUNK_FLAT      = 0x01,
        CHUNK_NO_CAVES  = 0x02,
        CHUNK_NO_HILLS  = 0x04,
        CHUNK_NO_PLANTS = 0x08,
        CHUNK_FULL      = 0x10
};

/* Relative positions. */
enum {
        CHUNK_RIGHT           = 0,
        CHUNK_LEFT            = 1,
        CHUNK_RENDER_DISTANCE = 5
};

/* Cellular automata modes. */
enum {
        CHUNK_BORDER         = 3,
        CHUNK_TREE           = 20,
        CHUNK_HILL           = CHUNK_HEIGHT / 5,
        CHUNK_SMOOTH_RADIUS  = CHUNK_WIDTH / 8,
        CHUNK_CAVE_SEED      = 40,
        CHUNK_CAVE_RULE      = 4
};

typedef struct chunk {
        u8 rules;
        int position;
        struct chunk *right;
        struct chunk *left;
        u8 heights[CHUNK_WIDTH];
        block fore[CHUNK_WIDTH][CHUNK_HEIGHT];
        block back[CHUNK_WIDTH][CHUNK_HEIGHT];
} chunk;

/* Global state variables. */
extern char save[SAVE_LEN];
extern int tilepix;
extern int width, height;
extern chunk *world;

extern ALLEGRO_BITMAP *buffer;
extern ALLEGRO_EVENT event;
extern ALLEGRO_EVENT_QUEUE *queue;
extern ALLEGRO_DISPLAY *screen;
extern ALLEGRO_FONT *font;
extern ALLEGRO_TIMEOUT timeout;
extern ALLEGRO_KEYBOARD_STATE state;

#endif /* DEFINES_H */
