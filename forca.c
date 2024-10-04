#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char palavra_facil[20] = "Macaco";
    char dica_facil[20] = "Animal";
    char palavra_medio[20] = "Pedregulho";
    char dica_medio[20] = "Mineral";
    char palavra_dificil[20] = "Paralelepipedo";
    char dica_dificil[20] = "Ladrilho";
    char palavra[20];
    char dica[20];
    char palpite;
    int escolha, pos;
    int i, j;
    int vidas;
    int dificuldade = 0;
    int opcao_menu = 0;

    // imprime o menu até a opção 4 ser digitada
    while (opcao_menu != 4) {
        printf("\nJogo da Forca\n");
        printf("1. Jogar (Vs CPU)\n");
        printf("2. Jogar (Vs Jogador)\n");
        printf("3. Regras\n");
        printf("4. Sair\n");
        scanf("%d", &opcao_menu);
        getchar();

        // opcao 1 do menu
        if (opcao_menu == 1) {
            printf("Voce selecionou o modo de jogo contra a cpu!\n");
            printf("Por favor, selecione uma dificuldade! \n");
            printf("1. Facil\n");
            printf("2. Medio\n");
            printf("3. Dificil\n");
            scanf("%d", &dificuldade);

            switch (dificuldade) {
                case 1:
                    printf("Voce selecionou a dificuldade FACIL!\n");
                    strcpy(palavra, palavra_facil);
                    strcpy(dica, dica_facil);
                    vidas = 6;
                    break;
                case 2:
                    printf("Voce selecionou a dificuldade MEDIO!\n");
                    strcpy(palavra, palavra_medio);
                    strcpy(dica, dica_medio);
                    vidas = 4;
                    break;
                case 3:
                    printf("Voce selecionou a dificuldade DIFICIL!\n");
                    strcpy(palavra, palavra_dificil);
                    strcpy(dica, dica_dificil);
                    vidas = 2;
                    break;
                default:
                    printf("ERRO! Selecione uma dificuldade valida!\n");
                    continue; 
            }

            // aqui começa strings de letras advinhadas e palavra
            char letras_advinhadas[strlen(palavra) + 1];
            char palpite_palavra[strlen(palavra) + 1];
            memset(letras_advinhadas, '_', strlen(palavra));
            letras_advinhadas[strlen(palavra)] = '\0';

            while (vidas > 0) {
                int todas_advinhadas = 1;
                printf("Voce tem: ");
                for (i = 0; i < vidas; i++) {
                    printf("x");
                }
                printf(" (%d) vidas\n", vidas);
                printf("Palavra: ");
                for (j = 0; j < strlen(palavra); j++) {
                    printf("%c", letras_advinhadas[j]);
                }
                printf("\nDica: %s", dica);
                printf("\nInsira a letra: ");
                scanf(" %c", &palpite);

                // 1 true 0 false
                int letra_encontrada = 0;

                // corre a palavra e ve se ta certo
                for (j = 0; j < strlen(palavra); j++) {
                    if (toupper(palpite) == toupper(palavra[j])) {
                        letras_advinhadas[j] = palavra[j]; 
                        letra_encontrada = 1;
                    }
                }
                if (letra_encontrada) {
                    printf("Palpite correto!\n");
                    printf("1. Continuar\n");
                    printf("2. Advinhar palavra\n");
                    scanf("%d", &escolha);
                    getchar();
                    if (escolha == 2) {
                        printf("Digite a palavra: \n");
                        if (fgets(palpite_palavra, sizeof(palpite_palavra), stdin) != NULL) {
                            palpite_palavra[strcspn(palpite_palavra, "\n")] = 0;
                            if (strcasecmp(palpite_palavra, palavra) == 0) {
                                printf("Acertou! A palavra era: %s\n", palavra);
                                break;
                            } else {
                                printf("Perdeu! A palavra era: %s\n", palavra);
                                break; 
                            }
                        } else {
                            printf("Erro ao ler a palavra!\n");
                        }
                    } else if (escolha == 1) {
                        continue;
                    } else {
                        printf("Escolha inválida! Tente novamente.\n");
                    }
                } else {
                    printf("Palpite errado!\n");
                    vidas--; // Remove uma vida se não encontrar nenhuma letra
                }

                // Verifica se todas as letras foram adivinhadas
                todas_advinhadas = 1; // Reset para verificar se todas as letras foram adivinhadas
                for (j = 0; j < strlen(palavra); j++) {
                    if (letras_advinhadas[j] == '_') {
                        todas_advinhadas = 0;
                        break;
                    }
                }

                if (todas_advinhadas) {
                    printf("Parabens! Voce advinhou a palavra: %s\n", palavra);
                    break;
                }
            }

            if (vidas == 0) {
                printf("Voce perdeu! A palavra era: %s\n", palavra);
            }

        } else if (opcao_menu == 2) {

            vidas = 6;
            printf("Voce selecionou o modo de jogo JxJ\n");
            printf("J1. Digite a palavra para ser advinhada pelo J2\n");
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = 0;
            printf("J1. Palavra registrada com sucesso!\n");
            printf("J1. Digite a dica da palavra: \n");
            fgets(dica, sizeof(dica), stdin);
            dica[strcspn(dica, "\n")] = 0;
            printf("J1. Dica registrada com sucesso!\n");
            printf("J2. Hora de advinhar!\n");

            char letras_advinhadas[strlen(palavra) + 1];
            char palpite_palavra[strlen(palavra) + 1];
            memset(letras_advinhadas, '_', strlen(palavra));
            letras_advinhadas[strlen(palavra)] = '\0';

            while (vidas > 0) {
                int todas_advinhadas = 1;
                printf("J2. Voce tem: ");
                for (i = 0; i < vidas; i++) {
                    printf("x");
                }
                printf(" (%d) vidas\n", vidas);
                printf("Palavra: ");
                for (j = 0; j < strlen(palavra); j++) {
                    printf("%c", letras_advinhadas[j]);
                }
                printf("\nDica: %s", dica);
                printf("\nJ2. Insira a letra: ");
                scanf(" %c", &palpite);

                // 0 para nao achado e 1 para achado
                int letra_encontrada = 0;

                // corre a string e verifica se achou alguma letra, se s vira 1
                for (j = 0; j < strlen(palavra); j++) {
                    if (toupper(palpite) == toupper(palavra[j])) {
                        letras_advinhadas[j] = palavra[j]; // underscore = letras descobertas
                        letra_encontrada = 1; // on
                    }
                }
                if (letra_encontrada) {
                    printf("Palpite correto!\n");
                    printf("1. Continuar\n");
                    printf("2. Advinhar palavra\n");
                    scanf("%d", &escolha);
                    getchar();
                    if (escolha == 2) {
                        printf("Digite a palavra: \n");
                        if (fgets(palpite_palavra, sizeof(palpite_palavra), stdin) != NULL) {
                            palpite_palavra[strcspn(palpite_palavra, "\n")] = 0;
                            if (strcasecmp(palpite_palavra, palavra) == 0) {
                                printf("Acertou! A palavra era: %s\n", palavra);
                                break;
                            } else {
                                printf("Perdeu! A palavra era: %s\n", palavra);
                                break; 
                            }
                        } else {
                            printf("Erro ao ler a palavra!\n");
                        }
                    } else if (escolha == 1) {
                        continue;
                    } else {
                        printf("Escolha inválida! Tente novamente.\n");
                    }

                } else {
                    printf("Palpite errado!\n");
                    vidas--; // Remove uma vida se não encontrar nenhuma letra
                }

                // Verifica se todas as letras foram adivinhadas
                todas_advinhadas = 1; // Reset para verificar se todas as letras foram adivinhadas
                for (j = 0; j < strlen(palavra); j++) {
                    if (letras_advinhadas[j] == '_') {
                        todas_advinhadas = 0;
                        break;
                    }
                }

                if (todas_advinhadas) {
                    printf("Parabens! Voce advinhou a palavra: %s\n", palavra);
                    break;
                }
            }

            if (vidas == 0) {
                printf("Voce perdeu! A palavra era: %s\n", palavra);
            }

        } else if (opcao_menu == 3) {
            printf("Regra 1. Ao jogo comecar, tera a quantidade de letras na palavra e uma dica\n");
            printf("Regra 2. Ao errar, perde vida\n");
            printf("Regra 3. Ao acertar, pode advinhar a palavra ou continuar por caracteres\n");
            printf("Regra 4. Ao errar a palavra inteira, perde o jogo!\n");
            printf("Regra 5. ao tentar advinhar e assim como no modo contra CPU, tente palavras sem acento.\n");
            continue;
        } else if (opcao_menu == 4) {
            printf("Obrigado por jogar!\n");
        } else {
            printf("ERRO! Selecione uma opcao valida do menu!\n");
        }
    }
    return 0;
}