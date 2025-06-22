NAME						=	miniRT
BONUS_NAME					=	miniRT-bonus
CC							=	cc
MAKE						=	make
CFLAGS						=	-Wall -Wextra -Werror
LIBFT_DIR					=	./libft
LIBFT						=	$(LIBFT_DIR)/libft.a
LIBMLX_DIR					=	./minilibx-linux
LIBMLX						=	$(LIBMLX_DIR)/libmlx.a
OBJ_DIR						=	obj
OBJ_BONUS_DIR				=	obj_bonus
SRC_DIR						=	./src

MLX_HANDLERS_DIR			=	handlers
MLX_HANDLERS_SRCS			=	keyboard_helpers.c	helpers.c mouse.c
MANDATORY_HANDLERS_SRCS		=	handlers/keyboard.c	handlers/light_helpers.c

MLX_DIR						=	mlx
MLX_SRCS					=	$(addprefix $(MLX_HANDLERS_DIR)/, $(MLX_HANDLERS_SRCS))				\
								init.c	renderer.c

PARSING_DIR					=	parsing
PARSING_SRCS				=	scene.c	general.c	instructions.c	unique_instructions.c

MANDATORY_PARSING_SRCS		=	check_props.c	assign_object.c

VALIDATING_DIR				=	validating
VALIDATING_SRCS				=	checkers.c	args.c
MANDATORY_VALIDATING_SRCS	=	is_identifier.c

INTERACTIONS_DIR			=	interactions
INTERACTIONS_SRCS			=	rotate.c	translate.c	resize.c
MANDATORY_INTERACTIONS_SRCS	=	resize_object.c

UTILS_DIR					=	utils
UTILS_SRCS					=	$(addprefix $(MLX_DIR)/, $(MLX_SRCS))								\
								$(addprefix $(PARSING_DIR)/, $(PARSING_SRCS))						\
								$(addprefix $(VALIDATING_DIR)/, $(VALIDATING_SRCS))					\
								error.c		clean.c			float.c			clean_obj.c				\
								vector.c	vector_ops.c	calculations.c	hit.c					\
								camera.c	light.c			cylinder_cap_utils.c

MANDATORY_UTILS_SRCS		=	$(addprefix $(MLX_DIR)/, $(MANDATORY_HANDLERS_SRCS))				\
								$(addprefix $(PARSING_DIR)/, $(MANDATORY_PARSING_SRCS))				\
								$(addprefix $(VALIDATING_DIR)/, $(MANDATORY_VALIDATING_SRCS))		\
								type_utils.c	clean_obj_list.c	scene.c	clean_light.c

PARSER_DIR					=	parser
PARSER_SRCS					=	ambient.c	camera.c
MANDATORY_PARSER_SRCS		=	light.c	plane.c	sphere.c	cylinder.c	parser.c

INTERSECTION_DIR			=	intersection
INTERSECTION_SRCS			=	sphere.c	plane.c	cylinder.c
MANDATORY_INTERSECTION_SRCS	=	intersect.c

RAY_DIR						=	ray
RAY_SRCS					=	generate_ray.c
MANDATORY_RAY_SRCS			=	trace_ray.c

LIGHT_DIR					=	light
LIGHT_SRCS					=	intensity.c

BONUS_DIR					=	bonus

SRC_FILES					=	$(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))							\
								$(addprefix $(PARSER_DIR)/, $(PARSER_SRCS))							\
								$(addprefix $(RAY_DIR)/, $(RAY_SRCS))								\
								$(addprefix $(INTERSECTION_DIR)/, $(INTERSECTION_SRCS))				\
								$(addprefix $(INTERACTIONS_DIR)/, $(INTERACTIONS_SRCS))				\
								main.c

MANDATORY_SRCS				=	$(addprefix $(LIGHT_DIR)/, $(LIGHT_SRCS))							\
								$(addprefix $(RAY_DIR)/, $(MANDATORY_RAY_SRCS))						\
								$(addprefix $(PARSER_DIR)/, $(MANDATORY_PARSER_SRCS))				\
								$(addprefix $(UTILS_DIR)/, $(MANDATORY_UTILS_SRCS))					\
								$(addprefix $(INTERSECTION_DIR)/, $(MANDATORY_INTERSECTION_SRCS))	\
								$(addprefix $(INTERACTIONS_DIR)/, $(MANDATORY_INTERACTIONS_SRCS))

BONUS_SRCS					=	assign_object_bonus.c bumpmap_bonus.c bumpmap_utils_bonus.c			\
								check_props_bonus.c checkerboard_bonus.c clean_light_bonus.c		\
								clean_obj_list_bonus.c cone_bonus.c instructions_bonus.c			\
								intersect_bonus.c is_identifier_bonus.c keyboard_bonus.c			\
								light_bonus.c parse_cone_bonus.c parse_cylinder_bonus.c				\
								parse_light_bonus.c parse_plane_bonus.c parse_sphere_bonus.c		\
								parser_bonus.c resize_bonus.c scene_utils_bonus.c					\
								trace_ray_bonus.c type_utils_bonus.c v_reflect_bonus.c

MANDATORY_SRC_FILES			=	$(MANDATORY_SRCS)	$(SRC_FILES)

BONUS_SRC_FILES				=	$(addprefix $(BONUS_DIR)/, $(BONUS_SRCS))							\
								$(SRC_FILES)

OBJS						=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(MANDATORY_SRC_FILES))
OBJS_BONUS					=	$(patsubst %.c, $(OBJ_BONUS_DIR)/%.o, $(BONUS_SRC_FILES))
MKDIR						=	mkdir -p

INCLUDES					=	-I./inc -I$(LIBMLX_DIR) -I$(LIBFT_DIR)
LINKERS						=	-L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR) -lmlx -lmlx_Linux -lXext -lX11 -lm -lz

all: $(NAME)

$(OBJ_DIR):
	$(MKDIR) $@

$(OBJ_BONUS_DIR):
	$(MKDIR) $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX):
	$(MAKE) -C $(LIBMLX_DIR)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCLUDES) $(LINKERS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -D BONUS -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBMLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

$(BONUS_NAME): $(LIBFT) $(LIBMLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) -D BONUS $(OBJS_BONUS) -o $(BONUS_NAME) $(INCLUDES) $(LINKERS)

bonus: $(BONUS_NAME)

.PHONY: all clean fclean re bonus
