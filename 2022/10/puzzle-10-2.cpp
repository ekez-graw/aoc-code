#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static int x_screen = 40;
static int y_screen = 6;

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    int row = 0;
    char line[32];
    char cmd[16];
    int cmd_opcode;
    int value;
    int x;
    int y;
    int cycle = 0;
    int cmd_cycle;
    int cmd_cycle_stop;
    int X = 0;
    int x_pos;
    int sprite_pos = 0;
    int screen[x_screen * y_screen];
    int screen2[x_screen * y_screen];

    memset(screen, 46, sizeof(screen));

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

                    memset(screen2, 46, sizeof(screen2));
                    x_pos = cycle % x_screen;

                    if ( (x_pos == X + 1) || (x_pos == X) || (x_pos == X + 2))
                        screen[cycle] = 35;

                    if (cycle > x_screen * y_screen)
                        cycle = x_screen * y_screen - 1; // Safety

                    screen2[X - 1] = 88;
                    screen2[X] = 88;
                    screen2[X + 1] = 88;
                    screen2[cycle] = 35;

                    printf("\033c");
                    printf("0        10        20        30       39\n");
                    printf("↓         ↓         ↓         ↓        ↓\n");
                    for (y = 0; y < y_screen * x_screen; y++) {
                        if (y > 0 && y % 40 == 0) {
                            printf("\n");
                        }
                        printf("%c", screen2[ y ]);
                    }
                    printf("\n\n");
                    printf("cycle: [%d]  X: [%d]\n", cycle, X);
                    printf("\n");
                    for (y = 0; y < y_screen; y++) {
                        for (x = 0; x < x_screen; x++) {
                            printf("%c", screen[ x + (y * x_screen) ]);
                        }
                        printf("\n");
                    }

                    usleep(200000);
                    // getc(stdin);
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

        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
