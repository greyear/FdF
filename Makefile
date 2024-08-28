# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 16:27:22 by azinchen          #+#    #+#              #
#    Updated: 2024/08/28 18:04:21 by azinchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME 			=	fdf

# Directories
LIBFT			= 	./libft/libft.a
LIBMLX			=	./libmlx/MLX42
INCLUDE_DIR 	=	include/
SRC_DIR 		=	src/
OBJ_DIR 		=	obj/

# Compiler and compilation flags
CC 				=	cc
CFLAGS 			=	-g -Wall -Wextra -Werror -I
RM				=	rm -f

# Source files
SRC				=	$(SRC_DIR)fdf.c \
					$(SRC_DIR)mouse.c \

# Object files         
OBJ 			=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

#Build rules
all: 			$(NAME)

$(LIBFT):
				@make -C ./libft

$(NAME): 		$(OBJ) $(LIBFT)
				@$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) 

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INCLUDE_DIR) -Imlx -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR)
				@$(RM) .cache_exists
				@make clean -C ./libft
		
fclean: 		clean 
				@$(RM) $(NAME)
				@$(RM) $(LIBFT)
			
re: 			fclean all

.PHONY: 		all clean fclean re

BLUE = \033[1;34m
GREEN = \033[1;32m
NC = \033[0m