#include "cube.h"
int	cubcheck(char *y)
{
	int	i;

	i = 0;
	while (y[i])
	{
		if (y[i] != 46)
			i++;
		else
		{
			return (0);
		}
		if (y[i + 1] == 'c')
		{
			if (y[i + 2] == 'u')
			{
				if (y[i + 3] == 'b')
				{
					if (y[i + 4] == '\0')
						return (1);
				}
			}
		}
	}
	return (0);
}
int main(int argc , char **argv)
{
	//t_vars *vars;
	//t_map map;
	if (argc != 2)
	{
		write(1,"invalid format",15); //wrote a message
		return (1); //changed to 1 instead of 0
	}
    if (cubcheck(argv[1]))
        cube3d(argv[1]);
	else
	{
		write(1,"invalid format2",15);
			return 1;	
	}
	//vars = ft_t_vars();
	// vars->image.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// vars->image.address = mlx_get_data_addr(vars->image.img,
	// 		&vars->image.bits_pixel, &vars->image.line_length,
	// 		&vars->image.endian);

	return(0);	
}