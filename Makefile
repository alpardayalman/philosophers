NAME=philo
INCLUDES=inc
CFLAGS=-Werror -Wall -Wextra -o
SRCS=source/actions.c source/control.c source/init.c source/philosophers.c source/utilities.c
OBJS=actions.o control.o init.o philosophers.o utilities.o

all: fclean $(NAME)

$(NAME): $(OBJS)
	@gcc $(CFLAGS) $(NAME) $? inc/libft/libft.a -lm
	@mkdir object_files
	@mv *.o ./object_files/

$(OBJS): $(SRCS)
	@make -C inc/libft
	@gcc -c $? -I $(INCLUDES)

clean:
	rm -rf object_files/
	@make clean -C ./inc/libft

fclean:	clean
	rm -rf $(NAME)
	@make fclean -C inc/libft/

re:
	@make fclean

.PHONY:	all re clean fclean