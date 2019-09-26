//#include <stdio.h>
#include "gulosa.h"
#include "refinamento.h"
#include "VND.h"
#include <cmath>

#define NUM_VIZINHANCAS 3
#define SEM_MELHORA 0
#define MELHORA 1




 vector<rota_veiculo> Pertubacao(vector<rota_veiculo> solucao_atual, double ** grafo){
     int i, j;
    srand(time(NULL));
    vector<rota_veiculo> solucao_pertubada;

    switch (rand() % 2)
    {
        case 0:
            solucao_pertubada = SWAP(grafo, solucao_atual);
            break;
        case 1:
            
            solucao_pertubada = DoitOPT(grafo, solucao_atual);
            break;
        case 2:

            solucao_pertubada = Inverter(grafo, solucao_atual);
            break;

        default:
            break;
    }

    return solucao_pertubada;
}



typedef struct {
    int incice_sol_j;
    int indice_sol_i;   
    double melhora_dist;
    int melhora;
}hist_t;


 vector<rota_veiculo> ChecaHistorico(vector<vector<rota_veiculo>> historico, int criterio_aceitacao){
    int i =0 , j = 0;
    vector<hist_t> indice;
    hist_t sol = {0};
    vector<rota_veiculo>::iterator it2, it1;
    vector<rota_veiculo> hist;
    rota_veiculo rota1, rota2;
    int cont =0;
    double melhora = 0, aux = 0;
     
  for (vector<vector<rota_veiculo>>::iterator it = historico.begin() ; it != historico.end(); ++it){
        hist = *it;
        
        for (it1 = it2 = hist.begin(); it2 != hist.end(); ++it2){

            if(it2 != hist.begin()){
                rota1 = *it1++;
                rota2 = *it2;
                melhora += std::abs((rota1.distancia) - (rota2.distancia));
               
                //printf("%.0f  %.0f\n", rota1.distancia, rota2.distancia);
                //printf("MLEHORA: %.2f\n", melhora);
                if(melhora == SEM_MELHORA){
                    //printf("(0)\n");

                }else
                {
                 
                 return historico[i];
                 
                    /* code */
                }
                
                
            }

            j++;
        }
        melhora = 0;
        i++;
    }
  
    
}

vector<rota_veiculo> IlsMetaheuristica(double **grafo, vector<rota_veiculo> solucao_gulosa, int criterio_aceitacao){
    
    vector<rota_veiculo> solucao_atual, nova_solucao, solucao_pertubada, melhor_solucao;
    vector<hist_t> indice_sol;
    int criterio=0, i;
    hist_t min;
    vector<vector<rota_veiculo>> historico;
    min.melhora_dist = (double)INT_MAX;

    //Melhor solucao
    solucao_atual = VND(solucao_gulosa, grafo);

    // pertubar a solucao e verificar se ouve melhora


    while(1){

        solucao_pertubada = Pertubacao(solucao_atual, grafo); //faz um pertubação na solucao encontrada pelo vnd
                                            //pode ser uma troca de pesos

        nova_solucao = VND(solucao_pertubada, grafo); // 
        historico.push_back(nova_solucao);

        if(!--criterio_aceitacao){
                break;
        }
        //printf("c = %d\n", criterio_aceitacao);
    }

    printf("HISTORICO: %d\n", historico.size());
    return ChecaHistorico(historico, criterio_aceitacao);
  
}