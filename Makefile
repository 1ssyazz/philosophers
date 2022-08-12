SRC_MAIN	=	./create_thread.c \
				./dead_philo.c \
				./eat_sleeping.c \
				./error.c \
				./fork.c \
				./free.c \
				./init.c \
				./main.c \
				./routine.c

SRC_UTILS	=	ft_atoi.c \
				ft_isnbr.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_strncmp.c

OBJS_DIR		=	objs/
OBJS_UTILS_DIR	=	utils/objs/
SRC_UTILS_DIR	=	utils/

OBJS_MAIN	=	${SRC_MAIN:.c=.o}
OBJECTS_PREFIXED	=	${addprefix $(OBJS_DIR), $(OBJS_MAIN)}

OBJS_UTILS	=	${SRC_UTILS:.c=.o}
OBJECTS_UTILS_PREFIXED	=	${addprefix $(OBJS_UTILS_DIR), $(OBJS_UTILS)}

INCLUDE		=	./philo.h

CFLAGS		=	-Wall -Wextra -Werror -g -pthread -fsanitize=address

CC			=	gcc -g3

RM			=	rm -rf

NAME		=	philo

all:		${NAME}

${OBJS_DIR}%.o		:	%.c
				@mkdir -p ${OBJS_DIR}
				${CC} ${CFLAGS} -c $< -o $@

${OBJS_UTILS_DIR}%.o		:	${SRC_UTILS_DIR}%.c
				@mkdir -p ${OBJS_UTILS_DIR}
				${CC} ${CFLAGS} -c $< -o $@

${NAME}	:	${OBJECTS_PREFIXED} ${OBJECTS_UTILS_PREFIXED}
			${CC} ${OBJECTS_PREFIXED} ${OBJECTS_UTILS_PREFIXED} ${CFLAGS} -I${INCLUDE} -o ${NAME}

clean	:
				${RM} ${OBJECTS_PREFIXED} ${OBJECTS_UTILS_PREFIXED} ${OBJS_DIR} ${OBJS_UTILS_DIR}

fclean	:	clean
				${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re