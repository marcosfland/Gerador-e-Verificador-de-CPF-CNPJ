#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void gerarCPF(char *cpf) {
    int i, soma = 0, resto;
    int digitos[11];
    
    srand(time(NULL));
    
    // Gerar os 9 primeiros dígitos aleatórios
    for (i = 0; i < 9; i++) {
        digitos[i] = rand() % 10;
    }

    // Calcular o primeiro dígito verificador
    for (i = 0; i < 9; i++) {
        soma += digitos[i] * (10 - i);
    }
    resto = soma % 11;
    digitos[9] = (resto < 2) ? 0 : 11 - resto;
    
    // Calcular o segundo dígito verificador
    soma = 0;
    for (i = 0; i < 10; i++) {
        soma += digitos[i] * (11 - i);
    }
    resto = soma % 11;
    digitos[10] = (resto < 2) ? 0 : 11 - resto;

    // Montar o CPF
    sprintf(cpf, "%d%d%d.%d%d%d.%d%d%d-%d%d", 
            digitos[0], digitos[1], digitos[2], 
            digitos[3], digitos[4], digitos[5], 
            digitos[6], digitos[7], digitos[8], 
            digitos[9], digitos[10]);
}

void gerarCNPJ(char *cnpj) {
    int i, soma = 0, resto;
    int digitos[14];
    int peso1[] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int peso2[] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    
    srand(time(NULL));

    // Gerar os 12 primeiros dígitos aleatórios (exceto o 9º, 10º, 11º e 12º que são fixos "0001")
    for (i = 0; i < 8; i++) {
        digitos[i] = rand() % 10;
    }
    digitos[8] = 0;
    digitos[9] = 0;
    digitos[10] = 0;
    digitos[11] = 1;

    // Calcular o primeiro dígito verificador
    for (i = 0; i < 12; i++) {
        soma += digitos[i] * peso1[i];
    }
    resto = soma % 11;
    digitos[12] = (resto < 2) ? 0 : 11 - resto;

    // Calcular o segundo dígito verificador
    soma = 0;
    for (i = 0; i < 13; i++) {
        soma += digitos[i] * peso2[i];
    }
    resto = soma % 11;
    digitos[13] = (resto < 2) ? 0 : 11 - resto;

    // Montar o CNPJ
    sprintf(cnpj, "%d%d.%d%d%d.%d%d%d/0001-%d%d",
            digitos[0], digitos[1], digitos[2],
            digitos[3], digitos[4], digitos[5],
            digitos[6], digitos[7], digitos[12],
            digitos[13]);
}

int validarCPF(const char *cpf) {
    int i, j, digito1 = 0, digito2 = 0, resto;
    int numeros[11];

    // Extrair os números do CPF
    for (i = 0, j = 0; i < 11; i++, j++) {
        if (cpf[j] == '.' || cpf[j] == '-') {
            j++;
        }
        numeros[i] = cpf[j] - '0';
    }

    // Calcular o primeiro dígito verificador
    for (i = 0; i < 9; i++) {
        digito1 += numeros[i] * (10 - i);
    }
    resto = digito1 % 11;
    digito1 = (resto < 2) ? 0 : 11 - resto;

    // Calcular o segundo dígito verificador
    for (i = 0; i < 10; i++) {
        digito2 += numeros[i] * (11 - i);
    }
    resto = digito2 % 11;
    digito2 = (resto < 2) ? 0 : 11 - resto;

    // Validar os dígitos verificadores
    return (digito1 == numeros[9] && digito2 == numeros[10]);
}

int validarCNPJ(const char *cnpj) {
    int i, j, digito1 = 0, digito2 = 0, resto;
    int numeros[14];
    int peso1[] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int peso2[] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};

    // Extrair os números do CNPJ
    for (i = 0, j = 0; i < 14; i++, j++) {
        if (cnpj[j] == '.' || cnpj[j] == '/' || cnpj[j] == '-') {
            j++;
        }
        numeros[i] = cnpj[j] - '0';
    }

    // Calcular o primeiro dígito verificador
    for (i = 0; i < 12; i++) {
        digito1 += numeros[i] * peso1[i];
    }
    resto = digito1 % 11;
    digito1 = (resto < 2) ? 0 : 11 - resto;

    // Calcular o segundo dígito verificador
    for (i = 0; i < 13; i++) {
        digito2 += numeros[i] * peso2[i];
    }
    resto = digito2 % 11;
    digito2 = (resto < 2) ? 0 : 11 - resto;

    // Validar os dígitos verificadores
    return (digito1 == numeros[12] && digito2 == numeros[13]);
}

int main() {
    int opcao, tipo;
    char documento[20];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Gerar CPF/CNPJ\n");
        printf("2. Validar CPF/CNPJ\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n1. Gerar CPF\n");
                printf("2. Gerar CNPJ\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &tipo);
                switch (tipo) {
                    case 1:
                        gerarCPF(documento);
                        printf("CPF Gerado: %s\n", documento);
                        break;
                    case 2:
                        gerarCNPJ(documento);
                        printf("CNPJ Gerado: %s\n", documento);
                        break;
                    default:
                        printf("Opcao invalida!\n");
                }
                break;
            case 2:
                printf("\n1. Validar CPF\n");
                printf("2. Validar CNPJ\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &tipo);
                switch (tipo) {
                    case 1:
                        printf("Digite o CPF (formato XXX.XXX.XXX-XX): ");
                        scanf("%s", documento);
                        if (validarCPF(documento)) {
                            printf("CPF %s é válido\n", documento);
                        } else {
                            printf("CPF %s é inválido\n", documento);
                        }
                        break;
                    case 2:
                        printf("Digite o CNPJ (formato XX.XXX.XXX/0001-XX): ");
                        scanf("%s", documento);
                        if (validarCNPJ(documento)) {
                            printf("CNPJ %s é válido\n", documento);
                        } else {
                            printf("CNPJ %s é inválido\n", documento);
                        }
                        break;
                    default:
                        printf("Opcao invalida!\n");
                }
                break;
            case 3:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}
