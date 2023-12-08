// (c) Leif Enblom
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Node
{
public:
    Node();

    char start[4];
    char left[4];
    char right[4];
};

Node::Node()
{
    memset(start, 0 , sizeof(start));
    memset(left, 0 , sizeof(left));
    memset(right, 0 , sizeof(right));
}

void strip_comma(char *line)
{
    int x = 0;
    while (*line != 0 && x < 256) {
        if (*line == ',')
            *line = ' ';
        line++;
        x++;
    }
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[64];
    char line[265];
    unsigned int nr_of_turns;
    unsigned int nr_of_nodes = 0;
    char turn[600];
    Node *node[1000];
    int i, x;
    unsigned int current_node;
    u_int64_t steps = 0;
    char next[4];

    strcpy(file_name, "2023/p08-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        memset(line, 0 , sizeof(line));
        if (fgets(line, sizeof(line), file) != NULL) {
            memcpy(turn, line, sizeof(turn));
            while (turn[nr_of_turns] != 0) {
                nr_of_turns++;
            }
        }
        nr_of_turns--;

        fgets(line, sizeof(line), file);
        nr_of_nodes = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            strip_comma(line);
            node[nr_of_nodes] = new Node();
            sscanf(line, "%s = (%s  %s)", node[nr_of_nodes]->start, node[nr_of_nodes]->left, node[nr_of_nodes]->right);
            nr_of_nodes++;
        }

        current_node = 0;
        for (x = 0; x < nr_of_nodes; x++) {
            if (memcmp(node[x]->start, "AAA", 3) == 0) {
                current_node = x;
                break;
            }
        }

        i = 0;
        do {
            if (turn[i] == 'L')
                memcpy( next, node[current_node]->left, 3);
            else if (turn[i] == 'R')
                memcpy( next, node[current_node]->right, 3);
            i++;
            if (i >= nr_of_turns)
                i = 0;

            x = 0;
            for (x = 0; x < nr_of_nodes; x++) {
                if (memcmp(node[x]->start, next, 3) == 0) {
                    current_node = x;
                    break;
                }
            }
            steps++;
        } while (memcmp(node[current_node]->start, "ZZZ", 1) != 0);

        fclose(file);
    }

    printf("Total Steps required: %lu\n", steps);

    return 0;
}
