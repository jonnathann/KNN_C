#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "knn.h"
#include "data_utils.h"

// Struct interna para armazenar distância + label
struct DistanceLabel {
    double distance;
    int label;
};

// Função de comparação para o qsort
int compare_distances(const void* a, const void* b) {
    struct DistanceLabel* dl1 = (struct DistanceLabel*)a;
    struct DistanceLabel* dl2 = (struct DistanceLabel*)b;
    if (dl1->distance < dl2->distance) return -1;
    else if (dl1->distance > dl2->distance) return 1;
    else return 0;
}

// Função para criar o KNN
struct KNN* create_knn(int k) {
    struct KNN* knn = (struct KNN*)malloc(sizeof(struct KNN));
    knn->k = k;
    knn->train_data = NULL;
    knn->train_size = 0;
    return knn;
}

// Função para treinar o KNN (armazenar os dados)
void knn_fit(struct KNN* knn, struct DATA* data, int length_data) {
    knn->train_data = data;
    knn->train_size = length_data;
}

// Função para fazer a predição
int knn_predict(struct KNN* knn, double* sample) {
    struct DistanceLabel* distances = (struct DistanceLabel*)malloc(knn->train_size * sizeof(struct DistanceLabel));

    // Calcula todas as distâncias
    for (int i = 0; i < knn->train_size; i++) {
        double sum = 0.0;
        for (int j = 0; j < knn->train_data[i].num_dimensions; j++) {
            double diff = sample[j] - knn->train_data[i].features[j];
            sum += diff * diff;
        }
        distances[i].distance = sqrt(sum);
        distances[i].label = knn->train_data[i].label;
    }

    // Ordena pelo qsort (menores distâncias primeiro)
    qsort(distances, knn->train_size, sizeof(struct DistanceLabel), compare_distances);

    // Votação: contar quantos votos cada label recebeu
    // (Aqui vamos assumir que os labels são pequenos inteiros positivos, tipo 0, 1, 2, etc)
    int max_label = 0;
    for (int i = 0; i < knn->k; i++) {
        if (distances[i].label > max_label) {
            max_label = distances[i].label;
        }
    }

    int* votes = (int*)calloc(max_label + 1, sizeof(int));
    for (int i = 0; i < knn->k; i++) {
        votes[distances[i].label]++;
    }

    // Achar o label mais votado
    int best_label = 0;
    int best_votes = 0;
    for (int i = 0; i <= max_label; i++) {
        if (votes[i] > best_votes) {
            best_votes = votes[i];
            best_label = i;
        }
    }

    // Liberar memória auxiliar
    free(distances);
    free(votes);

    return best_label;
}
