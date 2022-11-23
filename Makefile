NAME	:=	malloc

SRCS	=	${shell find ./src -name "*.c"}

OBJS	=	${SRCS:.c=.o}
CC		=	clang
FLAGS	=	-pthread -g3 #-fsanitize=address -g3
INCS	=	-I ./src

DEBUG	=	-DDEBUG

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m
_END= $'\033[37m

all:		${NAME}

.c.o:
			@printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"
			${CC} ${FLAGS} ${INCS} -c $< -o $@ ${DEBUG}

${NAME}:	${OBJS}		
			@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
			${CC} ${FLAGS} ${INCS} -o ${NAME} ${OBJS} ${DEBUG}
			@printf "\n${_GREEN}${_BOLD}Compilation done !${_END}\n"

clean:		
			@printf "%-15s ${_RED}${_BOLD}${NAME} binary files${_END}...\n" "Deleting"
			@rm -f ${OBJS} ${OBJS_BONUS}


fclean:		clean
			@printf "%-15s ${_RED}${_BOLD}${NAME}${_END}...\n" "Deleting"
			@rm -f ${NAME}

re:			fclean all

.PHONY:		all fclean clean all