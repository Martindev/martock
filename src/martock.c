#include <martock.h>
#include <time.h>
 
#define C 10000

int main (int argc, char **argv)
{
        init();
        block_init(NULL);

        chunk *ch = world_gen(5, CHUNK_FULL);
        fprintf(stderr, "GENNED\n");
        chunk_view(ch);
        free(ch);

        blocks_deinit();

        return 0;
}
