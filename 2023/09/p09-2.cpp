// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int64_t next_value(int64_t *in_seq, int in_values)
{
    int i;
    int64_t new_seq[32];
    int64_t value = 0;
    bool all_zeros = true;

    for (i = 0; i < in_values - 1; i++) {
        new_seq[i] = in_seq[i + 1] - in_seq[i];
        if (new_seq[i] != 0)
            all_zeros = false;
    }

    if (!all_zeros)
        value = in_seq[ in_values - 1] + next_value(new_seq, in_values - 1);
    else
        value = in_seq[0];

    return value;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[64];
    char line[512];
    char *cursor;
    int n;
    int64_t val;
    int i;
    int values;
    int64_t seq[32];
    int64_t total_value = 0;
    int64_t value;

    strcpy(file_name, "2023/p09-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            cursor = line;
            values = 0;
            while (sscanf(cursor, "%ld %n", &val, &n) == 1) {
                seq[values] = val;
                values++;
                cursor += n;
            }

            // Reverse the input
            for (i = 0; i < values; i++) {
                value = seq[i];
                if (i >= values - 1 - i) {
                    seq[i] = seq[values - 1 - i];
                    seq[values - 1 - i] = value;
                }
            }

            value = next_value(seq, values);
            total_value += value;
        }

        fclose(file);
    }

    printf("Total value: %ld\n", total_value);

    return 0;
}
