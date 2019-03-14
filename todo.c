#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

/*
    TODO Program

    Takes a daily list of todo items
    Displays on command line
    Option to restart list for a new day
    Notes for each item
    Items can be finished

    FUTURE:
        Plan out by date
*/

// Definitions
#define MAX_LENGTH 255 // Max length to be used for strings

// Structures
struct item {
    char name[MAX_LENGTH];
    char notes[MAX_LENGTH];
};

struct day {
    struct item list[3];
    //char date[MAX_LENGTH];
};

// Forward Declarations
void collect_items();
void print_items();
void write_file();
void cross_item();
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
        else if(strcmp((char*) argv[1], "-c") == 0) {
            if(load_file(today)) print_items(today);
            cross_item(today);
        }
        else printf("Invalid parameter, use -h for a list of acceptable parameters\n");
    }
    else printf("todo must be passed with a parameter:\n    -n    Create new day\n    -p    Print items\n    -h    Show this dialogue\n\n");
}

// Write items to a given struct day
void collect_items(struct day day)  {
    printf("Enter the name of the first item:\n");
    fgets(day.list[0].name, MAX_LENGTH, stdin);
    printf("Enter notes for this item:\n");
    fgets(day.list[0].notes, MAX_LENGTH, stdin);
    printf("Enter the name of the second item:\n");
    fgets(day.list[1].name, MAX_LENGTH, stdin);
    printf("Enter notes for this item:\n");
    fgets(day.list[1].notes, MAX_LENGTH, stdin);
    printf("Enter the name of the third item:\n");
    fgets(day.list[2].name, MAX_LENGTH, stdin);
    printf("Enter notes for this item:\n");
    fgets(day.list[2].notes, MAX_LENGTH, stdin);

    write_file(day); //Write new items to file
}

// Places tick next to item
void cross_item(struct day day) {
    int choice = 0;
    char temp[MAX_LENGTH];

    printf("Which item would you like to tick off?\n");
    scanf("%d", &choice);
    choice--;
    
    strcpy(temp, day.list[choice].name);
    strcpy(day.list[choice].name, "✓ ");
    printf("day: %s, temp: %s\n", day.list[choice].name, temp);
    strcat(day.list[choice].name, temp);

    write_file(day);
}

// Print items from a given struct day
void print_items(struct day day) {
    printf("\n");
    printf("    1: %s", day.list[0].name);
    if(strcmp(day.list[0].notes, "\n") != 0) printf("        ↳ %s", day.list[0].notes);
    printf("    2: %s", day.list[1].name);
    if(strcmp(day.list[1].notes, "\n") != 0) printf("        ↳ %s", day.list[1].notes);
    printf("    3: %s", day.list[2].name);
    if(strcmp(day.list[2].notes, "\n") != 0) printf("        ↳ %s", day.list[2].notes);
}

// Write a given struct day to file
void write_file(struct day day) {
    FILE *file = fopen("/home/rayray/.local/share/today.txt", "w+");

    // Print each item's name to file
    fprintf(file, "%s", day.list[0].name);
    fprintf(file, "%s", day.list[0].notes);
    fprintf(file, "%s", day.list[1].name);
    fprintf(file, "%s", day.list[1].notes);
    fprintf(file, "%s", day.list[2].name);
    fprintf(file, "%s", day.list[2].notes);
    
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
        fgets(day.list[0].notes, MAX_LENGTH, file);
        fgets(day.list[1].name, MAX_LENGTH, file);
        fgets(day.list[1].notes, MAX_LENGTH, file);
        fgets(day.list[2].name, MAX_LENGTH, file);
        fgets(day.list[2].notes, MAX_LENGTH, file);

        //fgets(day.date, MAX_LENGTH, file);
        fclose(file);
        return 1;
    }
    return 0;
}
