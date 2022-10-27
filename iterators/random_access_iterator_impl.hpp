#pragma once

#include "iterators/random_access_iterator.hpp"


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
			_ptr = it._ptr;
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
	typename random_access_iterator<T>::const_pointer random_access_iterator<T>::base() const
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

		// compare operations
		//
		template<typename T>
		bool operator==(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() == rhs.base();
		}
		template<typename T1, typename T2>
		bool operator==(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
		{
			return lhs.base() == rhs.base();
		}

		template <typename T>
		bool operator!=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() != rhs.base();
		}

		template <typename T>
		bool operator<(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() < rhs.base();
		}

		template <typename T>
		bool operator<=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

		template <typename T>
		bool operator>(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() > rhs.base();
		}

		template <typename T>
		bool operator>=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

		template<typename T>
		random_access_iterator<T>::operator random_access_iterator<const value_type>() const
		{
			return random_access_iterator<const value_type>(base());
		}

		template<typename LIter, typename RIter>
		typename random_access_iterator<LIter>::difference_type operator+(random_access_iterator<LIter> rhs,  typename random_access_iterator<LIter>::size_type lhs)
		{
			return rhs.base()  + lhs;
		}
}

