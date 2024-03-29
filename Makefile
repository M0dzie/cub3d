# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 12:20:01 by mehdisapin        #+#    #+#              #
#    Updated: 2023/08/01 13:54:53 by thmeyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ##################################### #
#               VARIABLES               #
# ##################################### #

NAME		=	cub3D

UNAME		=	$(shell uname)

NOCOLOR		=	\033[0m
BGREEN		=	\033[1;32m

HEADER		=	includes/cub3d.h

MAKEFILE	=	Makefile

LIBFT_DIR	=	includes/libft/
LIBFT_A		=	$(LIBFT_DIR)libft.a

ifeq ($(UNAME),Linux)
	MLX_DIR		=	includes/mlx_linux/
	MLX_A		=	$(MLX_DIR)libmlx_Linux.a
	MLX_FLAGS	=	-lm -lz -lXext -lX11
else
	MLX_DIR 	=	includes/mlx/
	MLX_A		=	$(MLX_DIR)libmlx.a
	MLX_FLAGS	=	-framework OpenGL -framework AppKit
endif

CFLAGS 		= 	-Wall -Wextra -Werror -O2

RM 			= 	rm -rf

AR 			= 	ar

ARFLAGS 	= 	-rcs


# ##################################### #
#                 PATHS                 #
# ##################################### #

SRCS_PATH	=	sources/

SRC_PARSING_PATH		=	$(SRCS_PATH)parsing/
SRC_EXECUTING_PATH		=	$(SRCS_PATH)executing/

OBJ_PARSING_PATH		=	$(SRC_PARSING_PATH).objs/
OBJ_EXECUTING_PATH		=	$(SRC_EXECUTING_PATH).objs/

OBJS_DIRS	=	$(OBJ_PARSING_PATH) $(OBJ_EXECUTING_PATH) 


# ##################################### #
#                SOURCES                #
# ##################################### #

SRC_EXECUTING_FILES		=	main.c	init_mlx.c	texture.c	render_3d.c	movement.c\
							raycasting.c

SRC_PARSING_FILES		=	parse_map.c	display_error.c	display_error_utils.c	\
							display_error_texture.c	init_map.c	init_texture.c	\
							parse_xpm.c init_utils.c	init_player.c	init_color.c

SRCS_PARSING		=	$(addprefix $(SRC_PARSING_PATH), $(SRC_PARSING_FILES))
SRCS_EXECUTING		=	$(addprefix $(SRC_EXECUTING_PATH), $(SRC_EXECUTING_FILES))

SRCS	=	$(SRCS_PARSING) $(SRCS_EXECUTING) 


# ##################################### #
#                OBJECTS                #
# ##################################### #

OBJS_PARSING		=	$(addprefix $(OBJ_PARSING_PATH),		\
						$(SRC_PARSING_FILES:.c=.o))
OBJS_EXECUTING		=	$(addprefix $(OBJ_EXECUTING_PATH),		\
						$(SRC_EXECUTING_FILES:.c=.o))

OBJS	=	$(OBJS_PARSING)	$(OBJS_EXECUTING)	

$(OBJ_PARSING_PATH)%.o: $(SRC_PARSING_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -o $@ -c $<

$(OBJ_EXECUTING_PATH)%.o: $(SRC_EXECUTING_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -o $@ -c $<


# ##################################### #
#                 RULES                 #
# ##################################### #

all:		make_libft make_mlx $(OBJS_DIRS) $(NAME)

make_libft:
			$(MAKE) -C $(LIBFT_DIR)

make_mlx:	
			@$(MAKE) -C $(MLX_DIR)

$(LIBFT_A):
			$(MAKE) make_libft

$(MLX_A):	
			@$(MAKE) make_mlx

$(OBJS_DIRS):
			mkdir -p $(OBJS_DIRS)

$(NAME):	$(LIBFT_A) $(MLX_A) $(OBJS)
ifeq ($(UNAME),Linux)
	$(AR) $(ARFLAGS) $(LIBFT_A) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT_A) $(MLX_A) $(MLX_FLAGS)
	@echo "$(BGREEN)Linux Compilation Done$(NOCOLOR)"
else ifeq ($(UNAME),Darwin)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT_A) $(MLX_A) $(OBJS) $(MLX_FLAGS)
	@echo "$(BGREEN)Mac OS Compilation Done$(NOCOLOR)"
endif

clean:
			$(MAKE) clean -C $(LIBFT_DIR)
			$(MAKE) clean -C $(MLX_DIR)
			$(RM) $(OBJS)

fclean:
			$(MAKE) fclean -C $(LIBFT_DIR)
			$(MAKE) clean
			$(RM) $(NAME)
			$(RM) $(OBJS_DIRS)

re:
			$(MAKE) fclean
			$(MAKE) all

.PHONY:		all clean fclean re make_libft make_mlx
