EXEC = philo_two

LIB = philo.a

SRCSFILE = main.c table.c fork.c utils/fct_libft.c utils/utils.c utils/fct_philo.c utils/fct_libft2.c utils/free.c

SRCSDIR = ./srcs/

SRCS = $(addprefix $(SRCSDIR), $(SRCSFILE))

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS =  -I./ -Wall -Wextra -Werror

all : $(EXEC)

$(EXEC) : $(OBJS)
	ar rc $(LIB) $(OBJS)
	ranlib $(LIB)
	gcc -o $(EXEC) srcs/main.o $(LIB) -pthread -L./

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(EXEC) $(LIB)

re : fclean all

.PHONY : re fclean clean all
