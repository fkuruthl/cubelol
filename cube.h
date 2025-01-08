// #ifndef CUBE_H
// #define CUBE_H

// # include <unistd.h>
// # include <stdlib.h>
// # include <mlx.h>
// # include <limits.h>
// # include <stdio.h>
// # include <string.h>
// #include <fcntl.h>
// #include <fcntl.h>
// #include <string.h>
// #include "libft/libft.h"

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 42
// # endif

// # define WINDOW_WIDTH 1000
// # define WINDOW_HEIGHT 1000

// typedef struct s_vars		t_vars;
// typedef struct s_map
// {
//     char **map;
//     int width;
//     int height;
// }       t_map;




// typedef struct s_texture
// {
// 		int			txt;
// 	void		*img;
// 	int			width;
// 	int			height;
// 	float		pix_x;
// 	float		pix_y;
// 	char		*addr;
// 	int			bits_per_pixel;
// 	int			line_length;
// 	int			endian;
// }				t_texture;
//  typedef struct s_img
// {
// 	t_texture	*no;
// 	t_texture	*so;
// 	t_texture	*we;
// 	t_texture	*ea;
// 	int			f;
// 	int			c;
// 	int			init;
// }				t_img;

// typedef struct s_image
// {
// 	void				*img;
// 	char				*address;
// 	int					bits_pixel;
// 	int					line_length;
// 	int					endian;
// 	int					width;
// 	int					height;
// }						t_image;
// typedef struct s_vars
// {
// 	void		*mlx;
// 	void		*win;
// 	char		*img;
// 	t_image     image;
// 	char		*addr;
// 	int			bits_per_pixel;
// 	int			line_length;
// 	int			endian;
// 	char		**map;
// 	int			map_y;
// 	int			map_x;
// 	int			pos; // player starting postion
// 	float		pos_x; // player  x position
// 	float		pos_y; //player y position
// 	int			player_side;
// 	int			map_on;
// 	int			enemy_win;
// 	t_image				north_texture;
// 	t_image				south_texture;
// 	t_image				west_texture;
// 	t_image				east_texture;
// 	int			end_game;
// 	int			steps;
// 	int			time;
// 	int			init;
// 	int			radian;
// 	int			player_angle;
// 	int			rotation;
// 	float		player_cos;
// 	float		player_sin;
// 	float		radius;
// 	double		speed;
// }
// t_vars;
//  typedef struct s_keys
// {
// 	int w;
// 	int a;
// 	int s;
// 	int d;
	
// }				t_keys;


// enum	e_element
// {
// 	NO = 1,
// 	SO = 2,
// 	WE = 3,
// 	EA = 4,
// 	F = 5,
// 	C = 6,

// };

// char	*get_next_line(int fd);

// void game(t_vars *vars);
// size_t	ft_strlen(char const *str);
// char	*ft_strch(char const *str, int c);
// char	*ft_strcpy(char *dest, char *src);
// char	*ft_strdup(char const *src);
// char	*ft_strjoin(char const *s1, char const *s2);
// void ft_free_pp(void **argv);
// char cube3d(char *c);
// void	free_cube3d(t_vars *vars);
// int	perror_cube3d(char *str, int flag);
// t_vars	*ft_t_vars(void);
// int path_struct(t_map *map);
// int	ft_array_length(char **array);
// char **ft_dup_cpp(char **src, int len);
// void validate_file_format(char *filename);

// int is_valid_config_line(const char *line);
// int is_valid_map_line(const char *line);
// #endif

#ifndef CUBE_H
#define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000

# define SKY_COLOR 0x87CEEB
# define FLOOR_COLOR 0x8B4513

# define ROTATE_SPEED 0.05

typedef struct s_map
{
    char **map;
    int width;
    int height;
} t_map;

typedef struct s_texture
{
    void *img;
    char *addr;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
    int txt;
    float pix_x;
    float pix_y;
} t_texture;
typedef struct s_player
{
	double				cam_height;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				speed;
	//t_line				line;
	double				camera_x;
	char				direction;

}						t_player;

typedef struct s_img
{
    t_texture *no;
    t_texture *so;
    t_texture *we;
    t_texture *ea;
    int f; // Floor color
    int c; // Ceiling color
    int init;
} t_img;

typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
} t_keys;

typedef struct s_vars
{
    void *mlx;
    void *win;
    t_img *textures;          // Pointer to texture structure
    t_img image;            // Image for rendering
    char **map;               // Map grid
    int map_x;                // Map width in cells
    int map_y;                // Map height in cells
    float pos_x;              // Player x position
    float pos_y;              // Player y position
	t_player			player;
    int player_side;          // Player's starting direction
    float player_cos;         // Cosine of player's direction
    float player_sin;         // Sine of player's direction
    float radius;             // Camera radius
    double speed;             // Movement speed
    int rotation;             // Rotation direction (-1, 0, 1)
    t_keys keys;              // Key states
    t_img north_texture;    // North wall texture
    t_img south_texture;    // South wall texture
    t_img west_texture;     // West wall texture
    t_img east_texture;     // East wall texture
    int floor_color;          // Floor color (hex)
    int ceiling_color;        // Ceiling color (hex)
    int init;                 // Initialization flag
} t_vars;

enum e_element
{
    NO = 1,
    SO = 2,
    WE = 3,
    EA = 4,
    F = 5,
    C = 6,
};

// Function prototypes
char *get_next_line(int fd);

void game(t_vars *vars, t_map *map);
void player_info(t_vars *vars, t_map *map);
void data_info(t_vars *vars, t_map *map);
size_t ft_strlen(char const *str);
char *ft_strch(char const *str, int c);
char *ft_strcpy(char *dest, char *src);
char *ft_strdup(char const *src);
char *ft_strjoin(char const *s1, char const *s2);
void ft_free_pp(void **argv);
char cube3d(char *filename);
void free_cube3d(t_vars *vars);
int perror_cube3d(char *str, int flag);
t_vars *ft_t_vars(void);
int path_struct(t_map *map);
int ft_array_length(char **array);
char **ft_dup_cpp(char **src, int len);
void validate_file_format(char *filename);
int is_valid_config_line(const char *line);
int is_valid_map_line(const char *line);
void init_player_direction(t_vars *vars, char dir);
int color_to_hex(int color);
void init_texture(t_vars *vars, t_texture *txt, char *element, int val);

#endif
