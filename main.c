#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

// Objeto que armazena os dados do jogador
typedef struct {
    char nome[31];  // 30 caracteres + \0
    char classe[20];
    int pv, ataque, def;
    int chanceCritico;
} personagem;

// Objeto que armazena os dados do Monstro
typedef struct {
    char nome[30];
    int pv, ataque, def;
} monstro;

// Função responsável por limpar o terminal
void limpartela() {
    system("pause");
    system("cls");
}

// Função para ler e validar o nome do personagem
void lerNomePersonagem(char *nome) {
    char buffer[100];
    int tamanho;

    do {
        printf("Digite o nome do personagem (1-30 caracteres, sem espaços): ");

        // Limpa o buffer de entrada
        fflush(stdin);

        // Lê a entrada do usuário
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro ao ler entrada. Tente novamente.\n");
            continue;
        }

        // Remove o caractere de nova linha
        buffer[strcspn(buffer, "\n")] = '\0';
        tamanho = strlen(buffer);

        // Validações
        if (tamanho < 1) {
            printf("Nome muito curto! Mínimo 1 caractere.\n");
            continue;
        }

        if (tamanho > 30) {
            printf("Nome muito longo! Máximo 30 caracteres.\n");
            continue;
        }

        // Verifica espaços
        int temEspaco = 0;
        for (int i = 0; i < tamanho; i++) {
            if (isspace(buffer[i])) {
                temEspaco = 1;
                break;
            }
        }

        if (temEspaco) {
            printf("Nome não pode conter espaços!\n");
            continue;
        }

        // Se passou todas as validações, copia o nome
        strcpy(nome, buffer);
        break;

    } while (1); // Loop infinito até nome válido
}

