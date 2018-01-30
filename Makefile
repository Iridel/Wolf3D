NAME=wolf3d
CC=gcc
FILES=main paint ft_rgb init_img draw_img init_screen init_coord \
		parse events raycast init_pair init_wolf draw_wolf jump move \
		set_screen
SRCDIR = srcs/
LIBDIR = libft/
INCDIR = includes/
MLXDIR = minilibx_macos/
FLAGS= -Wall -Werror -Wextra -I$(INCDIR) -I$(LIBDIR)$(INCDIR) -I$(MLXDIR)
LFLAG= -framework OpenGL -framework Appkit -L $(LIBDIR) -lft -L $(MLXDIR) -lmlx
LIB=$(addprefix $(LIBDIR), $(patsubst %, %.c, $(FILES)))
SRC=$(addprefix $(SRCDIR), $(patsubst %, %.c, $(FILES)))
OBJ=$(patsubst %, %.o, $(FILES))

all: $(NAME)

lib:
	make -C $(LIBDIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LFLAG) -o  $(NAME)

$(OBJ): $(SRC)
	$(MAKE) lib
	$(CC) $(FLAGS) $(SRC) -c

clean:
	make -C $(LIBDIR) clean
	rm -rf $(OBJ)

fclean: clean
	make -C $(LIBDIR) fclean
	rm -rf $(NAME)

re: fclean all
