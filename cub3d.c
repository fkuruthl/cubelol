/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:36:29 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/05 21:12:48 by fkuruthl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <ctype.h>  
int invisible_yes_no(char c)
{
    if(c == 32 || (c >= 9 && c<=11))
        return (1);
    return 0;
}
int is_valid_map_line(const char *line) {
    // Skip leading spaces
    while (*line && isspace(*line)) {
        line++;
    }

    // Ignore configuration lines (these should not be map lines)
    if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) ||
        !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) ||
        !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)) {
        return 0; // Not a valid map line
    }

    // Check for valid map characters (only '1', '0', 'N', 'E', 'W', 'S' are allowed)
    while (*line) {
        if (*line == '1' || *line == '0' || *line == 'N' || *line == 'E' || *line == 'W' || *line == 'S') {
            return 1; // Valid map line
        }
        if (!isspace(*line)) {  // Any non-whitespace invalid character
            return 0;
        }
        line++;
    }

    return 0; // If no valid map characters are found
}


int is_valid_config_line(const char *line) {
    while (*line && isspace(*line))  // Skip leading spaces
        line++;

    // Check if the line starts with valid identifiers
    return (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) ||
            !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) ||
            !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1));
}
void ft_free_pp(void **argv) {
    int i = 0;
    if (!argv) return; // Check for NULL array

    while (argv[i]) {
        if (argv[i]) {
            free(argv[i]);
            argv[i] = NULL; // Avoid double-free
        }
        i++;
    }
    free(argv);
}


void	init_color(int *color, char *element)
{
	char	**temp;
	int		r;
	int		g;
	int		b;

	temp = ft_split(element, ',');
	if (*temp)
	{
		r = atoi(temp[0]);
		g = atoi(temp[1]);
		b = atoi(temp[2]);
		ft_free_pp((void **)temp);
		if (r <= 255 && r >= 0 && g <= 255 && g >= 0 && b <= 255 && b >= 0)
		{
			*color = 65536 * r + 256 * g + b;
			return ;
		}		
	}
	 exit(perror_cube3d("colour invalid", 0));
}

void	init_texture(t_vars *vars, t_texture *txt, char *element, int val)
{
    if (!vars->mlx)
        exit(perror_cube3d("mlx is not initialized", 0));
    txt->img = mlx_xpm_file_to_image(vars->mlx, element,
            &txt->width, &txt->height);
    if (!txt->img)
        exit(perror_cube3d("Failed to load texture", 0));

    txt->addr = mlx_get_data_addr(txt->img, &txt->bits_per_pixel,
            &txt->line_length, &txt->endian);
    txt->pix_y = 0;
    txt->pix_x = 0;
    txt->txt = val;
}

t_img	*ft_t_img(void)
{
	static t_img			img;
	static t_texture		no;
	static t_texture		so;
	static t_texture		we;
	static t_texture		ea;

	if (!img.init)
	{
		img.no = &no;
		img.so = &so;
		img.we = &we;
		img.ea = &ea;
		img.f = 0;
		img.c = 0;
		img.init = 1;
	}
	return (&img);
}
static int	init_element(char *element, int val)
{
	if (element && val == NO)
		init_texture(ft_t_vars(), ft_t_img()->no, element, val);
	else if (element && val == SO)
		init_texture(ft_t_vars(), ft_t_img()->so, element, val);
	else if (element && val == WE)
		init_texture(ft_t_vars(), ft_t_img()->we, element, val);
	else if (element && val == EA)
		init_texture(ft_t_vars(), ft_t_img()->ea, element, val);
	else if (element && val == F)
		init_color(&ft_t_img()->f, element);
	else if (element && val == C)
		init_color(&ft_t_img()->c, element);
	else
		return (perror_cube3d("whattttt", 0));
	return (1);
}

