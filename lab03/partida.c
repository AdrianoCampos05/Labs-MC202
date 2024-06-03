#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

partida new_game(int id)
{
    partida game;
    game.id = id;
    return game;
}

void scan_no_of_circs(partida *game)
{
    scanf("%d", &game->no_of_circs);
}

void scan_players(partida *game)
{
    scanf("%d", &game->players);
}

void scan_equipment(partida *game)
{
    scanf("%d", &game->equipment);   
}

void scan_circuits(partida *game)
{
    game->circs = malloc(game->no_of_circs * sizeof(circuito));
    if (game->circs == NULL)
        exit(-1);
    
    for (int i = 0; i < game->no_of_circs; i++)
    {
        game->circs[i] = new_circ(game->players);
        scan_info(game->circs + i);
    }
}

void update_cost(partida *game)
{
    game->cost = 10 * game->no_of_circs + 17.50 * game->equipment;
}

int hardest_circ(partida game)
{
    int current_total, highest_total = 0;
    int highest_id = 0;
    for (int i = 0; i < game.no_of_circs; i++)
    {
        current_total = total_strokes(game.circs + i);
        if (current_total > highest_total)
        {
            highest_total = current_total;
            highest_id = game.circs[i].id;
        }
    }
    
    return highest_id;
}

int player_total(partida game, int player)
{
    int total = 0;
    for (int i = 0; i < game.no_of_circs; i++)
        total += game.circs[i].strokes[player];
    return total;
}

void print_pce(partida game)
{
    printf("Num. de Jogadores: %d - ", game.players);
    printf("Num. de Circuitos: %d - ", game.no_of_circs);
    printf("Num. de Equipamentos: %d\n", game.equipment);
}

void print_cost(partida game)
{
    printf("Valor do Aluguel: R$ %.2f\n", game.cost);
}

void print_hardest_circ(partida game)
{
    printf("Circuito mais dificil: %d\n", hardest_circ(game));
}

void print_player_totals(partida game)
{
    for (int i = 0; i < game.players; i++)
        printf("Jogador %d: %d\n", i + 1, player_total(game, i));
}

void print_summary(partida game)
{
    printf("Partida %d\n", game.id);
    print_pce(game);
    print_cost(game);
    print_player_totals(game);
    print_hardest_circ(game);
    printf("##########\n");
}

void delete_game(partida *game)
{
    for (int i = 0; i < game->no_of_circs; i++)
        delete_circ(game->circs + i);
    free(game->circs);
    game->circs = NULL;
}
