#include <stdio.h>
#include <stdlib.h>
#include "survivor.h"


p_survivor new_survivor(int id, int key, char *name, char *surname)
{
    p_survivor s = malloc(sizeof(struct Survivor));
    s->id = id;
    s->key = key;
    s->name = name;
    s->surname = surname;
    s->dish = NULL;
    return s;
}


void set_dish(p_survivor s, char *dish)
{
    free(s->dish);
    s->dish = dish;
}


void print_info(p_survivor s, int key)
{
    printf("%s %s %s %d\n", s->name, s->surname, s->dish, key);
}


void destroy_survivor(p_survivor s)
{
    free(s->dish);
    free(s->name);
    free(s->surname);
    free(s);
}
