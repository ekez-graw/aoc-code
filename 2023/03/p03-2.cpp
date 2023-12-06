// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stack>

class Gear {
public:
    Gear() { amount = 0; };

    std::stack<int> numberstack;
    char amount;
};

char schema[200][200];
Gear *gear[200][200];

bool is_symbol( int x, int y, int number)
{
    if (schema[y][x] >= 0x30 && schema[y][x] <= 0x39)
        return false;
    if (schema[y][x] == 0)
        return false;

    if (gear[y][x]) {
        gear[y][x]->amount += 1;
        gear[y][x]->numberstack.push(number);
    }

    return true;
}

bool check_adjacent_symbols( int x, int i, int y, int number)
{
    int x_i;
    int adjacent = false;

    if (is_symbol( x-1, y-1, number))
        adjacent = true;
    if (is_symbol( x-1, y, number))
        adjacent = true;
    if (is_symbol( x-1, y+1, number))
        adjacent = true;

    for (x_i = x; x_i < x + i; x_i++) {
        if (is_symbol( x_i, y-1, number))
            adjacent = true;
        if (is_symbol( x_i, y+1, number))
            adjacent = true;
    }

    if (is_symbol( x_i, y-1, number))
        adjacent = true;
    if (is_symbol( x_i, y, number))
        adjacent = true;
    if (is_symbol( x_i, y+1, number))
        adjacent = true;

    return adjacent;
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
    int int_number;
    int sum = 0;
    long int sum_gear_ratio = 0;
    long int val1, val2;
    long int gear_ratio;

    memset(gear, 0, sizeof(gear));

    for (x = 0; x < 200; x++) {
        for (y = 0; y < 200; y++) {
            gear[y][x] = new Gear();
        }
    }

    strcpy(file_name, "p3-input.txt");

    memset(schema, 0, sizeof(schema));

    if ((file = fopen(file_name, "r")) != NULL) {
        if (fgets(line, sizeof(line), file) != NULL)
            rowlength = strnlen(line, sizeof(line)) - 1;
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
                int_number = atoi(number);
                if (int_number != 0) {
                    found_adjacent_symbol = false;
                    if (check_adjacent_symbols( x, i, y, int_number))
                        found_adjacent_symbol = true;
                    if (found_adjacent_symbol) {
                        sum += int_number;
                        //printf("%6d : OK\n", int_number);
                    }
                }
                x += i;
            }
        }

        for (y = 0; y <= rowlength; y++) {
            for (x = 0; x <= rows; x++) {
                if (gear[y][x]->amount == 2) {
                    val1 = gear[y][x]->numberstack.top();
                    gear[y][x]->numberstack.pop();
                    val2 = gear[y][x]->numberstack.top();
                    gear[y][x]->numberstack.pop();
                    gear_ratio = val1 * val2;
                    sum_gear_ratio += gear_ratio;
                }
            }
        }

        for (x = 0; x < 200; x++) {
            for (y = 0; y < 200; y++) {
                delete gear[y][x];
            }
        }

        printf("sum            : %12d\n", sum);
        printf("sum_gear_ratio : %12ld\n", sum_gear_ratio);        
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
