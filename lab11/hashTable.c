#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

#define PHI 0.618033988749895

p_table new_table(int max_len)
{
    p_table ht = malloc(sizeof(struct h_table));
    ht->data = malloc(max_len * sizeof(Entry));
    ht->max_len = max_len;
    ht->len = 0;
    for (int i = 0; i < max_len; i++)
    {
        ht->data[i].key = NULL;
    }
    return ht;
}


/*Retorna um hash de key.
Devolve valores de 0 a (size - 1)*/
int hash(char *key, int size)
{
    double a = 0, b;
    int len = strlen(key);
    for (int i = 0; i < len; i++)
    {
        a *= 0x100;
        b = PHI * key[i];
        b -= (int)b;
        a += b;
        a -= (int)a;
    }
    return (int)(size * a);
}


/*Retorna (int):
---- o índice da chave caso seja encontrada
---- o primeiro espaço vazio após hash(key)
---- -1 se a tabela está cheia e a chave não for encontrada*/
int __index(p_table ht, char *key)
{
    int i = hash(key, ht->max_len);

    // Lista tem espaço
    if (ht->len < ht->max_len)
    {
        while (ht->data[i].key && strcmp(key, ht->data[i].key))
            i = (i + 1) % ht->max_len;
        return i;
    }

    // Lista cheia
    int start = i;
    while (strcmp(key, ht->data[i].key))
    {
        i = (i + 1) % ht->max_len;
        if (i == start)
            return -1;
    }
    return i;
}


int insert(p_table ht, char *key, int val)
{
    int i = __index(ht, key);

    if (i == -1)
        return 1;

    free(ht->data[i].key);  // caso haja chave repetida
    ht->data[i].key = malloc(MAX_KEY_LEN);
    strncpy(ht->data[i].key, key, MAX_KEY_LEN);
    
    ht->data[i].val = val;
    ht->len++;
    return 0;
}


int get_value(p_table ht, char *key)
{
    int i = __index(ht, key);
    if (i == -1 || ht->data[i].key == NULL)
        exit(1);
    return ht->data[i].val;
}


void set_value(p_table ht, char *key, int val)
{
    int i = __index(ht, key);
    if (i == -1 || ht->data[i].key == NULL)
        return;
    ht->data[i].val = val;
}


void add_to_value(p_table ht, char *key, int val)
{
    int i = __index(ht, key);
    if (i == -1 || ht->data[i].key == NULL)
        return;
    ht->data[i].val += val;
}


void print_keys(p_table ht)
{
    printf("KEYS:\n\n");
    for (int i = 0; i < ht->max_len; i++)
    {
        printf("%s\n", ht->data[i].key);
    }
    printf("\n");
}


void __reinsert(p_table ht, int pos)
{
    int i = pos;
    char *temp = ht->data[i].key;
    while (temp)
    {
        ht->data[i].key = NULL;
        ht->len--;
        insert(ht, temp, ht->data[i].val);
        free(temp);
        i = (i + 1) % ht->max_len;
        temp = ht->data[i].key;
    }
}


void remove_key(p_table ht, char *key)
{
    int start = hash(key, ht->max_len);
    int i = start;
    while (ht->data[i].key && strcmp(key, ht->data[i].key))
    {
        i = (i + 1) % ht->max_len;
        if (i == start)  // Chave não encontrada
            return;
    }

    if(ht->data[i].key == NULL)  // Espaço vazio encontrado
        return;
    free(ht->data[i].key);
    ht->data[i].key = NULL;
    ht->len--;

    __reinsert(ht, (i + 1) % ht->max_len);
    
    return;
}


void destroy_table(p_table ht)
{
    for (int i = 0; i < ht->max_len; i++)
        free(ht->data[i].key);
    free(ht->data);
    free(ht);
}
