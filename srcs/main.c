#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;

    // envp = нуль-терминальный массив указателей на строки переменных окружения.
    // Каждая строка в формате ИМЯ=ЗНАЧЕНИЕ

    int i;

    i = 0;
    while(envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }

    // char buf[1024];
    // while (1)
    // {
    //     write(1, "\e[32mminishell> \e[0m", 20);
    //     read(0, buf, 1024);
    //     //то, что в buf - идет в парсер
    // }
}