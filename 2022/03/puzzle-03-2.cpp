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
    char line[MAX_NUMBER_OF_ITEMS * 3];
    int opt;
    int rucksack = 1;
    int length;
    char rucksack_content[3][MAX_NUMBER_OF_ITEMS];
    int i_1;
    int i_2;
    int i_3;
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
            length = strnlen(line, sizeof(line)) - 1;
            memcpy(rucksack_content[rucksack % 3], line, length);
            if (rucksack % 3 == 0) {
                length = strnlen(rucksack_content[0], sizeof(rucksack_content[0])) - 1;
                found = false;
                for (i_1 = 0; rucksack_content[0][i_1] != 0 && !found; i_1++) {
                    for (i_2 = 0; i_2 < rucksack_content[1][i_2] != 0 && !found; i_2++) {
                        if (rucksack_content[0][i_1] == rucksack_content[1][i_2]) {
                            for (i_3 = 0; i_3 < rucksack_content[2][i_3] != 0 && !found; i_3++) {
                                if (rucksack_content[1][i_2] == rucksack_content[2][i_3]) {
                                    found = true;
                                    if (isupper(rucksack_content[2][i_3]))
                                        priority = (int)rucksack_content[2][i_3] - 64 + 27 - 1;
                                    if (islower(rucksack_content[2][i_3]))
                                        priority = (int)rucksack_content[2][i_3] - 96;
                                    total_priority += priority;
                                    if (verbose)
                                        printf("Group: %d Badge: %c Prio: %d\n", rucksack / 3, rucksack_content[1][i_2], priority);
                                }
                            }
                        }
                    }
                }
                memset(rucksack_content, 0, sizeof(rucksack_content));
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
