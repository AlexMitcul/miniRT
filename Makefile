
NAME	=	miniRT

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -O3 -g# -fsanitize=address
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
HEADER += $(INCLUDES)hooks.h
HEADER += $(INCLUDES)keys.h

vpath %.c src/
vpath %.c src/parser/
vpath %.c src/figures/
vpath %.c src/scene/
vpath %.c src/utils/
vpath %.c src/vector/
vpath %.c src/render/
vpath %.c src/hooks/

SRCS += main.c

SRCS += error.c color.c color_operations.c
SRCS += vector.c vector_operations.c vector_validation.c \
		vector_coordinates_update.c vector_operations_1.c

# Scene
SRCS += scene.c camera.c light.c

# Figures
SRCS += sphere.c plane.c cylinder.c

# Parser
SRCS += parser.c camera_parser.c light_parser.c cylinder_parser.c \
		plane_parser.c sphere_parser.c

SRCS += ft_atof.c ft_free_strings.c ft_isdecimal.c is_float.c is_color.c \
		ft_count_char.c is_unsigned_char_datatype.c

SRCS += menu.c menu_info.c sphere_info.c plane_info.c \
		cylinder_info.c light_info.c

SRCS += hooks_test.c

# Render
SRCS += interceptor.c interceptor_hit_points.c math_utils.c  picasso.c \
		picasso_utils.c rays.c ray_tracer.c

OBJ_DIR = ./obj/

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(LIB) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -I $(INCLUDES_LIB) -o $@ -fPIE

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -I$(INCLUDES_LIB) $(LIB_TERMCAP) $(LIB) libmlx_Linux.a libmlx.a -lXext -lX11 -lm -lz -o $(NAME) -fPIE

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
