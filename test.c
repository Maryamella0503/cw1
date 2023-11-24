#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"
#include <math.h>


// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

    }
    FILE* open_file(char filename[], char mode[]) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        return 0;
    }
    }


// Complete the main function
int main() {
        FITNESS_DATA data_array[100000]; 
        int mincount = 0;
        int maxcount = 0;
        int totalsteps = 0;
        int longestStart = -1;
        int longestEnd = -1;
        int currentStart = -1;
        char choice;
        FILE*file;
        char user_file[1000];
        int buffer_size = 1000;
        char line_buffer[buffer_size];
        int line_count = 0;
        int filefound = 0;

        while (1){
        printf("A: Input Filename:\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Exit\n");

        printf("Select an option: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
            case 'a': {
                printf("Input Filename: ");
                scanf("%s", user_file);
            
                file = open_file(user_file, "r");
                if (file == NULL){
                printf("Error: could not open file\n");
                return 1;
                }
                while (fgets(line_buffer, buffer_size, file) != NULL) {
                char steps[30]; 
                tokeniseRecord(line_buffer, ",", data_array[line_count].date, data_array[line_count].time, steps);
                data_array[line_count].steps = atoi(steps);
                    line_count++;
                }
                fclose(file); 
                printf("File read successfully!\n");      
                filefound = 1;
                break;
            }

            case 'B':
            case 'b': {
                file = fopen(user_file, "r");
                if (file == NULL) {
                    printf("Error: could not open file\n");
                break;
                }
                    line_count = 0;
                    while (fgets(line_buffer, buffer_size, file) != NULL) {
                        line_count++;
                    }
                    fclose(file);
                    printf("Total Records: %i\n", line_count);
                break;
            }
            case 'C':
            case 'c':{
                int minsteps = data_array[0].steps;

                for (int i = 1; i < line_count; i++) {
                if (data_array[i].steps < minsteps) {
                    minsteps = data_array[i].steps;
                    mincount = i;
                }
                }
                printf("Fewest steps: %s %s\n", data_array[mincount].date, data_array[mincount].time);
                break;
            }
            case 'D':
            case 'd':{
                int maxsteps = data_array[0].steps;

                for (int i = 1; i < line_count; i++) {
                if (data_array[i].steps > maxsteps) {
                    maxsteps = data_array[i].steps;
                    maxcount = i;
                }
                }
                printf("Largest steps: %s %s\n", data_array[maxcount].date, data_array[maxcount].time);
                break;
            }
            case 'E':
            case 'e':{
                totalsteps = 0;
                for (int i = 0; i < line_count; i++) {
                totalsteps += data_array[i].steps;
                }

                double mean = (double)totalsteps / line_count;
                printf("Mean step count: %d\n", (int)mean);
                break;
            }
            case 'F':
            case 'f':{
                for (int i = 0; i < line_count; i++){
                    if (data_array[i].steps > 500){
                        if (currentStart == -1){
                            currentStart = i;
                        }
                    } else{
                        if (currentStart != -1){
                            if (i - currentStart > longestEnd - longestStart){
                                longestStart = currentStart;
                                longestEnd = i;
                            }
                        currentStart = -1;
                        }
                    }
                }

                if (currentStart != -1 && line_count - currentStart > longestEnd - longestStart){
                    longestStart = currentStart;
                    longestEnd = line_count;
                }

                if (longestStart != -1 && longestEnd != -1){
                    printf("Longest period start: %s %s\n", data_array[longestStart].date, data_array[longestStart].time);
                    printf("Longest period end: %s %s\n", data_array[longestEnd - 1].date, data_array[longestEnd - 1].time);
                }
                break;
            }
            case 'Q':
            case 'q': {
                printf("Program returns 0 & exits\n");
                return 0;
            }
            default:{
                printf("Invalid option. Please try again.\n");
                break;
            } 
        }
        }
        return 0;
    }







