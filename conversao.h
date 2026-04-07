#ifndef CONVERSAO_H
#define CONVERSAO_H

// struct para os 4 bits do arquivo
typedef struct {
    unsigned char hexa : 4;
} half_char;

// struct para particao do formato da instrucao
typedef struct {
    unsigned short imediato : 6;
    unsigned char  rs1      : 3;
    unsigned char  rd       : 3;
    unsigned char  opcode   : 4;
} InstrucaoTipoI;

//funcoes conversao.c
const char* conversor_bin(char bin);
InstrucaoTipoI particionar_tipo_i(half_char *v);
void imprimir_assembly(InstrucaoTipoI inst);

#endif