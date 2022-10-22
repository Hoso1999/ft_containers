#pragma once

#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include <iostream>
#include "rb_tree_def.hpp"
#include "../utility.hpp"
namespace ft
{
	class rb_tree_node_base
	{
		//
		// NIL node of tree
		// 
		public:
			typedef rb_tree_node_base* 			base_ptr;
			typedef const rb_tree_node_base*	const_base_ptr;			

			base_ptr							_left;
			base_ptr							_right;
			base_ptr							_parent;
			bool								_is_nil;
			rb_tree_color						_color;

			rb_tree_node_base(rb_tree_color _color = rb_red) : _left(ft_nullptr), _right(ft_nullptr), _parent(ft_nullptr), _is_nil(true), _color(_color) {}
			rb_tree_node_base(const rb_tree_node_base& node) : _left(node._left), _right(node._right), _parent(node._parent), _is_nil(true), _color(node._color) {}
			rb_tree_node_base& operator=(const rb_tree_node_base& node)
			{
				_left = node._left;
				_right = node._right;
				_parent = node._parent;
				_color = node._color;
				_is_nil = node._is_nil;
				return *this;
			}



	};
	//rb_tree_node_base rb_tree_node_base::_nil_node = rb_tree_node_base(rb_black);
	//rb_tree_node_base* rb_tree_node_base::nil = &rb_tree_node_base::_nil_node;
	template<typename T>
	class rb_tree_node : public rb_tree_node_base
	{
		public:
			T _value;
			typedef rb_tree_node_base::base_ptr base_ptr;
			rb_tree_node(T _value, rb_tree_color _color = rb_red) : rb_tree_node_base(_color), _value(_value)
		{}

	};
	template<typename T, typename _Allocator>
	class rb_tree_impl
	{
		void initialize()
		{
			_left_sentinel = base_type();
			_right_sentinel = base_type();
			_nil_left = &_left_sentinel;
			_nil_right = &_right_sentinel;
			_root = _nil_left;
			_begin = _nil_left;
			_end = _nil_left;
		}
		public:
			typedef T										value_type;
			typedef rb_tree_node_base						base_type;
			typedef rb_tree_node_base*						base_ptr;
			typedef const rb_tree_node_base*				base_const_ptr;
			typedef const rb_tree_node<T>*					const_link_type;
			typedef rb_tree_node<T>*						link_type;
			typedef _Allocator								allocator_type;
			typedef typename _Allocator::size_type			size_type;
			typedef typename _Allocator::const_reference	const_reference;

			allocator_type		_alloc;
			base_ptr			_root;
			base_ptr			_begin;
			base_ptr			_nil_left;
			base_ptr			_nil_right;
			base_type			_left_sentinel;
			base_type			_right_sentinel;
			base_ptr			_end;
			size_type			_size;
		
			/*!
			 * @function	create_node
			 * @abstract	Creates new red-black tree node
			 * @discussion	This function take a value
			 * 				and creates new node for red-black tree
			 *
			 * @param		value of node
			 *
			 *
			 * @result		A poiner to new node
			 *
			*/
			base_ptr create_node(const_reference _value)
			{
				link_type node = _alloc.allocate(1);
				try
				{
					_alloc.construct(node, _value);
					node->_parent = _nil_left;
					node->_left = _nil_left;
					node->_right = _nil_left;
					node->_is_nil = false;
				}
				catch (...)
				{
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					throw ;
				}
				return node;
			}
			/*!
			 * @function	increment
			 * @abstract	Get next node of red-black tree
			 * @discussion	This function take a poiner of red-black tree
			 * 				and returns a pointer to next node 
			 * 				of tree
			 *
			 * @param		node pointer to node of red-black tree
			 *
			 *
			 * @result		A poiner to next node of tree
			 *
			*/
			static base_ptr increment(base_ptr node)
			{
				base_ptr _base = node;
				if (!_base->_right->_is_nil)
					_base = min(_base->_right);
				else
				{
					base_ptr node = _base->_parent;
					while (_base == node->_right)
					{
						_base = node;
						node = node->_parent;
					}
					_base = node;
				}
				return _base;
			}


			/*!
			 * @function	decrement
			 * @abstract	Get previous node of red-black tree
			 * @discussion	This function take a poiner of red-black tree
			 * 				and returns a pointer to previous node 
			 * 				of tree
			 *
			 * @param		node pointer to node of red-black tree
			 *
			 *
			 * @result		A poiner to previous node of tree
			 *
			*/
			static base_ptr decrement(base_ptr node)
			{
				base_ptr _base = node;

				if (!_base->_left->_is_nil)
					_base = max(_base->_left);
				else
				{
					base_ptr node = _base->_parent;
					while (_base->_is_nil && _base == node->_left)
					{
						_base = node;
						node = node->_parent;
					}
					_base = node;
				}
				return _base;
			}
			/*!
			 * @function	min
			 * @abstract	find a leftmost node of red-black tree node
			 * @discussion	This function take a node of red-black tree
			 * 				and returns a pointer to leftmost node 
			 * 				of argument subtree
			 *
			 * @param		base node of red-black tree
			 *
			 *
			 * @result		A poiner to leftmost node of subtree
			 *
			*/
			static base_ptr min(base_ptr base)
			{
				base_ptr node = base;
				if (node->_is_nil)
					return node;
				while (!node->_left->_is_nil)
					node = node->_left;
				return node;
			}
			/*!
			 * @function	max
			 * @abstract	find a rightmost node of red-black tree node
			 * @discussion	This function take a node of red-black tree
			 * 				and returns a pointer to rightmost node 
			 * 				of argument subtree
			 *
			 * @param		base node of red-black tree
			 *
			 *
			 * @result		A poiner to rightmost node of subtree
			 *
			*/
			static base_ptr max(base_ptr base)
			{
				base_ptr node = base;
				if (node->_is_nil)
					return node;
				while (!node->_right->_is_nil)
					node = node->_right;
				return node;
			}
		rb_tree_impl(const allocator_type alloc = allocator_type()) : _alloc(alloc), _size(0)
		{
			initialize();
		}
		rb_tree_impl(const rb_tree_impl& _rb_impl) : _alloc(_rb_impl._alloc), _size(_rb_impl._size)
		{
			_begin = _rb_impl._begin;
			_end = _rb_impl._end;
			_root = _rb_impl._root;
			_left_sentinel = _rb_impl._left_sentinel;
			_right_sentinel = _rb_impl._right_sentinel;
			_nil_left = _rb_impl._nil_left;
			_nil_right = _rb_impl._nil_right;

		}
		rb_tree_impl& operator=(const rb_tree_impl& _rb_impl)
		{
			if (&_rb_impl != this)
			{
				_alloc = _rb_impl._alloc;
				_size = _rb_impl._size;
				_begin = _rb_impl._begin;
				_end = _rb_impl._end;
				_root = _rb_impl._root;
				_left_sentinel = _rb_impl._left_sentinel;
				_right_sentinel = _rb_impl._right_sentinel;
				_nil_left = _rb_impl._nil_left;
				_nil_right = _rb_impl._nil_right;
			}
			return *this;
		}
	};
}
