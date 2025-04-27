#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_utils.h"
#include "data_utils.h"

#define MAX_LINE_LENGTH 1024

struct DATA* read_csv(const char* filename, int* num_samples, int num_dimensions) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    // Contar quantas linhas
    while (fgets(line, sizeof(line), file)) {
        // Pula a linha se for a linha de zeros
        char temp[MAX_LINE_LENGTH];
        strcpy(temp, line);
        char* token = strtok(temp, ",");
        token = strtok(NULL, ",");  // Pula o ID
        
        int is_zero_line = 1;
        for (int i = 0; i < num_dimensions; i++) {
            if (token == NULL || atof(token) != 0.0) {
                is_zero_line = 0;
                break;
            }
            token = strtok(NULL, ",");
        }
        
        if (!is_zero_line) {
            count++;
        }
    }
    rewind(file);

    // Alocar vetor de struct DATA
    struct DATA* dataset = (struct DATA*) malloc(count * sizeof(struct DATA));
    if (dataset == NULL) {
        printf("Erro de memória.\n");
        fclose(file);
        exit(1);
    }

    int idx = 0;
    while (fgets(line, sizeof(line), file)) {
        char temp[MAX_LINE_LENGTH];
        strcpy(temp, line);
        char* token_check = strtok(temp, ",");
        token_check = strtok(NULL, ",");  // Ignorar o 'Id'

        int is_zero_line = 1;
        for (int i = 0; i < num_dimensions; i++) {
            if (token_check == NULL || atof(token_check) != 0.0) {
                is_zero_line = 0;
                break;
            }
            token_check = strtok(NULL, ",");
        }

        if (is_zero_line) {
            continue; // pula a linha
        }

        char* token = strtok(line, ",");
        token = strtok(NULL, ",");  // Ignorar o 'Id'

        dataset[idx].features = (double*) malloc(num_dimensions * sizeof(double));
        dataset[idx].num_dimensions = num_dimensions;

        int dim = 0;
        while (token != NULL && dim < num_dimensions) {
            dataset[idx].features[dim] = atof(token);
            token = strtok(NULL, ",");
            dim++;
        }

        if (token != NULL) {
            dataset[idx].label = atoi(token);
        }

        idx++;
    }

    fclose(file);

    *num_samples = count;
    return dataset;
}
