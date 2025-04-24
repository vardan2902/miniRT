NAME				=	miniRT
CC					=	cc
MAKE				=	make
CFLAGS				=	-Wall -Wextra -Werror
LIBFTDIR			=	./libft
LIBFT				=	$(LIBFTDIR)/libft.a
MLXDIR				=	./minilibx-linux
LIBMLX				=	$(MLXDIR)/libmlx.a
OBJ_DIR				=	obj
SRC_DIR				=	src

MLX_DIR				=	mlx
MLX_SRCS			=	init.c handlers.c renderer.c

PARSING_DIR			=	parsing
PARSING_SRCS		=	general.c scene.c instructions.c unique_instructions.c

VALIDATING_DIR		=	validating
VALIDATING_SRCS		=	checkers.c args.c

UTILS_DIR			=	utils
UTILS_SRCS			=	$(addprefix $(MLX_DIR)/, $(MLX_SRCS))					\
						$(addprefix $(PARSING_DIR)/, $(PARSING_SRCS))			\
						$(addprefix $(VALIDATING_DIR)/, $(VALIDATING_SRCS))		\
						error.c		clean.c			float.c						\
						scene.c		clean_obj.c		clean_obj_list.c			\
						vector.c	vector_ops.c	calculations.c				\
						hit.c

PARSER_DIR			=	parser
PARSER_SRCS			=	ambient.c	camera.c	light.c	plane.c	sphere.c		\
						cylinder.c	parser.c

INTERSECTION_DIR	=	intersection
INTERSECTION_SRCS	=	intersect.c	sphere.c	plane.c	cylinder.c				\

RAY_DIR				=	ray
RAY_SRCS			=	generate_ray.c	trace_ray.c								\

LIGHT_DIR			=	light
LIGHT_SRCS			=	intensity.c												\

LOCAL_UTILS			=	local/print.c

SRC_FILES			=	$(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))				\
						$(addprefix $(PARSER_DIR)/, $(PARSER_SRCS))				\
						$(addprefix $(RAY_DIR)/, $(RAY_SRCS))					\
						$(addprefix $(INTERSECTION_DIR)/, $(INTERSECTION_SRCS))	\
						$(addprefix $(LIGHT_DIR)/, $(LIGHT_SRCS))				\
						$(LOCAL_UTILS)											\
						main.c
SRCS				=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS				=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
MKDIR				=	mkdir -p

INCLUDES			=	-Iinc -I$(MLXDIR) -I$(LIBFTDIR)
LINKERS				=	-L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lmlx_Linux -lXext -lX11 -lm -lz

all: $(NAME)

$(OBJ_DIR):
	$(MKDIR) $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(LIBMLX):
	$(MAKE) -C $(MLXDIR)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCLUDES) $(LINKERS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJ_DIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

bonus:
	@echo "TODO: implement bonuses."

.PHONY: all clean fclean re bonus
