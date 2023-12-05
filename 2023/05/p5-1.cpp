// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stack>

class Vector {
public:
    unsigned int dest;
    unsigned int src;
    unsigned int range;
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
    int sum = 0;
    int i;
    int map = 0;
    int x;
    int value;
    int nr_of_seeds = 0;
    int seed[32];
    int characters;
    int nr_of_maps = 0;
    int dest, src, range;
    bool end;
    int y;
    VectorMap maps[16];

    strcpy(file_name, "p5-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        if (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "seeds: %n", &characters);
            cursor = line + characters;
            while (sscanf(cursor, "%d %n", &value, &characters) == 1) {
                seed[nr_of_seeds++] = value;
                cursor = cursor + characters;
            }
        }

        fgets(line, sizeof(line), file);
        end = false;
        while (fgets(line, sizeof(line), file) != NULL) {
            x = 0;
            while (fgets(line, sizeof(line), file) != NULL) {
                if (line[0] == 0xa)
                    break;
                sscanf(line, "%d %d %d", &maps[map].list[x].dest, &maps[map].list[x].src, &maps[map].list[x].range);
                x = x + 1;
            }
            map++;
        }

        unsigned long int lowest_location = 99999999999;
        unsigned int new_category;

        for (i = 0; i < nr_of_seeds; i++) {
            new_category = seed[i];
            printf("Category: %d\n", new_category);
            for (x = 0; x < map; x++) {
                y = 0;    
                while (maps[x].list[y].range != 0) {
                    printf("  [%u] [%u] [%u] [%u]\n", new_category, maps[x].list[y].src, maps[x].list[y].dest, maps[x].list[y].range);
                    if ((new_category >= maps[x].list[y].src) &&
                        (new_category < (maps[x].list[y].src + maps[x].list[y].range))) {
                        new_category = new_category + (maps[x].list[y].dest - maps[x].list[y].src);
                        break;
                    }
                    y++;
                }

                printf("  new_category: %u\n", new_category);
            }

            if (new_category < lowest_location) {
                lowest_location = new_category;
                printf("    lowest_location: %ld\n", lowest_location);
            }
        }

        fclose(file);

        printf("lowest_location: %ld\n", lowest_location);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
