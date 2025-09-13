# Flags #

CC = cc

NAME = pipex

NAME_BONUS = pipex_bonus

HEADER = src/pipex.h

HEADER_BONUS = bonus/pipex_bonus.h

CFLAGS = -Wall -Werror -Wextra -g

# Files #

SRC = src/pipex.c src/parse.c src/ft_split.c src/str_utils.c src/process.c src/utils.c

SRC_BONUS = bonus/bonus.c bonus/parse_bonus.c bonus/process_bonus.c bonus/utils_bonus.c bonus/str_utils_bonus.c  bonus/ft_split_bonus.c bonus/get_next_line.c

OBJS = $(SRC:.c=.o)

OBJS_BONUS = $(SRC_BONUS:.c=.o)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Configuration #

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compiled Program"

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
	@echo "Compiled Bonus"

# Phonies #

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADER) $(SRC_BONUS) $(HEADER_BONUS)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo "Cleaned object files"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "Removed Program"

re: fclean all
