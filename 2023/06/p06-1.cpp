// (c) Leif Enblom
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[64];
    const char * file_path;
    bool verbose = false;
    int opt;
    char line[256];
    char *cursor;
    int characters;
    long unsigned int number_of_races = 0;
    long unsigned int race;
    long unsigned int time[10];
    long unsigned int distance[10];
    long unsigned int ways_to_win[10];
    long unsigned int i;
    long unsigned int value;
    long unsigned int distance_travelled;
    long unsigned int button_time;
    long unsigned int time_spent;
    long int remaining_time;
    long unsigned int speed;
    long unsigned int total;

    strncat( file_name, getenv( "AOC_DATA_PATH"), sizeof(file_name));

    while ((opt = getopt(argc, argv, "vf:")) != -1) {
        switch (opt) {
            case 'f':
                strncat( file_name, "/", sizeof(file_name));
                strncat( file_name, optarg, sizeof(file_name));
            break;
            case 'v':
                verbose = true;
            break;
        }
    }

    memset(&ways_to_win, 0 , sizeof(ways_to_win));

    if ((file = fopen(file_name, "r")) != NULL) {
        if (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "Time: %n", &characters);
            cursor = line + characters;
            i = 0;
            while (sscanf(cursor, "%lu %n", &value, &characters) == 1) {
                time[number_of_races++] = value;
                cursor = cursor + characters;
            }
        }

        if (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "Distance: %n", &characters);
            cursor = line + characters;
            i = 0;
            while (sscanf(cursor, "%lu %n", &value, &characters) == 1) {
                distance[i++] = value;
                cursor = cursor + characters;
            }
        }

        for (race = 0; race < number_of_races; race++) {
            if (verbose) printf("Race %lu: Time to beat: %lu\n", race, time[race]);
            time_spent = 0;
            distance_travelled = 0;
            for (button_time = 1; button_time < time[race]; button_time++) {
                remaining_time = time[race] - button_time;
                speed = button_time;
                distance_travelled = speed * remaining_time;
                if (distance_travelled > distance[race]) {
                    if (verbose) printf("  button_time: %lu , distance_travelled: %lu\n", button_time, distance_travelled);
                    ways_to_win[race] += 1;
                }
            }

            if (verbose) printf("Race %lu: ways_to_win: %lu\n-------------------------\n", race, ways_to_win[race]);
        }

        total = 1;
        for (race = 0; race < number_of_races; race++) {
            total *= ways_to_win[race];
        }
        printf("total: %lu\n", total);

        fclose(file);
    }
    else {
        if (verbose) printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
