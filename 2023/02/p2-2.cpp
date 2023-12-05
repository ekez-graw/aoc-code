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
    int max_red;
    int max_green;
    int max_blue;
    int power_sum = 0;
    int power;

    strcpy(file_name, "p2-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "Game %d:", &game) != 1)
                printf("ERROR\n");
            cursor = line;
            red = green = blue = 0;
            max_red = max_green = max_blue = 0;
            while (*cursor != 0x0a && *cursor != ':')
                cursor++;
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
                cursor = next_delimiter;
                if (red > max_red)
                    max_red = red;
                if (green > max_green)
                    max_green = green;
                if (blue > max_blue)
                    max_blue = blue;
                red = green = blue = 0;
                if (*next_delimiter == 0x0a)
                    break;
            }

            power = max_red * max_green * max_blue;
            power_sum += power;
            red = green = blue = 0;
            printf("Game: %d: power: %d\n", game, power);
        }

        printf("power_sum: %d\n", power_sum);

        fclose(file);
        return -1;
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
