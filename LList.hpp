/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LList.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:10:54 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/09/29 13:08:58 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLIST_HPP
#define LLIST_HPP
#include <iostream>

class LNode
{
    public: 
    LNode( int _data, LNode *nxt){
        this->data = _data;
        this->next = nxt;
    };
    LNode(){ this->data = 0; this->next = nullptr;};
    LNode(const LNode &rhs)
    {
        this->data = rhs.data;
        this->next = rhs.next;
    }
    ~LNode();
    
    // Operator 
    LNode operator=(const LNode &rhs)
    {
        this->data =  rhs.data;
        this->next =  rhs.next;
        return (*this);
    }

    //Setters 
    void setData(int data)
    {
        this->data = data;
    };
    void setNext(LNode *nxt)
    {
        this->next = nxt;
    };
    

    // Getter 
    int getData() const {return (this->data);};
    LNode *getNext() const {return (this->next);};
    
    private: 
    int data;
    LNode *next;
};

class LList
{
    public:
        LList()
        {
            begin = nullptr;
        };
        ~LList();
        void insert(int it)
        {
            
        }
        int find()
        {
            
        }

    private: 
        LNode *begin;

}; 


#endif