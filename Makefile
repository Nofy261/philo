# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 16:59:13 by nolecler          #+#    #+#              #
#    Updated: 2025/04/24 17:21:25 by nolecler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -I. -g 

FSRCS = src/checking.c \
		src/eat.c \
		src/init.c \
		src/main.c \
		src/parsing_utils.c \
		src/parsing.c \
		src/routine.c \
		src/time.c \
		src/utils.c \

OFILES = $(FSRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
		$(ARRC) $(NAME) $(OFILES)

clean :
	rm -f $(OFILES)

fclean : clean
	rm -f $(NAME)
	
re : fclean $(NAME)

.PHONY: all clean fclean re