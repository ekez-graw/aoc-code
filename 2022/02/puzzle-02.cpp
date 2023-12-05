#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

bool verbose = false;

void win(int &opponent_score, int &my_score)
{
    opponent_score += 0;
    my_score += 6;

    if (verbose)
        printf(" win:  %d %d\n", opponent_score, my_score);
}

void draw(int &opponent_score, int &my_score)
{
    opponent_score += 3;
    my_score += 3;

    if (verbose)
        printf(" draw: %d %d\n", opponent_score, my_score);
}

void lost(int &opponent_score, int &my_score)
{
    opponent_score += 6;
    my_score += 0;

    if (verbose)
        printf(" lost: %d %d\n", opponent_score, my_score);
}

void mode_1(char &opponent_move, char &my_move, int &opponent_turn_score, int &my_turn_score)
{
    switch (opponent_move)
    {
    case 'A': // Rock
        opponent_turn_score += 1;
        switch (my_move) {
        case 'X': // Rock
            my_turn_score += 1;
            draw(opponent_turn_score, my_turn_score); break;
        case 'Y': // Paper
            my_turn_score += 2;
            win(opponent_turn_score, my_turn_score); break;
        case 'Z': // Scissors
            my_turn_score += 3;
            lost(opponent_turn_score, my_turn_score); break;
        default:
            printf("ERROR: Wrong input my_move: %c (%d)\n", my_move, my_move);
            exit(1);
        }
        break;
    case 'B': // Paper
        opponent_turn_score += 2;
        switch (my_move) {
        case 'X': // Rock
            my_turn_score += 1;
            lost(opponent_turn_score, my_turn_score); break;
        case 'Y': // Paper
            my_turn_score += 2;
            draw(opponent_turn_score, my_turn_score); break;
        case 'Z': // Scissors
            my_turn_score += 3;
            win(opponent_turn_score, my_turn_score); break;
        default:
            printf("ERROR: Wrong input my_move: %c (%d)\n", my_move, my_move);
            exit(1);
        }
        break;
    case 'C': // Scissors
        opponent_turn_score += 3;
        switch (my_move) {
        case 'X': // Rock
            my_turn_score += 1;
            win(opponent_turn_score, my_turn_score); break;
        case 'Y': // Paper
            my_turn_score += 2;
            lost(opponent_turn_score, my_turn_score); break;
        case 'Z': // Scissors
            my_turn_score += 3;
            draw(opponent_turn_score, my_turn_score); break;
        default:
            printf("ERROR: Wrong input my_move: %c (%d)\n", my_move, my_move);
            exit(1);
        }
        break;
    default:
        printf("ERROR: Wrong input opponent_move: %c (%d)\n", opponent_move, opponent_move);
        exit(1);
    }
}

void mode_2(char &opponent_move, char &my_move, int &opponent_turn_score, int &my_turn_score)
{
    switch (opponent_move)
    {
    case 'A': // Rock
        opponent_turn_score += 1;
        switch (my_move) {
        case 'X': // Lose i.e. Scissors
            my_turn_score += 3;
            lost(opponent_turn_score, my_turn_score); break;
        case 'Y': // Draw i.e. Rock
            my_turn_score += 1;
            draw(opponent_turn_score, my_turn_score); break;
        case 'Z': // Win i.e. Paper
            my_turn_score += 2;
            win(opponent_turn_score, my_turn_score); break;
        default:
            printf("ERROR: Wrong input my_move: %c (%d)\n", my_move, my_move);
            exit(1);
        }
        break;
    case 'B': // Paper
        opponent_turn_score += 2;
        switch (my_move) {
        case 'X': // Lose i.e. Rock
            my_turn_score += 1;
            lost(opponent_turn_score, my_turn_score); break;
        case 'Y': // Draw i.e. Paper
            my_turn_score += 2;
            draw(opponent_turn_score, my_turn_score); break;
        case 'Z': // Win i.e. Scissors
            my_turn_score += 3;
            win(opponent_turn_score, my_turn_score); break;
        default:
            printf("ERROR: Wrong input my_move: %c (%d)\n", my_move, my_move);
            exit(1);
        }
        break;
    case 'C': // Scissors
        opponent_turn_score += 3;
        switch (my_move) {
        case 'X': // Lose i.e. Paper
            my_turn_score += 2;
            lost(opponent_turn_score, my_turn_score); break;
        case 'Y': // Draw i.e. Scissors
            my_turn_score += 3;
            draw(opponent_turn_score, my_turn_score); break;
        case 'Z': // Win i.e. Rock
            my_turn_score += 1;
            win(opponent_turn_score, my_turn_score); break;
        default:
            printf("ERROR: Wrong input my_move: %c (%d)\n", my_move, my_move);
            exit(1);
        }
        break;
    default:
        printf("ERROR: Wrong input opponent_move: %c (%d)\n", opponent_move, opponent_move);
        exit(1);
    }
}

int main( int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[32];
    int opt;
    int result;
    int row = 1;
    int round = 0;
    char opponent_move;
    char my_move;
    int opponent_score = 0;
    int my_score = 0;
    int opponent_turn_score = 0;
    int my_turn_score = 0;
    int opponent_total_score = 0;
    int my_total_score = 0;
    int mode = 1;
    int new_mode;

    strcpy(file_name, "puzzle-02-input.txt");

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

    printf("Calculating maximum total score in %s\n", file_name);

    if ((file = fopen(file_name, "r")) != NULL) {
        if (verbose)
            printf("Round %d\n", round);
        while (fgets(line, sizeof(line), file) != NULL) {
            result = sscanf(line, "%c %c", &opponent_move, &my_move);
            if (result == EOF || result != 2) {
                printf("ERROR in data. Result: %d\n", result);
                exit(1);
            }

            if (verbose)
                printf("%c %c : ", opponent_move, my_move);

            switch (mode) {
                case 1:
                    mode_1(opponent_move, my_move, opponent_turn_score, my_turn_score); break;
                case 2:
                    mode_2(opponent_move, my_move, opponent_turn_score, my_turn_score); break;
            }

            if (row % 3 == 0) {
                opponent_total_score += opponent_turn_score;
                my_total_score += my_turn_score;
                round += 1;
                opponent_turn_score = my_turn_score = 0;
                if (verbose) {
                    printf("Round %d complete. Total score opponent: %d me: %d\n", round, opponent_total_score, my_total_score);
                    printf("Round %d ---------------------------------------------\n", round);
                }
            }

            row += 1;
        }

        if (verbose)
            printf("\n");
        my_total_score += my_turn_score;
        opponent_total_score += opponent_turn_score;
        printf("------------------ Summary ------------------\n");
        printf("Total score: %d Total score opponent: %d\n", my_total_score, opponent_total_score);

        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
