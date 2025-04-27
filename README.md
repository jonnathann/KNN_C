# KNN_C

## Descrição

Este é um projeto de implementação do **K-Nearest Neighbors (KNN)** em C. O algoritmo KNN é um dos mais populares em Machine Learning, utilizado para classificação e regressão. Neste projeto, o KNN é implementado de forma simples e eficiente, com suporte para treinar e testar em conjuntos de dados.

O código foi projetado para ser fácil de entender e pode ser utilizado para trabalhar com conjuntos de dados simples. Ele também é compatível com integração em outros idiomas, como Python e MATLAB.

## Funcionalidades

- Implementação do algoritmo KNN (K-Nearest Neighbors).
- Divisão do conjunto de dados em treino e teste.
- Embaralhamento dos dados antes do treino.
- Cálculo da acurácia do modelo após a previsão.
- Suporte para treinamento de modelos com grandes volumes de dados.

## Como usar

### Pré-requisitos

Certifique-se de ter os seguintes programas instalados:

- **gcc** (compilador C)
- **make** (para automação da compilação)
- **git** (para controle de versão)

### Instalação

1. Clone este repositório para sua máquina local:

    ```bash
    git clone https://github.com/jonnathann/KNN_C.git
    cd KNN_C
    ```

2. Compile o projeto com o comando `make`:

    ```bash
    make
    ```

3. Execute o programa:

    ```bash
    ./build/knn_program
    ```

4. Você verá a acurácia do modelo exibida no terminal.

### Estrutura de diretórios

- **src/**: Contém o código-fonte do projeto.
- **include/**: Contém os arquivos de cabeçalho.
- **data/**: Contém os dados de entrada e saída, incluindo o arquivo CSV com o conjunto de dados Iris.
- **build/**: Contém os arquivos compilados e o executável gerado.
- **Makefile**: Usado para automatizar a compilação do projeto.

## Como funciona

O KNN classifica um ponto de dados com base nos `k` pontos mais próximos do conjunto de dados de treino. O algoritmo calcula a distância entre o ponto de teste e todos os pontos de treino, seleciona os `k` pontos mais próximos e, finalmente, faz a predição com base no "voto" da maioria entre esses pontos.

O projeto está configurado para usar o **Conjunto de Dados Iris**, que é um conjunto de dados amplamente utilizado para testes em problemas de classificação. O modelo é treinado com 80% dos dados e testado com os 20% restantes.

## Contribuindo

Se você deseja contribuir para o projeto, sinta-se à vontade para abrir um *pull request*. Basta seguir estas etapas:

1. Faça um fork deste repositório.
2. Crie uma branch para sua modificação:
   
   ```bash
   git checkout -b minha-modificacao
