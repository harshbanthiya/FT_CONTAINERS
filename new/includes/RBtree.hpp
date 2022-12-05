
#ifndef RBTREE_H
# define RBTREE_H

# include <iostream>
# include <memory>
# include "utility.hpp"

# ifndef RBT_DEBUG
#  define RBT_DEBUG 0		//setting to 0 turns debug off
# endif

namespace ft
{
	template <typename T>
	class Node	
	{
		T 		data;
		bool	color;
		bool 	db;
		Node	*parent;
		Node 	*right_child;
		Node 	*left_child;
	};

template <typename Key, typename T, typename Alloc = std::allocator<ft::pair<const Key, T > > >
class	RBtree 
{
	private:
		
		struct	node
		{
			pointer		data;
			bool		color;
			bool		db;
			node		*parent;
			node		*right_child;
			node		*left_child;
		};

		typedef	Key						                                key_type;
		typedef	T						                                mapped_type;
		typedef	pair<const key_type, mapped_type>		                value_type;
		typedef	Alloc						                            allocator_type;
		typedef	typename allocator_type::reference		                reference;
		typedef typename allocator_type::const_reference	            const_reference;
		typedef	typename allocator_type::pointer		                pointer;
		typedef typename allocator_type::const_pointer		            const_pointer;
		typedef	ptrdiff_t					                            difference_type;
		typedef	size_t						                            size_type;
		
		//private members
		size_type		_size;
		node			*_tree;
		allocator_type		_alloc;
		std::allocator<node>	_node_alloc;

		//copy constructor
		RBtree(RBtree const & cpy) {*this = cpy;}

		//assignment overload
		RBtree & operator=(RBtree const & right)
		{
			_size = right._size;
			_tree = right->_tree;
			return (*this);
		}
	
		// false if leaf node	
		bool	_hasChilds(node *nd) const
		{
			if (nd->right_child == NULL && nd->left_child == NULL)
				return (false);
			return (true);
		}

		// return true if all children are black
		// or if it is a leaf node
		bool	_allBlack(node *nd) const
		{
			if (nd == NULL)
				return (true);
			if (!nd->color)
				return (false);
			if (!_hasChilds(nd))
				return (true);
			if (_getColorRight(nd) && _getColorLeft(nd))
				return (true);
			return false;
		}

		//get brother of nd
		node*	_getSibling(node *nd)
		{
			node	*parent = nd->parent;

			if (parent == NULL)
				return (NULL);
			if (parent->right_child && parent->right_child == nd)
				return (parent->left_child);
			return (parent->right_child);
		}

		//instead of replacing we swap nodes so
		//_clear can be used on the last remaining
		//sub_tree
		void	_swap(node *nda, node *ndb)
		{
			pointer	tmp;

			if (RBT_DEBUG)
				std::cout << ndb->data->first << " swapped with " <<
					nda->data->first << std::endl;	
			tmp = nda->data;
			nda->data = ndb->data;
			ndb->data = tmp;
		}

		bool	_getColorRight(node *nd) const
		{
			if (nd->right_child)
				return (nd->right_child->color);
			return (true);
		}
		
		bool	_getColorLeft(node *nd) const
		{
			if (nd->left_child)
				return (nd->left_child->color);
			return (true);
		}

		void	_resolveDB1(node *nd, node *sibling)
			{
				if (RBT_DEBUG)
					std::cout << "DB1) We are all black !" << std::endl;
				nd->db = false;
				if (nd->parent->color)
					nd->parent->db = true;
				else
					nd->parent->color = true;
				sibling->color = false;
				_checkDoubleBlack(nd->parent);
			}

		void	_resolveDB2(node *nd, node *parent, node *sibling)
			{
				bool	hlp;

				if (RBT_DEBUG)
					std::cout << "DB2) I am red !" << std::endl;
				hlp = parent->color;
				parent->color = sibling->color;
				sibling->color = hlp;
				if (parent->right_child == nd)
					_turn_right(sibling);
				else
					_turn_left(sibling);
				_checkDoubleBlack(nd);
			}

