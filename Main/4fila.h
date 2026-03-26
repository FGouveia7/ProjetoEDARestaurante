#ifndef FILA_H
#define FILA_H
#include "2estruturas.h"
void imprimir_restaurante(Mesa*&mesas, int& numMesas, cliente filaEntrada[], int inicio, int fim, Balcao &balcao);
void mudar_preferencia_fila(cliente filaEntrada[], int inicio, int fim, string Pnome, string Unome, string novaPreferencia);
#endif //FILA_H
