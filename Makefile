# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 11:02:30 by amitcul           #+#    #+#              #
#    Updated: 2023/06/05 21:23:21 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	miniRT

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
RM		=	rm -rf

LIBDIR = ./libft
LIB = $(LIBDIR)/libft.a

INCLUDES = ./includes/
INCLUDES_LIB = ./libft/includes/

HEADER += $(INCLUDES)minirt.h
HEADER += $(INCLUDES)vector.h
HEADER += $(INCLUDES)error.h
HEADER += $(INCLUDES)sphere.h
HEADER += $(INCLUDES)camera.h
HEADER += $(INCLUDES)scene.h

vpath %.c src/
vpath %.c src/parser/
vpath %.c src/figures/
vpath %.c src/scene/
vpath %.c src/utils

SRCS += main.c

SRCS += error.c
SRCS += vector.c

# Scene
SRCS += camera.c
SRCS += scene.c

# Figures
SRCS += sphere.c

# Parser
SRCS += parser.c

# Tests
SRCS += parser_tests.c

OBJ_DIR = ./obj/

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(LIB)
	$(MAKE) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -I $(INCLUDES_LIB) -o $@ -fPIE

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -I$(INCLUDES_LIB) $(LIB_TERMCAP) -L./libft -lft -lm -o $@ -fPIE

$(OBJ_DIR):
	mkdir $@

$(LIB):
	$(MAKE) -C $(LIBDIR)

fclean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)
	$(RM) -R $(OBJ_DIR)

clean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)

re : fclean
	$(MAKE)
