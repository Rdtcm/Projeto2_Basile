/*
-------------------------------
Nome:
RA:
-------------------------------
Nome:Renan Horochk de Andrade
RA:10438120
-------------------------------
Nome:Ryan Vinicius Ledo
RA:10352727
-------------------------------
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct
    {
        char letra;
        float frequencia;
    }LetraFrequencia;

typedef struct 
    {
        char nome[20];
        LetraFrequencia letras[26];
    }Idiomas;

void limpar_entrada(char entrada[]) {
    for (int i = 0; i < strlen(entrada); i++) {
        entrada[i] = toupper(entrada[i]);
    }
}

float calcular_probabilidade_letra(char letra, char texto[], int tamanho_texto) {
    float contador = 0;
    float contador_de_letras = 0;
    for (int i = 0; i < tamanho_texto; i++)
    {
        if (letra == texto[i])
        {
            contador++;
        }
    }
    for (int i = 0; i < tamanho_texto; i++)
    {
        if (isalpha(texto[i]))
        {
            contador_de_letras++;
        }
    }
    return contador / contador_de_letras;
}


int main(void) {
    // populando as estruturas com os dados das probabilidades
    Idiomas idiomas[2] = {
        {
            "Portugues",
            {
                {'A', 14.63}, {'B', 1.04}, {'C', 3.88}, {'D', 4.99}, {'E', 12.57},
                {'F', 1.02}, {'G', 1.30}, {'H', 1.28}, {'I', 6.18}, {'J', 0.40},
                {'K', 0.02}, {'L', 2.78}, {'M', 4.74}, {'N', 5.05}, {'O', 10.73},
                {'P', 2.52}, {'Q', 1.20}, {'R', 6.53}, {'S', 7.81}, {'T', 4.34},
                {'U', 4.63}, {'V', 1.67}, {'W', 0.01}, {'X', 0.21}, {'Y', 0.01}, 
                {'Z', 0.47}
            }
        },
        {
            "Ingles",
            {
                {'A', 8.17}, {'B', 1.49}, {'C', 2.78}, {'D', 4.25}, {'E', 12.70},
                {'F', 2.23}, {'G', 2.02}, {'H', 6.09}, {'I', 6.97}, {'J', 0.15},
                {'K', 0.77}, {'L', 4.03}, {'M', 2.41}, {'N', 6.75}, {'O', 7.51},
                {'P', 1.93}, {'Q', 0.10}, {'R', 5.99}, {'S', 6.33}, {'T', 9.06},
                {'U', 2.76}, {'V', 0.98}, {'W', 2.36}, {'X', 0.15}, {'Y', 1.97}, 
                {'Z', 0.07}
            }
        }
    };

    // pegando a entrada do cidadao
    char texto[2000];

    printf("Informe o texto: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0';
    limpar_entrada(texto);

    // calculando as probabilidades de cada letra no texto
    char letras_verificadas[26] = {0};
    int tamanho_texto = strlen(texto);
    LetraFrequencia probabilidades[26];
    int j = 0;

    for (int i = 0; i < tamanho_texto; i++)
    {
        char letra = texto[i];
        if (isalpha(letra) && strchr(letras_verificadas, letra) == NULL) // letra nao foi verificada
        {          
            float probabilidade = calcular_probabilidade_letra(letra, texto, tamanho_texto);
            probabilidades[j].letra = letra;
            probabilidades[j].frequencia = probabilidade;
            letras_verificadas[j] = letra;
            j++; 
        }
    }

    // Calculando a diferenca absoluta das probabilidades de cada idioma comparado a probabilidade no texto
    float soma_dif_pt = 0.0f;
    float soma_dif_en = 0.0f;

    for (int i = 0; i < j; i++)
    {
        char letra = probabilidades[i].letra;
        int indice = letra - 'A';

        float probabilidade_texto = probabilidades[i].frequencia;
        float probabilidade_portugues = idiomas[0].letras[indice].frequencia / 100.0f;
        float probabilidade_ingles = idiomas[1].letras[indice].frequencia / 100.0f;

        float diferenca_absoluta_portugues = fabs(probabilidade_texto - probabilidade_portugues);
        float diferenca_absoluta_ingles = fabs(probabilidade_texto - probabilidade_ingles);

        soma_dif_pt += diferenca_absoluta_portugues;
        soma_dif_en += diferenca_absoluta_ingles;
    }

    printf("Idioma mais provavel: %s\n", (soma_dif_pt < soma_dif_en) ? "Portugues" : "Ingles");

    return 0;
}