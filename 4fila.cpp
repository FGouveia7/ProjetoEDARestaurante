//
// Created by franc on 11/03/2025.
//
#include "4fila.h"
#include "6balcao.h"
#include <iostream>
using namespace std;

//----------------------------------------------------------------------------------------------
/**
 * Função que imprime o estado atual do restaurante
 * @param mesas - referência para o array de mesas
 * @param numMesas - número total de mesas
 * @param filaEntrada - apontador para o array de clientes na fila de espera
 * @param inicio - índice do início da fila
 * @param fim - índice do fim da fila
 * @param b - referência para o balcão
 */

void imprimir_restaurante(Mesa*& mesas, int& numMesas, cliente* filaEntrada, int inicio, int fim, Balcao &b) {
    cout << "\nClientes no balcao:" << endl;
    if (b.quantidade == 0) {
        cout << "Nenhum cliente no balcao" << endl;
    } else {
        for (int i = 0; i < b.quantidade; i++) {
            cout <<"- ID: "<< b.clientes[i].id << " | Nome: " << b.clientes[i].Pnome << " " << b.clientes[i].Unome << " | " << b.clientes[i].Preferencia<< " (" << b.clientes[i].Temporefeicaototal << " , " << b.clientes[i].Temporefeicao << ")" << endl;
        }
    }
    cout << "\nEstado das mesas:\n" << endl;
    for (int i = 0; i < numMesas; i++) {
        cout << "Mesa " << mesas[i].ID << " | Refeicao: " << mesas[i].Preferencia<< " | Ocupacao: " << mesas[i].Clientes_sentados << "/" << mesas[i].Capacidade<< " | Reservas: " << mesas[i].Reserva << endl;
        if (mesas[i].Clientes_sentados > 0) {
            for (int j = 0; j < mesas[i].Clientes_sentados; j++) {
                cliente c = mesas[i].Clientes[j];
                cout << "    - ID: " << c.id<< " | Nome: " << c.Pnome << " " << c.Unome <<(c.Reserva ? " ( r ) " : " ( n )")<< " (" << c.Temporefeicaototal << "," << c.Temporefeicao << ")" << endl;
            }
        } else {
            cout << "    Mesa vazia" << endl;
        }
    }
    cout << "\nFila de espera:" << endl;
    if (inicio == fim) {
        cout << "Fila vazia" << endl;
    } else {
        for (int i = inicio; i < fim; i++) {
            if (filaEntrada[i].id != 0) {
                cout << filaEntrada[i].id << ". "<< filaEntrada[i].Pnome << " " << filaEntrada[i].Unome<< " | Preferencia: " << filaEntrada[i].Preferencia<< (filaEntrada[i].Reserva ? " ( r ) " : " ( n )") << endl;
            }
        }
    }
}
//------------------------------------------------------------

/**
 * Altera a preferência alimentar de um cliente específico na fila de entrada, com base no primeiro e ultimo nome.
 * @param filaEntrada - array de clientes na fila de entrada
 * @param inicio - índice inicial da fila
 * @param fim - índice final da fila
 * @param Pnome - primeiro nome do cliente a ser alterado
 * @param Unome - último nome do cliente a ser alterado
 * @param novaPreferencia - nova preferência alimentar a ser atribuída
 */

void mudar_preferencia_fila(cliente filaEntrada[], int inicio, int fim, string Pnome, string Unome, string novaPreferencia) {
    string preferenciasValidas[] = {"peixe", "carne", "vegan", "vegetariano"};

    bool preferenciaValida = false;
    for (int i = 0; i < 4; i++) {
        if (novaPreferencia == preferenciasValidas[i]) {
            preferenciaValida = true;
            break;
        }
    }
    if (!preferenciaValida) {
        cout << "Erro! A preferencia " << novaPreferencia << " nao e valida. Escolha entre: peixe, carne, vegan, vegetariano.\n";
        return;
    }
    for (int i = inicio; i < fim; i++) {
        if (filaEntrada[i].Pnome == Pnome && filaEntrada[i].Unome == Unome) {
            filaEntrada[i].Preferencia = novaPreferencia;
            cout << "Preferencia do cliente " << Pnome << " " << Unome << " foi alterada para: " << novaPreferencia;
            return;
        }
    }
    cout << "Cliente com o nome " << Pnome << " " << Unome << " nao foi encontrado na fila.";
}
