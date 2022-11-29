#include <memory>
#include <cstddef>
#include <utility>
#include <iostream>

class BST
{
    private :
        struct node
        {
            int key;
            node* left;
            node* right;
        };
    node * root;
    void Add_leaf_p(int key, node* ptr) 
    {
        if (root == NULL)
            root = Create_leaf(key);
        else if (key < ptr->key)
        {
            if (ptr->left != NULL)
                Add_leaf_p(key, ptr->left);
            else 
                ptr->left = Create_leaf(key);
        }
        else if (key > ptr->key)
        {
            if (ptr->right != NULL)
                Add_leaf_p(key, ptr->right);
            else 
                ptr->right = Create_leaf(key);
        }
        else 
            std::cout << "The key" << key << "has already been added to the tree \n";
    }
    void    PrintInOrderPrivate(node *ptr) 
    {
        if (root != NULL)
        {
            if (ptr->left != NULL) // possible to go left 
            {
                PrintInOrderPrivate(ptr->left);
            }
            std::cout << ptr->key << " ";
            if (ptr->right != NULL) // possible to go right 
            {
                PrintInOrderPrivate(ptr->right);
            }
        }   
        else 
            std::cout << "the tree is empty\n";
    }
    node*       ReturnNode_p(int key, node *ptr)
    {
        if (ptr != NULL)
        {
            if (ptr->key == key)
                return ptr;
            else 
            {
                if (key < ptr->key)
                    return (ReturnNode_p(key, ptr->left));
                else 
                    return (ReturnNode_p(key, ptr->right));
            }
        }    
        else 
            return NULL;
    }

    int         FindSmallest_p(node *ptr)
    {
        if (root == NULL)
        {
            std::cout << "The tree is empty\n";
            return (-1000);
        }
        else 
        {
            if (ptr->left != NULL)
                return FindSmallest_p(ptr->left);
            else 
                return ptr->key;
        }
    }

    void        RemoveRootMatch()
    {
        if (root != NULL)
        {
            node *delPtr = root;
            int rootkey = root->key;
            int smallest_key_in_right_subtree; 

            // Case 0 - 0 children 
            if (root->left == NULL && root->right == NULL)
            {
                root = NULL;
                delete delPtr;
            }
            // Case 1 - 1 Child
            else if (root->left == NULL && root->right != NULL)
            {
                root = root->right;
                delPtr->right = NULL;
                delete delPtr;
                std::cout << "The root node with key " << rootkey << " was deleted ";
                std::cout << "The new root contains key " << root->key << " \n";
            }
            else if (root->left != NULL && root->right == NULL)
            {
                root = root->left;
                delPtr->left = NULL;
                delete delPtr;
                std::cout << "The root node with key " << rootkey << " was deleted ";
                std::cout << "The new root contains key " << root->key << " \n";
            }
            // Case 2 - 2 children 
            else 
            {
                smallest_key_in_right_subtree = FindSmallest_p(root->right);
                RemoveNode_p(smallest_key_in_right_subtree, root);
                root->key = smallest_key_in_right_subtree;
                std::cout << "The root key containing key " << rootkey ;
                std::cout << "was overwritten by key " << root->key << "\n" ;
            }
        }
        else 
            std::cout << "Cannot remove root as tree is empty\n";
    }

    void        RemoveMatch(node *parent, node* match, bool left)
    {
            if (root != NULL)
            {
                node *delPtr; 
                int matchKey = match->key;
                int smallest_in_right_subtree;

                // Case 0 - 0 child
                if (match->left == NULL && match->right == NULL)
                {
                    delPtr = match;
                    left == true ? parent->left = NULL : parent->right = NULL;
                    delete delPtr;
                    std::cout << "the node containing key " << matchKey << " was removed \n";
                }
                // Case 1 - 1 child
                else if (match->left == NULL && match->right != NULL)
                {
                    left == true ? parent->left = match->right : parent->right = match->right;
                    match->right = NULL;
                    delPtr = match;
                    delete delPtr;
                    std::cout << "the node containing key " << matchKey << " was removed \n";
                }
                else if (match->left != NULL && match->right == NULL)
                {
                    left == true ? parent->left = match->left : parent->right = match->left;
                    match->left = NULL;
                    delPtr = match;
                    delete delPtr;
                    std::cout << "the node containing key " << matchKey << " was removed \n";
                }
                else // 2 - 2 children 
                {
                    smallest_in_right_subtree = FindSmallest_p(match->right);
                    RemoveNode_p(smallest_in_right_subtree, match);
                    match->key = smallest_in_right_subtree;
                    // no actual deletion but rather overwrite                         
                }
                 
                
            }
            else 
                std::cout << "Cannot remove match, tree empty \n";
    }

