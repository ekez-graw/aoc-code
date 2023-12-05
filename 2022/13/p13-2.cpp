// Created by Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <list>

using namespace std;

class Item {
    public:
    Item(long long unsigned int in_worry_level);
    long long unsigned int worry_level;
};

Item::Item( long long unsigned int in_worry_level) :
worry_level(in_worry_level)
{};

class Monkey {
public:
    Monkey( int in_number);
    int number;
    char operation;
    char valuestr[8];
    long unsigned int divisor;
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

int compare_round[12] = { 1, 20, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };
int compare_monkey_inspections[12][4] = {
    { 2, 4, 3, 6 },
    { 99, 97, 8, 103 },
    { 5204, 4792, 199, 5192 },
    { 10419, 9577, 392, 10391 },
    { 15638, 14358, 587, 15593 },
    { 20858, 19138, 780, 20797 },
    { 26075, 23921, 974, 26000 },
    { 31294, 28702, 1165, 31204 },
    { 36508, 33488, 1360, 36400 },
    { 41728, 38268, 1553, 41606 },
    { 46945, 43051, 1746, 46807 },
    { 52166, 47830, 1938, 52013 },
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
    long long unsigned int worry_level;
    Monkey * monkeys[32];
    class Monkey *monkey;
    class Item *item;
    int round;
    int new_monkey;
    int inspections;
    long unsigned int first_size;
    long unsigned int second_size;
    long unsigned int monkey_business;
    long long unsigned int op_argument;
    unsigned int lcm;

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
                if (sscanf(token, "%llu", &worry_level) != 1) goto fail;
                item = new Item(worry_level);
                monkey->items.push_back(item);
            }

            if (fgets(line, sizeof(line), file) != NULL)
                if (sscanf(line, " Operation: new = old %c %s", &monkey->operation, monkey->valuestr) != 2) goto fail;
            if (fgets(line, sizeof(line), file) != NULL)
                if (sscanf(line, " Test: divisible by %lu", &monkey->divisor) != 1) goto fail;
            if (fgets(line, sizeof(line), file) != NULL)
                if (sscanf(line, "    If true: throw to monkey %d", &monkey->true_monkey) != 1) goto fail;
            if (fgets(line, sizeof(line), file) != NULL)
                if (sscanf(line, "    If false: throw to monkey %d", &monkey->false_monkey) != 1) goto fail;

            if (monkey_number == 0) {
                lcm = monkey->divisor;
            } else {
                lcm *= monkey->divisor;
            }
            monkeys[monkey_number] = monkey;
            fgets(line, sizeof(line), file); // Always consume newline
        }

        for (round = 1; round <= 10000; round++) {
            for (i = 0; i <= monkey_number; i++) {
                inspections = 0;
                while ((item = monkeys[i]->items.front()) != NULL) {
                    monkeys[i]->items.pop_front();
                    worry_level = item->worry_level;

                    if (strcmp(monkeys[i]->valuestr, "old") == 0)
                        op_argument = item->worry_level;
                    else
                        op_argument = atoi(monkeys[i]->valuestr);

                    if (monkeys[i]->operation == '+')
                        worry_level += op_argument;

                    if (monkeys[i]->operation == '*')
                        worry_level *= op_argument;

                    worry_level %= lcm;
                    if (worry_level % monkeys[i]->divisor == 0)
                        new_monkey = monkeys[i]->true_monkey;
                    else
                        new_monkey = monkeys[i]->false_monkey;

                    item->worry_level = worry_level;
                    monkeys[new_monkey]->items.push_back(item);
                    inspections++;
                }
                monkeys[i]->inspections += inspections;
            }
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
