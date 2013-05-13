#include <martock.h>
#include <time.h>
 
#define C 10000

int main (int argc, char **argv)
{
        init();
        block_init(NULL);

        chunk *ch = chunk_generate(CHUNK_FULL, NULL, 0);
        chunk_view(ch);
        free(ch);

        blocks_deinit();

        return 0;
}
