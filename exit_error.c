/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:12:54 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/08 20:50:23 by fkuruthl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_img *init_textures(t_vars *vars)
{
    t_img *textures = malloc(sizeof(t_img));
    if (!textures)
    {
        perror("Failed to allocate memory for textures");
        exit(EXIT_FAILURE);
    }

    // Initialize textures
    textures->no = malloc(sizeof(t_texture));
    textures->so = malloc(sizeof(t_texture));
    textures->we = malloc(sizeof(t_texture));
    textures->ea = malloc(sizeof(t_texture));

    if (!textures->no || !textures->so || !textures->we || !textures->ea)
    {
        perror("Failed to allocate memory for textures");
        exit(EXIT_FAILURE);
    }

    // Initialize each texture with appropriate file names and values
printf("Loading texture: %s\n", "Texture/NO.xpm");
init_texture(vars, textures->no, "Texture/NO.xpm", NO);
printf("Loading texture: %s\n", "Texture/SO.xpm");
init_texture(vars, textures->so, "Texture/SO.xpm", SO);
printf("Loading texture: %s\n", "Texture/WE.xpm");
init_texture(vars, textures->we, "Texture/WE.xpm", WE);
printf("Loading texture: %s\n", "Texture/EA.xpm");
init_texture(vars, textures->ea, "Texture/EA.xpm", EA);

    textures->init = 1; // Set initialization flag if necessary

    return textures;
}


t_vars *ft_t_vars(void)
{
    t_vars *vars;

    vars = (t_vars *)malloc(sizeof(t_vars));
    if (!vars)
        return (NULL);
    
    // Initialize all members to 0/NULL
    ft_memset(vars, 0, sizeof(t_vars));
    
    // Initialize textures
    vars->textures = init_textures(vars);
    if (!vars->textures)
    {
        free(vars);
        return (NULL);
    }

    return (vars);
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

