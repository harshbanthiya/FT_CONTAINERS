# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:52:34 by hbanthiy          #+#    #+#              #
#    Updated: 2022/09/28 13:28:36 by hbanthiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= ft_containers
CPP	 		:=	c++
CPPFLAGS 	:=  -Wall -Werror -Wextra -std=c++98 
CPPFLAGS	+= 	-isystem $(GTESTDIR)/include  
GPP			:= g++

SRCS 		:= main.cpp
OBJS_DIR 	:= object_files
OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

GTESTDIR	:= googletest/googletest
GTESTHDRS 	:= $(GTESTDIR)/include/gtest/*.h \
			   $(GTESTDIR)/include/gtest/internal/*.h

TESTS_DIR 	:= tests
TEST_FILES 	:= $(wildcard $(TESTS_DIR)/*.cpp)
TEST_OBJS	:= test_object_files
TESTS		:= $(addprefix $(TEST_OBJS)/, $(TESTS_FILES:.cpp=.o))


all: $(NAME)
		@echo "./ft_containers ready to use"

$(OBJS_DIR)/%.o: %.cpp
		@mkdir -p $(OBJS_DIR)
		@$(CPP) $(CPPFLAGS) -o $@ -c $^
		
$(TESTS_DIR)/$(TEST_OBJS)/%.o: %.cpp
		@mkdir -p $(TESTS_DIR)/$(TEST_OBJS)
		@$(CPP) $(CPPFLAGS) -o $@ -c $^

$(NAME): $(OBJS)
		@$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

test: 
		g++ -pthread -Igoogletest/googletest/googletest/include -c -o $(SRCS)
		@echo "No tests written yet"
clean:
		rm -rf $(OBJS_DIR) $(OBJS)

fclean: clean 
		rm -rf $(NAME)

re: fclean all
 
.PHONY : re fclean clean all 