EXEC = philo_one

LIB = philo.a

SRCSFILE = main.c table.c fork.c sophos.c utils/fct_libft.c utils/fct_libft2.c utils/fct_philo.c utils/free.c

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
