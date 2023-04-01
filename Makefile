# START of Makefile color and typo of messages

_END='\033[0m'
_GREEN='\033[32m'

# END	of Makefile color and typo of messages

CC	?=	gcc

RM	?=	rm -rf

NAME	=	lem_in

ARCHIVER	=	ar

TESTS_BIN	:=	*.gc*
TESTS_BIN_NAME	:=	unit_tests
TESTS_LIBS	:=	-lcriterion --coverage

CFLAGS		+=	-Wall -Wextra -Werror -fPIC -pedantic
CPPFLAGS	+=	-iquote ./includes

MAIN	=	${addsuffix .c, ${addprefix ./, main }}
SRCS	=	${addsuffix .c, ${addprefix ./srcs/, ants array dijkstra lemin llist moves parser }}

ALL_SRCS	:=	${MAIN}
ALL_SRCS	+=	${SRCS}

TESTS_SRCS	:=	${SRCS}
TESTS_SRCS	+=	${addsuffix .c, ${addprefix ./tests/tests_, free }}

OBJS	=	${ALL_SRCS:.c=.o}
TESTS_OBJS	:=	${TESTS_SRCS:.c=.o}

%.o : %.c
	@$ ${CC} ${CFLAGS} ${CPPFLAGS} -c $< -o $@
	@echo "${CC} ${CFLAGS} ${CPPFLAGS} -c $< -o $@ ["${_GREEN}"OK"${_END}"]"
.SUFFIXES: .o .c

all:	${NAME}

${NAME}:	${OBJS}
	@${CC} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}
	${RM} ${NAME}
	${RM} ${NAME:.so=.a}
	${RM} logs.out

fclean:	clean
	${RM} ${TESTS_OBJS}
	${RM} ./${TESTS_BIN}
	${RM} ./tests/${TESTS_BIN}
	${RM} ${TESTS_BIN_NAME}

re:	fclean all

debug:	CFLAGS	+=	-g3
debug:	re

tests_run:	${TESTS_OBJS}
	${CC} ${TESTS_LIBS} ${TESTS_OBJS} -o ${TESTS_BIN_NAME}
	./${TESTS_BIN_NAME}
	${RM} ${TESTS_OBJS}
	${RM} ${TESTS_BIN_NAME}

valgrind:	CFLAGS	+=	-g3
valgrind:	${TESTS_OBJS}
	${CC} ${TESTS_LIBS} ${TESTS_OBJS} -o ${TESTS_BIN_NAME}
	valgrind --trace-children=yes ./${TESTS_BIN_NAME}
	${RM} ${TESTS_OBJS}
	${RM} ${TESTS_BIN_NAME}

.PHONY:	all clean fclean re debug tests_run valgrind static
