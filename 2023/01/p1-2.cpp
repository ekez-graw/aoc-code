// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int get_letter_number( char * cursor)
{
    if (strncmp(cursor, "one", 3) == 0)
        return 1;
    if (strncmp(cursor, "two", 3) == 0)
        return 2;
    if (strncmp(cursor, "three", 5) == 0)
        return 3;
    if (strncmp(cursor, "four", 4) == 0)
        return 4;
    if (strncmp(cursor, "five", 4) == 0)
        return 5;
    if (strncmp(cursor, "six", 3) == 0)
        return 6;
    if (strncmp(cursor, "seven", 5) == 0)
        return 7;
    if (strncmp(cursor, "eight", 5) == 0)
        return 8;
    if (strncmp(cursor, "nine", 4) == 0)
        return 9;

    return -1;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[256];
    int level;
    char *cursor;
    int row = 0;
    int index;
    char numbers[2 + 1];
    int calibration_value;
    int total_calibration_value = 0;
    int number;
    bool all_found;

    strcpy(file_name, "p1-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        numbers[2] = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            all_found = false;
            row++;
            index = 0;
            cursor = line;
            while (*cursor != 0x0a) {
                number = get_letter_number(cursor);
                number += 0x30;
                if (number <= 0x30 || number > 0x39) {
                    number = *cursor;
                    if (number <= 0x30 || number > 0x39)
                        number = -1;
                }

                if (number != -1) {
                    numbers[index] = number;
                    index++;
                    if (index > 1) {
                        index = 1;
                        all_found = true;
                    }
                }

                cursor++;
            }

            if (!all_found)
                numbers[1] = numbers[0];

            calibration_value = atoi(numbers);
            total_calibration_value += calibration_value;
            printf("Calibration value: %d\n", calibration_value);
            printf("Total calibration value: %d\n", total_calibration_value);
        }

        fclose(file);
        return -1;
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
