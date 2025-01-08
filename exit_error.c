/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:12:54 by inkahar           #+#    #+#             */
/*   Updated: 2024/12/13 14:35:54 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
t_vars *ft_t_vars(void)
{
    static t_vars vars;

    if (!vars.init)
    {
        vars.mlx = mlx_init();
        if (!vars.mlx)
        {
            perror("Error initializing MLX");
            exit(EXIT_FAILURE);
        }
        vars.map_x = 0;
        vars.map_y = 0;
        vars.init = 1;
    }
    return (&vars);
}

void	free_cube3d(t_vars *vars)
{
	if (vars->map)
		ft_free_pp((void **)vars->map);
}
int	perror_cube3d(char *str, int flag)
{
	free_cube3d(ft_t_vars());
	dprintf (2, "Error ");
	if (flag)
		perror (str);
	else
		dprintf (2, "%s\n", str);
	return (0);
}

