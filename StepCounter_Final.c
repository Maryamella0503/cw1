#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

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



// Complete the main function
int main() {
        FITNESS_DATA data_array[100000]; 
        int totalRecords = 0;
        char choice;
        FILE*file;
        char user_file[1000];
        int buffer_size = 1000;
        char line_buffer[buffer_size];
        int line_count = 0;

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
            case 'a':
                printf("Input Filename: ");
                scanf("%s", user_file);

                file = fopen(user_file, "r");
                if (user_file == NULL){
                printf("Error: could not open file\n");
                return 1;
                }
                fclose(file);
                break;

            case 'B':
                while (fgets(line_buffer, buffer_size, file) != NULL) {
                    line_count++;
                }
                printf("Total Records: %i\n", line_count);
                fclose(file);
                break;
            case 'C':
                
                break;
            case 'D':
                
                break;
            case 'E':
                
                break;
            case 'F':
                
                break;
            case 'Q':
                printf("Program returns 0 & exits\n");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
    
        } while (choice != 'A' && choice != 'a');
    return 0;
    }
