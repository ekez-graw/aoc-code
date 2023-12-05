#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>

bool verbose = false;
static int MAX_NUMBER_OF_ITEMS = 64;

bool mode_1( int &min_1, int &max_1, int &min_2, int&max_2)
{
    if ((min_1 >= min_2 && max_1 <= max_2) ||
        (min_2 >= min_1 && max_2 <= max_1))
        return true;

    return false;
}

bool mode_2( int &min_1, int &max_1, int &min_2, int&max_2)
{
    if ((min_1 < min_2 && max_1 < min_2) ||
        (max_1 > max_2 && min_1 > max_2))
        return false;

    return true;
}

int main( int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[MAX_NUMBER_OF_ITEMS * 2];
    int opt;
    int mode = 1;
    int new_mode;
    bool result;
    int section_assignment = 1;
    int overlaps = 0;
    int min_1, max_1, min_2, max_2 = 0;

    memset(line, 0, sizeof(line));

    strcpy(file_name, "puzzle-03-input.txt");

    while ((opt = getopt(argc, argv, "m:vf:")) != -1) {
        switch (opt) {
            case 'f':
                strncpy(file_name, optarg, sizeof(file_name));
            break;
            case 'm':
                new_mode = atoi(optarg);
                if (new_mode < 1 || new_mode > 2) {
                    printf("ERROR. Wrong mode: %d\n", mode);
                }
                else {
                    mode = new_mode;
                }
            break;
            case 'v':
                verbose = true;
            break;
        }
    }

    printf("Finding overlapping section assignements %s mode %d\n", file_name, mode);

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%d-%d,%d-%d", &min_1, &max_1, &min_2, &max_2);
            switch (mode) {
                case 1:
                    result = mode_1(min_1, max_1, min_2, max_2); break;
                case 2:
                    result = mode_2(min_1, max_1, min_2, max_2); break;
            }

            if (result) {
                overlaps += 1;
                if (verbose)
                    printf("Found overlap in section assignment pair %d\n", section_assignment);
            }

            min_1 = max_1 = min_2 = max_2 = 0;
            memset(line, 0, sizeof(line));
            section_assignment += 1;
        }

        if (verbose)
            printf("\n");

        printf("------------------ Summary ------------------\n");
        printf("Total overlapping section assignments: %d mode %d\n", overlaps, mode);

        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
