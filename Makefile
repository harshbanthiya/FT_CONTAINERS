# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:52:34 by hbanthiy          #+#    #+#              #
#    Updated: 2022/10/05 12:44:22 by hbanthiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= ft_containers
CPP	 		:=	c++
CPPFLAGS 	:=  -Wall -Werror -Wextra -std=c++98

SRCS 		:= _main.cpp
OBJS_DIR 	:= object_files
OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

TESTEXE 	:= test_containers
TESTCOMPLILER := g++
TESTFLAGS 	  := -std=c++11 
TESTSRCS 	  := main.cpp tests/exampletest.cpp


all: $(NAME)
		@echo "Usage: ./ft_containers ready to use"

$(OBJS_DIR)/%.o: %.cpp
		@mkdir -p $(OBJS_DIR)
		@$(CPP) $(CPPFLAGS) -o $@ -c $^

$(NAME): $(OBJS)
		@$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

test: 
		@$(TESTCOMPLILER) $(TESTFLAGS) $(TESTSRCS) -o $(TESTEXE)
		@echo "Usage: ./test_containers to run the tests."
clean:
		rm -rf $(OBJS_DIR) $(OBJS)

fclean: clean 
		rm -rf $(NAME) $(TESTEXE)

re: fclean all
 
.PHONY : re fclean clean all test 