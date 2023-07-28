NAME	=	miniRT

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
RM		=	rm -rf

LIBDIR = ./libft
LIB = $(LIBDIR)/libft.a

MINILIBXDIR = ./minilibx-linux

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
HEADER += $(INCLUDES)render.h

vpath %.c src/
vpath %.c src/parser/
vpath %.c src/figures/
vpath %.c src/scene/
vpath %.c src/utils/
vpath %.c src/vector/
vpath %.c src/tests/
vpath %.c src/render/


SRCS += main.c

SRCS += error.c color.c color_operations.c
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
		ft_count_char.c is_unsigned_char_datatype.c keys_control.c

# Render
SRCS += ray_ops.c render.c tmp_renderingcircle.c

OBJ_DIR = ./obj/

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(LIB) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -I $(INCLUDES_LIB) -o $@ -fPIE

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -I$(INCLUDES_LIB) $(LIB_TERMCAP) $(LIB) $(MINILIBXDIR)/libmlx_Linux.a $(MINILIBXDIR)/libmlx.a -lXext -lX11 -lm -lz -o $(NAME) -fPIE

$(OBJ_DIR):
	mkdir $@

$(LIB):
	$(MAKE) -C $(LIBDIR)
	$(MAKE) -C $(MINILIBXDIR)
	cp $(LIBDIR)/*.a .
	cp $(MINILIBXDIR)/*.a .

fclean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)
	$(RM) -R $(OBJ_DIR)
	$(MAKE) clean -C $(MINILIBXDIR)
	$(RM) *.a

clean :
	$(MAKE) fclean -C $(LIBDIR)
	$(MAKE) clean -C $(MINILIBXDIR)
	$(RM) $(NAME)*

re : fclean
	$(MAKE)

.PHONY: all clean fclean re
