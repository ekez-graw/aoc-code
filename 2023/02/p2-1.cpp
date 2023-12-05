// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void add_to_color(int number, char *color, int *red, int *green, int *blue)
{
    if (strncmp(color, "red", 3) == 0)
        *red += number;
    if (strncmp(color, "green", 5) == 0)
        *green += number;
    if (strncmp(color, "blue", 4) == 0)
        *blue += number;

    return;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[256];
    char *cursor;
    char *next_delimiter;
    int row = 0;
    int number;
    int red, green, blue;
    int game;
    char color[16];
    int max_red = 12;
    int max_green = 13;
    int max_blue = 14;
    bool impossible;
    int total_id = 0;

    strcpy(file_name, "p2-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "Game %d:", &game) != 1)
                printf("ERROR\n");
            printf("Game: %d\n", game);
            cursor = line;
            red = green = blue = 0;
            while (*cursor != 0x0a && *cursor != ':')
                cursor++;
            impossible = false;
            while (true) {
                cursor++;
                next_delimiter = cursor;
                while (*next_delimiter != 0x0a && *next_delimiter != ',' && *next_delimiter != ';')
                    next_delimiter++;
                if (*next_delimiter == 0x0a) {
                    sscanf(cursor, " %d %s", &number, color);
                    add_to_color(number, color, &red, &green, &blue);
                }
                if (*next_delimiter == ',') {
                    sscanf(cursor, " %d %s,", &number, color);
                    add_to_color(number, color, &red, &green, &blue);
                }
                if (*next_delimiter == ';') {
                    sscanf(cursor, " %d %s;", &number, color);
                    add_to_color(number, color, &red, &green, &blue);
                }
                if (red > max_red || green > max_green || blue > max_blue) {
                    impossible = true;
                }
                cursor = next_delimiter;
                if (*next_delimiter == 0x0a)
                    break;
                if (*next_delimiter == ';')
                    red = green = blue = 0;
            }

            if (!impossible) {
                total_id += game;
            }
        }

        printf("total_id: %d\n", total_id);

        fclose(file);
        return -1;
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
