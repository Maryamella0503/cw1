#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



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
    char* filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int buffer_size = 600;
    char line_buffer[buffer_size];
    int line_count;
    line_count = 0;

    FITNESS_DATA data_array[3];

    while (fgets(line_buffer, buffer_size, file) != NULL) {
        char date[11];
        char time[6];
        char steps[10]; 
    
        tokeniseRecord(line_buffer, ",", date, time, steps);
        
        strcpy(data_array[line_count].date, date);
        strcpy(data_array[line_count].time, time);
        data_array[line_count].steps = atoi(steps);
        line_count++;

    }

    printf("Number of records in file: %i \n", line_count);
    
    int i;
    for (i=0; i < 3; i++){
        printf("Record %d: %s/%s/%d\n", i+1, data_array[i].date, data_array[i].time, data_array[i].steps);
    }

    return 0;
}