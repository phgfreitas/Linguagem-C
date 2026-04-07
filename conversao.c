#include <stdio.h>
#include "conversao.h"
#include <ctype.h>

//funcao para converter hexa em binario(nao utilizada na versao final)
const char* conversor_bin(char bin) {
    const char* tabela_hex_bin[16] = {
        "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
    };
    bin = toupper(bin);
    if (bin >= '0' && bin <= '9') return tabela_hex_bin[bin - '0'];
    if (bin >= 'A' && bin <= 'F') return tabela_hex_bin[bin - 'A' + 10];
    return "erro";
}

//funcao para particionar os bits transformados de hexa->binario do arquivo e alocado no formato escolhido da instrucao
InstrucaoTipoI particionar_tipo_i(half_char *v) {
    InstrucaoTipoI inst;
    unsigned short palavra = 0;
    //montador para palavras de 4 bits
    palavra |= (v[0].hexa << 12);
    palavra |= (v[1].hexa << 8);
    palavra |= (v[2].hexa << 4);
    palavra |= (v[3].hexa);

    //ajuste da leitura dos bits com deslocamento para ler exatamente a posicao pre estabelecida dos regs
    inst.imediato = (palavra >> 10) & 0x3F; //10 bits de deslocamento
    inst.rs1      = (palavra >> 7)  & 0x07; //7 bits de deslocamento
    inst.rd       = (palavra >> 4)  & 0x07; //4 bits de deslocamento
    inst.opcode   = (palavra)       & 0x0F; //sem deslocamento, final da palavra

    return inst;
}

void imprimir_assembly(InstrucaoTipoI inst) {
     //correcao de erro para o primeiro digito do imediato que e um bit que representa sinal
    int imediato_real = inst.imediato;
    if (imediato_real & 0x20) {
        imediato_real -= 64; 
    }

    //tratamento dos regs
    int rs1_real = inst.rs1; 
    int rd_real  = inst.rd;

    printf("ASSEMBLY: ");
    
    switch (inst.opcode) {
        case 0://opcode 0000
            printf("addi x%d, x%d, %d\n", rd_real, rs1_real, imediato_real);
            break;
        case 1: //opcode 0001
            printf("subi x%d, x%d, %d\n", rd_real, rs1_real, imediato_real);
            break;
        case 2: //opcode 0010
            printf("andi x%d, x%d, %d\n", rd_real, rs1_real, imediato_real);
            break;
        case 3: //opcode 0011
            printf("lw x%d, %d(x%d)\n", rd_real, imediato_real, rs1_real);
            break;
        case 4: //opcode 0100
            printf("sw x%d, %d(x%d)\n", rd_real, imediato_real, rs1_real);
            break;
        default:
            printf("instrucao_desconhecida (Opcode %d) x%d, x%d, %d\n", 
                   inst.opcode, rd_real, rs1_real, imediato_real);
            break;
    }
}