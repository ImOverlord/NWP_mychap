##
## EPITECH PROJECT, 2019
## nwp_myftp_2018
## File description:
## Makefile
##

NAME	=	client

DIR		=	src/

TDIR	=	tests/

MAIN	=	main.c

SRC		=	arguments/parse_args.c											\
			arguments/valid_arguments.c										\
			network/resolve_hostname.c										\
			socket/send_socket.c											\
			socket/create_raw_socket.c										\
			socket/fill_header.c											\
			handshake/init.c												\
			handshake/hash.c												\

TSRC	=	arguments/parse_args.spec.c										\
			arguments/valid_arguments.spec.c								\

SRCS	=	$(addprefix $(DIR), $(SRC))										\
			$(addprefix $(DIR), $(MAIN))									\

TSRCS	=	$(addprefix $(DIR), $(SRC))										\
			$(addprefix $(TDIR), $(TSRC))									\

OBJ		=	$(SRCS:.c=.o)

TOBJ	=	$(TSRCS:.c=.o)

CFLAGS	=	-W -Wall -Wextra -pedantic -I$(DIR) -lcrypto

TEST	=	tests_run


all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

debug:		$(OBJ)
			$(eval CFLAGS += -fsanitize=address -lasan)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

re:			fclean $(NAME)

clean:
			rm -rf $(OBJ)
			rm -rf $(TOBJ)
			find . -name '*.gcda' -delete
			find . -name '*.gcno' -delete
			rm -rf coverage/

fclean:		clean
			rm -rf $(NAME)
			rm -rf test

test_fl:
			$(eval CFLAGS += -lcriterion --coverage)

$(TEST):	test_fl $(TOBJ)
			$(CC) $(CFLAGS) $(TOBJ) -lcriterion --coverage -o test
			./test || true

cov:		$(TEST)
			gcovr -r . --exclude tests/

cov_html:	$(TEST)
			-@mkdir coverage/ 2>/dev/null || true
			gcovr -r . --exclude tests/ --html --html-details -o coverage/coverage.html

.PHONY:		all re tests_run clean fclean $(NAME)