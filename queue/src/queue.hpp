#pragma once

#include <deque>

namespace ft
{
    
    template<typename T, typename Container = std::deque<T> >
    class queue
    {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef typename Container::size_type size_type;

        explicit queue (const container_type& ctnr = container_type());
        virtual ~queue();

        bool empty() const;
        size_type size() const;
        value_type& front();
        const value_type& front() const;
        value_type& back();
        const value_type& back() const;
        void push (const value_type& val);
        void pop();
        void swap (queue& x);
       
        friend bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
        friend bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
        friend bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
        friend bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
        friend bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
        friend bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
    protected:
        Container _cont;
    }; // class queue
}

#include "queue_impl.hpp"

