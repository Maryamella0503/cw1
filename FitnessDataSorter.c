#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;


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

// I used the comparator() function from my understanding of this website: https://www.geeksforgeeks.org/comparator-function-of-qsort-in-c/
int compareRecords(const void *a, const void *b) {
    return ((FitnessData *)b)->steps - ((FitnessData *)a)->steps;
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


    FitnessData *data = (FitnessData *)malloc(count * sizeof(FitnessData));
    rewind(file);  

    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {

        if (tokeniseRecord(line, ',', data[i].date, data[i].time, &data[i].steps) != 0) {
            printf("Skipping invalid record\n");
            continue;
        }
        i++;
    }

    fclose(file);
    // I used qsort() function from my understanding of this website: https://www.educative.io/answers/what-is-the-qsort-function-in-c
    qsort(data, count, sizeof(FitnessData), compareRecords);
    // I used the strcat() function from my understanding of this website: https://www.programiz.com/c-programming/library-function/string.h/strcat
    strcat(filename, ".tsv");

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: could not create output file\n");
        free(data);
        return 1;
    }

    for (int j = 0; j < count; j++) {
        fprintf(file, "%s\t%s\t%d\n", data[j].date, data[j].time, data[j].steps);
    }

    fclose(file);

    free(data);

    return 0;
}

