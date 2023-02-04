NAME = philo

SRC = ./srcs/philo.c ./srcs/initialization.c ./srcs/monitoring.c ./srcs/tools.c ./srcs/global_function.c

CC = gcc -Wextra -Werror -Wall -pthread

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME)

re: fclean all