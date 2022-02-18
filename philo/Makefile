SRCDIR = src/
OBJDIR = bin/
INCDIR = include/
######################################################################
SRCS = main.c
OBJS = $(addprefix $(OBJDIR),$(SRCS:.c=.o))
#####################################################################
CC = gcc
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
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all libft clean fclean re
