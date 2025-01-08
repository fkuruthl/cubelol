#include "cube.h"

// Function to find player position and direction
void player_facing(t_vars *vars, char dir)
{
    vars->player_side = 'N';
    if (dir == 'S')
        vars->player_side = 'S';
    else if (dir == 'E')
        vars->player_side = 'E';
    else if (dir == 'W')
        vars->player_side = 'W';
}

void find_player_position(char **map, t_vars *vars)
{
    if (!map)
    {
        fprintf(stderr, "Error: Map is NULL\n");
        exit(EXIT_FAILURE);
    }

    int i = -1;
    while (map[++i])
    {
        int j = -1;
        while (map[i][++j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                vars->pos_x = i;
                vars->pos_y = j;
                return;
            }
        }
    }

    fprintf(stderr, "Error: Player starting position not found in map\n");
    exit(EXIT_FAILURE);
}

void	rotate_left(t_vars *data)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(ROTATE_SPEED)
		- data->player.dir_y * sin(ROTATE_SPEED);
	data->player.dir_y = olddir_x * sin(ROTATE_SPEED) + data->player.dir_y
		* cos(ROTATE_SPEED);
	oldplane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(ROTATE_SPEED)
		- data->player.plane_y * sin(ROTATE_SPEED);
	data->player.plane_y = oldplane_x * sin(ROTATE_SPEED) + data->player.plane_y
		* cos(ROTATE_SPEED);
}

void	rotate_right(t_vars *data)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-ROTATE_SPEED)
		- data->player.dir_y * sin(-ROTATE_SPEED);
	data->player.dir_y = olddir_x * sin(-ROTATE_SPEED) + data->player.dir_y
		* cos(-ROTATE_SPEED);
	oldplane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-ROTATE_SPEED)
		- data->player.plane_y * sin(-ROTATE_SPEED);
	data->player.plane_y = oldplane_x * sin(-ROTATE_SPEED)
		+ data->player.plane_y * cos(-ROTATE_SPEED);
}
static void	init_player_direction_east(t_vars *data)
{
	while (data->player.dir_x < 1.0 && data->player.dir_y > 0)
	{
		rotate_right(data);
	}
}

static void	init_player_direction_west(t_vars  *data)
{
	while (data->player.dir_x > -1.0 || data->player.dir_y > 0.0)
	{
		rotate_left(data);
	}
}

static void	init_player_direction_north(t_vars  *data)
{
	while (data->player.dir_x > 0.0 || data->player.dir_y > -1.0)
	{
		rotate_left(data);
	}
}

void	init_player_direction(t_vars *data, char dir)
{
	data->player.dir_x = 0;
	data->player.dir_y = 1;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0;
	if (dir == 'E')
	{
		init_player_direction_east(data);
	}
	else if (dir == 'W')
	{
		init_player_direction_west(data);
	}
	else if (dir == 'N')
	{
		init_player_direction_north(data);
	}
}

void player_info(t_vars *vars, t_map *map)
{
    find_player_position(map->map, vars);
    // player_facing(vars, vars->map[(int)vars->pos_x][(int)vars->pos_y]);
    // vars->map[(int)vars->pos_x][(int)vars->pos_y] = 'T'; // Mark as visited
    // init_player_direction(vars, vars->player_side);
    // vars->radius = vars->map_y / 8.0; // Set camera height based on screen height
}
void init_keys(t_keys *keys)
{
    keys->w = 0;
    keys->s = 0;
    keys->a = 0;
    keys->d = 0;
    keys->left = 0;
    keys->right = 0;
}
void data_info(t_vars *vars, t_map *map)
{
    init_keys(&vars->keys);
    //vars->floor_color = color_to_hex(vars->textures->f); // Convert floor color to hex
    //vars->ceiling_color = color_to_hex(vars->textures->c); // Convert ceiling color to hex
    player_info(vars, map);

    //  init_texture(vars, vars->textures->no, "NO", NO);
    // init_texture(vars, vars->textures->so, "SO", SO);
    // init_texture(vars, vars->textures->ea, "EA", EA);
    // init_texture(vars, vars->textures->we, "WE", WE);
}

void game(t_vars *vars, t_map *map)
{
    data_info(vars, map);
	// cast_rays(vars, &vars->player);
	// mlx_hook(vars->win, 2, 0, &on_keypress, vars);
	// mlx_hook(vars->win, 3, 0, &on_keyrelease, vars);
	// mlx_hook(vars->win, 17, 1L << 17, &exit_game, vars);
	// mlx_loop_hook(vars->mlx, &hook_loop, vars);
	 mlx_loop(vars->mlx);
}