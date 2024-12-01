// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char rec[64];
char rec_original[64];
u_int32_t rec_count;
u_int32_t unknowns[64];
u_int32_t unknown_count;

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[64];
    char line[256];
    char * cursor;
    int group[16];
    int n;
    int i;
    int nr_groups;
    int val;
    u_int32_t arrangements;
    u_int32_t total_arrangements = 0;
    int 

    memset(rec, 0, sizeof(rec));
    memset(rec_original, 0, sizeof(rec_original));
    memset(unknowns, 0, sizeof(unknowns));

    strcpy(file_name, "/home/dad/src/aoc/aoc-data/2023/p12-example-input-1.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            cursor = line;
            rec_count = 0;
            unknown_count = 0;
            nr_groups = 0;
            while (*cursor != ' ') {
                if (*cursor == '.')
                    rec[rec_count] = 1;
                if (*cursor == '#')
                    rec[rec_count] = 2;
                if (*cursor == '?') {
                    unknowns[unknown_count] = rec_count;
                    unknown_count++;
                }
                rec[rec_count] = *cursor;
                cursor++;
                rec_count++;
            }
            memcpy(rec_original, rec, rec_count);

            sscanf(cursor, " %d %n", &val, &n);
            group[nr_groups] = val;
            nr_groups++;
            cursor += n;
            while (sscanf(cursor, ",%d %n", &val, &n) == 1) {
                group[nr_groups] = val;
                nr_groups++;
                cursor += n;
            }

            i = 0;
            bool looped = false;
            for (!looped) {

            }

        }

        fclose(file);
    }

    printf("Total Lengths: %u\n", total_arrangements);

    return 0;
}
