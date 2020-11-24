EXEC = philo_three

LIB = philo.a

SRCSFILE = main.c table.c fork.c pid.c utils/fct_libft.c utils/fct_philo.c utils/free.c utils/sem.c

SRCSDIR = ./srcs/

SRCS = $(addprefix $(SRCSDIR), $(SRCSFILE))

OBJS = $(SRCS:.c=.o)

CC = gcc -I./
CFLAGS = -Wall -Wextra -Werror

all : $(EXEC)

$(EXEC) : $(OBJS)
	ar rc $(LIB) $(OBJS)
	ranlib $(LIB)
	gcc -o $(EXEC) $(OBJS) -pthread -L./

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(EXEC) $(LIB)

re : fclean all

.PHONY : re fclean clean all
