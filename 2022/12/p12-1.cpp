// Created by Leif Enblom

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <list>
#include <climits>
#include <unistd.h>

using namespace std;

class Vertex {
public:
    Vertex();
    void set_height( char in_height) { height = in_height; };
    char get_height() { return height; };
    void set_x( int in_x) { x = in_x; };
    int get_x() { return x; };
    void set_y( int in_y) { y = in_y; };
    int get_y() { return y; };
    void set_distance( int in_distance) { distance = in_distance; };
    int calculate_distance( Vertex &neighbor);
    void calculate_distance_left( Vertex &neighbor) { dist_left = calculate_distance(neighbor); };
    void calculate_distance_up( Vertex &neighbor) { dist_up = calculate_distance(neighbor); };
    void calculate_distance_right( Vertex &neighbor) { dist_right = calculate_distance(neighbor); };
    void calculate_distance_down( Vertex &neighbor) { dist_down = calculate_distance(neighbor); };
    bool is_start() { if (height == 'S') return true; return false; }
    bool is_end() { if (height == 'E') return true; return false; }
// private:
    char height;
    int x;
    int y;
    int distance;
    bool visited;
    bool path;
    Vertex *prev;
    int dist_left;
    int dist_up;
    int dist_right;
    int dist_down;
};

Vertex::Vertex() :
height(0),
x(0),
y(0),
distance(INT_MAX - 1),
visited(false),
path(false),
prev(0),
dist_left(0),
dist_up(0),
dist_right(0),
dist_down(0)
{
};

int Vertex::calculate_distance( Vertex &neighbor)
{
    int diff;

    diff = neighbor.get_height() - height;
    if (diff <= 1 && diff >= -1) {
        diff = abs(diff);
        return diff;
    }
    else {
        return INT_MAX;
    }
}

static const int MAX_X_VERTICIES = 120;
static const int MAX_Y_VERTICIES = 120;

