#include "minishell.h"

int main()
{
    char buf[1024];
    while (1)
    {
        write(1, "minishell> ", 11);
        read(0, buf, 1024);
        //то, что в buf идет в парсер
    }
}