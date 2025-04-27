#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "csv_utils.h"
#include "data_utils.h"
#include "knn.h" 

#define MAX_LINE_LENGTH 1024

// Função para gerar um número aleatório
int rand_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Função para embaralhar os dados (embaralhar o vetor)
void shuffle_data(struct DATA* dataset, int num_samples) {
    srand(time(NULL));  // Inicializa a semente do gerador de números aleatórios
    
    for (int i = 0; i < num_samples; i++) {
        int j = rand_int(i, num_samples - 1);
        
        // Trocar os elementos de índice i e j
        struct DATA temp = dataset[i];
        dataset[i] = dataset[j];
        dataset[j] = temp;
    }
}

// Função para salvar os dados em um arquivo CSV
void save_csv(const char* filename, struct DATA* dataset, int num_samples, int num_dimensions) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar: %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < num_samples; i++) {
        fprintf(file, "%d,", i+1);  // ID (pode ser qualquer coisa, estou usando a linha como ID)
        for (int j = 0; j < num_dimensions; j++) {
            fprintf(file, "%.6f", dataset[i].features[j]);
            if (j < num_dimensions - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, ",%d\n", dataset[i].label); // Label
    }

    fclose(file);
}

// Função para dividir o dataset em treino e teste
void split_dataset(struct DATA* dataset, int num_samples, int num_dimensions, float train_ratio) {
    // Embaralhar os dados antes de dividir
    shuffle_data(dataset, num_samples);

    int train_size = (int)(num_samples * train_ratio);
    int test_size = num_samples - train_size;

    struct DATA* train_set = (struct DATA*) malloc(train_size * sizeof(struct DATA));
    struct DATA* test_set = (struct DATA*) malloc(test_size * sizeof(struct DATA));

    // Preencher os conjuntos de treino e teste
    for (int i = 0; i < train_size; i++) {
        train_set[i] = dataset[i];
    }
    for (int i = 0; i < test_size; i++) {
        test_set[i] = dataset[train_size + i];
    }

    // Salvar os dados nos arquivos CSV
    save_csv("data/processed/train_data.csv", train_set, train_size, num_dimensions);
    save_csv("data/processed/test_data.csv", test_set, test_size, num_dimensions);

    // Liberar memória
    free(train_set);
    free(test_set);
}

int main() {
    // Treinamento do KNN

    int num_samples = 0;
    int num_dimensions = 4;  // Número de características (Iris = 4)

    // Ler os dados
    struct DATA* dataset = read_csv("data/external/Iris.csv", &num_samples, num_dimensions);

    // Embaralhar e dividir em treino/teste
    //split_dataset(dataset, num_samples, num_dimensions, 0.8);

    // --- Agora carregar os dados processados para treino e teste ---
    int train_size = 0, test_size = 0;
    struct DATA* train_set = read_csv("data/processed/train_data.csv", &train_size, num_dimensions);
    struct DATA* test_set = read_csv("data/processed/test_data.csv", &test_size, num_dimensions);

    // Criar e treinar o KNN
    struct KNN* knn = create_knn(4); // Exemplo, k=4
    knn_fit(knn, train_set, train_size);

    // Arrays para armazenar as previsões e as probabilidades
    int labels[test_size];  // Armazenar as previsões dos labels
    double max_probabilities[test_size];  // Armazenar as probabilidades máximas para cada previsão

    // Testar o KNN no conjunto de teste
    for (int i = 0; i < test_size; i++) {
        double probabilities[3];  // Supondo que temos 3 classes no máximo
        int predicted = knn_predict(knn, test_set[i].features, probabilities);
        
        // Armazenar o rótulo previsto
        labels[i] = predicted;
        
        // Encontrar a maior probabilidade
        double max_prob = probabilities[0];
        for (int j = 1; j < 3; j++) {
            if (probabilities[j] > max_prob) {
                max_prob = probabilities[j];
            }
        }
        
        max_probabilities[i] = max_prob;  // Armazenar a probabilidade como percentual
    }

    // Imprimir as labels reais, as labels previstas e as probabilidades
    printf("real: [");
    for (int i = 0; i < test_size; i++) {
        printf("%d", test_set[i].label);  // Imprimir a label real
        if (i < test_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    printf("prev: [");
    for (int i = 0; i < test_size; i++) {
        printf("%d", labels[i]);  // Imprimir a label prevista
        if (i < test_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    printf("prob: [");
    for (int i = 0; i < test_size; i++) {
        printf("%.2f", max_probabilities[i]);  // Imprimir a maior probabilidade em formato percentual
        if (i < test_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // Calcular e imprimir a acurácia
    int correct = 0;
    for (int i = 0; i < test_size; i++) {
        if (labels[i] == test_set[i].label) {
            correct++;
        }
    }

    printf("Acurácia: %.2f%%\n", (100.0 * correct) / test_size);

    // Liberar memória
    for (int i = 0; i < num_samples; i++) {
        free(dataset[i].features);
    }
    free(dataset);

    for (int i = 0; i < train_size; i++) {
        free(train_set[i].features);
    }
    free(train_set);

    for (int i = 0; i < test_size; i++) {
        free(test_set[i].features);
    }
    free(test_set);

    free(knn);

    return 0;
}
