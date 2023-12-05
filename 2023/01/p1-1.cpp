// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
                if (*cursor >= 0x30 && *cursor <= 0x39) {
                    printf("digit %c\n", *cursor);
                    numbers[index] = *cursor;
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
