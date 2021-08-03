
NAME = philo

SRC = philo.c initialization.c monitoring.c tools.c

CC = gcc -Wextra -Werror -Wall -pthread

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME)

re: fclean all