SRCS	=	philo.c\
			thread.c\
			init.c\
			utils.c

OBJS	= ${SRCS:.c=.o}

NAME	= philo

GCC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

%.o:		%.c
		${GCC} ${CFLAGS} ${MLXFLAGS} -c $< -o $@

${NAME}:	${OBJS}
		gcc ${OBJS} -o ${NAME}

all:		${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean
		make all

.PHONY:		all clean fclean re bonus
