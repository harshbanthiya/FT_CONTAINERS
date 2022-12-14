COMPILER = clang++
INC_DIR		= ../includes/

SRCS_DIR	= ../src/
SRCS		= $(addprefix $(SRCS_DIR), rb_tree.cpp )
FLAGS_DEBUG = --std=c++98 -fsanitize=address -g3
FLAGS = --std=c++98 

alloc_test:
	@$(COMPILER) $(FLAGS_DEBUG) -I$(INC_DIR) $(SRCS) alloc_test.cpp -o alloc.out 

functor_test:
	@$(COMPILER) $(FLAGS_DEBUG)	 -I$(INC_DIR) $(SRCS) functor_test.cpp -o functor.out 

iterator_test:
	@$(COMPILER) $(FLAGS_DEBUG)	 -I$(INC_DIR) $(SRCS) iterator_test.cpp -o iterator.out 

vector:
	@$(COMPILER) $(FLAGS)	 -I$(INC_DIR) $(SRCS) vector_test.cpp -o vector.out 

map:
	@$(COMPILER) $(FLAGS)	 -I$(INC_DIR) $(SRCS) map_test.cpp -o map.out 

stack:
	@$(COMPILER) $(FLAGS) -I$(INC_DIR) $(SRCS) stack_test.cpp -o stack.out 

set:
	@$(COMPILER) $(FLAGS)	 -I$(INC_DIR) $(SRCS) set_test.cpp -o set.out 

pair:
	@$(COMPILER) $(FLAGS)	 -I$(INC_DIR) $(SRCS) pair_test.cpp -o pair.out 

raii:
	@$(COMPILER) $(FLAGS)	 -I$(INC_DIR) $(SRCS) raii_test.cpp -o raii.out 

tree:
	@$(COMPILER) $(FLAGS)	 -I$(INC_DIR) $(SRCS) tree_test.cpp -o tree.out 

type_traits:
	@$(COMPILER) $(FLAGS)	 -I$(INC_DIR) $(SRCS) type_traits.cpp -o type_traits.out 

testtest:
	@$(COMPILER) $(FLAGS)	 -I$(INC_DIR) $(SRCS) testtest.cpp -o testtest.out 

throwtest:
	@$(COMPILER) $(FLAGS)	 -I$(INC_DIR) $(SRCS) throw_test.cpp -o throwtest.out 

clean:
	rm -f vector.out map.out stack.out set.out alloc.out functor.out iterator.out pair.out raii.out tree.out type_traits.out testtest.out throwtest.out