# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 10:46:55 by msacaliu          #+#    #+#              #
#    Updated: 2024/04/26 15:44:01 by msacaliu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror -g

SRC = main.c input_validation.c utils.c data_init.c synchronize_utils.c \
	write_status.c getters_setters.c dinner.c monitor.c

OBJ = $(SRS:.c=.o)



all :$(NAME)
	# lldb ./$(NAME)  you can run directly with the debugger like that

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