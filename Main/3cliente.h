//
// Created by franc on 11/03/2025.
//

#ifndef CLIENTE_H
#define CLIENTE_H
#include "2estruturas.h"
cliente remover_cliente(cliente fila[], int& inicio, int& fim);
void criar_cliente(cliente fila[], int quantidade, string primeiros[],string ultimos[], int tamPrimeiros, int tamUltimos);
void por_clientes_mesas(cliente*& fila, int &inicio, int &fim, Mesa*& mesas, int& numMesas);
string criar_nomes(string nomes[], int tamanho);
void entrada_manual(Mesa* mesas, int numMesas, cliente* filaEntrada, int& inicio, int fim,Balcao balcao);
#endif //CLIENTE_H
