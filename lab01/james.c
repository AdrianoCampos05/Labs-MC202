#include <stdio.h>

void count_sales(int output[], int all_sales[], int len)
{
    //Registra a quantidade de saladas de cada preço no vetor output
    output[0] = 0;
    output[1] = 0;
    output[2] = 0;

    for (int i = 0; i < len; i++)
    {
        if (all_sales[i] == 5)
            output[0]++;
        else if (all_sales[i] == 7)
            output[1]++;
        else
            output[2]++;
    }
}

void get_streak(int output[], int all_sales[], int len)
{
    //Registra em output o maior número de saladas consecutivas e o preço correspondente
    int best_item, best_streak = 0, current_streak = 0;
    int last_item = all_sales[0];

    for (int i = 0; i < len; i++)
    {
        if (all_sales[i] == last_item)
            current_streak++;
        else
            current_streak = 1;

        if (current_streak > best_streak)
        {
            best_streak = current_streak;
            best_item = all_sales[i];
        }

        last_item = all_sales[i];
    }

    output[0] = best_streak;
    output[1] = best_item;
}

int main()
{
    int len;
    scanf("%d", &len);
    int all_sales[999], sales_per_type[3], streak[2];

    for (int i = 0; i < len; i++)
        scanf("%d", &all_sales[i]);
    
    count_sales(sales_per_type, all_sales, len);
    get_streak(streak, all_sales, len);
    
    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n",
        sales_per_type[0], sales_per_type[1], sales_per_type[2]);
    printf("James vendeu %d saladas de %d reais consecutivamente", streak[0], streak[1]);

    return 0;
}
