NAME	:=	malloc

SRCS	=	commun.c \
			leaks.c \
			malloc.c \
			mem_block.c \
			main.c

OBJS	=	$(addprefix ${OBJDIR}/,${SRCS:.c=.o})
CC		=	clang
FLAGS	=	-pthread -g3 #-fsanitize=address -g3
INCS	=	-I ./src
OBJDIR 	=	.objs
SRCDIR 	= 	./src

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

$(OBJDIR)/%.o: ${SRCDIR}/%.c
			@mkdir -p ${OBJDIR}
			@printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"
			${CC} ${FLAGS} ${INCS} -c $< -o $@ ${DEBUG}

${NAME}:	init ${OBJS}		
			@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
			${CC} ${FLAGS} ${INCS} -o ${NAME} ${OBJS} ${DEBUG}
			@printf "\n${_GREEN}${_BOLD}Compilation done !${_END}\n"

clean:		
			@printf "%-15s ${_RED}${_BOLD}${NAME}'s object files${_END}...\n" "Deleting"
			@rm -f ${OBJS} ${OBJS_BONUS}
			@printf "%-15s ${_RED}${_BOLD}${NAME}'s object directory${_END}...\n" "Deleting"
			@rm -rf ${OBJDIR}


fclean:		clean
			@printf "%-15s ${_RED}${_BOLD}${NAME}${_END}...\n" "Deleting"
			@rm -f ${NAME}

init:
			@printf "%-15s ${_GREEN}${_BOLD}${NAME}${_END}...\n" "Initiating"
			@mkdir -p ${OBJDIR}

show:
			@printf "${_GREEN}%-15s${_YELLOW}${NAME}${_END}\n" "NAME ="
			@printf "${_GREEN}%-15s${_YELLOW}${SRCS}${_END}\n" "SRCS ="
			@printf "${_GREEN}%-15s${_YELLOW}${OBJS}${_END}\n" "OBJS ="
			@printf "${_GREEN}%-15s${_YELLOW}${INCS}${_END}\n" "INCLUDES"
			@printf "${_GREEN}%-15s${_YELLOW}${CC}${_END}\n" "CC"
			@printf "${_GREEN}%-15s${_YELLOW}${FLAGS}${_END}\n" "CFLAGS ="

re:			fclean all

.PHONY:		all fclean clean init show re