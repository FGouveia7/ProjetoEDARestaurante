//
// Created by franc on 11/03/2025.
//

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#include <string>
using namespace std;
//---------------------------------------------------------------------------------------
/**
 * Estrutura que representa um cliente do restaurante.
 * @param id - id único do cliente
 * @param Pnome - primeiro nome do cliente
 * @param Unome - último nome do cliente
 * @param Preferencia - preferência alimentar do cliente ("carne", "vegan", "vegetariano","peixe")
 * @param Reserva - indica se o cliente possui reserva
 * @param Temporefeicao - tempo restante para terminar a refeição
 * @param Temporefeicaototal - tempo total originalmente atribuído para a refeição
 */

struct cliente {
    int id;
    string Pnome;
    string Unome;
    string Preferencia;
    bool Reserva;
    int Temporefeicao;
    int Temporefeicaototal;
};
//--------------------------------------------------------------------------------------------
/**
 *
 * @param ID - id da mesa
 * @param Capacidade - número máximo de clientes que a mesa pode receber
 * @param MaxReservas - número máximo de lugares reservados disponíveis na mesa
 * @param Reserva - quantidade atual de lugares reservados
 * @param Preferencia - tipo de preferência alimentar associada à mesa
 * @param Clientes_sentados - número atual de clientes sentados na mesa
 * @param Clientes - array de clientes atualmente sentados na mesa
 * @param Historico_clientes - array com os IDs dos clientes que já passaram pela mesa
 * @param Total_clientes_passados - total de clientes que já se sentaram na mesa
 */
struct Mesa {
    char ID;
    int Capacidade;
    int MaxReservas;               
    int Reserva;
    string Preferencia;
    int Clientes_sentados;
    cliente Clientes[10];
    int Historico_clientes[1000];
    int Total_clientes_passados;
};
//----------------------------------------------------------------------------------------------
/**
 *
 * @param clientes - array de clientes atualmente no balcão
 * @param quantidade - número atual de clientes no balcão
 * @param especialidade - tipo de refeição servida no balcão por padrão snack
 * @param horaPonta - indica se o sistema está na hora de ponta
 * @param ciclosRestantes - ciclos restantes até sair do balcão
 */
struct Balcao {
    cliente clientes[15];
    int quantidade;
    string especialidade = "snack";
    bool horaPonta;
    int ciclosRestantes;
};

#endif //ESTRUTURAS_H
