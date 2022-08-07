#pragma once

#include "random_access_iterator.hpp"


namespace ft
{
	template<typename T>
	random_access_iterator<T>::random_access_iterator()
		: _ptr(ft_nullptr)
	{}
	template<typename T>
	random_access_iterator<T>::random_access_iterator(pointer ptr)
		: _ptr(ptr)
	{}
	template<typename T>
	random_access_iterator<T>::random_access_iterator(const random_access_iterator<T>& it)
		: _ptr(it._ptr)
	{}
	template<typename T>
	random_access_iterator<T>& random_access_iterator<T>::operator=(const random_access_iterator<T>& it)
	{
		if (&it != this)
			_ptr = it.ptr;
		return *this;
	}
	//
	// dereference operators
	//
	template<typename T>
	typename random_access_iterator<T>::reference random_access_iterator<T>::operator*() const
	{
		return *_ptr;
	}

	template<typename T>
	typename random_access_iterator<T>::pointer random_access_iterator<T>::operator->() const
	{
		return _ptr;
	}
	//
	// other operations
	//
	template<typename T>
	random_access_iterator<T>& random_access_iterator<T>::operator++()
	{
		++_ptr;
		return *this;
	}

	template<typename T>
	random_access_iterator<T> random_access_iterator<T>::operator++(int)
	{
		random_access_iterator<T> tmp(*this);
		++_ptr;
		return tmp;
	}

	template<typename T>
	random_access_iterator<T>& random_access_iterator<T>::operator--()
	{
		--_ptr;
		return *this;
	}

	template<typename T>
	random_access_iterator<T> random_access_iterator<T>::operator--(int)
	{
		random_access_iterator<T> tmp(*this);
		--_ptr;
		return tmp;
	}

	template<typename T>
	random_access_iterator<T>& random_access_iterator<T>::operator+=(difference_type offset)
	{
		_ptr += offset;
		return *this;
	}

	template<typename T>
	random_access_iterator<T>& random_access_iterator<T>::operator-=(difference_type offset)
	{
		_ptr -= offset;
		return *this;
	}

	template<typename T>
	random_access_iterator<T> random_access_iterator<T>::operator+(difference_type offset)
	{
		random_access_iterator<T> tmp(*this);
		tmp += offset;
		return tmp;
	}
	template<typename T>
	random_access_iterator<T> random_access_iterator<T>::operator-(difference_type offset)
	{
		random_access_iterator<T> tmp(*this);
		tmp -= offset;
		return tmp;
	}

	template<typename T>
	typename random_access_iterator<T>::value_type random_access_iterator<T>::operator[](difference_type n)
	{
		return _ptr[n];
	}
	//
	// compare operations
	//
	template<typename T>
	bool random_access_iterator<T>::operator<(const random_access_iterator<T>& it)
	{
		return _ptr < it._ptr;
	}

	template<typename T>
	bool random_access_iterator<T>::operator>(const random_access_iterator<T>& it)
	{
		return _ptr > it._ptr;
	}

	template<typename T>
	bool random_access_iterator<T>::operator<=(const random_access_iterator<T>& it)
	{
		return _ptr <= it._ptr;
	}

	template<typename T>
	bool random_access_iterator<T>::operator>=(const random_access_iterator<T>& it)
	{
		return _ptr >= it._ptr;
	}

	template<typename T>
	bool random_access_iterator<T>::operator==(const random_access_iterator<T>& it)
	{
		return _ptr == it._ptr;
	}

	template<typename T>
	bool random_access_iterator<T>::operator!=(const random_access_iterator<T>& it)
	{
		return _ptr != it._ptr;
	}
	template<typename T>
	typename random_access_iterator<T>::pointer random_access_iterator<T>::base()
	{
		return _ptr;
	}

	template<typename T>
	typename random_access_iterator<T>::difference_type operator-(random_access_iterator<T> rhs,
			random_access_iterator<T> lhs)
	{
		return rhs._ptr - lhs._ptr;
	}
	template<typename LIter, typename RIter>
	typename random_access_iterator<LIter>::difference_type operator-(random_access_iterator<LIter> rhs,
			random_access_iterator<RIter> lhs)
	{
		return rhs._ptr - lhs._ptr;
	}
}
