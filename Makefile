# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 10:46:55 by msacaliu          #+#    #+#              #
#    Updated: 2024/03/26 11:00:16 by msacaliu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror

SRC = main.c 

OBJ = $(SRS:.c=.o)

all :$(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cc $(FLAGS) $(SRC) -o $(NAME)
	rm -rf $(NAME).o

clean:
	rm -f *.o
	rm -f $(NAME)

fclean :clean
	rm -f $(NAME)
    
re :fclean all