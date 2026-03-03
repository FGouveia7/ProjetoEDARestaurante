#ifndef PROJETO_H
#define PROJETO_H
#include "2estruturas.h"
void iniciar_mesas(Mesa*& mesas, int quantidade);
void array_clientes_sairam(const cliente& cliente);
void remover_cliente_mesa(Mesa*& mesas, int& numMesas);
void mostrar_clientes_removidos(Mesa* mesas, int& numMesas);
void ler_nomes(string Pnomes[], string Unomes[], int tamanho);
void juntar_mesas(Mesa*& mesas, int& numMesas);
void adicionar_mesa(Mesa*& mesas, int& totalMesas);
void alterar_refeicao(Mesa*& mesas, int& numMesas, char idMesa, string novoTipoRefeicao);
#endif // PROJETO_H
