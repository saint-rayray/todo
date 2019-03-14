#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

/*
    TODO Program

    Takes a daily list of todo items
    Displays on command line
    Option to restart list for a new day

    FUTURE:
        Notes for items
        Plan out by date
        Items can be checked off
*/

// Definitions
#define MAX_LENGTH 255 // Max length to be used for strings

// Structures
struct item {
    char name[MAX_LENGTH];
};

struct day {
    struct item list[3];
    //char date[MAX_LENGTH];
};

// Forward Declarations
void collect_items();
void print_items();
void write_file();
int load_file();

// Program
int main(int argc, char** argv[]) {
    struct day *today = malloc(sizeof(struct day));
    
    printf("\e[1;1H\e[2J"); //Clear console
    printf("todo:\n");
    
    // Take parameters
    if(argc > 3) printf("Too many arguments\n");
    else if(argc == 2) {
        if(strcmp((char*) argv[1], "-p") == 0) {
            if(load_file(today)) print_items(today);
        }
        else if(strcmp((char*) argv[1], "-n") == 0) collect_items(today);
        else if(strcmp((char*) argv[1], "-h") == 0) printf("todo must be passed with a parameter\n    -n    Create new day\n    -p    Print items\n    -h    Show this dialogue\n\n");
        else printf("Invalid parameter, use -h for a list of acceptable parameters\n");
    }
    else printf("todo must be passed with a parameter:\n    -n    Create new day\n    -p    Print items\n    -h    Show this dialogue\n\n");
}

// Write items to a given struct day
void collect_items(struct day day)  {
    printf("Enter the name of the first item\n");
    fgets(day.list[0].name, MAX_LENGTH, stdin);
    printf("Enter the name of the second item\n");
    fgets(day.list[1].name, MAX_LENGTH, stdin);
    printf("Enter the name of the third item\n");
    fgets(day.list[2].name, MAX_LENGTH, stdin);

    write_file(day); //Write new items to file
}

// Print items from a given struct day
void print_items(struct day day) {
    printf("\n");
    printf("    1: %s", day.list[0].name);
    printf("    2: %s", day.list[1].name);
    printf("    3: %s\n", day.list[2].name);
}

// Write a given struct day to file
void write_file(struct day day) {
    FILE *file = fopen("/home/rayray/.local/share/today.txt", "w+");

    // Print each item's name to file
    fprintf(file, "%s", day.list[0].name);
    fprintf(file, "%s", day.list[1].name);
    fprintf(file, "%s", day.list[2].name);
    
    // Add date to file
    //time_t rawtime;
    //struct tm *info;

    //TODO
    //time( &rawtime );
    //info = localtime( &rawtime );
    //char buffer[MAX_LENGTH]; 
    
    //strftime(buffer, MAX_LENGTH, "%D", tm); 
    //fprintf(file, "%s", day.date);
    fclose(file);
}

// Load a file into a struct day, returns 0 if loading fails
int load_file(struct day day) {
    FILE *file = fopen("/home/rayray/.local/share/today.txt", "r+");
    
    if(file == NULL) {
        printf("Failed to open file\n");
    }
    else {
        fgets(day.list[0].name, MAX_LENGTH, file);
        fgets(day.list[1].name, MAX_LENGTH, file);
        fgets(day.list[2].name, MAX_LENGTH, file);
        //fgets(day.date, MAX_LENGTH, file);
        fclose(file);
        return 1;
    }
    return 0;
}
