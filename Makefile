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
RM		=	rm -f

LIBDIR = ./libft
LIB = $(LIBDIR)/libft.a

INCLUDES = ./includes/
INCLUDES_LIB = ./libft/includes/

HEADER += $(INCLUDES)minirt.h
HEADER += $(INCLUDES)vector.h
HEADER += $(INCLUDES)error.h
HEADER += $(INCLUDES)sphere.h
HEADER += $(INCLUDES)plane.h
HEADER += $(INCLUDES)cylinder.h
HEADER += $(INCLUDES)camera.h
HEADER += $(INCLUDES)scene.h
HEADER += $(INCLUDES)color.h
HEADER += $(INCLUDES)light.h
HEADER += $(INCLUDES)parser.h
HEADER += $(INCLUDES)test.h

vpath %.c src/
vpath %.c src/parser/
vpath %.c src/figures/
vpath %.c src/scene/
vpath %.c src/utils/
vpath %.c src/vector/
vpath %.c src/tests/


SRCS += main.c

SRCS += error.c color.c
SRCS += vector.c vector_operations.c vector_validation.c

# Scene
SRCS += scene.c camera.c light.c

# Figures
SRCS += sphere.c plane.c cylinder.c

# Parser
SRCS += parser.c camera_parser.c light_parser.c cylinder_parser.c \
		plane_parser.c sphere_parser.c plane_parser_tests.c

# Tests
SRCS += parser_tests.c color_tests.c test.c light_parser_tests.c \
		sphere_parser_tests.c

SRCS += ft_atof.c ft_free_strings.c ft_isdecimal.c is_float.c is_color.c \
		ft_count_char.c is_unsigned_char_datatype.c

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
	$(RM) $(NAME)*

re : fclean
	$(MAKE)
