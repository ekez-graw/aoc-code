// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Vector {
public:
    unsigned long int dest;
    unsigned long int src;
    unsigned long int range;
};

class VectorMap {
public:
    Vector list[64];
};

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[256];
    char map_str[128];
    char *cursor;
    int characters;
    unsigned long int i;
    unsigned long int x;
    unsigned long int y;
    unsigned long int map = 0;
    unsigned long int value;
    unsigned long int nr_of_seeds = 0;
    unsigned long int seed[32];
    unsigned long int dest, src, range;
    unsigned long int nr_of_maps = 0;
    unsigned long int lowest_location = 99999999999;
    unsigned long int new_category;
    unsigned long int s;
    VectorMap maps[16];

    strcpy(file_name, "p5-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        if (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "seeds: %n", &characters);
            cursor = line + characters;
            while (sscanf(cursor, "%lu %n", &value, &characters) == 1) {
                seed[nr_of_seeds++] = value;
                cursor = cursor + characters;
            }
        }

        fgets(line, sizeof(line), file);
        while (fgets(line, sizeof(line), file) != NULL) {
            x = 0;
            while (fgets(line, sizeof(line), file) != NULL) {
                if (line[0] == 0xa)
                    break;
                sscanf(line, "%lu %lu %lu", &maps[map].list[x].dest, &maps[map].list[x].src, &maps[map].list[x].range);
                x = x + 1;
            }
            map++;
        }

        for (i = 0; i < nr_of_seeds; i = i + 2) {
            printf("Categories: [%lu] --> [%lu]\n", seed[i], seed[i] + seed[i+1]);
            for (s = seed[i]; s < seed[i] + seed[i+1]; s++) {
                new_category = s;
                for (x = 0; x < map; x++) {
                    y = 0;    
                    while (maps[x].list[y].range != 0) {
                        if ((new_category >= maps[x].list[y].src) &&
                            (new_category < (maps[x].list[y].src + maps[x].list[y].range))) {
                            new_category = new_category + (maps[x].list[y].dest - maps[x].list[y].src);
                            break;
                        }
                        y++;
                    }
                }

                if (new_category < lowest_location) {
                    lowest_location = new_category;
                    printf("    lowest_location: %lu\n", lowest_location);
                }
            }
        }

        fclose(file);

        printf("lowest_location: %lu\n", lowest_location);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
