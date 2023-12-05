#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>
#include <algorithm>
#include <list>
#include <string>
#include <iostream>

using namespace std;

class Dir;

class File {
    public:
    File(string in_name, int in_size);
    string name;
    Dir *parent;
    int file_size;
};

File::File(string in_name, int in_size) :
name(in_name),
file_size(in_size)
{};

class Dir {
    public:
    Dir(string in_name, Dir* in_parent);
    std::list<File *> files;
    std::list<Dir *> dirs;
    string name;
    int total_size;
    Dir *parent;
};

Dir::Dir(string in_name, Dir * in_parent) :
name(in_name),
total_size(0),
parent(in_parent)
{};

int total_size = 0;
int closest_size = 0;

void dir_to_free(Dir *dir, int comp_size)
{
    Dir *iter_dir;
    File *iter_file;

    for (auto iter_dir : dir->dirs) {
        if (iter_dir->total_size > comp_size)
            if (iter_dir->total_size < closest_size)
                closest_size = iter_dir->total_size;
        dir_to_free(iter_dir, comp_size);
    }

    if (dir->total_size > comp_size)
        if (dir->total_size < closest_size)
            closest_size = dir->total_size;

}

int df(Dir *dir)
{
    Dir *iter_dir;
    File *iter_file;

    for (auto iter_dir : dir->dirs) {
        dir->total_size += df(iter_dir);
    }

    for (auto iter_file : dir->files) {
        dir->total_size += iter_file->file_size;
    }

    if (dir->total_size <= 100000)
        total_size += dir->total_size;

    return dir->total_size;
}

Dir *ls_cmd(FILE * file, Dir *dir)
{
    int value;
    char line[32];
    char arg[32];
    Dir *new_dir;
    File *new_file;
    int offset;

    offset = ftell(file);
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "$", 1) == 0) {
            fseek(file, offset, SEEK_SET);
            break;
        }
        if (sscanf(line, "dir %s", arg) == 1) {
            new_dir = new Dir(arg, dir);
            dir->dirs.push_back(new_dir);
        }
        if (sscanf(line, "%d %s", &value, arg) == 2) {
            new_file = new File(arg, value);
            dir->files.push_back(new_file);
        }
        offset = ftell(file);
    }

    return dir;
}

Dir *cd_cmd(FILE * file, Dir *dir, char *arg)
{
    Dir *iter_dir;
    string comp_str(arg);

    if (strncmp(arg, "..", 2) == 0) {
        if (dir->parent != NULL) {
            return dir->parent;
        }
        else {
            return dir; // At root already
        }
    }
    else if (strcmp(arg, "/") == 0) {
        while (dir->parent != NULL)
            dir = dir->parent;
    }
    else {
        for (auto iter_dir : dir->dirs) {
            if (iter_dir->name.compare(comp_str) == 0)
                return iter_dir;
        }
    }

    return dir;
}

Dir *parse(FILE * file, char *line, Dir *dir)
{
    char arg[32];

    if (strncmp(line, "$ ls", 4) == 0) {
        dir = ls_cmd(file, dir);
    }
    else if (sscanf(line, "$ cd %s", arg) == 1) {
        dir = cd_cmd(file, dir, arg);
    }

    return dir;
}

int main(int argc, char *argv[])
{
    FILE *file;
    char file_name[32];
    int opt;
    char line[32];
    char *lineptr;
    Dir *root;
    Dir *dir;
    int grand_total;
    int to_free_up;

    strcpy(file_name, "puzzle-07-example-input.txt");

    while ((opt = getopt(argc, argv, "l:f:")) != -1) {
        switch (opt) {
            case 'f':
                strncpy(file_name, optarg, sizeof(file_name));
            break;
        }
    }

    root = new Dir("/", NULL);
    dir = root;
    lineptr = line;
    if ((file = fopen(file_name, "r")) != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            if ((dir = parse(file, line, dir)) == NULL) {
                cout << "ERROR";
            }
        }

        grand_total = df(root);
        to_free_up = 30000000 - (70000000 - grand_total);
        cout << "Grand total size: " << grand_total << std::endl;
        cout << "Total of small directories: " << total_size << std::endl;
        cout << "Now we need to free up " << to_free_up << std::endl;
        closest_size = 999999999;
        dir_to_free(root, to_free_up);
        cout << "Size of the directory is: " << closest_size << std::endl;

        fclose(file);
    }
    else {
        printf("ERROR: Could not open file %s\n", file_name);
        return -1;
    }

    return 0;
}
