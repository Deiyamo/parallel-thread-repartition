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

    // omp_get_num_thread()
    // omp_set_num_threads()
    // #pragma omp parallel for
    omp_set_num_threads(atoi(argv[2]));
    // printf(omp_get_num_threads());

    for (int m = 0; m < WIDTH; ++m) {
#pragma omp parallel for // schedule()
        for (int n = 0; n < HEIGHT; ++n) {
            // printf("%d ", omp_get_thread_num());

            // 0-Red, 1-Green, 2-Blue, 3- Yellow, 4-Magenta, 5-Cyan, 6-White, 7-Black
            switch (omp_get_thread_num()) {
                case 0:
                    pixel.Red = 255;
                    pixel.Green = 0;
                    pixel.Blue = 0;
                    break;
                case 1:
                    pixel.Red = 0;
                    pixel.Green = 255;
                    pixel.Blue = 0;
                    break;
                case 2:
                    pixel.Blue = 255;
                    pixel.Green = 0;
                    pixel.Red = 0;
                    break;
                case 3:
                    pixel.Red = 255;
                    pixel.Green = 255;
                    pixel.Blue = 0;
                    break;
                case 4:
                    pixel.Red = 255;
                    pixel.Green = 0;
                    pixel.Blue = 255;
                    break;
                case 5:
                    pixel.Red = 0;
                    pixel.Green = 255;
                    pixel.Blue = 255;
                    break;
                case 6:
                    pixel.Red = 255;
                    pixel.Green = 255;
                    pixel.Blue = 255;
                    break;
                case 7:
                    pixel.Red = 0;
                    pixel.Green = 0;
                    pixel.Blue = 0;
                    break;
                default:
                    pixel.Red = 192;
                    pixel.Green = 255;
                    pixel.Blue = 192;
                    break;

            }
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