		void	_resolveDB3(node *nd,node *parent, node *sibling)
		{
			bool	hlp;

			//far child is red
			if (RBT_DEBUG)
			{
				std::cout << "node: " << nd->data->first << std::endl;
				std::cout << "parent: " << parent->data->first << std::endl;
				std::cout << "sibling: " << sibling->data->first << std::endl;
			}
			if (parent->right_child == sibling && !_getColorRight(sibling))
			{
				if (RBT_DEBUG)
					std::cout << "Sibling on the right" << std::endl;
				hlp = parent->color;
				parent->color = sibling->color;
				sibling->color = hlp;
				sibling->right_child->color = true;
				_turn_left(sibling);
			}
			if (parent->left_child == sibling && !_getColorLeft(sibling))
			{
				if (RBT_DEBUG)
					std::cout << "Sibling on the left" << std::endl;
				hlp = parent->color;
				parent->color = sibling->color;
				sibling->color = hlp;
				sibling->left_child->color = true;
				_turn_right(sibling);
			}
		}

		void	_checkDoubleBlack(node *nd)
		{
			node	*parent = nd->parent;
			node	*sibling;
			bool	hlp;

			if (!nd->db)
				return ;
			if (parent == NULL)
			{
				nd->db = false;
				return;
			}
			sibling = _getSibling(nd);
			if (RBT_DEBUG)
			{
				std::cout << "Doubleblack is " << nd->data->first << ", ";
				std::cout << "Sibling is " << sibling->data->first << ", ";
				if (!sibling->color)
					std::cout << "RED" << std::endl;
				else
					std::cout << "BLACK" << std::endl;
			}
			//has a sibling and sibling and it's children
			//are all black
			if (sibling && _allBlack(sibling))
				_resolveDB1(nd, sibling);

			//has a sibling but it is red color
			else if (sibling && !sibling->color)
				_resolveDB2(nd, parent, sibling);

			//check color of sibling's children and
			//resolve accordingly to it's distance from DB
			else if (sibling && sibling->color && !_allBlack(sibling))
			{
				//far child is black
				if (parent->right_child == sibling && _getColorRight(sibling))
				{
					hlp = sibling->color;
					sibling->color = _getColorLeft(sibling);
					if (sibling->left_child)
						sibling->left_child->color = hlp;
					_turn_right(sibling->left_child);
				}
				if (parent->left_child == sibling && _getColorLeft(sibling))
				{
					hlp = sibling->color;
					sibling->color = _getColorRight(sibling);
					if (sibling->right_child)
						sibling->right_child->color = hlp;
					_turn_left(sibling->right_child);
				}
				//mandatory or if far child is red
				_resolveDB3(nd, nd->parent, _getSibling(nd));
			}
		}

		void	_delete(node *nd)
		{
			node	*help = NULL;

			if (nd == NULL)
				return ;
			if (!_hasChilds(nd) && !nd->color)
			{
				if (RBT_DEBUG)
					std::cout << "Adress " << nd << ", key " <<
					nd->data->first << " was deleted" << std::endl;
				_clear(nd);
				return ;
			}
			else if (!_hasChilds(nd) && nd->color)
			{
				nd->db = true;
				_checkDoubleBlack(nd);
				_clear(nd);
			}
			else if (_hasChilds(nd))
			{
				if (nd->right_child)
				       help = _getSuccessor(nd->right_child);
				else if (nd->left_child)
				       help = _getPredecessor(nd->left_child);
				_swap(help, nd);
				_delete(help);
				return ;
			}
		}

		node	*_getSuccessor(node *nd)
		{
			while (nd->left_child)
				nd = nd->left_child;
			return (nd);
		}

		node	*_getPredecessor(node *nd)
		{
			while (nd->right_child)
				nd = nd->right_child;
			return (nd);
		}

		//add new node
		node	*_add_new_child(value_type const & chl, node *prt)
		{
			node	*tmp = _node_alloc.allocate(1);

			tmp->data = _alloc.allocate(1);
			_alloc.construct(tmp->data, chl);
			tmp->right_child = NULL;
			tmp->left_child = NULL;
			tmp->parent = prt;
			tmp->db = false;
			if (prt == NULL)
				tmp->color = true;
			else
				tmp->color = false;
			_size++;
			return (tmp);
		}

