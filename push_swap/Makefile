# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/29 17:55:16 by mmoros            #+#    #+#              #
#    Updated: 2018/05/29 18:38:10 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

all: $(NAME)

$(NAME): $(OBJ)
	@make -C p_push_swap/
	@make -C p_checker/

clean:
	@make clean -C p_push_swap/
	@make clean -C p_checker/

fclean: clean
	@make fclean -C p_push_swap/
	@make fclean -C p_checker/

re: fclean all
