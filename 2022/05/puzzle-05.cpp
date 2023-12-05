#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>
#include <stack>

bool verbose = false;
static int MAX_NUMBER_OF_ITEMS = 64;
static char barrier[] = " 1   2   3   4   5   6   7   8   9 ";

int main( int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[MAX_NUMBER_OF_ITEMS * 2];
    int opt;
    int mode = 1;
    int new_mode;
    char entry[5];
    char *line_ptr;
    std::stack<int> *stacks[9];
    std::stack<int> tmpstack;
    int move = 1;
    int from, to;
    char crate;
    int number_of_crates;
    int value;
    int i;
    int number_of_stacks = 3;

    strcpy(file_name, "puzzle-05-example-input.txt");

    while ((opt = getopt(argc, argv, "n:m:vf:")) != -1) {
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
            case 'n':
                number_of_stacks = atoi(optarg);
            break;
            case 'v':
                verbose = true;
            break;
        }
    }

    printf("Rearranging stacks in %s mode %d\n", file_name, mode);

    for (i = 0; i < number_of_stacks; i++) {
        stacks[i] = new std::stack<int>;
    }

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strncmp(line, barrier, number_of_stacks * 3) == 0) {
                break;
            }

            line_ptr = line;
            for (i = 0; i < number_of_stacks; i++) {
                memcpy(entry, line_ptr, 4);
                line_ptr += 4;
                if (sscanf(entry, "[%c] ", &crate) != 0) {
                    stacks[i]->push((int)crate);
                }
            }
        }

        for (i = 0; i < number_of_stacks; i++) {
            while (stacks[i]->empty() == false) {
                value = stacks[i]->top();
                stacks[i]->pop();
                tmpstack.push(value);
            }
            *stacks[i] = tmpstack;
            while (tmpstack.empty() == false) {
                tmpstack.pop(); 
            }
        }

        switch (mode) {
            case 1:

                while (fgets(line, sizeof(line), file) != NULL) {
                    if (sscanf(line, "move %d from %d to %d", &number_of_crates, &from, &to) > 0) {
                        from -= 1;
                        to -= 1;
                        for (i = 0; i < number_of_crates; i++) {
                            value = stacks[from]->top();
                            stacks[from]->pop();
                            stacks[to]->push(value);
                        }
                    }

                    move += 1;
                }

            break;
            case 2:

                while (fgets(line, sizeof(line), file) != NULL) {
                    if (sscanf(line, "move %d from %d to %d", &number_of_crates, &from, &to) > 0) {
                        from -= 1;
                        to -= 1;
                        for (i = 0; i < number_of_crates; i++) {
                            value = stacks[from]->top();
                            stacks[from]->pop();
                            tmpstack.push(value);
                        }

                        while (tmpstack.empty() == false) {
                            stacks[to]->push(tmpstack.top());
                            tmpstack.pop(); 
                        }
                    }

                    move += 1;
                }

                break;
        }



        printf("------------------ Summary ------------------\n");
        printf("Top stack:\n");

        for (i = 0; i < number_of_stacks; i++) {
            printf("%c", stacks[i]->top());
            delete stacks[i];
        }

        printf("\n");
        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
