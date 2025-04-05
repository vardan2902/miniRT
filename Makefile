NAME		=	miniRT
CC			=	cc
MAKE		=	make
CFLAGS		=	-Wall -Wextra -Werror
LIBFTDIR	=	./libft
LIBFT		=	$(LIBFTDIR)/libft.a
MLXDIR		=	./minilibx-linux
LIBMLX		=	$(MLXDIR)/libmlx.a
OBJ_DIR		=	obj
SRC_DIR		=	src

UTILS_DIR	=	utils
UTILS_SRCS	=	validator.c

SRC_FILES	=	$(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))	\
				main.c
SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
MKDIR		=	mkdir -p

INCLUDES	=	-Iinc -I$(MLXDIR) -I$(LIBFTDIR)
LINKERS		=	-L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lmlx_Linux -lXext -lX11 -lm -lz

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
