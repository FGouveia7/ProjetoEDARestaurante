//
// Created by franc on 11/03/2025.
//
#include <iostream>
using namespace std;
#include "3cliente.h"
#include <fstream>
#include <string>

//------------------------------------------------------------
/**
 * Função que cria um cliente com primeiro nome e ultimo
 * @param nomes - array de nomes disponíveis
 * @param tamanho - número de elementos no array de nomes
 */
string criar_nomes(string nomes [], int tamanho) {
    return nomes[rand() % tamanho];
}

//---------------------------------------------------------------------------------------------------
/**
 * Função que remove e da o cliente no início da fila.
 * @param fila - array de clientes na fila
 * @param inicio - referência para o índice do início da fila.
 * @param fim - referência para o índice do fim da fila
 */
cliente remover_cliente(cliente fila[], int& inicio, int& fim){
    if (inicio==fim) {
        cout<<"Fila vazia"<<endl;
        return cliente();
    }
    cliente removido = fila[inicio];
    inicio++;
    return removido;
}
//----------------------------------------------------------------------------------------------------
/**
 * Função que inicia uma fila de clientes com dados aleatórios.
 * @param fila - array de clientes a ser preenchido
 * @param quantidade - número de clientes a serem criados
 * @param primeiros - array de possíveis primeiros nomes
 * @param ultimos - array de possíveis últimos nomes
 * @param tamPrimeiros - tamanho do array de primeiros nomes
 * @param tamUltimos - tamanho do array de últimos nomes
 */
int ultimoID = 0;
void criar_cliente(cliente fila[], int quantidade, string primeiros[], string ultimos[], int tamPrimeiros, int tamUltimos) {
    string opcoesPref[] = {"snack", "vegetariano", "vegan", "peixe", "carne"};
    int num_opcoes = 5;

    for (int i = 0; i < quantidade; i++) {
        fila[i].id = ++ultimoID;
        fila[i].Pnome = criar_nomes(primeiros, tamPrimeiros);
        fila[i].Unome = criar_nomes(ultimos, tamUltimos);
        fila[i].Preferencia = opcoesPref[rand() % num_opcoes];
        fila[i].Reserva = (rand() % 100 < 15);
        fila[i].Temporefeicao = 3 + (rand() % 6);
        fila[i].Temporefeicaototal=fila[i].Temporefeicao;
    }
}
//------------------------------------------------------------------------------------------------------
/**
 * Função que coloca automaticamente até 8 clientes da fila de entrada nas mesas disponíveis,
 * @param filaEntrada - referência para o array dinâmico de clientes na fila entrada
 * @param inicio - referência para o índice inicial da fila
 * @param fim - referência para o índice final da fila
 * @param mesas - referência para o array de mesas disponíveis
 * @param numMesas - referência para o número total de mesas
 */
void por_clientes_mesas(cliente*& filaEntrada, int &inicio, int &fim, Mesa*& mesas, int& numMesas) {
    int clientesColocados = 0;
    int numtotal = 8;
    int indiceatual = inicio;

    while (clientesColocados < numtotal && indiceatual < fim) {
        cliente c = filaEntrada[indiceatual];

        if (c.Preferencia == "snack") {
            indiceatual++;
            continue;
        }
        bool colocado = false;

        for (int i = 0; i < numMesas; i++) {
            if (mesas[i].Preferencia == c.Preferencia) {
                int capacidadeTotal = mesas[i].Capacidade;
                int capacidadeReserva = mesas[i].Reserva;


                if (c.Reserva && mesas[i].Clientes_sentados < capacidadeReserva) {
                    mesas[i].Clientes[mesas[i].Clientes_sentados] = c;
                    mesas[i].Clientes_sentados++;
                    colocado = true;
                    break;
                }
                if (!c.Reserva && mesas[i].Clientes_sentados < capacidadeReserva && mesas[i].Clientes_sentados < capacidadeTotal) {
                    mesas[i].Clientes[mesas[i].Clientes_sentados] = c;
                    mesas[i].Clientes_sentados++;
                    colocado = true;
                    break;
                }
            }
        }
        if (colocado) {
            for (int j = indiceatual; j < fim - 1; j++) {
                filaEntrada[j] = filaEntrada[j + 1];
            }
            fim--;
            clientesColocados++;
        } else {
            indiceatual++;
        }
    }
}
//--------------------------------------------------------------------------------------------

/**
 * Função que permite colocar manualmente um cliente da fila de espera em uma mesa disponível,
 * @param mesas - array de mesas disponíveis no restaurante
 * @param numMesas - número total de mesas
 * @param filaEntrada - fila de entrada
 * @param inicio - índice inicial da fila
 * @param fim - índice final da fila
 * @param balcao - estrutura que representa o balcão
 */
void entrada_manual(Mesa* mesas, int numMesas, cliente* filaEntrada, int& inicio, int fim, Balcao balcao) {
    if (inicio >= fim) {
        cout << "Fila vazia!" << endl;
        return;
    }

    int idCliente;
    cout << "\nIntroduza o ID do cliente para que quer colocar: ";
    if (!(cin >> idCliente)) {
        cout << "Erro: Entrada invalida! Introduza um ID valido.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    int posCliente = -1;
    for (int i = inicio; i < fim; i++) {
        if (filaEntrada[i].id == idCliente) {
            posCliente = i;
            break;
        }
    }
    if (posCliente == -1) {
        cout << "Erro: Cliente nao encontrado na fila!" << endl;
        return;
    }
    cliente clienteEscolhido = filaEntrada[posCliente];
    bool colocado = false;

    for (int i = 0; i < numMesas; i++) {
        if (mesas[i].Clientes_sentados < mesas[i].Capacidade && (mesas[i].Preferencia == "snack" || mesas[i].Preferencia == clienteEscolhido.Preferencia)){
            mesas[i].Clientes[mesas[i].Clientes_sentados++] = clienteEscolhido;
            filaEntrada[posCliente].id = 0;
            cout << "\nO Cliente " << clienteEscolhido.Pnome << " " << clienteEscolhido.Unome
                 << " foi colocado na Mesa " << mesas[i].ID << "!" << endl;
            colocado = true;
            break;
            }
    }

    if (!colocado) {
        cout << "Erro: Nenhuma mesa disponivel para este cliente!" << endl;
    }
}
//------------------------------------------------------------
