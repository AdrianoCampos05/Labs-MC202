#include <stdio.h>
#include "partida.h"

int main()
{
    int no_of_games;
    partida game;
    scanf("%d", &no_of_games);

    for (int i = 0; i < no_of_games; i++)
    {
        game = new_game(i + 1);
        scan_players(&game);
        scan_no_of_circs(&game);
        scan_equipment(&game);
        update_cost(&game);
        scan_circuits(&game);
        print_summary(game);
        delete_game(&game);
    }
    return 0;
}