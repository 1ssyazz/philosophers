SRC_MAIN	=	./create_thread.c \
				./dead_philo.c \
				./eat_sleeping.c \
				./error.c \
				./fork.c \
				./free.c \
				./init.c \
				./main.c \
				./routine.c

SRC_UTILS	=	./utils/ft_atoi.c \
				./utils/ft_isnbr.c \
				./utils/ft_putnbr_fd.c \
				./utils/ft_putstr_fd.c \
				./utils/ft_strncmp.c

OBJS_MAIN	=	${SRC_MAIN:.c=.o}

OBJS_UTILS	=	${SRC_UTILS:.c=.o}

INCLUDE		=	./philo.h

CFLAGS		=	-Wall -Wextra -Werror -g -pthread -g -fsanitize=address

CC			=	gcc -g3

RM			=	rm -f

NAME		=	philo

all:		${NAME}

%.o		:	%.c
				${CC} ${CFLAGS} -c $< -o $@

${NAME}	:	${OBJS_MAIN} ${OBJS_UTILS}
			${CC} ${OBJS_MAIN} ${OBJS_UTILS} ${CFLAGS} -I${INCLUDE} -o ${NAME}

clean	:
				${RM} ${OBJS_MAIN} ${OBJS_UTILS}

fclean	:	clean
				${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re