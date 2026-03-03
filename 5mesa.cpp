// Created by lucas on 07/03/2025.
#include <fstream>
#include <iostream>
using namespace std;
#include "5mesa.h"
#include "4fila.h"


/**
 * Cria um array de mesas com capacidades, preferências e reservas aleatórias.
 * @param mesas - referência para o array dinâmico de mesas
 * @param quantidade - número total de mesas a serem iniciadas
 */

void iniciar_mesas(Mesa*& mesas , int quantidade){
    string opcoesPref[]={"vegetariano","vegan","peixe","carne"};
    int num_opcoes=4;
    for (int i = 0; i < quantidade; i++) {
        mesas[i].ID= 'A' + i;
        mesas[i].Capacidade= 2 + rand() % 5;
        mesas[i].Reserva= mesas[i].Capacidade/2;
        mesas[i].Preferencia= opcoesPref[rand() % num_opcoes];
        mesas[i].Clientes_sentados= 0;
        mesas[i].MaxReservas = mesas[i].Reserva;
    }
}
//------------------------------------------------------------------------------------
/**
 * Adiciona um cliente ao array de clientes removidos
 * @param c - Referência para o cliente que saiu
 * @param mesaID - Id da mesa de onde o cliente saiu
 */

cliente* clientesRemovidos = nullptr;
int numRemovidos = 0;

void array_clientes_sairam(const cliente& c, char mesaID) {
    cliente* novoArray = new cliente[numRemovidos + 1];

    for (int i = 0; i < numRemovidos; i++) {
        novoArray[i] = clientesRemovidos[i];
    }

    novoArray[numRemovidos] = c;
    numRemovidos++;

    delete[] clientesRemovidos;
    clientesRemovidos = novoArray;
}

//--------------------------------------------------------------------------------------
/**
 * Verifica todos os clientes sentados nas mesas e remove aqueles que ja acabaram a refeição
 * @param mesas - referência para o array de mesas
 * @param numMesas - número total de mesas
 */

void remover_cliente_mesa(Mesa*& mesas, int& numMesas) {
    cout << "\nClientes que terminaram a refeicao :\n";
    for (int i = 0; i < numMesas; i++) {
        for (int j = 0; j < mesas[i].Clientes_sentados; j++) {
            if (mesas[i].Clientes[j].Temporefeicao == 1) {
                cout << "ID: " << mesas[i].Clientes[j].id << " | Nome: " << mesas[i].Clientes[j].Pnome << " " << mesas[i].Clientes[j].Unome << " | Mesa: " << mesas[i].ID << endl;
                array_clientes_sairam(mesas[i].Clientes[j], mesas[i].ID);
                for (int k = j; k < mesas[i].Clientes_sentados - 1; k++) {
                    mesas[i].Clientes[k] = mesas[i].Clientes[k + 1];
                }
                mesas[i].Clientes_sentados--;
                j--;
            } else {
                mesas[i].Clientes[j].Temporefeicao--;
            }
        }
    }
}
//--------------------------------
/**
 * Mostra a lista de clientes que terminaram a refeição e foram removidos das mesas.
 * @param mesas - Apontador para o array de mesas disponíveis
 * @param numMesas - Número total de mesas disponíveis
 */
void mostrar_clientes_removidos(Mesa* mesas, int& numMesas) {
    if (numRemovidos == 0) {
        cout << "\n Nenhum cliente terminou a sua refeicao:";
        return;
    }
    cout << "\n Clientes que terminaram a refeicao:\n";
    for (int i = 0; i < numRemovidos; i++) {
        cout << "Mesa: " << mesas[i % numMesas].ID << " | " << "ID: " << clientesRemovidos[i].id << " | " << "Nome: " << clientesRemovidos[i].Pnome << " " << clientesRemovidos[i].Unome << endl;
    }
}
//-----------------------------------------------------------------------------------------
/**
 * Lê "primeiro.txt" e "ultimo.txt"
 * @param Pnomes - array onde serão guardados os primeiros nomes
 * @param Unomes - array onde serão guardados os últimos nomes
 * @param tamanho - número máximo de nomes a ler de cada ficheiro
 */

