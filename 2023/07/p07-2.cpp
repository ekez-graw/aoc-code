// (c) Leif Enblom
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum HandType { distinct = 0, one_pair, two_pair, three_of_a_kind, full_house, four_of_a_kind, five_of_a_kind};

class Hand
{
public:
    Hand(char * in_hand, int in_bid);

    u_int8_t hand[5];
    u_int8_t original_hand[5];
    int bid;
    HandType type;

    int nrOfAKind( int in_card);
    bool isFiveOfAKind( int in_card);
    bool isFourOfAKind( int in_card);
    bool isFullHouse( int in_card);
    bool isThreeOfAKind( int in_card);
    bool isTwoPair( int in_card);
    bool isPair( int in_card);
    void tweakHand();
    HandType determineType();
    bool operator>(Hand &in_hand);
    void print();
};

Hand::Hand(char * in_hand, int in_bid)
{
    int x;

    for (x = 0; x < 5; x++) {
        if (in_hand[x] == 'T')
            hand[x] = 10;
        else if (in_hand[x] == 'J')
            hand[x] = 11;
        else if (in_hand[x] == 'Q')
            hand[x] = 12;
        else if (in_hand[x] == 'K')
            hand[x] = 13;
        else if (in_hand[x] == 'A')
            hand[x] = 14;
        else
            hand[x] = in_hand[x] - 0x30;
        original_hand[x] = hand[x];
    }

    bid = in_bid;
    type = determineType();
};

int Hand::nrOfAKind( int in_card)
{
    int x, nr_of_equal = 0;

    for (x = 0; x < 5; x++) {
        if (hand[x] == in_card)
            nr_of_equal++;
    }

    return nr_of_equal;
}

bool Hand::isFiveOfAKind( int in_card)
{
    if (nrOfAKind( in_card) == 5)
        return true;
    return false;
}

bool Hand::isFourOfAKind( int in_card)
{
    if (nrOfAKind( in_card) == 4)
        return true;
    return false;
}

bool Hand::isFullHouse( int in_card)
{
    int x;
    if (isThreeOfAKind( in_card)) {
        for (x = 2; x <= 14; x++) {
            if (isPair( x) && in_card != x)
                return true;
        }
    }

    return false;
}

bool Hand::isThreeOfAKind( int in_card)
{
    if (nrOfAKind( in_card) == 3)
        return true;
    return false;
}

bool Hand::isTwoPair( int in_card)
{
    int x;
    if (isPair( in_card)) {
        for (x = 2; x <= 14; x++) {
            if (isPair( x) && in_card != x)
                return true;
        }
    }

    return false;
}

bool Hand::isPair( int in_card)
{
    if (nrOfAKind( in_card) == 2)
        return true;
    return false;
}

void Hand::tweakHand()
{
    int x1, x2, x3, x4, x5;
    Hand best_hand = *this;
    Hand temp_hand = *this;

    for (x1 = 1; x1 <= 14; x1++) {
        if (original_hand[0] == 11) {
            temp_hand.hand[0] = x1;
            temp_hand.type = temp_hand.determineType();
            if (temp_hand > best_hand) {
                best_hand = temp_hand;
            }
        }
        for (x2 = 1; x2 <= 14; x2++) {
            if (original_hand[1] == 11) {
                temp_hand.hand[1] = x2;
                temp_hand.type = temp_hand.determineType();
                if (temp_hand > best_hand) {
                    best_hand = temp_hand;
                }
            }
            for (x3 = 1; x3 <= 14; x3++) {
                if (original_hand[2] == 11) {
                    temp_hand.hand[2] = x3;
                    temp_hand.type = temp_hand.determineType();
                    if (temp_hand > best_hand) {
                        best_hand = temp_hand;
                    }
                }
                for (x4 = 1; x4 <= 14; x4++) {
                    if (original_hand[3] == 11) {
                        temp_hand.hand[3] = x4;
                        temp_hand.type = temp_hand.determineType();
                        if (temp_hand > best_hand) {
                            best_hand = temp_hand;
                        }
                    }
                    for (x5 = 1; x5 <= 14; x5++) {
                        if (original_hand[4] == 11) {
                            temp_hand.hand[4] = x5;
                            temp_hand.type = temp_hand.determineType();
                            if (temp_hand > best_hand) {
                                best_hand = temp_hand;
                            }
                        }
                    }
                }
            }
        }
    }

    *this = best_hand;
}

