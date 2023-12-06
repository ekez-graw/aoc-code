// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stack>

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[256];
    int rows = 0;
    int sum;
    int card;
    int value;
    int number_of_cards;
    int characters;
    char *cursor;
    int worth = 0;
    int win_cards[20];
    int winners;
    char str_value[4];
    int i;

    memset(str_value, 0, sizeof(str_value));
    strcpy(file_name, "p4-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "Card %d: %n", &card, &characters) != 1)
                printf("ERROR\n");
            printf("Card: %d\n", card);
            cursor = line + characters;
            number_of_cards = 0;
            while (sscanf(cursor, "%d %n", &value, &characters) == 1) {
                win_cards[number_of_cards] = value;
                number_of_cards++;
                cursor = cursor + characters;
            }

            // sscanf(cursor, "|%n", &characters);
            cursor = cursor + 2;
            
            sum = 0;
            winners = 0;
            while (*(cursor-1) != 0xa) {
                memcpy(str_value, cursor, 3);
                value = atoi(str_value);
                for (i = 0; i < number_of_cards; i++) {
                    if (win_cards[i] == value) {
                        winners++;
                        if (winners == 1) 
                            sum = 1;    
                        else {
                            sum = sum * 2;
                        }
                        printf("winners: %d sum: %d\n", winners, sum);
                    }
                }
                cursor = cursor + 3;
            }

            printf("  winners: %d sum: %d\n", winners, sum);
            worth += sum;
            rows++;
        }

        fclose(file);

        printf("Total worth %d\n", worth);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
