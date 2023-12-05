#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    int row = 0;
    char line[32];
    char cmd[16];
    int cmd_opcode;
    int value;
    int s;
    int cycle = 1;
    int cmd_cycle;
    int cmd_cycle_stop;
    bool do_sample = false;
    int X = 1;
    int sample_total = 0;

    strcpy(file_name, "puzzle-10-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            row++;
            if (sscanf(line, "%s %d", cmd, &value)) {
                if (strncmp(cmd, "noop", sizeof(cmd)) == 0) {
                    cmd_cycle_stop = 1;
                    cmd_opcode = 1;
                }
                if (strncmp(cmd, "addx", sizeof(cmd)) == 0) {
                    cmd_cycle_stop = 2;
                    cmd_opcode = 2;
                }

                cmd_cycle = 1;
                while (cmd_cycle < cmd_cycle_stop + 1) {
                    do_sample = false;
                    if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
                        do_sample = true;
                        sample_total += (X * cycle);
                    }
                    cmd_cycle++;
                    cycle++;
                }

                switch (cmd_opcode) {
                    case 2:
                        X += value;
                    break;
                }
            }
        }

        printf("Sample total value: %d\n", sample_total);

        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
