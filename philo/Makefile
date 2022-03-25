SRCDIR = src/
OBJDIR = bin/
INCDIR = include/
######################################################################
SRCS = main.c\
		time.c\
		parse.c\
		error.c\
		utils.c\
		log.c\
		routine.c\
		lonely_philo.c
OBJS = $(addprefix $(OBJDIR),$(SRCS:.c=.o))
#####################################################################
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LINK = -pthread
INCPATH = -I$(INCDIR)
NAME = philo
######################################################################
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBPATH) $(LINK) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) $(INCPATH) $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all libft clean fclean re
