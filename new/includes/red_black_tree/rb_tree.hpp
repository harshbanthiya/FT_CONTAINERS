#pragma once 

#include <iostream>
#include "utility.hpp"
#include <memory>

# ifndef RBT_DEBUG
#  define RBT_DEBUG 0		//setting to 0 turns debug off
# endif

namespace ft
{
    template <typename Key, typename T, typename Alloc = std::allocator<ft::pair<const Key, T> > >
    class _red_black_tree
    {
        private:
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef pair<const key_type, mapped_type>           value_type;
            typedef Alloc                                       allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef ptrdiff_t                                   difference_type;
            typedef size_t                                      size_type;
   
            struct node
            {
                pointer     data;
                bool        color;
                bool        double_black;
                node        *parent;
                node        *left_child;
                node        *right_child;
            };

            size_type               __size;
            node                    *__tree;
            allocator_type          __alloc;
            std::allocator<node>    __node_alloc;
        
        // Copy Constructor 
        _red_black_tree(_red_black_tree const &cpy) {*this = cpy;}
        
        // Assignment Overload 
        _red_black_tree& operator=(_red_black_tree const &rhs) 
        {
            __size = rhs.__size;
            __tree = rhs.__tree;
            return (*this);
        }

        // True if both children are not NILL 
        bool    has_children(node *tree_node) const
        {
            if (tree_node->right_child == NULL && tree_node->left_child == NULL)
                return (false);
            return (true);
        }

        // True if both children black or if it is a leaf node {default black children}
        bool    has_all_black_children(node *tree_node) const
        {
            if (tree_node == NULL)
                return (true);
            if (!tree_node->color)
                return (false);
            if (!has_children(tree_node))
                return (true);
            if (get_right_child_color(tree_node) && get_left_child_color(tree_node))
                return (true);
            return (false);
        }

        // Get Sibling node 
        node    *get_sibling_node(node *tree_node)
        {
            node *parent = tree_node->parent;

            if (parent == NULL)
                return (NULL);
            if (parent->right_child && parent->right_child == tree_node)
                return (parent->left_child);
            return (parent->right_child);
        }

        // Using swap instead of replacing nodes ; clear can be used on the subtree that way
        void    swap(node *nodeA, node *nodeB)
        {
            pointer     tmp;

            if (RBT_DEBUG)
                std::cout << nodeB->data->first << " swapped with " << nodeA->data->first << "\n"; 
            tmp = nodeA->data;
            nodeA->data = nodeB->data; 
            nodeB->data = tmp;
        }

        // Get color of right child 
        bool    get_right_child_color(node *tree_node) const 
        {
            if (tree_node->right_child)
                return (tree_node->right_child->color);
            return (true);
        }

        // Get color of right child 
        bool    get_left_child_color(node *tree_node) const 
        {
            if (tree_node->left_child)
                return (tree_node->left_child->color);
            return (true);
        }

        // Resolve Double Black 1 - All black - sibling and children    
        void    _resolve_double_black1(node *tree_node, node *sibling)
        {
            if (RBT_DEBUG)
                std::cout << "DB1: all black case \n";
            tree_node->double_black = false;
            if (tree_node->parent->color)
                tree_node->parent->double_black = true;
            else 
                tree_node->parent->color = true;
            sibling->color = false;
            _check_double_black(tree_node->parent); // reapply cases 
        }

        // Resolve Double Black 2 - Sibling Red 
        void    _resolve_double_black2(node * tree_node, node *parent, node *sibling)
        {
            bool    tmp;

            if (RBT_DEBUG)
                std::cout << "DB2: Sibling Red case \n";
            tmp = parent->color;   // Swap parent and sibling colors
            parent->color = sibling->color;
            sibling->color = tmp;
            if (parent->right_child == tree_node) // Rotate in the direction of the sibling
                _rotate_right(sibling);
            else 
                _rotate_left(sibling);
            _check_double_black(tree_node); // reapply cases 
        }

