CC		=	gcc
NAME	=	cub3D
CFLAGS	= 	-Wall -Wextra -Werror
LDFLAGS =	-lXext -lX11 -lm -ggdb
INC		=	./includes/
SRCS	=	./srcs/get_next_line.c ./srcs/init_and_parse.c ./srcs/minimap.c ./srcs/movement.c \
			./srcs/parse.c ./srcs/parse2.c ./srcs/parsemap.c ./srcs/raycast_dda.c ./srcs/sprite.c \
			./srcs/cub3d.c ./srcs/utils.c ./srcs/utils2.c ./srcs/utils3.c ./srcs/utils4.c ./srcs/init.c 
MLX_DIR =	./minilibx-linux/
DEP		=	xorg zlib1g-dev libxext-dev libxrandr-dev libx11-dev libbsd-dev libssl-dev
OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

bonus:		$(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -I$(INC) -I$(MLX_DIR) -c $< -o $@ 	

$(NAME): $(OBJS)
			make --silent -C $(MLX_DIR)
			$(CC) $(CFLAGS) $(OBJS) $(MLX_DIR)libmlx_Linux.a $(LDFLAGS) -o $(NAME)

clean:	
			make clean --silent -C $(MLX_DIR)
			rm -rf $(OBJS)
			rm -f *.bmp

fclean: clean
			rm -f $(NAME)

qwerty:
	sed -i "s%azerty.h%qwerty.h%" ./includes/cub.h

azerty:	
	sed -i "s%qwerty.h%azerty.h%" ./includes/cub.h

re: fclean all

install: sudo apt-get update && apt-get install $(DEP)

.PHONY: all bonus clean re install	
