# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/30 19:01:08 by rrhaenys          #+#    #+#              #
#    Updated: 2019/02/20 17:23:15 by rrhaenys         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = ft_select

ifndef VERBOSE
MAKEFLAGS += --no-print-directory
endif

### PATH ###
SRCS_PATH = src/
OBJ_PATH  = obj/
LIBFT_PATH = libft/

FLAGS = #-Wall -Werror -Wextra
INC = -I ./includes/ -I ./$(LIBFT_PATH)includes/

SRCS_NAME = $(shell ls src | grep -E ".+\.c")

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	DOP_FLAGS = -lreadline -ltinfo -lncurses -ltermcap
endif
ifeq ($(UNAME_S),Darwin)
	DOP_FLAGS = -lreadline -lncurses -ltermcap
endif
all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@echo "\033[92m$(LIBFT_PATH)\033[0m compiled."
	@gcc -g $(FLAGS) $(OBJ) $(INC) -L $(LIBFT_PATH) -lft -o $(NAME) $(DOP_FLAGS)
	@echo "\033[35m$(NAME)\033[0m created."

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	@gcc -g -c $(FLAGS) $(INC) $< -o $@
	@echo "\033[33m$<\033[0m compiled."
	
clean:
	@make -C $(LIBFT_PATH)/ clean
	@/bin/rm -rf $(OBJ_PATH)
	
fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	
re: fclean all

.PHONY: all, clean, fclean, re