int val_chk(t_img *img, char *temp)
{
    if(!*temp)
        return 0;
    if(strncmp(temp, "NO", 2) == 0 && !img->no->img )
        return(NO);
    if(strncmp(temp, "SO", 2) == 0 && !img->so->img )
        return(SO);
    if(strncmp(temp, "WE", 2) == 0 && !img->we->img )
        return(WE);
    if(strncmp(temp, "EA", 2) == 0 && !img->ea->img )
        return(EA);
    if(strncmp(temp, "F", 1) == 0 && !img->f )
        return(F);
    if(strncmp(temp, "C", 1) == 0 && !img->c )
        return(C);
    return 0;
}
int find_element(char *element, int fd)
{
    int val = 0, i = 0;
    while (*element && invisible_yes_no(*element))
        element++;

    val = val_chk(ft_t_img(), element);
    if (val > 0)
    {
        element++;
        if (val < 5)
            element++;
        while (invisible_yes_no(*element))
            element++;
        i = 0;
        while (element[i] && !invisible_yes_no(element[i]))
            i++;
        element[i] = '\0';

        if (init_element(element, val))
            return (1);

        close(fd);
        exit(perror_cube3d("Element initialization failed", 0));
    }
    return 0;
}


int ft_stronlyspaces(const char *line) {
    while (*line) {
        if (!isspace(*line)) {
            return 0;  // Contains non-space character
        }
        line++;
    }
    return 1;  // Only spaces or tabs
}

int fill(t_map *map, char *filename) {
    int fd;
    char *line;
    size_t width = 0;
    int height = 0;
    int map_started = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error: Failed to open file %s\n", filename);
        exit(perror_cube3d("Error opening map file", 0));
    }

    line = get_next_line(fd);
    while (line) {
        // Skip empty or whitespace-only lines (including extra newlines)
        if (ft_stronlyspaces(line)) {
            free(line);
            line = get_next_line(fd);
            continue;
        }

        // Check if line is valid map line
        int validity = is_valid_map_line(line);
        if (validity == 1) {  // Valid map line
            map_started = 1;
            size_t temp_width = ft_strlen(line);
            if (temp_width > width) {
                width = temp_width;
            }
            height++;
        }

        free(line);
        line = get_next_line(fd);
    }

    close(fd);

    if (height == 0) {
        fprintf(stderr, "Error: No valid map lines found\n");
        exit(perror_cube3d("No valid map lines in file", 0));
    }
    map->height = height;
    return width;  // Return width for later use in padding
}

void element_hunter(char *filename) {
    char *temp;
    int fd;
    int config_count = 6;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror_cube3d("Failed to open map file", 1);
        return;
    }

    temp = get_next_line(fd);
    while (temp && config_count > 0) {
        if (find_element(temp, fd)) {
            config_count--;
        }
        free(temp);
        temp = get_next_line(fd);
    }
    free(temp);

    if (config_count != 0) {
        close(fd);
        exit(perror_cube3d("Missing configuration elements", 0));
    }
    close(fd);
}



void store(t_map *map, char *filename) {
    int fd, map_line_count = 0;
    char *line;

    map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
    if (!map->map)
        exit(perror_cube3d("Memory allocation failed for map storage", 0));

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error: Failed to open file %s\n", filename);
        free(map->map);
        exit(perror_cube3d("Error opening map file", 0));
    }

    line = get_next_line(fd);
    while (line && map_line_count < map->height) {
        // Skip empty or newline-only lines
        if (ft_stronlyspaces(line)) {
            free(line);
            line = get_next_line(fd);
            continue;
        }

        // Check for valid map line
        int validity = is_valid_map_line(line);
        if (validity == 1) {  // Valid map line
            map->map[map_line_count++] = ft_strdup(line);
            if (!map->map[map_line_count - 1]) {
                fprintf(stderr, "Error: Memory allocation failed for map line\n");
                free(line);
                ft_free_pp((void **)map->map);
                exit(perror_cube3d("Failed to allocate memory for map line", 0));
            }

        }

        free(line);
        line = get_next_line(fd);
    }

    map->map[map_line_count] = NULL; // Null-terminate the array
    close(fd);

    // Ignore any extra lines after the map section
    if (get_next_line(fd)) {
        fprintf(stderr, "Error: Extra lines found after map data\n");
        close(fd);
        exit(perror_cube3d("Extra lines found after map data", 0));
    }
}



char cube3d(char *filename) {
    t_vars *vars;
    t_map map;

    validate_file_format(filename);

    vars = ft_t_vars();
    element_hunter(filename);

    map.width = fill(&map, filename);

    store(&map, filename);

    if (!path_struct(&map)) { 
        exit(perror_cube3d("map invalid", 0));
    }
    //vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
    game(vars, &map);
    mlx_loop(vars->mlx);
    return 0;
}
