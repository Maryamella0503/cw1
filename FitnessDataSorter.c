#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

int compareFitnessData(const void *a, const void *b) {
    FitnessData *fitnessDataA = (FitnessData *)a;
    FitnessData *fitnessDataB = (FitnessData *)b;

    int comparison = strcmp(fitnessDataA->date, fitnessDataB->date);
    if (comparison != 0) {
        return comparison;
    }

    comparison = strcmp(fitnessDataA->time, fitnessDataB->time);
    if (comparison != 0) {
        return comparison;
    }

    return (fitnessDataA->steps - fitnessDataB->steps);
}

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

int compare(const void *a, const void *b) {
    FitnessData *recordA = (FitnessData *)a;
    FitnessData *recordB = (FitnessData *)b;
    return recordB->steps - recordA->steps;
}


int main() {
    char filename[250];
    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
    printf("Error: could not open file.\n");
    return 1;
    }
    
    FitnessData fitnessDataArray[100];
    int numberOfRecords = 0;

    char record[200];
    while (fgets(record, sizeof(record), file)) {
        char *date, *time, *stepsStr;
        int steps;

        tokeniseRecord(record, ' ', &date, &time, &steps);

}
}
}