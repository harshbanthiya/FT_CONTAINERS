#include "rb_tree.hpp"
#include "utility.hpp"

namespace ft
{
    tree_node_base*     _minimum(tree_node_base *x) FT_NOEXCEPT
    {
        while (x->left_child != NULL)
            x = x->left_child;
        return x;
    }

    const tree_node_base* _minimum(const tree_node_base *x) FT_NOEXCEPT
    {
        while (x->left_child != NULL)
            x = x->left_child;
        return x;
    }

    tree_node_base*     _maximum(tree_node_base *x) FT_NOEXCEPT
    {
        while (x->right_child != NULL)
            x = x->right_child;
        return x;
    }

    const tree_node_base* _maximum(const tree_node_base *x) FT_NOEXCEPT
    {
        while (x->right_child != NULL)
            x = x->right_child;
        return x;
    }

    // Return next node by in order traversal 
    static tree_node_base* local_tree_increment(tree_node_base *x) FT_NOEXCEPT
    {
        if (x->right_child != NULL)
            return (_minimum(x->right_child));
        tree_node_base *y = x->parent;
        while (x == y->right_child)
        {
            x = y;
            y = y->parent;
        }
        if (x->right_child != y)
            x = y;
        return x;
    }

    tree_node_base* tree_increment(tree_node_base *x) FT_NOEXCEPT
    {
        return local_tree_increment(x);
    }

    const tree_node_base* tree_increment(const tree_node_base *x) FT_NOEXCEPT
    {
        return local_tree_increment(const_cast<tree_node_base *>(x));
    }