        // Resolve Double Black 3 - Far Child is Red 
        void    _resolve_double_black3(node *tree_node, node *parent, node *sibling)
        {
            bool        tmp;

            if (RBT_DEBUG)
            {
                std::cout << "node :" << tree_node->data->first << "\n";
                std::cout << "parent :" << parent->data->first << "\n";
                std::cout << "sibling :" << sibling->data->first << "\n";
            }

            if (parent->right_child == sibling && !get_right_child_color(sibling))
            {
                if (RBT_DEBUG)
                    std::cout << "Sibling is on the right \n";
                tmp = parent->color; // Swap parent and sibling color
                parent->color = sibling->color;
                sibling->color = tmp;
                sibling->right_child->color = true;
                _rotate_left(sibling); // Rotate sibling is opp direction
            }

            if (parent->left_child == sibling && !get_left_child_color(sibling))
            {
                if (RBT_DEBUG)
                    std::cout << "Sibling is on the left \n";
                tmp = parent->color; // Swap parent and sibling color
                parent->color = sibling->color;
                sibling->color = tmp;
                sibling->left_child->color = true;
                _rotate_right(sibling); // Rotate sibling is opp direction
            }
        }

        void        _check_double_black(node *tree_node)
        {
            node*   parent = tree_node->parent;
            node*   sibling;
            bool    tmp;

            if (!tree_node->double_black)
                return ;
            if (parent == NULL)
            {
                tree_node->double_black = false;  // Simply remove double black if root node
                return ;
            }
            sibling = get_sibling_node(tree_node);
            if (RBT_DEBUG)
            {
                std::cout << "Double black is " << tree_node->data->first << ", ";
                std::cout << "Sibling is " << sibling->data->first << ", ";
                if (!sibling->color)
                    std::cout << "RED \n";
                else  
                    std::cout << "BLACK \n";
            }
            // has a sibling and all the sibling & childern are black 
            if (sibling && has_all_black_children(sibling))
                _resolve_double_black1(tree_node, sibling);
            // has a red sibling 
            else if (sibling && !sibling->color)
                _resolve_double_black2(tree_node, parent, sibling);
            // check sibling's children's color and resolve depending on whether it is far/near child
            else if (sibling && sibling->color && !has_all_black_children(sibling))
            {
                // far child is black
                if (parent->right_child == sibling && get_right_child_color(sibling))
                {
                    tmp = sibling->color;
                    sibling->color = get_left_child_color(sibling);
                    if (sibling->left_child)
                        sibling->left_child->color = tmp;
                    _rotate_right(sibling->left_child);
                }
                if (parent->left_child == sibling && get_left_child_color(sibling))
                {
                    tmp = sibling->color;
                    sibling->color = get_right_child_color(sibling);
                    if (sibling->right_child)
                        sibling->right_child->color = tmp;
                    _rotate_left(sibling->right_child);
                }
                // if far child is red or mandatory part
                _resolve_double_black3(tree_node, tree_node->parent, get_sibling_node(tree_node));
            }         
        }

        void    _delete(node *tree_node)
        {
            node*   tmp = NULL;

            if (tree_node == NULL)
                return ;
            if (!has_children(tree_node) && !tree_node->color)
            {
                if (RBT_DEBUG)
                    std::cout << "Address " << tree_node << ", key " << tree_node->data->first << "was deleted \n";
                _clear(tree_node);
                return ;
            }
            else if (!has_children(tree_node) && tree_node->color)
            {
                tree_node->double_black = true;
                _check_double_black(tree_node);
                _clear(tree_node);
            }
            else if (has_children(tree_node))
            {
                if (tree_node->right_child)
                    tmp = _get_successor(tree_node->right_child);
                else if (tree_node->left_child)
                    tmp = _get_predecessor(tree_node->left_child);
                swap(tmp, tree_node);
                _delete(tmp);
                return ;
            }
        }

        node*   _get_successor(node *tree_node)
        {
            while (tree_node->left_child)
                tree_node = tree_node->left_child;
            return (tree_node);
        }

