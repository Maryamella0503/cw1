#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

// Function to compare two FitnessData records for qsort
int compareRecords(const void *a, const void *b) {
    return ((FitnessData *)b)->steps - ((FitnessData *)a)->steps;
}

int main() {
    // Ask the user for a filename
    char filename[100];
    printf("Enter filename: ");
    scanf("%s", filename);

    // Check if the file can be opened
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: invalid file\n");
        return 1;
    }

    // Read data from the file
    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }

    // Allocate memory for FitnessData array
    FitnessData *data = (FitnessData *)malloc(count * sizeof(FitnessData));
    rewind(file);

    // Populate the FitnessData array
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        tokeniseRecord(line, ',', data[i].date, data[i].time, &data[i].steps);
        i++;
    }

    // Close the file
    fclose(file);

    // Sort the data in descending order of steps
    qsort(data, count, sizeof(FitnessData), compareRecords);

    // Write the sorted data to a new file with .tsv extension
    strcat(filename, ".tsv");
    file = fopen(filename, "w");
    for (int j = 0; j < count; j++) {
        fprintf(file, "%s\t%s\t%d\n", data[j].date, data[j].time, data[j].steps);
    }

    // Close the file
    fclose(file);

    // Free allocated memory
    free(data);

    return 0;
}
