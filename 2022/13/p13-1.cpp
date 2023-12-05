// Created by Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <list>

using namespace std;

void print_line(char *line, int start, int stop)
{
    int i;

    for (i = start; i <= stop; i++)
        printf("%c", line[i]);
    printf("\n");
}

int parse( char *line, int start, int stop)
{
    int next_start = start + 1;
    int next_stop;
    int level;
    int value;

    print_line(line, start, stop);
    if (line[start] != '[')
        printf("ERROR\n");

    while (next_start != next_stop) {
        if (line[next_start] == '[') {
            next_stop = next_start + 1;
            level = 1;
            while (level >= 1) {
                if (line[next_stop] == '[')
                    level++;
                if (line[next_stop] == ']')
                    level--;
                if (level == 0)
                    break;
                next_stop++;
            }
            parse(line, next_start, next_stop);
        }
        else if (line[next_start] == ',') {
            parse(line, next_start + 1, stop);
        }
        else {
            sscanf(line, "%d", &value);
            if (value == 10)
                next_start += 2;
            else
                next_start += 1;
        }
    }

    // if (next_start != stop) {
    //     next_stop = next_start + 1;
    //     while (line[next_stop] != ']' && next_start < stop)
    //         next_stop++;
    //     return parse(line, next_start, next_stop);
    // }
    // else { // Last level
    //     print_line(line, start+1, stop-1);
    //     return false;
    // }

    return true;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[256];
    int level;
    char *cursor;
    int line_len;

    strcpy(file_name, "p13-example-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            line_len = strlen(line);
            cursor = line;
            while (parse(line, 0, line_len-2));

            // printf("\n");
        }

        fclose(file);
        return -1;
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
