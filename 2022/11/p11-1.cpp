#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <list>

using namespace std;

class Item {
    public:
    Item(long unsigned int in_worry_level);
    long unsigned int worry_level;
};

Item::Item( long unsigned int in_worry_level) :
worry_level(in_worry_level)
{};

class Monkey {
public:
    Monkey( int in_number);
    int number;
    char operation;
    char valuestr[8];
    unsigned int divisor;
    int true_monkey;
    int false_monkey;
    int inspections;
    std::list<Item *> items;
};

Monkey::Monkey( int in_number) :
number(in_number),
operation(0),
divisor(0),
true_monkey(0),
false_monkey(0),
inspections(0)
{
    memset(valuestr, 0, sizeof(valuestr));
};

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[64];
    char *lineptr;
    char *token;
    char valuestr[8];
    int i;
    int monkey_number;
    long unsigned int worry_level;
    Monkey * monkeys[32];
    class Monkey *monkey;
    class Item *item;
    int round;
    int new_monkey;
    int inspections;
    int first_size;
    int second_size;
    long unsigned int monkey_business;

    memset(monkeys, 0, sizeof(monkeys));
    strcpy(file_name, "p11-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "Monkey %d:", &monkey_number) != 1) goto fail;
            monkey = new Monkey(monkey_number);

            if (fgets(line, sizeof(line), file) == NULL)
                if (strcmp(line, " Starting items:") != 0) goto fail;
            lineptr = line;
            lineptr += strlen(" Starting items:") + 1;
            while ((token = strtok_r(lineptr," ,", &lineptr)) != NULL) {
                if (sscanf(token, "%ld", &worry_level) != 1) goto fail;
                item = new Item(worry_level);
                monkey->items.push_back(item);
            }

            if (fgets(line, sizeof(line), file) != NULL)
                if (sscanf(line, " Operation: new = old %c %s", &monkey->operation, monkey->valuestr) != 2) goto fail;
            if (fgets(line, sizeof(line), file) != NULL)
                if (sscanf(line, " Test: divisible by %d", &monkey->divisor) != 1) goto fail;
            if (fgets(line, sizeof(line), file) != NULL)
                if (sscanf(line, "    If true: throw to monkey %d", &monkey->true_monkey) != 1) goto fail;
            if (fgets(line, sizeof(line), file) != NULL)
                if (sscanf(line, "    If false: throw to monkey %d", &monkey->false_monkey) != 1) goto fail;
            monkeys[monkey_number] = monkey;
            fgets(line, sizeof(line), file); // Always consume newline
        }

        long unsigned int op_argument;

        for (round = 1; round <= 20; round++) {
            printf("Round: %d\n", round);
            for (i = 0; i <= monkey_number; i++) {
                printf("Monkey: %d\n", monkeys[i]->number);
                inspections = 0;
                while ((item = monkeys[i]->items.front()) != NULL) {
                    monkeys[i]->items.pop_front();
                    worry_level = item->worry_level;
                    printf("Monkey inspects an item with a worry level of %lu.\n", item->worry_level);

                    if (strcmp(monkeys[i]->valuestr, "old") == 0)
                        op_argument = item->worry_level;
                    else
                        op_argument = atoi(monkeys[i]->valuestr);

                    if ( monkeys[i]->operation == '+') {
                        worry_level += op_argument;
                        printf("Worry level increases by %lu to %lu.\n", op_argument, worry_level);
                    }
                    if ( monkeys[i]->operation == '*') {
                        worry_level *= op_argument;
                        printf("Worry level is multiplied by %lu to %lu.\n", op_argument, worry_level);
                    }

                    worry_level /= 3;
                    printf("Monkey gets bored with item. Worry level is divided by 3 to %lu.\n", worry_level);                    
                    if (worry_level % monkeys[i]->divisor == 0) {
                        printf("Current worry level is divisible by %u\n", monkeys[i]->divisor);
                        new_monkey = monkeys[i]->true_monkey;
                    } else {
                        printf("Current worry level is not divisible by %u\n", monkeys[i]->divisor);
                        new_monkey = monkeys[i]->false_monkey;
                    }

                    item->worry_level = worry_level;
                    printf("Item with worry level %lu is thrown to monkey %d.\n", item->worry_level, new_monkey);
                    monkeys[new_monkey]->items.push_back(item);
                    inspections++;
                    printf("\n");
                }
                monkeys[i]->inspections += inspections;
            }

            printf("\n");
        }

        first_size = 0; second_size = 0;
        for (i = 0; i < monkey_number + 1; i++)
            if (monkeys[i]->inspections > first_size)
                first_size = monkeys[i]->inspections;

        for (i = 0; i < monkey_number + 1; i++) 
            if (first_size != monkeys[i]->inspections && monkeys[i]->inspections > second_size)
                second_size = monkeys[i]->inspections;

        monkey_business = first_size * second_size;
        printf("Monkey business: %lu\n", monkey_business);

        fclose(file);
        return 0;

fail:
        printf("Parse ERROR\n");
        fclose(file);
        return -1;
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
