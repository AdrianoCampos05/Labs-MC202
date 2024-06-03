#ifndef __SURVIVOR_H__
#define __SURVIVOR_H__


struct Survivor
{
    int id;
    int key;
    char *name;
    char *surname;
    char *dish;
};

typedef struct Survivor *p_survivor;

/*Cria um novo sobrevivente.
____________
Parâmetros:
---- int id: código do sobrevivente
---- int key: dias sobrevividos
---- char *name: primeiro nome
---- char *surname: sobrenome

Obs: strings devem ser dinamicamente alocadas;
Guarda diretamente as strings fornecidas, não cópias.
_____________________
Retorna (p_survivor):
---- ponteiro para o sobrevivente*/
p_survivor new_survivor(int id, int key, char *name, char *surname);


/*Altera o prato pedido pelo sobrevivente.
____________
Parâmetros:
---- p_survivor s: o sobrevivente
---- char *dish: o nome do prato

Obs: string deve ser dinamicamente alocada;
Guarda diretamente a string fornecida, não uma cópia.
Libera a string antiga.*/
void set_dish(p_survivor s, char *dish);


/*Imprime as informações de um pedido.
____________
Parâmetros:
---- p_survivor s: o sobrevivente
---- int key: a prioridade final do pedido*/
void print_info(p_survivor s, int key);


/*Destrói um sobrevivente
___________
Parâmetro:
---- p_survivor s: o sobrevivente*/
void destroy_survivor(p_survivor s);


#endif //__SURVIVOR_H__