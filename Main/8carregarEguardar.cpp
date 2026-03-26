#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "2estruturas.h"
using namespace std;
//----------------------------------------------------------------------------------------
/**
 * Função que grava o estado atual do restaurante num ficheiro de texto.
 * O estado inclui os dados do balcão, mesas e fila de entrada.
 * @param arquivo - nome do ficheiro onde será guardado o estado
 * @param mesas - apontador para o array dinâmico de mesas do restaurante
 * @param numMesas - número atual de mesas existentes
 * @param filaEntrada - array com os clientes que estão na fila de entrada
 * @param tamanhoFila - número de clientes presentes na fila de entrada
 * @param balcao - referência ao balcão
 */
void gravarRestaurante(const char* arquivo, Mesa* mesas, int numMesas, cliente* filaEntrada, int tamanhoFila, Balcao& balcao) {
    ofstream file(arquivo);
    if (!file.is_open()) {
        cerr << "Erro ao gravar o arquivo!" << endl;
        return;
    }
    file <<balcao.quantidade << " CLIENTES" <<" | "<<balcao.especialidade << endl;
    for (int i = 0; i < balcao.quantidade; ++i) {
        cliente c = balcao.clientes[i];
        file
            <<"ID : "<< c.id << "\nCLIENTE : "<< c.Pnome << " "<< c.Unome << "\nPREFERENCIA : "<< c.Preferencia << endl;
    }
    for (int i = 0; i < numMesas; ++i) {
        file << "MESA : "<<mesas[i].ID<< "\nCAPACIDADE : "<< mesas[i].Capacidade << "\nPREFERENCIA : "<< mesas[i].Preferencia << "\nCLIENTES SENTADOS : "<< mesas[i].Clientes_sentados <<endl;

        for (int j = 0; j < mesas[i].Clientes_sentados; ++j) {
            cliente c = mesas[i].Clientes[j];
            file
                 <<"CLIENTE: " << c.id << " | "
                 << c.Pnome << " "
                 << c.Unome << endl;
        }
        for (int j = 0; j < mesas[i].Total_clientes_passados; ++j) {
            file << mesas[i].Historico_clientes[j] << " | ";
        }
        file << endl;
    }
    for (int i = 0; i < tamanhoFila; ++i) {
        cliente c = filaEntrada[i];
        file <<"ID : "<< c.id << "\nCLIENTE : " << c.Pnome << ","<< c.Unome << " \nPREFERENCIA : "<< c.Preferencia << endl;
    }
    file.close();
    cout << "Estado gravado em " << arquivo << "!" << endl;
}