Vertex verticies[MAX_X_VERTICIES][MAX_Y_VERTICIES];
int distance[MAX_X_VERTICIES][MAX_Y_VERTICIES];

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    char line[256];
    int max_x, max_y = 0;
    int x, y;
    int dir;
    Vertex *start;
    Vertex *end;

    strcpy(file_name, "p12-input.txt");

    if ((file = fopen(file_name, "r")) != NULL) {
        y = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            if (y == 0) max_x = strnlen(line, sizeof(line)) - 1;
            for (x = 0; x < max_x; x++) {
                verticies[x][y].set_height(line[x]);
                verticies[x][y].set_x(x);
                verticies[x][y].set_y(y);
            }
            y++;
        }

        max_y = y;

        for (y = 0; y < max_y; y++) {
            for (x = 0; x < max_x; x++) {
                if (verticies[x][y].is_start()) {
                    start = &verticies[x][y];
                    start->height = 'a';
                }
                if (verticies[x][y].is_end()) {
                    end = &verticies[x][y];
                    start->height = 'z';
                }
                if (x-1 >= 0)
                    verticies[x][y].calculate_distance_left(verticies[x-1][y]);
                else
                    verticies[x][y].dist_left = INT_MAX;
                if (y-1 >= 0)
                    verticies[x][y].calculate_distance_up(verticies[x][y-1]);
                else
                    verticies[x][y].dist_up = INT_MAX;
                if (x+1 < MAX_X_VERTICIES)
                    verticies[x][y].calculate_distance_right(verticies[x+1][y]);
                else
                    verticies[x][y].dist_right = INT_MAX;
                if (y+1 < MAX_Y_VERTICIES)
                    verticies[x][y].calculate_distance_down(verticies[x][y+1]);
                else
                    verticies[x][y].dist_down = INT_MAX;
                // printf("%c", verticies[x][y].get_height());
            }
            // printf("\n");
        }

        Vertex *current = NULL;
        Vertex *min = NULL;
        int xx, yy;
        int alt;
        int mycount;

        if (start != NULL && end != NULL) {
            start->set_distance(0);
            do  {
                mycount++;
                min = NULL;
                for (x = 0; x < max_x; x++) {
                    for (y = 0; y < max_y; y++) {
                        if (verticies[x][y].visited == false) {
                            if (min == NULL) {
                                min = &verticies[x][y];
                            } else {
                                if (verticies[x][y].distance < min->distance) {
                                    min = &verticies[x][y];
                                }
                            }
                        }
                    }
                }

                if (min != NULL) {
                    min->visited = true;

                    if (min->x > 0) {
                        if (verticies[min->x - 1][min->y].visited == false) {
                            alt = verticies[min->x][min->y].distance + verticies[min->x - 1][min->y].dist_left;
                            if (alt < verticies[min->x - 1][min->y].distance) {
                                verticies[min->x - 1][min->y].distance = alt;
                                verticies[min->x - 1][min->y].prev = &verticies[min->x][min->y];
                            }
                        }                    
                    }

                    if (min->x < MAX_X_VERTICIES - 1) {
                        if (verticies[min->x + 1][min->y].visited == false) {
                            alt = verticies[min->x][min->y].distance + verticies[min->x + 1][min->y].dist_right;
                            if (alt < verticies[min->x + 1][min->y].distance) {
                                verticies[min->x + 1][min->y].distance = alt;
                                verticies[min->x + 1][min->y].prev = &verticies[min->x][min->y];
                            }
                        }                    
                    }

                    if (min->y > 0) {
                        if (verticies[min->x][min->y - 1].visited == false) {
                            alt = verticies[min->x][min->y].distance + verticies[min->x][min->y - 1].dist_up;
                            if (alt < verticies[min->x][min->y -1].distance) {
                                verticies[min->x][min->y - 1].distance = alt;
                                verticies[min->x][min->y - 1].prev = &verticies[min->x][min->y];
                            }
                        }                    
                    }

                    if (min->y < MAX_Y_VERTICIES - 1) {
                        if (verticies[min->x][min->y + 1].visited == false) {
                            alt = verticies[min->x][min->y].distance + verticies[min->x][min->y + 1].dist_down;
                            if (alt < verticies[min->x][min->y + 1].distance) {
                                verticies[min->x][min->y + 1].distance = alt;
                                verticies[min->x][min->y + 1].prev = &verticies[min->x][min->y];
                            }
                        }                    
                    }
                }

                printf("\033c");
                for (y = 0; y < max_y; y++) {
                    for (x = 0; x < max_x; x++) {
                        if (verticies[x][y].prev != NULL) {
                            if (verticies[x][y].prev->x < verticies[x][y].x && verticies[x][y].prev->y == verticies[x][y].y)
                                printf("<");
                            else if (verticies[x][y].prev->x > verticies[x][y].x && verticies[x][y].prev->y == verticies[x][y].y)
                                printf(">");
                            else if (verticies[x][y].prev->x == verticies[x][y].x && verticies[x][y].prev->y < verticies[x][y].y)
                                printf("^");
                            else if (verticies[x][y].prev->x == verticies[x][y].x && verticies[x][y].prev->y > verticies[x][y].y)
                                printf("v");
                            else
                                printf("-");        
                        }
                        else {
                            printf("%c", verticies[x][y].height);
                            // printf(".");
                        }
                    }
                    printf("\n");
                }
                printf("mycount: %d\n", mycount);
                getc(stdin);
                // usleep(500000);

            } while (min != NULL);

            for (y = 0; y < max_y; y++) {
                for (x = 0; x < max_x; x++) {
                    if (verticies[x][y].prev != NULL) {
                        if (verticies[x][y].prev->x < verticies[x][y].x && verticies[x][y].prev->y == verticies[x][y].y)
                            printf("<");
                        else if (verticies[x][y].prev->x > verticies[x][y].x && verticies[x][y].prev->y == verticies[x][y].y)
                            printf(">");
                        else if (verticies[x][y].prev->x == verticies[x][y].x && verticies[x][y].prev->y < verticies[x][y].y)
                            printf("^");
                        else if (verticies[x][y].prev->x == verticies[x][y].x && verticies[x][y].prev->y > verticies[x][y].y)
                            printf("v");
                        else
                            printf("-");        
                    }
                    else {
                        printf(".");
                    }
                }
                printf("\n");
            }

            Vertex * current = end;
            // end->prev = &verticies[89][20];
//            end->prev = &verticies[4][2];
            int count = 0;

            while (true) {
                printf("%d:%d --> ", current->x, current->y);
                current->path = true;
                if (count % 10 == 0)
                    printf("\n");
                current = current->prev;
                count++;
                if (current == NULL || (current->x == start->x && current->y == start->y))
                    break;
            }

            printf("Count: %d\n", count);

            // for (y = 0; y < max_y; y++) {
            //     for (x = 0; x < max_x; x++) {
            //         printf("%c", verticies[x][y].height);
            //         if (x < max_x-1 && verticies[x][y].dist_right < 2 && verticies[x][y].dist_right >= 0) {
            //             printf("\033[31;1;1m%d\033[0m", verticies[x][y].dist_right);
            //         }
            //         else {
            //             printf("\033[31;1;1mX\033[0m");
            //         }
            //     }
            //     printf("\n");
            //     for (x = 0; x < max_x; x++) {
            //         if (y < max_y-1 && verticies[x][y].dist_down < 2 && verticies[x][y].dist_right >= 0) {
            //             printf("\033[31;1;1m%d\033[0m", verticies[x][y].dist_down);
            //         }
            //         else {
            //             printf("\033[31;1;1mX\033[0m");
            //         }
            //         printf(" ");
            //     }
            //     printf("\n");
            // }


            for (y = 0; y < max_y; y++) {
                for (x = 0; x < max_x; x++) {
                    if (verticies[x][y].path == true) {
                        printf("\033[31;1;1m%c\033[0m", verticies[x][y].height);
                    }
                    else {
                        printf("%c", verticies[x][y].height);
                    }
                }
                printf("\n");
            }
        }

        fclose(file);
        return 0;
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
