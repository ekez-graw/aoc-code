// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char schema[200][200];

bool is_symbol( int x, int y)
{
    bool ret = true;

    if (schema[y][x] >= 0x30 && schema[y][x] <= 0x39)
        ret = false;
    if (schema[y][x] == 0)
        ret = false;
    return ret;
}

bool check_adjacent_symbols( int x, int y)
{
    if (is_symbol( x-1, y-1))
        return true;
    if (is_symbol( x, y-1))
        return true;
    if (is_symbol( x+1, y-1))
        return true;
    if (is_symbol( x-1, y))
        return true;
    if (is_symbol( x+1, y))
        return true;
    if (is_symbol( x-1, y+1))
        return true;
    if (is_symbol( x, y+1))
        return true;
    if (is_symbol( x+1, y+1))
        return true;

    return false;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[256];
    int rowlength;
    int rows = 0;
    int i;
    int x;
    int y;
    int z;
    int c_x;
    int c_y;
    char number[10];
    bool found_adjacent_symbol;
    int sum = 0;

    strcpy(file_name, "p3-input.txt");

    memset(schema, 0, sizeof(schema));

    if ((file = fopen(file_name, "r")) != NULL) {
        if (fgets(line, sizeof(line), file) != NULL) {
            rowlength = strnlen(line, sizeof(line)) - 1;
        }

        fclose(file);
    }

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            for (i = 1; i <= rowlength; i++) {
                schema[rows + 1][i] = line[i - 1];
                if (schema[rows + 1][i] == 0x2e)
                    schema[rows + 1][i] = 0;
            }
            rows++;
        }

        fclose(file);

        for (y = 1; y <= rowlength; y++) {
            for (x = 1; x <= rows; x++) {
                memset(number, 0, sizeof(number));
                i = 0;
                while (schema[y][x+i] >= 0x30 && schema[y][x+i] <= 0x39) {
                    number[i] = schema[y][x+i];
                    i++;
                }
                if (atoi(number) != 0) {
                    found_adjacent_symbol = false;
                    for (c_x = x; c_x < x + i; c_x++) {
                        if (check_adjacent_symbols( c_x, y))
                            found_adjacent_symbol = true;
                    }
                    if (found_adjacent_symbol)
                        sum += atoi(number);
                }
                x += i;
            }
        }

        printf("sum: %d\n", sum);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
