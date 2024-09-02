# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 16:27:22 by azinchen          #+#    #+#              #
#    Updated: 2024/09/02 19:52:43 by azinchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME 			=	fdf

# Directories
LIBFT_DIR		= 	./libft/
MLX_DIR			=	./MLX42
SRC_DIR 		=	src/
OBJ_DIR 		=	obj/

#Includes
LIBFT_INC		=	$(LIBFT_DIR)/include
MLX_INC			=	$(MLX_DIR)/include
INCLUDE 	=	include/

#Libraries (do I need first 2? omg I'm going mad with this Makefile)
LIBFT			=	$(LIBFT_DIR)/libft.a
MLX42			=	$(MLX_DIR)/build/libmlx42.a
LIB				=	-L$(MLX_DIR)/build -lmlx42 -L$(LIBFT_DIR) -ldl -lglfw -pthread -lm

#HZ!!!!!!!!!!!!!!!!!!!!!!!!!111
-framework OpenGL -framework AppKit

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
				@$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx  -o $(NAME) 

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