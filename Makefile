CC 		= clang
NAME 	= minishell
BONUS_NAME = minishell_bonus
CFLAGS 	= -Wall -Wextra -Werror -fsanitize=address -g
LDFLAGS = -lreadline -lncurses
LIBFT = libft
SRC_DIR = src/
BONUS_DIR = src/bonus/
OBJ_DIR = src/obj/
BONUS_OBJ_DIR = src/bonus/obj/
MINISHELL_H = $(NAME).h

MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY 	= \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD	= \033[1m
RED		= \033[31;1m

SHARED_FILES = arg_list args_struct_a \
				args_struct_b args_struct_c \
				args_struct_d args_struct_e \
				env_list env_struct expand closures \
				chunks \

SRC_FILES = main $(SHARED_FILES)
BONUS_FILES = main_bonus

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
BONUS_SRC = $(addprefix $(BONUS_DIR), $(addsuffix .c, $(BONUS_FILES)))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(addsuffix .o, $(BONUS_FILES)))
SHARED_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(addsuffix .o, $(SHARED_FILES)))

OBJF = .cache_exists

all: $(NAME)

$(NAME): compiling $(OBJ)
		@echo
		@make all -C $(LIBFT)
		@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -L$(LIBFT) -lft -o $(NAME)
		@echo "$(YELLOW)Minishell compiled!$(RESET)"

bonus: $(BONUS_NAME)

$(BONUS_NAME): compiling_bonus $(BONUS_OBJ) $(SHARED_OBJ)
		@echo
		@make all -C $(LIBFT)
		@$(CC) $(CFLAGS) $(LDFLAGS) $(BONUS_OBJ) $(SHARED_OBJ) -L$(LIBFT) -lft -o $(BONUS_NAME)
		@echo "$(YELLOW)Minishell Bonus compiled!$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(MINISHELL_H)| $(OBJF)
		@mkdir -p $(dir $@)
		@echo "$(GREEN)Compiling: $(RESET)$(notdir $<)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)%.o: $(BONUS_DIR)%.c $(MINISHELL_H)| $(OBJF)
		@mkdir -p $(dir $@)
		@echo "$(GREEN)Compiling Bonus: $(RESET)$(notdir $<)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)%.o: $(SRC_DIR)%.c $(MINISHELL_H)| $(OBJF)
		@mkdir -p $(dir $@)
		@echo "$(GREEN)Compiling Shared: $(RESET)$(notdir $<)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR) $(BONUS_OBJ_DIR)

compiling:
		@echo "$(GREEN)Compiling Minishell: $(RESET)"

compiling_bonus:
		@echo "$(GREEN)Compiling Minishell Bonus: $(RESET)"

clean:
		@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
		@make clean -C $(LIBFT)
		@echo "$(BLUE)Cleaning Minishell's objects. $(RESET)"
		@echo

fclean:
		@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
		@rm -rf $(NAME) $(BONUS_NAME)
		@make fclean -C $(LIBFT)
		@echo "$(BLUE)Cleaning Minishell's executables.$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re compiling compiling_bonus
