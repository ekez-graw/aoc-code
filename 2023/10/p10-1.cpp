// (c) Leif Enblom
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char maze[200][200];

enum Direction {
    north = 0,
    east,
    south,
    west
};

const char *dir_to_str(enum Direction in_dir)
{
    switch(in_dir) {
        case north:
            return "North";
        break;
        case east:
            return "East";
        break;
        case south:
            return "South";
        break;
        case west:
            return "West";
        break;
    }

    return "N/A";
}

bool accepted_north(u_int32_t in_y, u_int32_t in_x, Direction &out_dir)
{
    char pipe = maze[in_y][in_x];

    if (pipe == 'S')
        return true;

    if (pipe == '7') {
        out_dir = west;
        return true;
    }

    if (pipe == '|') {
        out_dir = north;
        return true;
    }
       
    if (pipe == 'F') {
        out_dir = east;
        return true;
    }
        
    return false;
}

bool accepted_east(u_int32_t in_y, u_int32_t in_x, Direction &out_dir)
{
    char pipe = maze[in_y][in_x];

    if (pipe == 'S')
        return true;

    if (pipe == 'J') {
        out_dir = north;
        return true;
    }
    
    if (pipe == '-') {
        out_dir = east;
        return true;
    }
        
    if (pipe == '7') {
        out_dir = south;
        return true;
    }

    return false;
}

bool accepted_south(u_int32_t in_y, u_int32_t in_x, Direction &out_dir)
{
    char pipe = maze[in_y][in_x];

    if (pipe == 'S')
        return true;

    if (pipe == 'L') {
        out_dir = east;
        return true;
    }
    
    if (pipe == '|') {
        out_dir = south;
        return true;
    }
        
    if (pipe == 'J') {
        out_dir = west;
        return true;
    }

    return false;
}

bool accepted_west(u_int32_t in_y, u_int32_t in_x, Direction &out_dir)
{
    char pipe = maze[in_y][in_x];

    if (pipe == 'S')
        return true;

    if (pipe == 'F') {
        out_dir = south;
        return true;
    }
    
    if (pipe == '-') {
        out_dir = west;
        return true;
    }
        
    if (pipe == 'L') {
        out_dir = north;
        return true;
    }

    return false;
}

bool find_next(u_int32_t &y_next, u_int32_t &x_next, enum Direction &in_dir)
{
    if (in_dir == north)
        if (accepted_north(y_next - 1, x_next, in_dir)) {
            y_next = y_next - 1;
            return true;
        }

    if (in_dir == east)
        if (accepted_east(y_next, x_next + 1, in_dir)) {
            x_next = x_next + 1;
            return true;
        }

    if (in_dir == south)
        if (accepted_south(y_next + 1, x_next, in_dir)) {
            y_next = y_next + 1;
            return true;
        }

    if (in_dir == west)
        if (accepted_west(y_next, x_next - 1, in_dir)) {
            x_next = x_next - 1;
            return true;
        }

    return false;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[64];
    char line[256];
    u_int32_t x;
    u_int32_t y;
    u_int32_t x_next = 0; // Next
    u_int32_t y_next = 0;
    u_int32_t x_s_start = 0;
    u_int32_t y_s_start = 0;
    u_int32_t x_max;
    u_int32_t y_max = 1;
    u_int32_t steps;
    int len;
    u_int64_t total_value = 0;
    Direction dir;

    memset(maze, 0, sizeof(maze));
    strcpy(file_name, "2023/p10-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            len = strlen(line);
            for (x = 0; x < len; x++) {
                if (line[x] == '\n')
                    break;
                maze[y_max][x + 1] = line[x];
            }
            y_max++;
        }
        x_max = x;

        for (x_s_start = 1; x_s_start <= x_max; x_s_start++) {
            for (y_s_start = 1; y_s_start <= x_max; y_s_start++) {
                if (maze[y_s_start][x_s_start] == 'S')
                    goto found;
            }
        }

found:
        printf("Starting position: [%u][%u]\n", y_s_start, x_s_start);

        y_next = y_s_start;
        x_next = x_s_start;

        if (accepted_north(y_s_start - 1, x_s_start, dir))
            dir = north;
        else if (accepted_east(y_s_start, x_s_start + 1, dir))
            dir = east;
        else if (accepted_south(y_s_start + 1, x_s_start, dir))
            dir = south;
        else if (accepted_west(y_s_start, x_s_start - 1, dir))
            dir = west;

        printf("Starting position: [%u][%u] heading in the direction %s\n", y_s_start, x_s_start, dir_to_str(dir));

        steps = 0;
        while (true) {
            printf("[%u][%u]", y_next, x_next);
            if (find_next(y_next, x_next, dir)) {
                if (y_next == y_s_start && x_next == x_s_start) {
                    printf(" COMPLETED LOOP\n");
                    steps++;
                    break;
                }
                printf(" --> [%u][%u] going %s\n",y_next, x_next, dir_to_str(dir));
            }
            else {
                printf("ERROR\n");
                break;
            }
            steps++;
        }

        fclose(file);
    }

    printf("Furthest point %u/2 = %u\n", steps, steps/2);

    return 0;
}
