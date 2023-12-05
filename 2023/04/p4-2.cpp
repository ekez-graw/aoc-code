// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Card {
public:
    Card() { copies = 0; };

    char numbers[128];
    int copies;
};


int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[128];
    int rows = 0;
    int card;
    int value;
    int number_of_cards = 0;
    int numbers;
    int characters;
    char *cursor;
    int win_cards[20];
    int winners;
    char str_value[4];
    int i = 0;
    int x;
    int y;
    int sum = 0;
    Card * cardstack[256];

    memset(str_value, 0, sizeof(str_value));
    memset(cardstack, 0, sizeof(cardstack));
    strcpy(file_name, "p4-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            cardstack[number_of_cards] = new Card();
            memcpy(&cardstack[number_of_cards]->numbers, line, sizeof(cardstack[number_of_cards]->numbers));
            number_of_cards++;
        }
    }

    for (i = 0; i < number_of_cards; i++) {
        (void)sscanf(cardstack[i]->numbers, "Card %d: %n", &card, &characters);
        cursor = cardstack[i]->numbers + characters;
        numbers = 0;
        while (sscanf(cursor, "%d %n", &value, &characters) == 1) {
            win_cards[numbers] = value;
            numbers++;
            cursor = cursor + characters;
        }
        cursor = cursor + 2;
        
        winners = 0;
        while (*(cursor-1) != 0xa) {
            memcpy(str_value, cursor, 3);
            value = atoi(str_value);
            for (x = 0; x < numbers; x++)
                if (win_cards[x] == value)
                    winners++;
            cursor = cursor + 3;
        }

        for (y = 0; y < cardstack[i]->copies + 1; y++) {
            for (x = i + 1; x <= i + winners && x < number_of_cards; x++)
                cardstack[x]->copies++;
            sum++;
        }

        rows++;
    }

    printf("Sum of scratchcards: %d\n", sum);

    for (i = 0; i < number_of_cards; i++)
        delete cardstack[i];

    return 0;
}
