#ifndef __LEITURA_NORMAL_H_
#define __LEITURA_NORMAL_H_

#include "auxiliar.h"

void Leitura_Normal(FILE *arq, char const *dir)
{
    //abrindo o arquivo
    int count, temp = 0;//Contador para pegar os dados de dimensão, veículos e capacidade do arquivo
    char *Linha = (char*)malloc(sizeof(char)*999), *strDimensao, *strVeiculos, *strCapacidade, *result;//Buffer que terá a linha do arquivo a cada vez no loop, e ponteiros que receberão os dados do arquivo que serão em string.
    int linha = 0, coluna = 0, num_linha=0, indice_demanda = 0, num_demanda = 0;
    char *demanda_valor;

    arq = fopen(dir, "r"); 
    if(arq == NULL) //verificando se tudo ocorreu corretamente
    {
       puts("Problemas em abrir o arquivo\n");
        exit(-1);
    }
    //leitura do arquivo e imprimi-lo todo na tela
//ok

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
            matriz = (double**)malloc(sizeof(double*)*dimensao);
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
        //ok demanda esta sendo alterada inesperadamente
        if (count > 5 && count < 6 + dimensao)
        {
            
            //demanda[num_demanda++] = (int)malloc(sizeof(int)*dimensao); // linha desnecessaria

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
    

    // ok
        if((count > 7 + dimensao) && (count <= 7 + (dimensao+dimensao))){ // ultrapassadno em dois o espaço de mememoria, concertado
            //tratando os espaços
            
            char *token;
            token = strtok(Linha, " ");
            matriz[num_linha++] = (double*)malloc(sizeof(double)*dimensao);

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
}

#endif