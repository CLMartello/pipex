# Configuration --------------------------------------------------- #

NAME = pipex

HEADER = pipex.h

BONUS = pipex_bonus

HEADER_BONUS = pipex_bonus.h

# Flags ----------------------------------------------------------- #

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

# Files ----------------------------------------------------------- #

C_FILES = pipex.c parse.c ft_split.c str_utils.c process.c utils.c

BON_C_FILES = bonus.c parse_bonus.c process_bonus.c utils_bonus.c str_utils_bonus.c  ft_split_bonus.c get_next_line.c

O_DIR = objs

BON_O_DIR = bonus_objs

O_FILES = $(patsubst %.c, $(O_DIR)/%.o, $(C_FILES))

BON_O_FILES = $(patsubst %.c, $(BON_O_DIR)/%.o, $(BON_C_FILES))

# Pattern Rule ---------------------------------------------------- #

all: $(NAME)

$(NAME): $(O_FILES)
	@$(CC) $(CFLAGS) $(O_FILES) -o $(NAME)
	@echo "Compiled Program"

$(O_DIR)/%.o: %.c $(HEADER) | $(O_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BON_O_FILES) 
	@$(CC) $(CFLAGS) $(BON_O_FILES) -o $(BONUS)
	@echo "Compiled Bonus"

$(BON_O_DIR)/%.o: %.c $(BONUS_HEADER) | $(BON_O_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Directory Rule -------------------------------------------------- #

$(O_DIR):
	@mkdir -p $@

$(BON_O_DIR):
	@mkdir -p $@

# Phonies --------------------------------------------------------- #

.PHONY: all clean fclean re norm

norm:
	@norminette -R CheckForbiddenSourceHeader $(C_FILES) $(HEADER) $(BON_C_FILES) $(HEADER_BONUS)

clean:
	@rm -rf $(O_FILES) $(O_DIR) $(BON_O_FILES) $(BON_O_DIR)
	@echo "Cleaned object files"

fclean: clean
	@rm -rf $(NAME) $(BONUS)
	@echo "Removed Program"

re: fclean all
