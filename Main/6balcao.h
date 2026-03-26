//
// Created by franc on 14/03/2025.
//
#ifndef BALCAO_H
#define BALCAO_H
#include "2estruturas.h"
void iniciar_balcao(Balcao &b);
bool adicionar_balcao(Balcao &b, cliente &c);
void mostrar_balcao(const Balcao &b);
void remover_clientes_balcao(Balcao &b);
void mudar_especialidade (Balcao &b, const string &novaEspecialidade,int duracaoCiclos); // para horas de ponta
void atualizar_balcao(Balcao &b);
void transferir_balcao(Balcao &b, cliente fila[], int &inicio, int &fim);
#endif //BALCAO_H