        node*   _get_predecessor(node *tree_node)
        {
            while (tree_node->right_child)
                tree_node = tree_node->right_child;
            return (tree_node);
        }

        // Add new node 
        node*   _add_new_child(value_type const &child, node *_parent)
        {
            node*   tmp = __node_alloc.allocate(1);

            tmp->data = __alloc.allocate(1);
            __alloc.construct(tmp->data, child);
            tmp->right_child = NULL;
            tmp->left_child = NULL;
            tmp->parent = _parent;
            tmp->double_black = false;
            if (_parent == NULL)
                tmp->color = true;
            else 
                tmp->color = false;
            __size++;
            return (tmp);
        }

        // Check and balance tree 
        void    _check_parent(node *tree_node)
        {
            node    *sibling;
            node    *parent = tree_node->parent;
            node    *grandfather = parent->parent;

            // check parent's color, if black exit
            if (parent->color)
                return ;
            if (grandfather->right_child == parent)
                sibling = grandfather->left_child;
            else 
                sibling = grandfather->right_child;
            
            // check parent's sibling if it is NULL or black ; rotate and recolor
            if (sibling == NULL || sibling->color)
                _find_rotation(tree_node);
            else if (sibling && !sibling->color)
            {
                // if parents sibling is red; recolor both and check grandfather
                sibling->color = !sibling->color;
                parent->color = !parent->color;
                grandfather->color = !grandfather->color;
                if (grandfather->parent != NULL)
                    _check_parent(grandfather);
                else 
                    grandfather->color = true;

            }
        }

        // check which nodes must rotate and in which directons from top to bottom
        void    _find_rotation(node *tree_node)
        {
                std::string code = "";
                node    *parent = tree_node->parent;
                node    *grandfather = parent->parent;

                if (grandfather->right_child == parent)
                    code += "R";
                else if (grandfather->left_child == parent)
                    code += "L";
                if (parent->right_child == tree_node)
                    code += "R";
                else if (parent->left_child == tree_node)
                    code += "L";
                if (code == "RL")
                {
                    _rotate_right(tree_node);
                    _rotate_left(tree_node);
                    tree_node->color = !tree_node->color;
                    tree_node->left_child->color = !tree_node->left_child->color;
                }
                if (code == "LR")
                {
                    _rotate_left(tree_node);
                    _rotate_right(tree_node);
                    tree_node->color = !tree_node->color;
                    tree_node->right_child->color = !tree_node->right_child->color;
                }
                if (code == "RR")
                {
                    _rotate_left(parent);
                    parent->color = !parent->color;
                    parent->left_child->color = !parent->left_child->color;
                }
                if (code == "LL")
                {
                    _rotate_right(parent);
                    parent->color = !parent->color;
                    parent->right_child->color = !parent->right_child->color;
                }
        }

        void    _rotate_right(node *tree_node)
        {
            node    *root = tree_node->parent->parent;
            node    *tmp = tree_node->right_child;

            tree_node->parent->parent = tree_node;
            if (root == NULL) 
                __tree = tree_node;
            else 
            {
                if (root->right_child == root->parent)
                    root->right_child = tree_node;
                else 
                    root->left_child = tree_node;
            }
            tree_node->right_child = tree_node->parent;
            tree_node->parent = root;
            tree_node->right_child->left_child = tmp;
            if (tmp)
                tmp->parent = tree_node->right_child;
        }

        void    _rotate_left(node *tree_node)
        {
            node    *root = tree_node->parent->parent;
            node    *tmp = tree_node->left_child;

            tree_node->parent->parent = tree_node;
            if (root == NULL) 
                __tree = tree_node;
            else 
            {
                if (root->right_child == root->parent)
                    root->right_child = tree_node;
                else 
                    root->left_child = tree_node;
            }
            tree_node->left_child = tree_node->parent;
            tree_node->parent = root;
            tree_node->left_child->right_child = tmp;
            if (tmp)
                tmp->parent = tree_node->left_child;
        }

