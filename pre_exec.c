#include "cube.h"
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
    if (!vars || !map || !map->map) {
        fprintf(stderr, "Error: Invalid parameters in player_info\n");
        exit(EXIT_FAILURE);
    }

    find_player_position(map->map, vars);
    player_facing(vars, map->map[(int)vars->pos_x][(int)vars->pos_y]);
    map->map[(int)vars->pos_x][(int)vars->pos_y] = 'T'; // Mark as visited
    init_player_direction(vars, vars->player_side);
    vars->radius = vars->map_y / 8.0; // Set camera height based on screen height
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
    if (!vars || !map)
    {
        fprintf(stderr, "Error: NULL pointer passed to data_info\n");
        exit(EXIT_FAILURE);
    }

    // Initialize keys
    init_keys(&vars->keys);

    // Initialize player data
    player_info(vars, map);

    // Check if textures structure exists
    if (!vars->textures)
    {
        fprintf(stderr, "Error: Textures not initialized\n");
        exit(EXIT_FAILURE);
    }

    // Allocate texture objects if they haven't been allocated yet
    if (!vars->textures->no) vars->textures->no = malloc(sizeof(t_texture));
    if (!vars->textures->so) vars->textures->so = malloc(sizeof(t_texture));
    if (!vars->textures->ea) vars->textures->ea = malloc(sizeof(t_texture));
    if (!vars->textures->we) vars->textures->we = malloc(sizeof(t_texture));

    if (!vars->textures->no || !vars->textures->so || 
        !vars->textures->ea || !vars->textures->we)
    {
        fprintf(stderr, "Error: Failed to allocate texture objects\n");
        exit(EXIT_FAILURE);
    }

    // Initialize textures
    init_texture(vars, vars->textures->no, "NO", NO);
    init_texture(vars, vars->textures->so, "SO", SO);
    init_texture(vars, vars->textures->ea, "EA", EA);
    init_texture(vars, vars->textures->we, "WE", WE);
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