# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 10:46:55 by msacaliu          #+#    #+#              #
#    Updated: 2024/05/03 12:21:18 by msacaliu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror -g #-lpthread -fsanitize=address -fno-omit-frame-pointer

SRC = main.c input_validation.c utils.c data_init.c synchronize_utils.c \
	write_status.c getters_setters.c dinner.c monitor.c

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