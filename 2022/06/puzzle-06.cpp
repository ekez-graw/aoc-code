#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>

int main( int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char *data;
    int opt;
    int i;
    int j;
    int cursor;
    int file_size;
    int message_length = 3;
    bool duplicate;

    memset(&data, 0, sizeof(data));
    strcpy(file_name, "puzzle-06-example-input.txt");

    while ((opt = getopt(argc, argv, "l:f:")) != -1) {
        switch (opt) {
            case 'f':
                strncpy(file_name, optarg, sizeof(file_name));
            break;
            case 'l':
                message_length = atoi(optarg) - 1;
            break;
        }
    }

    printf("Finding markers %s\n", file_name);

    if ((file = fopen(file_name, "r")) != NULL) {
        fseek(file, 0L, SEEK_END);
        file_size = ftell(file);
        fseek(file, 0L, SEEK_SET);
        data = (char *)malloc(file_size);
        if (fread((void *)data, 1, file_size, file) == file_size) {
            for (cursor = message_length; cursor < file_size; cursor++) {
                int checker = (cursor - message_length);
                duplicate = false;
                for (i = cursor - message_length; i <= cursor; i++) {
                    for (j = cursor - message_length; j <= cursor; j++) {
                        if ((i != j) && (data[i] == data[j])) {
                            duplicate = true;
                            break;
                        }
                    }
                }

                if (duplicate == false) {
                    printf("Marker found after %d characters\n", cursor + 1);
                    break;
                }
            }
        }

        fclose(file);
        delete data;
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
