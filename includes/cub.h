#ifndef CUB_H
# define CUB_H
# define BUFFER_SIZE 1

# include "mlx.h"
# include "linux_azerty.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct s_img {
	void	*img;
	int		*addr;
	int		bpp;
	int		line;
	int		w;
	int		h;
	int		endian;
}				t_img;

typedef struct s_move {
	int		forward;
	int		back;
	int		left;
	int		right;
	int		rotright;
	int		rotleft;
	double	tdx;
	double	tplane_x;
}				t_move;

typedef struct s_scast
{
	double	sx;
	double	sy;
	double	invdet;
	double	transx;
	double	transy;
	int		sscreenx;
	int		sheight;
	int		swidth;
	int		starty;
	int		endy;
	int		startx;
	int		endx;
	t_img	img;
	int		d;
	int		texy;
	int		texx;
	int		color;
}			t_scast;

typedef struct s_info
{
	double	px;
	double	py;
	double	dx;
	double	dy;
	double	plane_x;
	double	plane_y;
	void	*mlx;
	void	*win;
	t_img	img;
	t_move	movement;
	double	move;
	double	rot;
	int		toogle_minimap;
	t_img	textures[5];
	double	*zbuf;
	double	*spritesdist;
}				t_info;

typedef struct s_sprite
{
	double	x;
	double	y;
}				t_sprite;

typedef struct s_game
{
	char			*textures_path[5];
	int				w;
	int				h;
	int				colors[2];
	int				fd;
	char			*str;
	int				rows;
	char			**map;
	char			player;
	int				player_column;
	int				player_row;
	int				count_sprites;
	int				bmp;
	int				minimap;
	int				maxline;
	t_sprite		*sprites;
	t_info			info;
}					t_game;

typedef struct s_sort
{
	double		*sprites;
	double		tmp;
	t_sprite	tmp2;
	int			i;
	int			y;
	int			check;
}				t_sort;

typedef struct s_cast
{
	double	cameraX;
	double	rx;
	double	ry;
	int		mapX;
	int		mapY;
	double	deltaX;
	double	deltaY;
	double	sideX;
	double	sideY;
	int		stepX;
	int		stepY;
	double	perpwall;
	double	wallX;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	int		i;
	int		texy;
	int		texx;
	double	step;
	double	textpos;
	t_img	img;
}				t_cast;

typedef struct s_gnl
{
	char	*buf;
	size_t	i;
	size_t	max;
	int		y;
}			t_gnl;

int		get_next_line(int fd, char **line);
//utils
size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_isspace_parse(char **str);
int		ft_isspace(char c);
void	double_atoi(char **str, size_t *w, size_t *h);
//error_and_clean
int		close_fd_and_err(char *str, t_game *game);
int		display_error(char *str, t_game *game);
void	free_map(char **map, int limit);
void	clean_textures(t_game *game);
//parse
void	parsing(char *file, t_game *game);
int		first_parse(char *str, t_game *game);
void	loop_first_parse(int *g, int *i, t_game *game);
int		check_two_letters(char **str);
int		check_emtpy_line(char *str);
int		textures(char *str, t_game *game, int i);
int		parsing_map(t_game *game);
int		is_player(char c);
int		resolution_parse(char *str, t_game *game);
int		alloc_map_line(t_game *game, char *str);
int		check_mapline(char *str, t_game *game, int g);
int		realloc_map(t_game *game);
//init and general
void	init_sprites(t_game *game);
int		init_textures(t_game *game);
int		bmp(t_img img, t_game *game);
void	init_game(t_game *game);
void	new_image(t_game *game, t_img *img);
int		check_arg(int ac, char **av, t_game *game);
int		quit(t_game *game);
int		verify_params(t_game *game);
//mlx
void	vertical_stripe(t_game *game, int x, int y1, int y2);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
//raycast
void	calc_step_side(t_info *info, t_cast *ry);
void	dda(t_game *game, t_cast *ray);
void	dda2(t_game *game, t_cast *ray);
void	sprite(t_game *game);
void	choose_good_texture(t_game *game, t_cast *ray);
void	draw_text(t_game *game, t_cast *ray, int x);
void	minimap(t_game *game);
void	movement(t_game *game);

#endif