		//check and balance tree
		void	_check_parent(node *nd)
		{
			node	*sibling;
			node	*parent = nd->parent;
			node	*granny = parent->parent;

			//check parent color, if black exit
			if (parent->color)
				return ;
			
			if (granny->right_child == parent)
				sibling = granny->left_child;
			else
				sibling = granny->right_child;

			//check parent's sibling if it is NULL or black
			//then rotate and recolor
			if (sibling == NULL || sibling->color)
				_find_rotation(nd);
			else if (sibling && !sibling->color)
			{
				//if parents's sibling is red, recolor both 
				//and check parent of parent
				sibling->color = !sibling->color;
				parent->color = !parent->color;
				granny->color = !granny->color;
				if (granny->parent != NULL)
					_check_parent(granny);
				else
					granny->color = true;
			}
		}
	
		//check which nodes must rotate
		//in which directions, from top to bottom
		void	_find_rotation(node *nd)
		{
			std::string	code = "";
			node		*parent = nd->parent;
			node		*granny = parent->parent;
		
			if (granny->right_child == parent)
				code += "R";
			else if (granny->left_child == parent)
				code += "L";
			if (parent->right_child == nd)
				code += "R";
			else if (parent->left_child == nd)
				code += "L";
			if (code == "RL")
			{
				_turn_right(nd);
				_turn_left(nd);
				nd->color = !nd->color;
				nd->left_child->color = !nd->left_child->color;
			}
			if (code == "LR")
			{
				_turn_left(nd);
				_turn_right(nd);
				nd->color = !nd->color;
				nd->right_child->color = !nd->right_child->color;
			}
			if (code == "RR")
			{
				_turn_left(parent);
				parent->color = !parent->color;
				parent->left_child->color = !parent->left_child->color;
			}
			if (code == "LL")
			{
				_turn_right(parent);
				parent->color = !parent->color;
				parent->right_child->color = !parent->right_child->color;
			}
		}

		void	_turn_right(node *nd)
		{
			node	*root = nd->parent->parent;
			node	*hlp = nd->right_child;
		
			nd->parent->parent = nd;
			if (root == NULL)
			{
				_tree = nd;
			}
			else
			{
				if (root->right_child == nd->parent)
					root->right_child = nd;
				else
					root->left_child = nd;
			}
			nd->right_child = nd->parent;
			nd->parent = root;
			nd->right_child->left_child = hlp;
			if (hlp)
				hlp->parent = nd->right_child;
		}

		void	_turn_left(node *nd)
		{
			node	*root;
			node	*hlp;

			root = nd->parent->parent;
			hlp = nd->left_child;
			nd->parent->parent = nd;
			if (root == NULL)
			{
				_tree = nd;
			}
			else
			{
				if (root->right_child == nd->parent)
					root->right_child = nd;
				else
					root->left_child = nd;
			}
			nd->left_child = nd->parent;
			nd->parent = root;
			nd->left_child->right_child = hlp;
			if (hlp)
				hlp->parent = nd->left_child;
		}

		//deletes all nodes starting from *in
		//no argument given -> delete from root
		void	_clear(node *in = NULL)
		{
			if (_tree == NULL)
				return ;
			if (in == NULL)
				in = _tree;
			if (in->right_child)
				_clear(in->right_child);
			if (in->left_child)
				_clear(in->left_child);
			if (!_hasChilds(in))
			{
				if (RBT_DEBUG)
					std::cout << "Leaf found, deleting :" << in << std::endl;
				if (in->parent && in->parent->right_child == in)
					in->parent->right_child = NULL;
				else if (in->parent && in->parent->left_child == in)
					in->parent->left_child = NULL;
				_alloc.destroy(in->data);
				_alloc.deallocate(in->data, 1);
                _node_alloc.destroy(in);
				_node_alloc.deallocate(in, 1);
			}
			else if (RBT_DEBUG)
				std::cout << in << ">> " << in->left_child << " -- " 
					<< in->right_child << std::endl << std::endl;
			if (RBT_DEBUG)
				std::cout << in << " :: " << _tree << std::endl;
			if (in == _tree)
				_tree = NULL;
			_size--;
		}
		
