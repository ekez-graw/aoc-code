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
    unsigned int visited[10];
};

Node::Node()
{
    memset(start, 0 , sizeof(start));
    memset(left, 0 , sizeof(left));
    memset(right, 0 , sizeof(right));
    memset(visited, 0 , sizeof(visited));
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[64];
    char line[265];
    unsigned int nr_of_instr = 0;
    unsigned int nr_of_nodes = 0;
    unsigned int nr_of_ghosts = 0;
    char instr[600];
    Node *node[1000];
    unsigned int i, n, g = 0;
    unsigned int current_node[10];
    unsigned int steps = 0;
    char next[10][4];
    unsigned int loop[10];
    unsigned int loops_detected;

    memset(current_node, 0 , sizeof(current_node));
    memset(next, 0 , sizeof(next));
    strcpy(file_name, "/home/dad/src/aoc/aoc-data/2023/p08-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {

        // Read instructions and count them
        memset(line, 0 , sizeof(line));
        if (fgets(line, sizeof(line), file) != NULL) {
            memcpy(instr, line, sizeof(instr));
            while (instr[nr_of_instr] != 0)
                nr_of_instr++;
        }
        nr_of_instr--;

        // Parse all node input and count nodes
        fgets(line, sizeof(line), file);
        nr_of_nodes = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            node[nr_of_nodes] = new Node();
            sscanf(line, "%s = (%s  %s)", node[nr_of_nodes]->start, node[nr_of_nodes]->left, node[nr_of_nodes]->right);
            nr_of_nodes++;
        }

        // Find starting node for all ghosts and count them
        for (n = 0; n < nr_of_nodes; n++) {
            if (node[n]->start[2] == 'A') {
                current_node[nr_of_ghosts] = n;
                if (current_node[nr_of_ghosts] != 0)
                    nr_of_ghosts++;
            }
        }

        do {
            // Find next node label for all ghosts
            for (g = 0; g < nr_of_ghosts; g++) {
                if (instr[i] == 'L')
                    memcpy( next[g], node[current_node[g]]->left, 3);
                else if (instr[i] == 'R')
                    memcpy( next[g], node[current_node[g]]->right, 3);
            }
            steps++;

            // Next instruction and handle wrap-around
            i++;
            if (i >= nr_of_instr)
                i = 0;

            // Handle next node for all ghosts and detect loops
            for (g = 0; g < nr_of_ghosts; g++) {
                for (n = 0; n < nr_of_nodes; n++) {
                    if (memcmp(node[n]->start, next[g], 3) == 0) {
                        current_node[g] = n;
                        if (node[n]->visited[g] != 0 && loop[g] == 0) {
                            loop[g] = steps - node[n]->visited[g];
                            printf("[%u] Loop detected at node %u [%u]-[%u] = %u\n", g, n, steps, node[n]->visited[g], loop[g]);
                        }
                        node[n]->visited[g] = steps;
                        break;
                    }
                }
            }

            // Count loops for ghosts
            loops_detected = 0;
            for (g = 0; g < nr_of_ghosts; g++) {
                if (loop[g] != 0)
                    loops_detected++;
            }
        } while (loops_detected != nr_of_ghosts);

        fclose(file);
    }

    printf("Total Steps required: %u\n", steps);

    return 0;
}
