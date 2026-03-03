#include <iostream>
#include <time.h>
#include "5mesa.h"
#include "3cliente.h"
#include "4fila.h"
#include "6balcao.h"
#include "7Menus.h"
using namespace std;


/**
 * Função principal que inicia o estado do restaurante
 */
int main() {
    srand(time(NULL));
    Balcao balcao;
    iniciar_balcao(balcao);
    string Pnomes[100];
    string Unomes[100];
    ler_nomes(Pnomes,Unomes,15);
    int numMesas = 5 + rand() % 6;
    Mesa* mesas = new Mesa[numMesas];
    iniciar_mesas(mesas, numMesas);

    cliente filaEntrada[10000];
    criar_cliente(filaEntrada, 15, Pnomes, Unomes, 13, 13);

    int inicio = 0;
    int fim= 15;

    cout << "================ ESTADO INICIAL DO RESTAURANTE ================\n";

    imprimir_restaurante(mesas,numMesas,filaEntrada,inicio,fim,balcao);
    char opcao;
    bool escolha = false;
    cout << "\nEscolha uma opcao: (s) Seguinte, (o) Opcoes: ";

    while (true) {
        cin >> opcao;
        if (opcao != 's' && opcao != 'S' && opcao != 'o' && opcao != 'O') {
          cout<<"Opcao invalida!"<<endl;
            imprimir_restaurante(mesas,numMesas,filaEntrada,inicio,fim,balcao);
            cout << "\nEscolha uma opcao: (s) Seguinte, (o) Opcoes: ";
            continue;
        }
        if (opcao == 's' || opcao == 'S') {
            menu_s(filaEntrada, inicio, fim, mesas, numMesas, Pnomes, Unomes, 13, 13, balcao);
        } else if (opcao == 'o' || opcao == 'O') {
            menu_o(filaEntrada, inicio, fim, mesas, numMesas,balcao);
        }
    }
    return 0;
}