// Função que solicita ao usuário as informações do personagem
void criarPersonagem(personagem *jogador) {
    int escolha;

    system("cls");
    lerNomePersonagem(jogador->nome);
    system("cls");

    printf("Escolha a classe do personagem:\n");
    printf("1- Guerreiro \n2- Mago \n3- Arqueiro\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    getchar(); // Limpa o buffer do teclado
    system("cls");

    // Condicional que define os status do personagem
    switch (escolha){
        case 1:
            strcpy(jogador->classe, "Guerreiro");
            jogador->pv = 100;
            jogador->ataque = 15;
            jogador->def = 10;
            jogador->chanceCritico = 10;
            break;
        case 2:
            strcpy(jogador->classe, "Mago");
            jogador->pv = 60;
            jogador->ataque = 20;
            jogador->def = 5;
            jogador->chanceCritico = 15;
            break;
        case 3:
            strcpy(jogador->classe, "Arqueiro");
            jogador->pv = 90;
            jogador->ataque = 18;
            jogador->def = 8;
            jogador->chanceCritico = 20;
            break;
        default:
            printf("Classe invalida! Definindo como Guerreiro por padrao.\n");
            strcpy(jogador->classe, "Guerreiro");
            jogador->pv = 100;
            jogador->ataque = 15;
            jogador->def = 10;
            jogador->chanceCritico = 10;
            break;
    }
}

// Gera os status do monstro de forma aleatória
void gerarMonstro(monstro *monstro) {
    srand(time(NULL));
    strcpy(monstro->nome,"Monstro");
    monstro->pv = 50 + rand()%51;
    monstro->ataque = 10 + rand()%11;
    monstro->def = 5 + rand()%11;
}

// Função para exibir frases de ataque do personagem
void exibirFrasePersonagem(personagem *jogador, int critico) {
    const char* frasesGuerreiro[] = {
        "Tome isso, criatura imunda!",
        "Pela honra e glória!",
        "Sinta o peso da minha espada!",
        "HAAAAAA!",
        "Você não vai escapar!"
    };

    const char* frasesMago[] = {
        "Pelo poder dos arcanos!",
        "Magia é poder!",
        "Sinta a fúria dos elementos!",
        "Abracadabra!",
        "Queime na chama eterna!"
    };

    const char* frasesArqueiro[] = {
        "Olho no alvo... e FOGO!",
        "Flecha certeira!",
        "Direto no coração!",
        "Não há como errar!",
        "Alvo abatido!"
    };

    const char* frasesCriticas[] = {
        "ACERTEI EM CHEIO!",
        "ISSO VAI DOER!",
        "ATAQUE PERFEITO!",
        "DANO MÁXIMO!",
        "ACERTO CRÍTICO!"
    };

    int numFrases = 5;
    int indice = rand() % numFrases;

    if (critico) {
        printf("%s grita: \"%s\"\n", jogador->nome, frasesCriticas[indice]);
    } else {
        if (strcmp(jogador->classe, "Guerreiro") == 0) {
            printf("%s grita: \"%s\"\n", jogador->nome, frasesGuerreiro[indice]);
        } else if (strcmp(jogador->classe, "Mago") == 0) {
            printf("%s invoca: \"%s\"\n", jogador->nome, frasesMago[indice]);
        } else {
            printf("%s diz: \"%s\"\n", jogador->nome, frasesArqueiro[indice]);
        }
    }
}

// Função para exibir frases de ataque do monstro
void exibirFraseMonstro(monstro *monstro) {
    const char* frasesMonstro[] = {
        "Grrrrr!",
        "RAAAAARGH!",
        "Você vai morrer!",
        "Hahaha, é tudo que você tem?",
        "Sinta meu poder!",
        "Eu vou te devorar!",
        "Mais um para minha coleção!",
        "Ninguém escapa de mim!"
    };

    int numFrases = 8;
    int indice = rand() % numFrases;

    printf("%s rosna: \"%s\"\n", monstro->nome, frasesMonstro[indice]);
}

void realizarBatalha(personagem *jogador, monstro *monstro) {
    int i = 1;
    srand(time(NULL));

    printf("=== Inicio da Batalha ===\n");
    while (jogador->pv > 0 && monstro->pv > 0) {
        printf("\n>>>>> TURNO %d <<<<<\n", i);
        i++;

        // Ataque do jogador
        int rolagemCritico = rand() % 100 + 1;
        int danoJ = jogador->ataque - monstro->def;
        int ehCritico = 0;

        if (rolagemCritico <= jogador->chanceCritico) {
            danoJ *= 2;
            ehCritico = 1;
        }

        if (danoJ < 0) danoJ = 0;
        monstro->pv -= danoJ;
        if (monstro->pv < 0) monstro->pv = 0;

        exibirFrasePersonagem(jogador, ehCritico);
        printf("%s ataca %s!\n", jogador->nome, monstro->nome);
        if (ehCritico) {
            printf("DANO CRITICO!!! ");
        }
        printf("Dano causado: %d\n", danoJ);
        printf("PV do %s: %d\n\n", monstro->nome, monstro->pv);

        if (monstro->pv <= 0) break;

        // Ataque do monstro
        int danoM = monstro->ataque - jogador->def;
        if (danoM < 0) danoM = 0;
        jogador->pv -= danoM;
        if (jogador->pv < 0) jogador->pv = 0;

        exibirFraseMonstro(monstro);
        printf("%s ataca %s!\n", monstro->nome, jogador->nome);
        printf("Dano causado: %d\n", danoM);
        printf("PV do %s: %d\n\n", jogador->nome, jogador->pv);

        printf("Proximo turno");
        for (int j = 0; j < 3; j++) {
            printf(".");
            Sleep(600);
        }
        printf("\n\n");
    }
}

void exibirResultado(personagem *jogador) {
    printf("=== FIM DA BATALHA ===\n");
    if (jogador->pv <= 0) {
        printf("Derrota! Voce perdeu!\n");
    } else {
        printf("Parabens! Voce derrotou o monstro!\n");
    }
}

void jogarPartida() {
    personagem meuHeroi;
    monstro m;

    criarPersonagem(&meuHeroi);
    printf("Voce escolheu: %s\n", meuHeroi.classe);
    printf("Atributos do personagem\n");
    printf("- Nome: %s\n", meuHeroi.nome);
    printf("- Classe: %s\n", meuHeroi.classe);
    printf("- PV: %d\n", meuHeroi.pv);
    printf("- Ataque: %d\n", meuHeroi.ataque);
    printf("- Def: %d\n", meuHeroi.def);
    printf("- Chance de critico: %d%%\n", meuHeroi.chanceCritico);
    limpartela();

    gerarMonstro(&m);
    printf("Monstro gerado!\n");
    printf("Atributos do monstro: \n");
    printf("- Nome: %s\n", m.nome);
    printf("- Pv: %d\n", m.pv);
    printf("- Ataque: %d\n", m.ataque);
    printf("- Defesa: %d\n", m.def);
    limpartela();

    realizarBatalha(&meuHeroi, &m);
    limpartela();

    exibirResultado(&meuHeroi);
    limpartela();
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    int escolha;
    int jogarNovamente = 1;

    while (jogarNovamente) {
        printf("=== RPG BATTLE SIMULATOR ===\n");
        printf("1 - Criar personagem e iniciar batalha\n2 - Sair do programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado
        system("cls");

        if (escolha == 1) {
            do {
                jogarPartida();

                printf("Deseja jogar novamente?\n");
                printf("1 - Sim\n2 - Nao, voltar ao menu principal\n");
                printf("Escolha: ");
                scanf("%d", &escolha);
                getchar(); // Limpa o buffer do teclado
                system("cls");

                if (escolha != 1 && escolha != 2) {
                    printf("Opcao invalida!\n");
                    limpartela();
                }
            } while (escolha == 1);
        }
        else if (escolha == 2) {
            printf("Voce esta saindo do programa\n");
            Sleep(2000);
            jogarNovamente = 0;
        }
        else {
            printf("Escolha invalida\n");
            limpartela();
        }
    }

    return 0;
}