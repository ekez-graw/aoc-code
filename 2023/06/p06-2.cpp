// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    long unsigned int number_of_races = 0;
    long unsigned int race;
    long unsigned int time[10];
    long unsigned int distance[10];
    long unsigned int ways_to_win[10];
    long unsigned int value;
    long unsigned int distance_travelled;
    long unsigned int button_time;
    long int remaining_time;
    long unsigned int speed;
    long unsigned int total;

    memset(&ways_to_win, 0 , sizeof(ways_to_win));

    time[0] = 48938466;
    distance[0] = 261119210191063;
    number_of_races = 1;

    for (race = 0; race < number_of_races; race++) {
        distance_travelled = 0;
        for (button_time = 1; button_time < time[race]; button_time++) {
            remaining_time = time[race] - button_time;
            speed = button_time;
            distance_travelled = speed * remaining_time;
            if (distance_travelled > distance[race])
                ways_to_win[race] += 1;
        }
    }

    total = 1;
    for (race = 0; race < number_of_races; race++) {
        total *= ways_to_win[race];
    }
    printf("total: %lu\n", total);

    return 0;
}