    void        RemoveNode_p(int key, node *parent)
    {
        if (root != NULL)
        {
            if (root->key == key)
                RemoveRootMatch();
            else 
            {
                if (key < parent->key && parent->left != NULL)
                {
                    parent->left->key == key ? RemoveMatch(parent, parent->left, true) :
                    RemoveNode_p(key, parent->left);
                }
                else if (key > parent->key && parent->right != NULL)
                {
                    parent->right->key == key ? RemoveMatch(parent, parent->right, false) :
                    RemoveNode_p(key, parent->right);
                }
                else 
                    std::cout << "The key " << key << "was not found in the tree\n"; 
            }
        }
        else 
            std::cout << "The tree is empty \n";
    }
        node*   Create_leaf(int key) {node* n = new node; n->key = key; n->left = NULL; n->right = NULL; return n;}
        node*   ReturnNode(int key) {return (ReturnNode_p(key, root));}
        void    RemoveSubtree(node *ptr)
        {
            if (ptr != NULL)
            {
                if (ptr->left != NULL)
                    RemoveSubtree(ptr->left);
                if (ptr->right != NULL)
                    RemoveSubtree(ptr->right);
                std::cout << "Deleting the node containing the key " << ptr->key << '\n';
                delete ptr;
            }
        }

    public :
    
        BST() {root = NULL;}
        ~BST() {RemoveSubtree(root);}
        void    Add_leaf(int key) {Add_leaf_p(key, root);}
        void    PrintInOrder() {PrintInOrderPrivate(root);}
        int     ReturnRootKey() {if (root != NULL) return (root->key); else return (-1000);}
        void    PrintChildren(int key) 
        {
            node *ptr = ReturnNode(key); 
            if (ptr != NULL) 
            {
                std::cout << "\nParent Node is " << ptr->key << "\n";
                ptr->left == NULL ? std::cout << "Left child is NULL\n" : std::cout << "Left Child " << ptr->left->key << "\n"; 
                ptr->right == NULL ? std::cout << "Right child is NULL\n" : std::cout << "Right Child " << ptr->right->key << "\n"; 
            }
            else 
                std::cout << "Key " << key << "is not part of the tree\n";
        }
        int     FindSmallest() {return FindSmallest_p(root);} 
        void    RemoveNode(int key) {RemoveNode_p(key, root);}
};


int main()
{
    int arr[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
    BST m_tree;
    int input = 0;
    std::cout << "Print the tree in order before adding numbers\n";
    m_tree.PrintInOrder();

    for(int i = 0; i < 16; ++i)
    {
        m_tree.Add_leaf(arr[i]);    
    }
    std::cout << "Print the tree in order after adding numbers\n";
    m_tree.PrintInOrder();

    // testing print children 
    m_tree.PrintChildren(m_tree.ReturnRootKey());

    // Printing all the children
    for(int i = 0; i < 16; ++i)
    {
        m_tree.PrintChildren(arr[i]);    
    }

    // Find smallest 
    std::cout << "The smallest value in the tree is " << m_tree.FindSmallest() << " \n";

    // Delete tests
    while (input != -1)
    {
        std::cout << "delete node : ";
        std::cin >> input;
        {
            if (input != -1)
            {
                std::cout << '\n';
                m_tree.RemoveNode(input);
                m_tree.PrintInOrder();
                std::cout << '\n';
            }
        }
    }
}