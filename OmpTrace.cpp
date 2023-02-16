/// OmpTrace.cpp : painting OMP threads
/// tim: g++ -Xpreprocessor -fopenmp -I /opt/homebrew/opt/libomp/include -L /opt/homebrew/opt/libomp/lib -lomp EasyBMP.cpp OmpTrace.cpp -o OmpTrace
/// gcc++ -Xpreprocessor -fopenmp -I /usr/local/opt/libomp/include -L /usr/local/opt/libomp/lib -lomp EasyBMP.cpp OmpTrace.cpp -o OmpTrace

#include "EasyBMP.h"
#include "/opt/homebrew/opt/libomp/include/omp.h"

#define  HEIGHT   1080
#define  WIDTH    1920


int main(int argc, char **argv) {
    RGBApixel pixel;
    BMP img;

#ifdef _OPENMP
    printf("*** Compiled with OpenMP ***\n");
#endif

    if (argc < 3)
        goto finally;

    img.SetSize(WIDTH, HEIGHT);

    for (int m = 0; m < WIDTH; ++m) {
        for (int n = 0; n < HEIGHT; ++n) {
            pixel.Blue = 192;
            pixel.Green = 255;
            pixel.Red = 192;

            img.SetPixel(m, n, pixel);
        }
    }
    img.WriteToFile(argv[1]);

    printf("...done\n");
    return 0;

    finally:
    printf("syntax: %s  bmp_file  thread_number\n", argv[0]);
    printf("    ex: %s  trace.bmp 4\n", argv[0]);
    return -1;
}
