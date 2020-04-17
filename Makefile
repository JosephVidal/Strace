##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

## ------ COLORS ------ ##

DEFAULT 	= 	"\033[00m"
RED			=	"\033[31m"
GREEN		=	"\033[1;32m"
TEAL		=	"\033[1;36m"
YELLOW		=	"\033[1;7;25;33m"
MAGENTA		=	"\033[1;3;4;35m"
ERROR		=	"\033[5;7;1;31m"
BLINK		=	"\033[5m"
END			=	"\n"

CC			=	gcc

RULE		=	re

SRC			=	src/main.c		\
				src/strace.c	\
				src/utils.c		\

CFLAGS		=	-W -Wall -Wextra -Wpedantic -Wpadded -std=c99 -I include -O3

OBJ			=	$(SRC:.c=.o)

NAME		=	strace

%.o	:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@ && \
	printf "["$(GREEN)"OK"$(DEFAULT)"] "$(TEAL)$<$(DEFAULT)" -----> "$(GREEN)$@$(DEFAULT)$(END) || \
	printf "["$(RED)"KO"$(DEFAULT)"] "$(BLINK)$(YELLOW)$^$(DEFAULT)$(END)

all:    $(NAME) ## Build

$(NAME): $(OBJ) ## Linking
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	@printf "["$(GREEN)"OK"$(DEFAULT)"]"$(TEAL)" Done : "$@$(DEFAULT)$(END) || \
	printf "["$(RED)"KO"$(DEFAULT)"]"$(BLINK)$(YELLOW)$(NAME)$(DEFAULT)$(END)

mac:	CC = clang
mac:	all

debeug: CFLAGS += -g3 ## Build with debeug symbols
debeug: RULE = debeug
debeug: all

mac_debeug: CC = clang ## Debeug for mac
mac_debeug: debeug

clean: ## Remove useless files
	@rm -f $(OBJ)
	@printf "["$(RED)"DEL"$(DEFAULT)"] $(OBJ)"$(END)

fclean: clean ## Restart to 0
	@rm -f $(NAME)
	@printf "["$(RED)"DEL"$(DEFAULT)"] $(NAME)"$(END)

re:     fclean all

tests_run: all

docker_test: fclean
	docker run --rm -v $(PWD):/project -it epitech zsh -c "cd project && make"

help: ## Display help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: all clean fclean
