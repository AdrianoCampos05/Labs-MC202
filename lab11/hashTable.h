#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__


#ifndef MAX_KEY_LEN
#define MAX_KEY_LEN 11
#endif


typedef struct
{
    char *key;
    int val;
} Entry;


struct h_table
{
    Entry *data;
    int len;
    int max_len;
};

typedef struct h_table *p_table;


/*Cria uma nova tabela de hash.
___________
Parâmetro:
---- int max_len: quantos elementos cabem na tabela
__________________
Retorna (p_table):
---- ponteiro para a tabela*/
p_table new_table(int max_len);


/*Insere um par chave/valor na tabela.
Se a chave já existe, sobrescreve seu valor.
____________
Parâmetros:
---- p_table ht: a tabela
---- char *key: a chave
---- int val: o valor

obs: guarda uma cópia de key, não a string original
___________
Retorna (int):
---- 0 se a inserção foi bem-sucedida
---- 1 se não há espaço para a inserção*/
int insert(p_table ht, char *key, int val);


/*Devolve o valor associado a uma chave.
Encerra o programa se chave não está na tabela.
____________
Parâmetros:
---- p_table ht: a tabela
---- char *key: a chave
_____________
Retorna (int):
---- o valor da chave*/
int get_value(p_table ht, char *key);


/*Altera o valor de uma chave.
____________
Parâmetros:
---- p_table ht: a tabela
---- char *key: a chave
---- int val: o novo valor*/
void set_value(p_table ht, char *key, int val);


/*Soma um número ao valor de uma chave.
____________
Parâmetros:
---- p_table ht: a tabela
---- char *key: a chave
---- int val: o valor adicionado*/
void add_to_value(p_table ht, char *key, int val);


/*Remove uma chave.
____________
Parâmetros:
---- p_table ht: a tabela
---- char *key: a chave*/
void remove_key(p_table ht, char *key);


/*Destrói uma tabela de hash.
___________
Parâmetro:
---- p_table ht: a tabela*/
void destroy_table(p_table ht);


#endif /*__HASH_TABLE_H__*/