void ler_nomes(string Pnomes[], string Unomes[], int tamanho) {
    ifstream primeiro("primeiro.txt");
    ifstream ultimo("ultimo.txt");
    if (!primeiro.is_open() || !ultimo.is_open()) {
        cout << "Erro ao abrir os ficheiros. Verifique o caminho e as permissoes." << endl;
        exit(1);
    }
    string linhaPnome, linhaUnome;
    int i = 0;
    while (getline(primeiro, linhaPnome) && getline(ultimo, linhaUnome) && i < tamanho) {
        Pnomes[i] = linhaPnome;
        Unomes[i] = linhaUnome;
        i++;
    }
    primeiro.close();
    ultimo.close();
}
//-------------------------------------------
/**
 * Junta duas mesas do restaurante
 * @param mesas - array dinâmico de mesas existentes no restaurante
 * @param numMesas - número atual de mesas
 */

void juntar_mesas(Mesa*& mesas, int& numMesas) {
    char id1, id2;
    cout <<"Insira o ID da mesa 1:";
    cin >> id1;
    cout <<"Insira o ID da mesa 2:";
    cin >> id2;

    int indice1 = -1, indice2 = -1;
    for (int i = 0; i < numMesas; i++) {
        if (mesas[i].ID == id1) indice1 = i;
        if (mesas[i].ID == id2) indice2 = i;
    }
    if (indice1 == -1 || indice2 == -1) {
        cout << "Erro! Uma ou ambas as mesas nao foram encontradas." << endl;
        return;
    }
    if (indice1 == indice2) {
        cout << "Erro! Nao e possivel juntar uma mesa consigo mesmo." << endl;
        return;
    }

    string opcoesPref[] = {"snack", "vegetariano", "vegan", "peixe", "carne"};
    string prefMesa1 = mesas[indice1].Preferencia;
    string prefMesa2 = mesas[indice2].Preferencia;

    if (prefMesa1 == prefMesa2) {
        for (int j = 0; j < mesas[indice2].Clientes_sentados; j++) {
            if (mesas[indice1].Clientes_sentados < mesas[indice1].Capacidade + mesas[indice2].Capacidade) {
                mesas[indice1].Clientes[mesas[indice1].Clientes_sentados++] = mesas[indice2].Clientes[j];
            }
        }
        mesas[indice1].Capacidade += mesas[indice2].Capacidade;
        mesas[indice1].Reserva += mesas[indice2].Reserva;
    }
    else {
        cout <<"As preferencias das mesas sao diferentes (" << prefMesa1 << " e " << prefMesa2 << "). Escolha a preferencia: \n";
        cout <<"1. " << prefMesa1 <<"\n2. " << prefMesa2 << "\nEscolha: ";
        int escolha;
        cin >> escolha;
        string novaPreferencia;
        if (escolha == 1) novaPreferencia = prefMesa1;
        else if (escolha == 2) novaPreferencia = prefMesa2;
        else {
            cout << "Opcao invalida!" << endl;
            return;
        }
        int novosClientesMesa1 = 0;
        for (int j = 0; j < mesas[indice1].Clientes_sentados; j++) {
            if (mesas[indice1].Clientes[j].Preferencia == novaPreferencia) {
                mesas[indice1].Clientes[novosClientesMesa1++] = mesas[indice1].Clientes[j];
            }
        }
        mesas[indice1].Clientes_sentados = novosClientesMesa1;
        int novosClientesMesa2 = 0;
        for (int j = 0; j < mesas[indice2].Clientes_sentados; j++) {
            if (mesas[indice2].Clientes[j].Preferencia == novaPreferencia) {
                mesas[indice2].Clientes[novosClientesMesa2++] = mesas[indice2].Clientes[j];
            }
        }
        mesas[indice2].Clientes_sentados = novosClientesMesa2;
        for (int j = 0; j < mesas[indice2].Clientes_sentados; j++) {
            if (mesas[indice1].Clientes_sentados < mesas[indice1].Capacidade + mesas[indice2].Capacidade) {
                mesas[indice1].Clientes[mesas[indice1].Clientes_sentados++] = mesas[indice2].Clientes[j];
            }
        }
        mesas[indice1].Preferencia = novaPreferencia;
        mesas[indice1].Capacidade += mesas[indice2].Capacidade;
        mesas[indice1].Reserva += mesas[indice2].Reserva;
    }
    for (int i = indice2; i < numMesas - 1; i++) {
        mesas[i] = mesas[i + 1];
    }
    numMesas--;
    cout <<"Mesas " << id1 << " e " << id2 << " foram unidas! A mesa " << id2 << " foi removida." << endl;
}
//----------------------------------------------------------------------------
/**
 * Adiciona uma nova mesa ao array das mesas do restaurante.
 *
 * @param mesas - referência ao apontador do array das mesas
 * @param numMesas - referência ao número atual de mesas
 *
 */
