##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SHELL		=	bash

CC			=	gcc

RULE		=	re

SRC			=	src/main.c		\
				src/strace.c	\
				src/utils.c		\

CFLAGS		=	-W -Wall -Wextra -Wpedantic -Wpadded -std=c99 -I include -O3

OBJ			=	$(SRC:.c=.o)

NAME		=	strace

all:    $(NAME) ## Build

$(NAME): $(OBJ) ## Linking
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

mac:	CC = clang
mac:	all

debeug: CFLAGS += -g3 ## Build with debeug symbols
debeug: RULE = debeug
debeug: all

mac_debeug: CC = clang ## Debeug for mac
mac_debeug: debeug

clean: ## Remove useless files
	rm -f *~
	rm -f $(OBJ)

fclean: clean ## Restart to 0
	rm -f $(NAME)

re:     fclean all

tests_run: all

docker_test: fclean
	docker run --rm -v $(PWD):/project -it epitech zsh -c "cd project && make"

help: ## Display help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: all clean fclean
