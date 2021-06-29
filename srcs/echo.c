#include "minishell.h" 

void echo(t_parsing_data *parsing_data)
{
    if (parsing_data->single_quoted)
        printf("%s", parsing_data->str);


    if (!parsing_data->option_n)
        printf("\n");
    
    //exit code
}