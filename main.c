#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "construcao.h"
#include "auxiliar.h"
#include "refinamento.h"

int **matriz;

int main()
{
    FILE *arq; //Variável que receberá o endereço do arquivo caso esse seja aberto sem dificuldades
    int count, temp = 0;//Contador para pegar os dados de dimensão, veículos e capacidade do arquivo
    char Linha[999999], *strDimensao, *strVeiculos, *strCapacidade, *result;//Buffer que terá a linha do arquivo a cada vez no loop, e ponteiros que receberão os dados do arquivo que serão em string.
    int linha = 0, coluna = 0, num_linha=0, indice_demanda = 0, num_demanda = 0;
    int **matriz;

    //abrindo o arquivo
    arq = fopen("P-n20-k2.txt", "r"); 
    if(arq == NULL) //verificando se tudo ocorreu corretamente
    {
       puts("Problemas em abrir o arquivo\n");
        return -1;
    }
    //leitura do arquivo e imprimi-lo todo na tela
    count = 0;
    while (!feof(arq))
    {
        fgets(Linha, 8192, arq);//ler linha a linha
        Linha[strlen(Linha) - 1] = '\0';
       
        //guardar as variáveis de dimensão. veículos e capacidade
        count++;
        if(count == 2)//Caso esteja na segunda linha
        {
            strDimensao = strchr(Linha, ' '); //
            strDimensao++; 
            dimensao = atoi(strDimensao); //transforme essa string em inteiro
            matriz = (int**)malloc(sizeof(int*)*dimensao);
            demanda = (int*)malloc(sizeof(int)*dimensao);
            printf("Demanda: %d\n", dimensao);
            //percurso = (struct caminho*)malloc(sizeof(struct caminho)*dimensao);
        
        }
        if(count == 3)//Caso esteja na terceira linha
        {
            strVeiculos = strchr(Linha, ' ');
            strVeiculos++;
            veiculos = atoi(strVeiculos);
            printf("#Veiculos: %d\n", veiculos);
        }
        if (count == 4)//Caso esteja na quarta linha
        {
            strCapacidade = strchr(Linha, ' ');
            strCapacidade++;
            capacidade =  atoi(strCapacidade);
            printf("Capacidade: %d\n", capacidade);

            /*printf("%s\n", pular_linha);

            printf("Dimensao: %d, Capacidade: %d, #Veiculos: %d\n", capacidade, veiculos);

            printf("%s\n", pular_linha);
            printf("Dimensoes dos veiculos:\n");*/
        }

        if (count > 5 && count < 6 + dimensao)
        {
            char *demanda_valor;
            demanda[num_demanda++] = (int)malloc(sizeof(int)*dimensao);

            demanda_valor = strtok(Linha, " ");

            while(demanda_valor != NULL)
            {
                //percorre a linha pesquisando cada número
                demanda_valor = strtok(NULL, " \n");
                
                demanda[indice_demanda] = atoi(demanda_valor); //guarda os números como inteiros na matriz
                //printf("%d: %d\n", indice_demanda, demanda[indice_demanda]);

                indice_demanda++;
              
                demanda_valor = strtok(NULL, " ");
            }
        }

        if(count > 7 + dimensao){
            //tratando os espaços
            
            char *token;
            token = strtok(Linha, " ");
            matriz[num_linha++] = (int*)malloc(sizeof(int)*dimensao);

            while(token != NULL)
            {
                //percorre a linha pesquisando cada número
                
                matriz[linha][coluna] = atoi(token); //guarda os números como inteiros na matriz
              
                token = strtok(NULL, " ");
         
                coluna++;
            }
            linha++; //pulando pra próxima linha da matriz a ser preenchida
        }
        coluna = 0;//voltando para 1º coluna quando começar a atribuição na matriz da nova linha

    }

    int i, j;

    i = 0;
    j = 0;

    /*for (int k = 0; k < dimensao; k++)
        printf("demanda[%d] = %d\n", k, demanda[k]);*/

    printf("%s\n", pular_linha);
    
    struct rota_veiculo *solucao_inicial = (struct rota_veiculo*)malloc(sizeof(struct rota_veiculo)*(veiculos));

    solucao_inicial = Guloso(matriz);

    puts(pular_linha);
    puts(pular_linha);

    for (int o = 0; o < veiculos; o++)
    {
        printf("Veiculo %d:\n", o);
        Print_Percurso(solucao_inicial[o].percurso, solucao_inicial[o].tamanho_percurso);
        printf("Distancia obtida: %d\n\n", solucao_inicial[o].distancia);
    }
    puts(pular_linha);

    struct rota_veiculo *nova_solucao_swap = (struct rota_veiculo*)malloc(sizeof(struct rota_veiculo)*(veiculos));

    nova_solucao_swap = SWAP(matriz, solucao_inicial);

    puts(pular_linha);

    for (int o = 0; o < veiculos; o++)
    {
        printf("Veiculo (SWAP) %d:\n", o);
        Print_Percurso(nova_solucao_swap[o].percurso, nova_solucao_swap[o].tamanho_percurso);
        printf("Distancia obtida (SWAP): %d --- Distancia verdadeira: %d\n\n", nova_solucao_swap[o].distancia, Distancia(nova_solucao_swap[o].percurso, matriz, nova_solucao_swap[o].tamanho_percurso));
    }
    puts(pular_linha);

    struct rota_veiculo *nova_solucao_dopt = (struct rota_veiculo*)malloc(sizeof(struct rota_veiculo)*(veiculos));

    nova_solucao_dopt = Dois_OPT(matriz, solucao_inicial);

    puts(pular_linha);

    for (int o = 0; o < veiculos; o++)
    {
        printf("Veiculo (2OPT) %d:\n", o);
        Print_Percurso(nova_solucao_dopt[o].percurso, nova_solucao_dopt[o].tamanho_percurso);
        printf("Distancia obtida (2OPT): %d --- Distancia verdadeira: %d\n\n", nova_solucao_dopt[o].distancia, Distancia(nova_solucao_dopt[o].percurso, matriz, nova_solucao_dopt[o].tamanho_percurso));
    }
    puts(pular_linha);

    //printf("Nos percorridos:\n");

    /*solucao_inicial = primMST(matriz);

    Print_Percurso(solucao_inicial);
    printf("Distancia: %d\n", Distancia(solucao_inicial, matriz));

    if (Verifica_Visitado(solucao_inicial))
        printf("Solucao inicial errada!\n");

    int *nova_solucao = (int*)malloc(sizeof(int)*(dimensao));

    nova_solucao = VND(matriz, solucao_inicial, 10000);

    printf("%s\n", pular_linha);
    Print_Percurso(nova_solucao);
    printf("Distancia: %d\n", Distancia(nova_solucao, matriz));
    if (Verifica_Visitado(nova_solucao))
        printf("Nova solucao errada!\n");*/
    
    fclose(arq);   
    return 0;
}
