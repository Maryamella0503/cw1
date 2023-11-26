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
int tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                if (sscanf(ptr, "%d", steps) != 1) {
                    printf("Error: invalid steps data\n");
                    return 1;
                }
                return 0;
            }
        }
    }
    printf("Error: invalid record format\n");
    return 1;
}


int main() {
    char filename[100];
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: invalid file\n");
        return 1;
    }

    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }


    fclose(file);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: failed to reopen file\n");
        return 1;
    }

    FitnessData data[100000];  
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (tokeniseRecord(line, ',', data[i].date, data[i].time, &data[i].steps) != 0) {
            printf("Skipping invalid record\n");
            continue;
        }
        i++;
    }

    fclose(file);

    for (int m = 0; m < count - 1; m++) {
        for (int n = 0; n < count - m - 1; n++) {
            if (data[n].steps < data[n + 1].steps) {
                FitnessData temp = data[n];
                data[n] = data[n + 1];
                data[n + 1] = temp;
            }
        }
    }

    strcat(filename, ".tsv");
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: could not create output file\n");
        return 1;
    }

    for (int j = 0; j < count; j++) {
        fprintf(file, "%s\t%s\t%d\n", data[j].date, data[j].time, data[j].steps);
    }

    fclose(file);

    return 0;
}
