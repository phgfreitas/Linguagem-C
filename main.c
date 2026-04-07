#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "conversao.h"

#define n 5

//função para imprimir os valores hexadecimais do arquivo em binário
void imprime_binario(unsigned int valor, int num_bits) {
    for (int i = num_bits - 1; i >= 0; i--) {
        int bit = (valor >> i) & 1;
        printf("%d", bit);
    }
}

//função para passar o valor lido do arquivo(ASCII) para valores numericos, visto que a leitura do fgetc e em ASCII
unsigned char char_para_hex(int c) {
    c = toupper(c);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

int main() {
    //vetor para armazenar na struct (contida na biblioteca conversao.h) metade do valor de uma palavra do que é lido no arquivo
    half_char vet[n];
    
    FILE *file = fopen("hexa.txt", "r");

    if (file == NULL) {
        printf("erro ao abrir arquivo.\n");
        return 1;
    }

    int c, i = 0;
    //registro de cada caractere da palavra escrita no arquivo
    while ((c = fgetc(file)) != EOF && i < n) {
        if (isxdigit(c)) {
            vet[i].hexa = char_para_hex(c);
            i++;
        }
    }
    fclose(file);

    if (i >= 4) {
        //struct da biblioteca conversao.h com tamanho de vetor para receber o particionamento em binario para cada divisão da instrução determinada para a arquitetura
        InstrucaoTipoI res = particionar_tipo_i(vet);
        
        printf("--- Instrucao Decodificada (Em Binario) ---\n");
        
        printf("Imediato (6 bits): ");
        imprime_binario(res.imediato, 6);
        printf("\n");
        
        printf("RS1      (3 bits): ");
        imprime_binario(res.rs1, 3);
        printf("\n");
        
        printf("RD       (3 bits): ");
        imprime_binario(res.rd, 3);
        printf("\n");
        
        printf("Opcode   (4 bits): ");
        imprime_binario(res.opcode, 4);
        printf("\n\n");
        //fim da impressão do particionamento dos bits e codigo binário armazenado em cada
        // desassemblador
        imprimir_assembly(res);
    }

    return 0;
}