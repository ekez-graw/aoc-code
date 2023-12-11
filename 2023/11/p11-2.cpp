// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int uni[200][200];
int uni_dist[200][200];
int x_max = 0;
int y_max = 0;

const int expansion_factor = 999999;
const int GALAXY = 0x23;

void print_uni()
{
    int y, x;

    for (y = 0; y < y_max; y++) {
        for (x = 0; x < x_max; x++) {
            if (uni[y][x] == GALAXY)
                printf("#");
            else if (uni_dist[y][x] == expansion_factor) {
                printf("E");
            }
            else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int get_distance( int in_y, int in_x, int in_yn, int in_xn)
{
    int y;
    int x;
    int distance = 0;

    if (in_yn > in_y) {
        for (y = in_y + 1; y <= in_yn; y++) {
            // printf("  [%3d][%3d]", y, in_x);
            distance += uni_dist[y][in_x];
        }
        if (in_xn > in_x) {
            for (x = in_xn - 1; x >= in_x; x--) {
                // printf("  [%3d][%3d]", in_yn, x);
                distance += uni_dist[in_yn][x];
            }
        }
        else {  
            for (x = in_x - 1; x >= in_xn; x--) {
                // printf("  [%3d][%3d]", in_yn, x);
                distance += uni_dist[in_yn][x];
            }
        }
    }
    else {
        for (y = in_yn + 1; y <= in_y; y++) {
            // printf("  [%3d][%3d]", y, in_x);
            distance += uni_dist[y][in_x];
        }
        if (in_xn > in_x) {
            for (x = in_xn - 1; x >= in_x; x--) {
                // printf("  [%3d][%3d]", in_yn, x);
                distance += uni_dist[in_y][x];
            }
        }
        else {  
            for (x = in_x - 1; x >= in_xn; x--) {
                // printf("  [%3d][%3d]", in_yn, x);
                distance += uni_dist[in_y][x];
            }
        }
    }

    // printf("\n");

    return distance;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[64];
    char line[256];
    int x;
    int y;
    int xn;
    int yn;
    int x_tmp;
    int y_tmp;
    int nr_found;
    int distance;
    long int total_distance = 0;
    int nr_of_galaxies = 0;
    u_int32_t galaxy_nr = 0;
    u_int32_t galaxy_next_nr;
    size_t len;

    memset(uni, 0, sizeof(uni));
    memset(uni_dist, 0, sizeof(uni_dist));
    strcpy(file_name, "2023/p11-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            len = strlen(line);
            for (x = 0; x < len; x++) {
                uni_dist[y_max][x] = 1;
                if (line[x] == '#')
                    uni[y_max][x] = GALAXY;
            }
            y_max++;
        }
        x_max = x;

        // Expand universe (y)
        for (y = 0; y < y_max; y++) {
            nr_found = 0;
            for (x = 0; x < x_max; x++)
                if (uni[y][x] == GALAXY)
                    nr_found++;
            if (nr_found == 0) {
                for (y_tmp = y_max - 1; y_tmp > y; y_tmp--) {
                    for (x = 0; x < x_max; x++) {
                        uni[y_tmp + 1][x] = uni[y_tmp][x];
                        uni[y_tmp][x] = 0;
                        uni_dist[y_tmp + 1][x] = uni_dist[y_tmp][x];
                        uni_dist[y_tmp][x] = expansion_factor;
                    }
                }
                y++;
                y_max++;
                // printf("Expand y [%d]\n", y);
                // print_uni();
            }
        }

        // Expand universe (x)
        for (x = 0; x < x_max; x++) {
            nr_found = 0;
            for (y = 0; y < y_max; y++)
                if (uni[y][x] == GALAXY)
                    nr_found++;
            if (nr_found == 0) {
                for (x_tmp = x_max - 1; x_tmp > x; x_tmp--) {
                    for (y = 0; y < y_max; y++) {
                        uni[y][x_tmp + 1] = uni[y][x_tmp];
                        uni[y][x_tmp] = 0;
                        uni_dist[y][x_tmp + 1] = uni_dist[y][x_tmp];
                        uni_dist[y][x_tmp] = expansion_factor;
                    }
                }
                x++;
                x_max++;
                // printf("\nExpand x [%d]\n", x);
                // print_uni();
            }
        }

        int y3;
        int x3;

        // Iterate over all galaxies and calculate distance to all consecutive ones.
        for (y = 0; y < y_max; y++) {
            for (x = 0; x < x_max; x++) {
                if (uni[y][x] == GALAXY) {
                    galaxy_nr++;
                    // printf("Galaxy %3d\n", galaxy_nr);
                    galaxy_next_nr = 0;
                    for (yn = 0; yn < y_max; yn++) {
                        for (xn = 0; xn < x_max; xn++) {
                            if (uni[yn][xn] == GALAXY) {
                                galaxy_next_nr++;
                                if (galaxy_next_nr > galaxy_nr) {
                                    distance = get_distance(y, x, yn, xn);
                                    // distance = abs(yn - y);
                                    // distance += abs(xn - x);
                                    total_distance += distance;
                                    // printf("        [%3d][%3d] --> [%3d][%3d] = %12d [Tot: %6ld]\n", y, x, yn, xn, distance, total_distance);
                                }                                
                            }
                        }
                    }
                }
            }
        }

        // Print universe
        // print_uni();
        fclose(file);
    }

    printf("Total Lengths: %lu\n", total_distance);

    return 0;
}
