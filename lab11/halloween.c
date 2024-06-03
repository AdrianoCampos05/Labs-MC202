#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 2048
#define MAX_KEY_LEN 11
#include "hashTable.h"


/*Lê as notas dadas por cada família.
Transfere os doces.
Imprime as mensagens adequadas.*/
void trick_or_treat(p_table families, char *name, char *surname, int house_no)
{
    int candy_obtained = 0;
    char family[11], grade;
    for (int i = 0; i < house_no; i++)
    {
        //Lê a nota
        scanf(" %10s %c%*s", family, &grade);

        int candy_owed = 1;
        if (grade == 'M')
            candy_owed = 2;
        else if (grade == 'B')
            candy_owed = 3;

        //Transfere os doces
        int available_candy = get_value(families, family);
        if (available_candy > candy_owed)
        {
            candy_obtained += candy_owed;
            add_to_value(families, family, -candy_owed);
            continue;
        }

        //Não há doces o suficiente
        candy_obtained += available_candy;
        if (available_candy > 0)
        {
            printf("A familia %s ficou sem doces.\n", family);
            set_value(families, family, 0);
        }
    }

    if (candy_obtained > 0)
        printf("%s %s recebeu %d doce(s) das familias.\n", name, surname, candy_obtained);
    else
        printf("%s %s recebeu 10 doces da prefeitura.\n", name, surname);
}


int main()
{
    p_table families = new_table(TABLE_SIZE);
    char command;
    char name[11], surname[11];
    int loop = 1, amount;  //Doces ou casas.

    while (loop)
    {
        scanf(" %c%*[^ \n]", &command);
        switch (command)
        {
            case 'E':   //Entrar
                scanf(" %10s %d", surname, &amount);
                insert(families, surname, amount);
                break;
            case 'S':   //Sair
                scanf(" %10s", surname);
                printf("A familia %s saiu com %d doce(s) sobrando.\n", surname, get_value(families, surname));
                remove_key(families, surname);
                break;
            case 'C':   //Comprar
                scanf(" %10s %d", surname, &amount);
                add_to_value(families, surname, amount);
                printf("A familia %s agora possui %d doces.\n", surname, get_value(families, surname));
                break;
            case 'T':   //Trick or Treat
                scanf(" %10s %10s %d", name, surname, &amount);
                trick_or_treat(families, name, surname, amount);
                break;
            case 'F':   //Finalizar
                loop = 0;
        }
    }
    destroy_table(families);
    return 0;
}