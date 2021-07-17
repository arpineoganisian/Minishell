#include "minishell.h"

//void change_envp_oldpwd(char *key, char *value, t_data *data, int flag)
//{
//
//}

void change_envp_pwd(char *key, char *value, t_data *data, int flag)
{
	int		i;
	char	*tmp;

	tmp = str_3_join(key, "=", value);
	if (flag == 2 && check_and_change_env_vars(tmp, data) == -1)
		add_env_var(data, tmp);
	else if (flag == 1)
	{
		i = find_env_var("key", data->envp);
		if (i == -1)
			i = strings_counter(data->envp);
		data->envp[i] = tmp;
		data->envp[i + 1] = NULL;
	}
	free(tmp);
}

void	cd_err_handler(char *str1, char *str2, char *str3)
{
	char	*tmp;

	tmp = str_3_join(str1, str2, str3);
	error_handler(ft_strjoin(tmp, strerror(errno)), 1);
	free(tmp);
}

int	cd_home(t_data *data)
{
	char	*home;

	home = get_minishell_env("HOME", data->envp);
	if (!home)
	{
		error_handler("cd: HOME not set", 1);
		return (1);
	}
	if (chdir(home) == -1)
	{
		cd_err_handler("cd: ", home, ": ");
		free(home);
		return (1);
	}
	free(home);
	return (0);
}

int cd(char **cmd_line, t_data *data)
{
	int		ret;
	char	*old_pwd;
	char	*pwd;

	ret = 0;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		error_handler(strerror(errno), 1);
		return (1);
	}
	if (strings_counter(cmd_line) == 1)
		ret = cd_home(data);
	else if (chdir(cmd_line[1]) == -1)
	{
		cd_err_handler("cd: ", cmd_line[1], ": ");
		ret = 1;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		error_handler(strerror(errno), 1);
		return (1);
	}
//	change_envp_oldpwd("OLDPWD", old_pwd, data, 1);
	change_envp_pwd("PWD", pwd, data, 2);
	return (ret);
}
