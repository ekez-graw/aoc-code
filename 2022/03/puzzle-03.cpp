#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>

bool verbose = false;
static int MAX_NUMBER_OF_ITEMS = 64;

int main( int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[MAX_NUMBER_OF_ITEMS * 2];
    int opt;
    int result;
    int rucksack = 1;
    int round = 0;
    int length;
    int comp_length;
    char comp_1[MAX_NUMBER_OF_ITEMS];
    char comp_2[MAX_NUMBER_OF_ITEMS];
    int i;
    int i_1;
    int i_2;
    bool found;
    int priority;
    int total_priority = 0;

    memset(line, 0, sizeof(line));

    strcpy(file_name, "puzzle-03-input.txt");

    while ((opt = getopt(argc, argv, "m:vf:")) != -1) {
        switch (opt) {
            case 'f':
                strncpy(file_name, optarg, sizeof(file_name));
            break;
            case 'v':
                verbose = true;
            break;
        }
    }

    printf("Finding misplaced rucksacks in %s\n", file_name);

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            memset(comp_1, 0, sizeof(comp_1));
            memset(comp_2, 0, sizeof(comp_2));

            length = strnlen(line, sizeof(line)) - 1;
            if ((length % 2) == 0) {
                comp_length = length / 2;
                memcpy(comp_1, line, length / 2);
                memcpy(comp_2, &line[length / 2], length / 2);
            }
            else {
                printf("ERROR in input. Lenght of rucksack %d is %d\n", rucksack, length);
                break;
            }

            found = false;

            for (i_1 = 0; i_1 < comp_length && !found; i_1++) {
                for (i_2 = 0; i_2 < comp_length && !found; i_2++) {
                    if (comp_1[i_1] == comp_2[i_2]) {
                        if (isupper(comp_1[i_1])) {
                            priority = (int)comp_1[i_1] - 64 + 27 - 1;
                        }
                        if (islower(comp_1[i_1]))
                            priority = (int)comp_1[i_1] - 96;
                        if (verbose)
                            printf("%4d %c %d %d\n", rucksack, comp_1[i_1], comp_1[i_1], priority);
                        found = true;
                        total_priority += priority;
                    }
                }
            }

            if (found == false) {
                printf("ERROR. No duplicate found in rucksack %d\n", rucksack);
                break;
            }



            memset(line, 0, sizeof(line));
            rucksack += 1;
        }

        if (verbose)
            printf("\n");

        printf("------------------ Summary ------------------\n");
        printf("Total priorities: %d\n", total_priority);

        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
