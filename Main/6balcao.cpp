//
// Created by franc on 14/03/2025.
//
#include "6balcao.h"
#include <iostream>
using namespace std;
//-----------------------------------------------------------------------------------------
/**
 * Inicia o estado do balcão
 * @param b - Referência à estrutura do tipo Balcao.
 */
void iniciar_balcao(Balcao &b) {
    b.quantidade = 0;
    b.especialidade = "snack";
}
//-------------------------------------------------------------------------------------------

/**
 * Remove clientes do balcão que terminaram a refeição.
 * @param b - Referência à estrutura do Balcao.
 */

void remover_clientes_balcao(Balcao& b) {
    int i = 0;

    while (i < b.quantidade) {

        if (b.clientes[i].Temporefeicao == 1) {
            cout << "ID: " << b.clientes[i].id << " | Nome: " << b.clientes[i].Pnome << " " << b.clientes[i].Unome<<" | Balcao "<< endl;
            for (int j = i; j < b.quantidade - 1; j++) {
                b.clientes[j] = b.clientes[j + 1];
            }
            b.quantidade--;
        } else {
            b.clientes[i].Temporefeicao--;
            i++;
        }
    }
}
//-------------------------------------------------------------------------------------
/**
 * Altera temporariamente a especialidade do balcão e ativa o modo Hora de Ponta.
 * @param b Referência a estrutura do Balcao.
 * @param novaEspecialidade Nova especialidade a ser atribuída ao balcão durante a hora de ponta.
 * @param duracaoCiclos Número de ciclos que a nova especialidade fica ativa.
 */
void mudar_especialidade(Balcao &b, const string &novaEspecialidade, int duracaoCiclos) {

    if (duracaoCiclos <= 0) {
        cout << "Duracao invalida. O tempo de Hora de Ponta deve ser maior que zero." << endl;
        return;
    }
    string especialidadesValidas[] = {"peixe", "carne", "vegan", "vegetariano"};
    string especialidadeLower = novaEspecialidade;
    bool especialidadeValida = false;

    for (int i = 0; i < 4; i++) {
        if (especialidadeLower == especialidadesValidas[i]) {
            especialidadeValida = true;
            break;
        }
    }
    if (!especialidadeValida) {
        cout << "Erro! Especialidade '" << novaEspecialidade << "invalida. Escolhe entre: peixe, carne, vegan, vegetariano." << endl;
        return;
    }
    b.especialidade = novaEspecialidade;
    b.horaPonta = true;
    b.ciclosRestantes = duracaoCiclos;
    cout << "Hora de Ponta iniciada: " << novaEspecialidade << " por " << duracaoCiclos << " ciclos." << endl;
}
//------------------------------------------------------------------------------------------------
/**
 * Atualiza o estado do balcão ao longo do tempo.
 * @param b Referência a estrutura do Balcao.
 */
void atualizar_balcao(Balcao &b) {

    if (!b.horaPonta) return;
    b.ciclosRestantes--;
    if (b.ciclosRestantes <= 0) {
        b.especialidade = "snack";
        b.horaPonta = false;
        cout << "Hora de ponta encerrada. O balcao voltou a aceitar apenas snack!" << endl;
    }
}
//-------------------------------------------------------------------------------------------

/**
 * Tenta verificar se o cliente pode ser coloacdo no balcao
 * @param b - Referência à estrutura do tipo Balcao.
 * @param c - Referência ao cliente a ser adicionado.
 */

bool adicionar_balcao(Balcao &b, cliente &c) {
    if (b.quantidade >= 15) {
        cout << "Balcao cheio. Nao podem ser adicionados mais clientes." << endl;
        return false;
    }
    if (c.Preferencia == "snack" || c.Preferencia == b.especialidade) {
        b.clientes[b.quantidade++] = c;
        return true;
    }
    return false;
}

/**
 * Coloca até 5 clientes da fila para o balcão, se forem compatíveis com a especialidade.
 * @param b Referência ao Balcao.
 * @param fila array com os clientes na fila de entrada.
 * @param inicio Índice de início da fila.
 * @param fim Índice do fim da fila.
 */
void transferir_balcao(Balcao &b, cliente fila[], int &inicio, int &fim) {
    int adicionados = 0;
    int i = inicio;

    while (i != fim && b.quantidade < 15 && adicionados < 5) {

        if (fila[i].Preferencia == "snack" || fila[i].Preferencia == b.especialidade) {
            if (adicionar_balcao(b, fila[i])) {
                for (int k = i; k < fim - 1; k++) {
                    fila[k] = fila[k + 1];
                }
                fim--;
                adicionados++;
            } else {
                break;
            }
        } else {
            i++;
        }
    }
}
//-------------------------------------------