#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

const int MAX_ELVES = 10;

int main( int argc, char *argv[])
{
    int unbused = 0;
    bool verbose = false;
    FILE *file;
    char file_name[32];
    char line[32];
    int opt;
    int i;
    int y;
    int calories;
    int current_elf_calories;
    int top_elf_calories[MAX_ELVES];
    int top_elf_number[MAX_ELVES];
    int top_elf_row[MAX_ELVES];
    int total_calories = 0;
    int current_elf = 1;
    int row = 1;
    int top = 1;

    memset(top_elf_calories, 0, sizeof(top_elf_calories));
    memset(top_elf_number, 0, sizeof(top_elf_number));
    memset(top_elf_row, 0, sizeof(top_elf_row));
    strcpy(file_name, "p1-input.txt");

    while ((opt = getopt(argc, argv, "t:vf:")) != -1) {
        switch (opt) {
            case 'f':
                strncpy(file_name, optarg, sizeof(file_name));
            break;
            case 'v':
                verbose = true;
            break;
            case 't':
                top = atoi(optarg);
                if (top > MAX_ELVES)
                    top = MAX_ELVES;
            break;
        }
    }

    printf("Finding maximum calory Elf/Elves (top %d) in %s\n", top, file_name);

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            calories = atoi(line);
            current_elf_calories += calories;
            if (strncmp(line, "\n", 2) == 0) {
                if (verbose)
                    printf("Elf %d has %d calories", current_elf, current_elf_calories);

                for (i = 0; i < top; i++) {
                    if (current_elf_calories > top_elf_calories[i]) {
                        for (y = top - 1; y >= i; y--) {
                            top_elf_calories[y + 1] = top_elf_calories[y];
                        }
                        top_elf_calories[i] = current_elf_calories;
                        top_elf_number[i] = current_elf;
                        top_elf_row[i] = row;
                        if (verbose)
                            printf(" (updated %d) Row: %d", i + 1, row);
                        break;
                    }
                }
                if (verbose)
                    printf("\n");
                current_elf_calories = 0;
                current_elf += 1;
            }
            row += 1;
        }
        printf("------------------ Summary ------------------\n");
        printf("Elf %d has maximum calories: %d\n", top_elf_number[0], top_elf_calories[0]);
        total_calories = top_elf_calories[0];

        if (top > 1) {
            for (i = 1; i < top; i++) {
                printf("Place %d has calories: %d\n", i + 1, top_elf_calories[i]);
                total_calories += top_elf_calories[i];
            }

            printf("Total calories: %d\n", total_calories);
        }

        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
