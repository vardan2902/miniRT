NAME					=	miniRT
CC						=	cc
MAKE					=	make
CFLAGS					=	-Wall -Wextra -Werror
LIBFT_DIR				=	./libft
LIBFT					=	$(LIBFT_DIR)/libft.a
LIBMLX_DIR				=	./minilibx-linux
LIBMLX					=	$(LIBMLX_DIR)/libmlx.a
OBJ_DIR					=	obj
OBJ_BONUS_DIR			=	obj_bonus
SRC_DIR					=	minirt/src
SRC_BONUS_DIR			=	minirt-bonus/src

MLX_HANDLERS_DIR		=	handlers
MLX_HANDLERS_SRCS		=	keyboard.c	helpers.c mouse.c
MLX_DIR					=	mlx
MLX_SRCS				=	$(addprefix $(MLX_HANDLERS_DIR)/, $(MLX_HANDLERS_SRCS))			\
							init.c	renderer.c

PARSING_DIR				=	parsing
PARSING_SRCS			=	general.c scene.c instructions.c unique_instructions.c

VALIDATING_DIR			=	validating
VALIDATING_SRCS			=	checkers.c args.c

INTERACTIONS_DIR		=	interactions
INTERACTIONS_SRCS		=	rotate.c translate.c resize.c

UTILS_DIR				=	utils
UTILS_SRCS				=	$(addprefix $(MLX_DIR)/, $(MLX_SRCS))							\
							$(addprefix $(PARSING_DIR)/, $(PARSING_SRCS))					\
							$(addprefix $(VALIDATING_DIR)/, $(VALIDATING_SRCS))				\
							error.c		clean.c			float.c								\
							scene.c		clean_obj.c		clean_obj_list.c					\
							vector.c	vector_ops.c	calculations.c						\
							hit.c		camera.c		type_utils.c						\
							cylinder_cap_utils.c

PARSER_DIR				=	parser
PARSER_SRCS				=	ambient.c	camera.c	light.c	plane.c	sphere.c				\
							cylinder.c	parser.c

INTERSECTION_DIR		=	intersection
INTERSECTION_SRCS		=	intersect.c	sphere.c	plane.c	cylinder.c

RAY_DIR					=	ray
RAY_SRCS				=	trace_ray.c generate_ray.c

LIGHT_DIR				=	light
LIGHT_SRCS				=	intensity.c

SRC_FILES				=	$(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))						\
							$(addprefix $(PARSER_DIR)/, $(PARSER_SRCS))						\
							$(addprefix $(RAY_DIR)/, $(RAY_SRCS))							\
							$(addprefix $(INTERSECTION_DIR)/, $(INTERSECTION_SRCS))			\
							$(addprefix $(LIGHT_DIR)/, $(LIGHT_SRCS))						\
							$(addprefix $(INTERACTIONS_DIR)/, $(INTERACTIONS_SRCS))			\
							main.c

UTILS_BONUS_SRCS		=	bumpmap.c resize_utils.c v_reflect.c
INTERSECTION_BONUS_SRCS	=	cone.c
PARSER_BONUS_SRCS		=	cone.c
STYLING_DIR				=	styling
STYLING_BONUS_SRCS		=	bumpmap.c	checkerboard.c

SRC_BONUS_FILES			=	$(SRC_FILES)													\
							$(addprefix $(UTILS_DIR)/, $(UTILS_BONUS_SRCS))					\
							$(addprefix $(INTERSECTION_DIR)/, $(INTERSECTION_BONUS_SRCS))	\
							$(addprefix $(PARSER_DIR)/, $(PARSER_BONUS_SRCS))				\
							$(addprefix $(STYLING_DIR)/, $(STYLING_BONUS_SRCS))


OBJS					=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJS_BONUS				=	$(patsubst %.c, $(OBJ_BONUS_DIR)/%.o, $(SRC_BONUS_FILES))
MKDIR					=	mkdir -p

MINIRT_INC				=	-Iminirt/inc
MINIRT_BONUS_INC		=	-Iminirt-bonus/inc

INCLUDES				=	-I$(LIBMLX_DIR) -I$(LIBFT_DIR)
LINKERS					=	-L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR) -lmlx -lmlx_Linux -lXext -lX11 -lm -lz

all: $(NAME)

$(OBJ_DIR):
	$(MKDIR) $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX):
	$(MAKE) -C $(LIBMLX_DIR)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(MINIRT_INC) $(INCLUDES) $(LINKERS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(MINIRT_INC) $(INCLUDES) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(MINIRT_BONUS_INC) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBMLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: $(LIBFT) $(LIBMLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME) $(MINIRT_BONUS_INC) $(INCLUDES) $(LINKERS)

.PHONY: all clean fclean re bonus
