
NAME	=	philo

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -pthread

RM		=	rm	-rf

SRCS 	=	main.c		\
			parse.c		\
			actions.c	\
			utilis2.c	\
			utilis.c	\
			error_message.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) MKDIR

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

MKDIR:
	@mkdir obj
	@mv *.o obj

clean:
	$(RM) $(OBJS)
	$(RM) obj

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME) MKDIR

.PHONY = all clean fclean re MKDIR 
