//
// Created by lucas on 16/03/2025.
//
#include <iostream>
#include "7Menus.h"
#include "3cliente.h"
#include "5mesa.h"
#include "4fila.h"
#include "6balcao.h"
#include "8carregarEguardar.h"

//------------------------------------------------------------------------------------------------
/**
 * Função que simula um ciclo de operação no restaurante, atualizando o estado
 * do balcão, mesas e fila de clientes. Remove clientes, transfere da fila para
 * o balcão e mesas, cria novos clientes e imprime o estado atual.
 *
 * @param filaEntrada - array de clientes que estão na fila de entrada
 * @param inicio - índice de início da fila
 * @param fim - índice de fim da fila
 * @param mesas - apontador para o array dinâmico de mesas
 * @param numMesas - número atual de mesas disponíveis
 * @param Pnomes - array de possíveis primeiros nomes para criacao de clientes
 * @param Unomes - array de possíveis últimos nomes para a criacao de clientes
 * @param tamPrimeiros - tamanho do array de primeiros nomes
 * @param tamUltimos - tamanho do array de últimos nomes
 * @param balcao - referência ao balcão
 */

void menu_s(cliente filaEntrada[], int& inicio, int& fim, Mesa*& mesas, int& numMesas, string Pnomes[], string Unomes[], int tamPrimeiros, int tamUltimos, Balcao &balcao) {

    remover_cliente_mesa(mesas, numMesas);

    remover_clientes_balcao(balcao);

    transferir_balcao(balcao, filaEntrada, inicio, fim);

    por_clientes_mesas(filaEntrada, inicio, fim, mesas, numMesas);

    int novosClientes = 10;

    criar_cliente(filaEntrada + fim, novosClientes, Pnomes, Unomes, tamPrimeiros, tamUltimos); // Adiciona no final da fila

    fim += novosClientes;

    imprimir_restaurante(mesas, numMesas, filaEntrada, inicio, fim, balcao);


    cout << "\nEscolha uma opcao: (s) Seguinte, (o) Opcoes: ";

}
//--------------------------------------------------------------------------------------------------------

/**
 * Função que apresenta e executa o menu de opções do restaurante. Permite ao utilizador
 * realizar diversas operações como entrada manual de clientes, juntar/adicionar mesas,
 * alterar preferências, guardar/carregar estado do restaurante e ativar a Hora de Ponta.
 *
 * @param filaEntrada - array de clientes na fila de entrada
 * @param inicio - índice do início da fila
 * @param fim - índice do fim da fila
 * @param mesas - apontador para o array dinâmico de mesas do restaurante
 * @param numMesas - número atual de mesas disponíveis
 * @param balcao - referência ao balcão onde os clientes são atendidos
 */

void menu_o(cliente filaEntrada[], int& inicio, int& fim, Mesa*& mesas, int& numMesas, Balcao& balcao) {
    char opcao;
    bool escolha = false;

    do {
        cout <<"\n _____________________________"  <<endl;
        cout << "[        ***Opcoes***         ]" << endl;
        cout << " _____________________________ " << endl;
        cout << "[ 1. Entrada Manual           ]" << endl;
        cout << "[ 2. Juntar Mesas             ]" << endl;
        cout << "[ 3. Adicionar Mesas          ]" << endl;
        cout << "[ 4. Alterar Preferencia      ]" << endl;
        cout << "[ 5. Gravar Restaurante       ]" << endl;
        cout << "[ 6. Carregar Restaurante     ]" << endl;
        cout << "[ 7. Hora de Ponta            ]" << endl;
        cout << "[ 8. Clientes Removidos       ]" << endl;
        cout << "[ 9. Fechar Menu              ]" << endl;
        cout << " _____________________________ " << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cout << endl;
        switch (opcao) {
            case '1':
                cout << "Escolheu Entrada Manual.\n";
            entrada_manual(mesas, numMesas,filaEntrada,inicio, fim,balcao);
            break;
            case '2':
                cout << "Escolheu Juntar Mesas.\n";
            juntar_mesas( mesas,  numMesas);
            break;
            case '3':
                cout << "Escolheu Adicionar Mesas.\n";
            adicionar_mesa(mesas, numMesas);
            break;
            case '4':
                cout << "Escolheu Alterar Preferencia.\n";
            char subOpcao;
            cout << "Escolha uma opcao:\n";
            cout << "1 - Alterar preferencia de um cliente na fila de entrada\n";
            cout << "2 - Alterar tipo de refeicao de uma mesa\n";
            cout << "Escolha (1 ou 2): ";
            cin >> subOpcao;
            //---------------------------------------------------------------------------------------------------------------

            switch (subOpcao) {
                case '1': {
                    string Pnome, Unome, novaPreferencia;
                    cout << "Introduza o primeiro nome do cliente: ";
                    cin >> Pnome;
                    cout << "Introduza o ultimo nome do cliente: ";
                    cin >> Unome;
                    cout << "Introduza a nova preferencia (peixe, carne, vegetariano, vegan): ";
                    cin >> novaPreferencia;
                    mudar_preferencia_fila(filaEntrada, inicio, fim, Pnome, Unome, novaPreferencia);
                    break;
                }
                case '2': {
                    char idMesa;
                    string novoTipoRefeicao;
                    cout << "Introduza o ID da mesa para alterar o tipo de refeicao: ";
                    cin >> idMesa;
                    cout << "Introduza o novo tipo de refeiçao: (peixe, carne, vegetariano, vegan) ";
                    cin >> novoTipoRefeicao;
                    alterar_refeicao(mesas, numMesas, idMesa, novoTipoRefeicao);
                    break;
                }
                default:
                    cout << "Opcao invalida! Tente novamente.\n";
                break;
            }

            break;
            case '5':
                cout << "Escolheu Gravar Restaurante.\n";
            gravarRestaurante("arquivo.txt", mesas, numMesas, filaEntrada,fim, balcao);
            break;
            case '6':
                cout << "Funcao nao implementada pedimos desculpa! \n";
            break;
            case '7':{
                cout << "Escolheu Hora de Ponta.\n";
                string novaEspecialidade;
                int duracaoCiclos;
                cout << "Introduza a nova especialidade: ";
                cin >> novaEspecialidade;
                cout << "Introduza a duracao em ciclos: ";
                cin >> duracaoCiclos;
                mudar_especialidade(balcao, novaEspecialidade, duracaoCiclos);
                break;
            }
            case '8':
                cout<<"\n Escolheu Mostrar clientes que ja foram removidos.\n";
            mostrar_clientes_removidos(mesas, numMesas);
            break;
            case '9':
                cout << "Fechando Menu.\n";
                escolha = true;
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    } while (!escolha);
    imprimir_restaurante(mesas, numMesas, filaEntrada, inicio, fim, balcao);
    cout << "\nEscolha uma opcao: (s) Seguinte, (o) Opcoes: ";
}
//-------------------------------------------
