# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tosinga <tosinga@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/05 14:00:12 by tosinga       #+#    #+#                  #
#    Updated: 2022/04/06 10:37:00 by tosinga       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 			= pipex

SRCS 			=	main.c 			\
					envp_paths.c	\
					ft_split_add.c	\
					utils.c			\
					child_process.c		\
					childs_utils.c

LIB				= ./libft/libft.a
LIBFT_LOC		= libft
CFLAGS 			= -Wall -Wextra -Werror -fsanitize=address -g
CC				= gcc
HEADER 			= pipex.h

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	@$(MAKE) -s -C $(LIBFT_LOC)
	$(CC) $(CFLAGS) $(OBJECTS)  $(LIB) -o $(NAME)
	@echo "maked"

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJECTS)
	@$(MAKE) -s -C $(LIBFT_LOC) clean
	@echo "maked clean"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_LOC) fclean
	@echo "maked fclean"

re: fclean all

.PHONY: all clean fclean re