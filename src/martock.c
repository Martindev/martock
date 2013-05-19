#include <martock.h>
#include <time.h>
 
#define C 10000

int main (int argc, char **argv)
{
        init();

        fprintf(stderr, "Looper.\n");
        world_view();
        fprintf(stderr, "Looper.\n");

        return 0;
}