    // Return previous node by in order traversal 
    static tree_node_base *local_tree_decrement(tree_node_base *x)
    {
        if (x->color == RED && x->parent->parent == x)
            return x->right_child;
        if (x->left_child != NULL)
            return _maximum(x->left_child);
        tree_node_base *y = x->parent;
        while (x == y->left_child)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    tree_node_base* tree_decrement(tree_node_base *x) FT_NOEXCEPT
    {
        return local_tree_decrement(x);
    }

    const tree_node_base* tree_decrement(const tree_node_base *x) FT_NOEXCEPT
    {
        return local_tree_decrement(const_cast<tree_node_base *>(x));
    }


    // Rotations 
    void    tree_rotate_left(tree_node_base* const x, tree_node_base *& root)
    {
        tree_node_base *const y = x->right_child;

        x->right_child = y->left_child;
        if (y->left_child != NULL)
            y->left_child->parent = x;
        y->parent = x->parent;
        if (x == root)
            root = y;
        else if (x == x->parent->left_child)
            x->parent->left_child = y;
        else 
            x->parent->right_child = y;
        y->left_child = x;
        x->parent = y;
    }

    void tree_rotate_right(tree_node_base * const x, tree_node_base *&root)
    {
        tree_node_base *const y = x->left_child;

        x->left_child = y->right_child;
        if (y->right_child != NULL)
            y->right_child->parent = x;
        y->parent = x->parent;

        if (x == root)
            root = y;
        else if (x == x->parent->right_child)
            x->parent->right_child = y;
        else 
            x->parent->left_child = y;
        y->right_child = x;
        x->parent = y;
    }

    static void local_insert_new_node(const bool insert_left, tree_node_base *&x,
                                        tree_node_base *&p, tree_node_base &header) FT_NOEXCEPT
    {
        // Initiate new node 
        x->parent = p;
        x->right_child = NULL;
        x->left_child = NULL;
        x->color = RED;

        if (insert_left)
            p->left_child = x;
        if (p == &header)
        {
            header.parent = x;
            header.right_child = x;
        }
        else if (p == header.left_child)
            header.left_child = x;
        else 
        {
            p->right_child = x;
            if (p == header.right_child)
                header.right_child = x;
        }
    }

    static void local_insert_fixup(tree_node_base *&x, tree_node_base *&root)
    {
        while (x != root && x->parent->color == RED)
        {
            tree_node_base* const xpp = x->parent->parent;
            if (x->parent == xpp->left_child)
            {
                tree_node_base *const y = xpp->right_child;

                if (y && y->color == RED)
                {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    xpp->color = RED;
                    x = xpp;
                }
                else 
                {
                    if (x == x->parent->right_child)
                    {
                        x = x->parent;
                        tree_rotate_left(x, root);
                    }
                    x->parent->color = BLACK;
                    xpp->color = RED;
                    tree_rotate_right(xpp, root);
                }
            }
            else 
            {
                tree_node_base* const y = xpp->left_child;
                if (y && y->color == RED)
                {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    xpp->color = RED;
                    x = xpp;
                }
                else 
                {
                    if (x == x->parent->left_child)
                    {
                        x = x->parent;
                        tree_rotate_right(x, root);
                    }
                    x->parent->color = BLACK;
                    xpp->color = RED;
                    tree_rotate_left(xpp, root);
                }
            }
        }
        root->color = BLACK;
    }

    void    tree_insert_and_fixup(const bool insert_left, tree_node_base *x,
                                    tree_node_base *p, tree_node_base &header) FT_NOEXCEPT
    {
        tree_node_base  *& root = header.parent;
        local_insert_new_node(insert_left, x, p, header);
        local_insert_fixup(x, root);
    }


    static void local_erase_node(tree_node_base *const &z, tree_node_base *&y,
                                    tree_node_base *&x, tree_node_base *& xp,
                                    tree_node_base &header)
    {
        tree_node_base *& root = header.parent;
        tree_node_base *& leftmost = header.left_child;
        tree_node_base *& rightmost = header.right_child;

        if (y->left_child != NULL && y->right_child != NULL)
        {
            y = _minimum(y->right_child);
            x = y->right_child;

            z->left_child->parent = y;
            y->left_child = z->left_child;
            if (y != z->right_child)
            {
                xp = y->parent;
                if (x)
                    x->parent = y->parent;
                y->parent->left_child = x;
                y->right_child = z->right_child;
                z->right_child->parent = y;
            }
            else 
                xp = y;
            if (root == z)
                root = y;
            else if (z->parent->left_child == z)
                z->parent->left_child = y;
            else 
                z->parent->right_child = y;
            y->parent = z->parent;
            std::swap(y->color, z->color);
            y = z;
            return ;
        }

        x = (z->left_child == NULL) ? z->right_child : z->left_child;
        xp = z->parent;
        if (x) x->parent = z->parent;
        if (root == z)
            root = x;
        else if (z->parent->left_child == z)
            z->parent->left_child = x;
        else 
            z->parent->right_child = x;
        if (leftmost == z)
        {
            if (z->right_child == NULL)
                leftmost = z->parent;
            else 
                leftmost = _minimum(x);
        }
        if (rightmost == z)
        {
            if (z->left_child == NULL)
                rightmost = z->parent;
            else 
                rightmost = _maximum(x);
        }
    }

    inline static bool local_erase_fixup_left(tree_node_base *&x, 
                                                tree_node_base *&xp,
                                                tree_node_base *&root)
    {
        tree_node_base *w = xp->right_child;
        if (w->color == RED)
        {
            w->color = BLACK;
            xp->color = RED;
            tree_rotate_left(xp, root);
            w = xp->right_child;
        }
        if ((w->left_child == NULL || w->left_child->color == BLACK) &&
            (w->right_child == NULL || w->right_child->color == BLACK))
        {
            w->color = RED;
            x = xp;
            xp = xp->parent;
        }
        else 
        {
            if (w->right_child == NULL || w->right_child->color == BLACK)
            {
                w->left_child->color = BLACK;
                w->color = RED;
                tree_rotate_right(w, root);
                w = xp->right_child;
            }
            w->color = xp->color;
            xp->color = BLACK;
            if (w->right_child) w->right_child->color = BLACK;
            tree_rotate_left(xp, root);
            return true;
        }
        return false;
    }

    inline static bool local_erase_fixup_right(tree_node_base *&x, 
                                                tree_node_base *&xp,
                                                tree_node_base *&root)
    {
        tree_node_base *w = xp->left_child;
        if (w->color == RED)
        {
            w->color = BLACK;
            xp->color = RED;
            tree_rotate_right(xp, root);
            w = xp->left_child;
        }
        if ((w->right_child == NULL || w->right_child->color == BLACK) &&
            (w->left_child == NULL || w->left_child->color == BLACK))
        {
            w->color = RED;
            x = xp;
            xp = xp->parent;
        }
        else 
        {
            if (w->left_child == NULL || w->left_child->color == BLACK)
            {
                w->right_child->color = BLACK;
                w->color = RED;
                tree_rotate_left(w, root);
                w = xp->left_child;
            }
            w->color = xp->color;
            xp->color = BLACK;
            if (w->left_child) w->left_child->color = BLACK;
            tree_rotate_right(xp, root);
            return true;
        }
        return false;
    }

    static void local_erase_fixup(tree_node_base *&x, tree_node_base *&xp,
                                    tree_node_base *& root)
    {
        bool    is_end = false;

        while (x != root && (x == NULL || x->color == BLACK) && !is_end)
        {
            if (x == xp->left_child)
                is_end = local_erase_fixup_left(x, xp, root);
            else 
                is_end = local_erase_fixup_right(x, xp, root);
        }
        if (x)
            x->color = BLACK;
    }


    tree_node_base *tree_erase_and_fixup(tree_node_base *const z,
                                        tree_node_base &header) FT_NOEXCEPT
    {
        tree_node_base *&root = header.parent;
        tree_node_base *y = z;
        tree_node_base *x = NULL;
        tree_node_base *xp = NULL;

        local_erase_node(z, y, x, xp, header);
        if (y->color != RED)
            local_erase_fixup(x, xp, root);
        return y;
    }

    void tree_header::tree_reset()
    {
        header.parent = NULL;
        header.left_child = &header;
        header.right_child = &header;
        node_count = 0;
    }

    void tree_header::tree_move_data(tree_header &other)
    {
        header.color = other.header.color;
        header.parent = other.header.parent;
        header.left_child = other.header.left_child;
        header.right_child = other.header.right_child;
        header.parent->parent = &header;
        node_count = other.node_count;
        other.tree_reset();
    }

}