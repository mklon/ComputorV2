#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/03 14:35:22 by oposhiva          #+#    #+#              #
#    Updated: 2018/06/03 14:35:54 by oposhiva         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = name

SOURCE =    src/main.cpp \
            src/Computor.class.cpp \
            src/Solver_1.class.cpp \
            src/Solver_2.class.cpp \
            src/Solver_4.class.cpp \
            src/Helper.class.cpp \


OBJECTS = $(SOURCE:.cpp=.o)

CC = g++

FL = -std=c++11

all: $(NAME) done

$(NAME): $(OBJECTS)
	@$(CC) $(FL) $(SOURCE) -o $(NAME)

%.o: %.cpp
	@$(CC) $(FL) -c $< -o $@

clean:
	@rm -f $(OBJECTS)
	@echo "\033[;33m[ It's clean ]\033[33;0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[;31m[ Deleted ]\033[33;0m"

re: fclean all

done:
	@echo "\033[;32m[ Well done ]\033[33;0m"