		node	*_findKey(key_type const & key, node *nd) const
		{
			node	*bck = NULL;

			if (_tree == NULL)
				return (NULL);
			if (nd == NULL)
				nd = _tree;
			if (nd->data->first == key)
				return (nd);
			if (!_hasChilds(nd))
				return (NULL);
			if (nd->data->first > key && nd->left_child == NULL)
				return (NULL);
			else if (nd->data->first > key && nd->left_child)
				bck = _findKey(key, nd->left_child);
			if (nd->data->first < key && nd->right_child == NULL)
				return (NULL);
			else if (nd->data->first < key && nd->right_child)
				bck = _findKey(key, nd->right_child);
			return (bck);
		}

		void	_insert(value_type const & val)
		{
			node	*runner;
			node	*parent;
			
			if (!_tree)
			{
				_tree = _add_new_child(val, NULL);
				if (RBT_DEBUG)
					std::cout << std::endl << "Inserted " << val.first 
						<< std::endl;
				return ;
			}
			if (find(val.first))
			{
				if (RBT_DEBUG)
					std::cout << "Error: Key is already in the tree !" 
						<< std::endl;
				return ;
			}
			parent = NULL;
			runner = _tree;
			while (runner != NULL)
			{
				parent = runner;
				if ((val.first) < (runner->data->first))
					runner = runner->left_child;
				else 
					runner = runner->right_child;
			}
			if (RBT_DEBUG)
				std::cout << std::endl << "Inserted " << val.first << std::endl;
			if ((val.first) < (parent->data->first))
			{
				parent->left_child = _add_new_child(val, parent);
				_check_parent(parent->left_child);
			}
			else
			{
				parent->right_child = _add_new_child(val, parent);
				_check_parent(parent->right_child);
			}
			if (RBT_DEBUG)
				print();
		}

	public:
		typedef value_type *	valPtr;

		RBtree(void): _size(0), _tree(NULL) {}

		~RBtree(void) {_clear();}

		size_type	size(void) const {return (_size);}

		bool	empty(void) const {return (_size == 0);}

		void	clear(void) const {_clear();}

		bool	find(key_type const & key) const
		{
			if (_findKey(key, NULL))
				return (true);
			return (false);

		}

		valPtr	getValue(key_type const & key) const
		{
			node	*nd = _findKey(key, NULL);

			if (!nd)
				return (NULL);
			return (nd->data);
		}

		void	setValue(key_type const & key, mapped_type const & data)
		{
			node	*nd = _findKey(key, NULL);

			if (!nd)
				insert(key, data);
			nd->data->second = data;
		}

		void	erase(key_type const & key) 
		{
			node	*fnd = _findKey(key, NULL);

			if (!fnd)
			{
				if (RBT_DEBUG)
					std::cout << "Error: key not found" << std::endl;
				return ;
			}
			_delete(fnd);
		}
	
		void	erase(valPtr const & val)
		{
			erase(val->first);
		}

		void	insert(key_type const & key, mapped_type data)
			{
				_insert(ft::make_pair(key,data));
			}

		void	print(node *in = NULL) const
		{
			if (in == NULL)
				in = _tree;
			if (in == NULL)
				return;
			if (in->db)
				std::cout << "DB <<<";
			else
				std::cout << "   <<<";
			if (in->color)
				std::cout << "\033[0mBLACK :: ";
			else
				std::cout << "\033[1;31m  RED :: ";
			std::cout << "Parent: ";
			if (in->parent)
				std::cout << in->parent->data->first << " -- ";
			else
				std::cout << "NULL -- ";
			std::cout << "Adress: " << in << ", value: " << in->data->first;
			if (in->right_child == NULL)
				std::cout << ", right child is NULL" << std::endl;
			else
			{
				std::cout << ", right child is " << in->right_child << std::endl;
				print(in->right_child);
			}
			//left subtree
			if (in->db)
				std::cout << "DB <<<";
			else
				std::cout << "   <<<";
			if (in->color)
				std::cout << "\033[0mBLACK :: ";
			else
				std::cout << "\033[1;31m  RED :: ";
			std::cout << "Parent: ";
			if (in->parent)
				std::cout << in->parent->data->first << " -- ";
			else
				std::cout << "NULL -- ";
			std::cout << "Adress: " << in << ", value: " << in->data->first;
			if (in->left_child == NULL)
				std::cout << ", left child is NULL" << std::endl;
			else
			{
				std::cout << ", left child is " << in->left_child << std::endl;
				print(in->left_child);
			}
			std::cout << "\033[0m";
		}
};

} //end namespace

#endif
