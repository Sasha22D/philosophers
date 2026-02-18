NAME = philo

SRC_DIR = srcs
INCLUDE_DIR = include
OBJ_DIR = objs

SRCS =	main.c \
		init_functions.c \
		create_threads.c \
		monitor_thread.c \
		philo_routines.c \
		routine_actions.c \
		utils.c \
		free_all.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "./$(NAME) created."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "deleted obj files"

fclean: clean
	@rm -f $(NAME)
	@echo "deleted ./$(NAME)"

re: fclean all

.PHONY: all clean fclean re
