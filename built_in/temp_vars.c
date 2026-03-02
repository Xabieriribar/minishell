/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:10:23 by rick              #+#    #+#             */
/*   Updated: 2026/03/02 18:41:00 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_temp(char **arr)
{
	int	i;

	i = 0;
	if (arr[0] && arr[1] != NULL)
		return (false);
	if (ft_isalnum(arr[0]))
		return (false);
	while (arr[0] && arr[0][i])
	{
		if (!valid_key(arr[i]))
			return (false);
		i++;
	}
	return (true);
}

int	make_temp_var(t_data *data, char **arr)
{
	if (!valid_temp(arr))
		return (0);
	
}

int	b_export(char **arr, t_env **env, int out_nmb)
{
	int		i;
	int		status;
	char	*key;

	i = 0;
	status = 0;
	if (!arr[1])
		return (sort_and_print_export(*env, out_nmb), 0);
	while (arr[++i])
	{
		if (!valid_key(arr[i]))
			status = export_error(arr[i]);
		else
		{
			key = get_key(arr[i]);
			if (update_or_add(env, arr[i], key))
			{
				free(key);
				return (1);
			}
			free(key);
		}
	}
	return (status);
}


hay que agregar a la lista con el booleano prendido,

edgecases: que pasa si ya existe ? lo modifica?

ver de modificar el exit status correspondiente en success (es 0).

??Cuando terminamos la ejecucion nosotros? en success. si no es valido 
entonces return-false y que se encarge el resto del ejecutor.