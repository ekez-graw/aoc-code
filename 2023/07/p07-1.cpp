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
    int bid;
    HandType type;

    int nrOfAKind( int in_card);
    bool isFiveOfAKind( int in_card);
    bool isFourOfAKind( int in_card);
    bool isFullHouse( int in_card);
    bool isThreeOfAKind( int in_card);
    bool isTwoPair( int in_card);
    bool isPair( int in_card);
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
    if (type > in_hand.type)
        return true;
    if (type == in_hand.type) {
        for (x = 0; x < 5; x++) {
            if (hand[x] < in_hand.hand[x])
                return false;
            if (hand[x] > in_hand.hand[x])
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

    strcpy(file_name, "2023/p07-input.txt");
    memset(hand, 0, sizeof(hand));

    if ((file = fopen(file_name, "r")) != NULL) {
        nr_of_hands = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%s %u", hand_val, &bid_val);
            hand[nr_of_hands] = new Hand(hand_val, bid_val);
            nr_of_hands++;
        }

        while (progress) {
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
            printf( " %d\n", hand[x]->bid);
            total += hand[x]->bid * (x + 1);
        }

        fclose(file);
        if (verbose) printf("total: %lu\n", total);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
