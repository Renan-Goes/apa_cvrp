#ifndef __CONSTRUCAO_H_
#define __CONSTRUCAO_H_

#include "auxiliar.h"
#include <vector>
using namespace std;

vector<rota_veiculo> Gulosa(double **grafo)
{
    qtdveiculos = 0;
    int count = 0, c, numcliente;
    vector<rota_veiculo> rotas;
    int countcliente = 1;
    bool *clientes = (bool*)malloc(sizeof(bool)*dimensao);
    
    for (int i = 0; i < dimensao; i++)
    {
        clientes[i] = false;
    }

    clientes[0] = 1;

    while (countcliente < dimensao)
    {
        rotas.push_back(rota_veiculo());
        count = 0;
        rotas[qtdveiculos].carga = demanda[0];
        rotas[qtdveiculos].distancia = 0;
        rotas[qtdveiculos].tamanho_percurso = 1;
        rotas[qtdveiculos].percurso.push_back(int());

        rotas[qtdveiculos].percurso[0] = 0;

        while (rotas[qtdveiculos].carga < capacidade)        
        {
            //Print_Percurso(rotas[qtdveiculos].percurso, rotas[qtdveiculos].tamanho_percurso);
            if (countcliente == dimensao)
            {
                rotas[qtdveiculos].percurso.push_back(int());
                rotas[qtdveiculos].distancia += grafo[rotas[qtdveiculos].percurso[count]][0];
                count++;
                rotas[qtdveiculos].tamanho_percurso++;
                rotas[qtdveiculos].percurso[count] = 0;
                rotas[qtdveiculos].carga += demanda[0];
                return rotas;
            }
            numcliente = rotas[qtdveiculos].percurso[count];
            c = BuscaMenor(grafo, numcliente, clientes);
            
            if (demanda[c] + rotas[qtdveiculos].carga <= capacidade)
            {
                clientes[c] = true;
                
                rotas[qtdveiculos].percurso.push_back(int());
                int aux = rotas[qtdveiculos].percurso[count];
                count++;
                rotas[qtdveiculos].percurso[count] = c;
                rotas[qtdveiculos].distancia += grafo[c][aux];
                rotas[qtdveiculos].tamanho_percurso++;
                rotas[qtdveiculos].carga += demanda[c];
                countcliente++;
                
            }
            else
            {  
                if (countcliente == dimensao)
                {
                    rotas[qtdveiculos].percurso.push_back(int());
                    rotas[qtdveiculos].distancia += grafo[rotas[qtdveiculos].percurso[count]][0];
                    count++;
                    rotas[qtdveiculos].tamanho_percurso++;
                    rotas[qtdveiculos].percurso[count] = 0;
                    rotas[qtdveiculos].carga += demanda[0];
                    return rotas;
                }
                break;
            }           
            
        }
        rotas[qtdveiculos].percurso.push_back(int());
        rotas[qtdveiculos].distancia += grafo[rotas[qtdveiculos].percurso[count]][0];
        count++;
        rotas[qtdveiculos].tamanho_percurso++;
        rotas[qtdveiculos].percurso[count] = 0;
        rotas[qtdveiculos].carga += demanda[0];
        //Print_Percurso(rotas[qtdveiculos].percurso, rotas[qtdveiculos].tamanho_percurso);
        qtdveiculos++;
    }

    //return rotas;
}

#endif