        // Deletes all nodes starting from in_node if no argument given then it deletes from root
        void    _clear(node *in_node = NULL)
        {
            if (__tree == NULL)
                return ;
            if (in_node == NULL)
                in_node = __tree;
            if (in_node->right_child)
                _clear(in_node->right_child);
            if (in_node->left_child)
                _clear(in_node->left_child);
            if (!has_children(in_node))
            {
                if (RBT_DEBUG)
                    std::cout << "Leaf found, deleting: " << in_node << "\n";
                if (in_node->parent && in_node->parent->right_child == in_node)
                    in_node->parent->right_child = NULL;
                else if (in_node->parent && in_node->parent->left_child == in_node)
                    in_node->parent->left_child = NULL;
                __alloc.destroy(in_node->data);
                __alloc.deallocate(in_node->data, 1);
                __node_alloc.deallocate(in_node, 1);
            }
            else if (RBT_DEBUG)
                std::cout << in_node << ">> " << in_node->left_child << " -- "  << in_node->right_child << "\n";
            if (RBT_DEBUG)
                std::cout << in_node << " :: " << __tree << "\n";
            if (in_node == __tree)
                __tree = NULL;
            __size--;
        }

        node*   find_key(key_type const &key, node* tree_node) const
        {
            node    *back = NULL;

            if (__tree == NULL)
                return (NULL);
            if (tree_node == NULL)
                tree_node = __tree;
            if (tree_node->data->first == key)
                return (tree_node);
            if (!has_children(tree_node))
                return (NULL);
            if (tree_node->data->first > key && tree_node->left_child == NULL)
                return (NULL);
            else if (tree_node->data->first > key && tree_node->left_child)
                back = find_key(key, tree_node->left_child);
            if (tree_node->data->first < key && tree_node->right_child == NULL)
                return (NULL);
            else if (tree_node->data->first < key && tree_node->right_child)
                back = find_key(key, tree_node->right_child);
            return (back);
        }

        void    _insert(value_type const& val)
        {
            node    *runner;
            node    *parent;

            if (!__tree)
            {
                __tree = _add_new_child(val, NULL);
                if (RBT_DEBUG)
                    std::cout << "\n Inserted " << val.first << "\n";
                return ;
            }
            if (find(val.first))
            {
                if (RBT_DEBUG)
                    std::cout << "Error: key is already in the tree! \n";
                return ; 
            }
            parent = NULL;
            runner = __tree;
            while (runner != NULL)
            {
                parent = runner;
                if ((val.first) < (runner->data->first))
                    runner = runner->left_child;
                else 
                    runner = runner->right_child;
            }
            if (RBT_DEBUG)
                std::cout << "\n Inserted " << val.first << "\n";
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
            
            typedef value_type*     value_ptr;
            _red_black_tree(void) : __size(0), __tree(NULL) {}
            ~_red_black_tree(void) {_clear();}

            size_type   size(void) const {return (__size);}
            bool        empty(void) const {return (__size == 0);}
            void        clear(void) const {_clear();}
            bool        find(key_type const& key) const
            {
                if (find_key(key, NULL))
                    return true;
                return false;
            }

            value_ptr   get_value(key_type const& key) const
            {
                node *n = find_key(key, NULL);

                if (!n)
                    return (NULL);
                return (n->data);
            }

            void    set_value(key_type const &key, mapped_type const &data)
            {
                node *n = find_key(key, NULL);

                if (!n)
                    insert(key, data);
                n->data->second = data;
            }

            void    erase(key_type const & key)
            {
                node *n = find_key(key, NULL);

                if (!n)
                {
                    if (RBT_DEBUG)
                        std::cout << "Error: key not found\n";
                    return ;
                }
                _delete(n);
            }

            void    erase(value_ptr const & val)
            {
                erase(val->first);
            }

            void    insert(key_type const & key, mapped_type data)
            {
                _insert(ft::make_pair(key, data));
            }

            void	print(node *in = NULL) const
		    {
                if (in == NULL)
                    in = __tree;
                if (in == NULL)
                    return;
                if (in->double_black)
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
                if (in->double_black)
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
}