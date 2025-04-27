#ifndef KNN_H
#define KNN_H

#include "data_utils.h" // Importa a struct DATA

// Definição da estrutura do KNN
struct KNN
{
    int k;                      // Número de vizinhos
    struct DATA* train_data;     // Ponteiro para dados de treino
    int train_size;              // Número de amostras de treino
};

// Cria e inicializa o KNN
struct KNN* create_knn(int k);

// Treina o KNN (aponta para os dados)
void knn_fit(struct KNN* knn, struct DATA* train_data, int length_data);

// Faz uma previsão
int knn_predict(struct KNN* knn, double* sample);

#endif // KNN_H