HandType Hand::determineType()
{
    HandType type = distinct;
    int x, y;

    for (x = 2; x <= 14; x++) {
        if (isFiveOfAKind(x)) {
            type = five_of_a_kind;
            goto out;
        }
    }

    for (x = 2; x <= 14; x++) {
        if (isFourOfAKind(x)) {
            type = four_of_a_kind;
            goto out;
        }
    }

    for (x = 2; x <= 14; x++) {
        if (isFullHouse(x)) {
            type = full_house;
            goto out;
        }
    }

    for (x = 2; x <= 14; x++) {
        if (isThreeOfAKind(x)) {
            type = three_of_a_kind;
            goto out;
        }
    }

    for (x = 2; x <= 14; x++) {
        if (isTwoPair(x)) {
            type = two_pair;
            goto out;
        }
    }

    for (x = 2; x <= 14; x++) {
        if (isPair(x)) {
            type = one_pair;
            goto out;
        }
    }

out:
    return type;
}

bool Hand::operator>(Hand &in_hand)
{
    int x;
    u_int8_t temp_hand[5];
    u_int8_t in_temp_hand[5];

    if (type > in_hand.type)
        return true;
    if (type == in_hand.type) {
        memcpy(temp_hand, original_hand, 5);
        memcpy(in_temp_hand, in_hand.original_hand, 5);
        for (x = 0; x < 5; x++) {
            if (temp_hand[x] == 11)
                temp_hand[x] = 1;
            if (in_temp_hand[x] == 11)
                in_temp_hand[x] = 1;
            if (temp_hand[x] < in_temp_hand[x])
                return false;
            if (temp_hand[x] > in_temp_hand[x])
                return true;
        }
    }

    return false;
}

void Hand::print()
{
    int x;

    for (x = 0; x < 5; x++) {
        if (hand[x] == 10)
            printf("T");
        else if (hand[x] == 11)
            printf("J");
        else if (hand[x] == 12)
            printf("Q");
        else if (hand[x] == 13)
            printf("K");
        else if (hand[x] == 14)
            printf("A");
        else
            printf("%d", hand[x]);
    }

    printf(" %d ", type);

    for (x = 0; x < 5; x++) {
        if (original_hand[x] == 10)
            printf("T");
        else if (original_hand[x] == 11)
            printf("J");
        else if (original_hand[x] == 12)
            printf("Q");
        else if (original_hand[x] == 13)
            printf("K");
        else if (original_hand[x] == 14)
            printf("A");
        else
            printf("%d", original_hand[x]);
    }

    printf(" ");
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[64];
    const char * file_path;
    bool verbose = false;
    int opt;
    char line[256];
    u_int64_t total = 0;
    int x;
    int nr_of_hands = 0;
    Hand * hand[1001];
    Hand * temp_hand;
    char hand_val[5];
    unsigned int bid_val;
    bool progress = true;

    strncat( file_name, getenv( "AOC_DATA_PATH"), sizeof(file_name) - 1);

    while ((opt = getopt(argc, argv, "vf:")) != -1) {
        switch (opt) {
            case 'f':
                strncat( file_name, "/", sizeof(file_name) - 1);
                strncat( file_name, optarg, sizeof(file_name) - 1);
            break;
            case 'v':
                verbose = true;
            break;
        }
    }

    strcpy(file_name, "/home/dad/src/aoc/aoc-data/2023/p07-input.txt");
    memset(hand, 0, sizeof(hand));

    if ((file = fopen(file_name, "r")) != NULL) {
        nr_of_hands = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%s %u", hand_val, &bid_val);
            hand[nr_of_hands] = new Hand(hand_val, bid_val);
            hand[nr_of_hands]->tweakHand();
            hand[nr_of_hands]->type = hand[nr_of_hands]->determineType();
            if (nr_of_hands % 50 == 0)
                printf("\nHand %.5d: ", nr_of_hands);
            nr_of_hands++;
            printf(".");
            fflush(stdout);
        }

        printf("\nSorting\n");
        while (progress) {
            fflush(stdout);
            progress = false;
            for (x = 0; x < nr_of_hands - 1; x++) {
                if (*hand[x] > *hand[x + 1]) {
                    temp_hand = hand[x];
                    hand[x] = hand[x + 1];
                    hand[x + 1] = temp_hand;
                    progress = true;
                }
            }
        }

        for (x = 0; x < nr_of_hands; x++) {
            printf( "%.4d: ", x);
            hand[x]->print();
            printf( "%d\n", hand[x]->bid);
            total += hand[x]->bid * (x + 1);
        }

        fclose(file);
        printf("total: %lu\n", total);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