void adicionar_mesa(Mesa*& mesas, int& numMesas) {
    if (numMesas >= 100) {
        cout << "Erro: Numero maximo de mesas atingido!\n";
        return;
    }
    Mesa* novoArrayMesas = new Mesa[numMesas + 1];
    for (int i = 0; i < numMesas; i++) {
        novoArrayMesas[i] = mesas[i];
    }
    novoArrayMesas[numMesas].ID = 'A' + numMesas;
    cout << "Capacidade da nova mesa: ";
    cin >> novoArrayMesas[numMesas].Capacidade;
    novoArrayMesas[numMesas].MaxReservas = novoArrayMesas[numMesas].Capacidade / 2;
    cout << "Preferencia (0 - vegetariano, 1 - vegan, 2 - peixe, 3 - carne): ";
    int pref;
    string opcoesPref[] = {"vegetariano", "vegan", "peixe", "carne"};

    while (true) {
        cin >> pref;
        if (pref < 0 || pref > 3) {
            cout << "Entrada invalida! Introduza um numero correspondente a preferencia (0-3): ";
        } else {
            novoArrayMesas[numMesas].Preferencia = opcoesPref[pref];
            break;
        }
    }
    delete[] mesas;
    mesas = novoArrayMesas;
    numMesas++;

    cout << "Nova mesa " << mesas[numMesas - 1].ID << " adicionada com sucesso!\n";
}
//-----------------------------------------------------------------------------------
/**
 * Altera o tipo de refeição de uma mesa específica.
 * @param mesas - referência ao apontador para o array de mesas.
 * @param numMesas - número total de mesas no array.
 * @param idMesa - id da mesa que o tipo de refeição será alterado.
 * @param novoTipoRefeicao - nova preferência alimentar da mesa
 */

void alterar_refeicao(Mesa*& mesas, int& numMesas, char idMesa, string novoTipoRefeicao) {
    string tiposRefeicaoValidos[] = {"peixe", "carne", "vegan", "vegetariano"};

    bool tipoValido = false;
    for (int i = 0; i < 4; i++) {
        if (novoTipoRefeicao == tiposRefeicaoValidos[i]) {
            tipoValido = true;
            break;
        }
    }
    if (!tipoValido) {
        cout << "Erro! O tipo de refeicao " << novoTipoRefeicao << " nao e valido. Escolha entre: peixe, carne, vegan, vegetariano." << endl;
        return;
    }
    int indiceMesa = -1;
    for (int i = 0; i < numMesas; i++) {
        if (mesas[i].ID == idMesa) {
            indiceMesa = i;
            break;
        }
    }
    if (indiceMesa == -1) {
        cout << "Erro! Mesa com ID " << idMesa << " nao encontrada." << endl;
        return;
    }
    mesas[indiceMesa].Preferencia = novoTipoRefeicao;
    mesas[indiceMesa].Clientes_sentados = 0;
    cout << "Mesa " << idMesa << " agora serve " << novoTipoRefeicao << ", e todos os clientes foram removidos." << endl;
}