# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:52:34 by hbanthiy          #+#    #+#              #
#    Updated: 2022/11/24 10:18:31 by hbanthiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = my_containers
NAME_STD = real_containers

SRCS = main.cpp

OBJS = ${SRCS:.cpp=.o}

INC = includes/

CXX  = clang++

RM  = rm -f

INC_CMP = -I .

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all:			$(NAME) $(NAME_STD)

$(NAME):		$(SRCS) $(INC)
				$(CXX) $(CXXFLAGS) $(INC_CMP) $(SRCS) -o $(NAME)

$(NAME_STD):	$(SRCS) $(INC)
				$(CXX) $(CXXFLAGS) $(INC_CMP) $(SRCS) -o $(NAME_STD) -D TEST_NAMESPACE=std

$(OBJS):		$(INC)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME) $(NAME_STD)

re:			 fclean all

.PHONY: all clean fclean re