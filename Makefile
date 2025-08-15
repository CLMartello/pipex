# Configuration --------------------------------------------------- #

NAME = pipex

HEADER = h_pipex.h

# Flags ----------------------------------------------------------- #

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

# Files ----------------------------------------------------------- #

C_FILES = pipex.c args.c ft_split.c str_utils.c process.c utils.c

O_DIR = objs

O_FILES = $(patsubst %.c, $(O_DIR)/%.o, $(C_FILES))

# Pattern Rule ---------------------------------------------------- #

all: $(NAME)

$(NAME): $(O_FILES)
	@$(CC) $(CFLAGS) $(O_FILES) -o $(NAME)
	@echo "Compiled Program"

$(O_DIR)/%.o: %.c $(HEADER) | $(O_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Directory Rule -------------------------------------------------- #

$(O_DIR):
	@mkdir -p $@

# Phonies --------------------------------------------------------- #

.PHONY: all clean fclean re norm

norm:
	@norminette -R CheckForbiddenSourceHeader $(C_FILES) $(HEADER)

clean:
	@rm -rf $(O_FILES) $(O_DIR)
	@echo "Cleaned object files"

fclean: clean
	@rm -rf $(NAME)
	@echo "Removed pipex"

re: fclean all
