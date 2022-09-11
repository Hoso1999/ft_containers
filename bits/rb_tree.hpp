#pragma once

#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "rb_tree_node.hpp"

namespace ft
{

	template<typename _K, typename _V, typename _KOV, typename _Compare, typename _Allocator>
	class rb_tree
	{
		
		enum rb_tree_recolor
		{
			rb_right = true,
			rb_left = false
		};
		typedef typename _Allocator::template rebind<_V>::other node_allocator;
		protected:
			typedef _K key_type;
			typedef _V value_type;
			typedef _KOV key_of_value_type;
			typedef _Compare key_compare;
			typedef _Allocator allocator_type;
			typedef rb_tree_node_base* base_ptr;
			typedef const rb_tree_node_base* const_base_ptr;
			typedef rb_tree_node<value_type>* link_type;
			typedef const rb_tree_node<value_type>* const_link_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef const value_type* const_pointer;
			typedef typename _Allocator::difference_type difference_type;
			typedef typename _Allocator::size_type size_type;
		private:
			node_allocator		_alloc_node;
			_Allocator			_alloc;
			node_allocator		_node_alloc;
			_Compare			_comp;
			key_of_value_type	_key_of_value;
			base_ptr			_root;
			size_type			_size;
		public:
			rb_tree(const _Allocator& alloc = _Allocator(), const _Compare comp = _Compare()) : _root(rb_tree_node_base::nil), _comp(comp), _alloc(alloc), _size(0) {}
			base_ptr root()
			{
				return _root;
			}
			size_type size()
			{
				return _size;
			}
			allocator_type get_allocator()
			{
				return _alloc;
			}
			size_type count(const key_type& key)
			{
				rb_tree_node_base* node = find(key);
			}
			base_ptr lower_bound(const_reference data)
			{
				
			}
			base_ptr upper_bound()
			{

			}
			rb_tree_node_base* createNode(const_reference data)
			{
				rb_tree_node<value_type>* node =_alloc_node.allocate(1);
				_alloc_node.construct(node, data);
				return node;
			}
			static key_type key(const_link_type link)
			{
				return key_of_value_type()(link->data);
			}
			const_base_ptr root() const
			{
				return _root;
			}
			static reference value(const_base_ptr ptr)
			{
				return static_cast<rb_tree_node<value_type> *>(ptr)->data;
			}
			static reference value(const_link_type link)
			{
				return link->data;
			}
			void clear()
			{
				rb_tree_node_base* node = root();
				while (node != rb_tree_node_base::nil)
				{
					value_type data = value(node);
					erase(data);
					node = root();
				}
				_root = rb_tree_node_base::nil;
			}
			link_type begin()
			{
				return static_cast<rb_tree_node<value_type> *>(_root->min());
			}
			const_link_type begin() const
			{
				return static_cast<rb_tree_node<value_type> *>(_root->min());
			}
			link_type end()
			{
				return static_cast<rb_tree_node<value_type> *>(rb_tree_node_base::nil);
			}
			const_link_type end() const
			{
				return static_cast<rb_tree_node<value_type> *>(rb_tree_node_base::nil);
			}

			void insert(const_reference data)
			{
				if (_root == rb_tree_node_base::nil)
				{
					_root = createNode(data);
					_root->color = rb_black;
					_size = 1;
					return ;
				}
				rb_tree_node_base* y = rb_tree_node_base::nil;
				rb_tree_node_base* x = _root;
				while (x != rb_tree_node_base::nil)
				{
					y = x;
					rb_tree_node<value_type>* node = static_cast<rb_tree_node<value_type>*>(x);
					if (_comp(data.first, node->data.first))	
						x = x->left;
					else
						x = x->right;
				}
				rb_tree_node_base* z = createNode(data);
				z->parent = y;
				rb_tree_node<value_type>* node = static_cast<rb_tree_node<value_type>*>(y);
				if (y == rb_tree_node_base::nil)
					_root = z;
				else if (_comp(data.first, node->data.first))
					y->left = z;
				else
					y->right = z;
				insert_fixup(z);
				++_size;
			}

			void insert_fixup(rb_tree_node_base* z)
			{
				while (z->parent->color == rb_red)
				{
					if (z->parent->parent->left == z->parent)
						recolor(z, z->parent->parent->right, rb_right);
					else
						recolor(z, z->parent->parent->left, rb_left);
				}
			}

			void recolor(rb_tree_node_base* z, rb_tree_node_base* y, rb_tree_recolor side)
			{
				if (y->color == rb_red)
				{
					z->parent->color = rb_black;
					y->color = rb_black;
					z->parent->parent->color = rb_red;
					z = z->parent->parent;
				}
				else 
				{
					if (side)
					{
						if (z == z->parent->right)
						{
							z = z->parent;
							left_rotate(z);
						}
						z->parent->color = rb_black;
						z->parent->parent->color = rb_red;
						right_rotate(z->parent->parent);
					}
					else
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							right_rotate(z);
						}
						z->parent->color = rb_black;
						z->parent->parent->color = rb_red;
						left_rotate(z->parent->parent);
					}
				}
			}
			void left_rotate(rb_tree_node_base* x)
			{
				rb_tree_node_base*  y = x->right;
				x->right = y->left;
				if (y->left != rb_tree_node_base::nil)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == rb_tree_node_base::nil)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
				
			}
			void right_rotate(rb_tree_node_base* x)
			{
				rb_tree_node_base*  y = x->left;
				x->left = y->right;
				if (y->right != rb_tree_node_base::nil)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == rb_tree_node_base::nil)
					_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;

			}

			void erase(const_reference data)
			{
				rb_tree_node_base* z = find(data);
				if (z == rb_tree_node_base::nil)
					return ;
				rb_tree_node_base* y = z;
				rb_tree_node_base* x;
				rb_tree_color orig_color = y->color;
				if (z->left == rb_tree_node_base::nil)
				{
					x = z->right;
					transplant(z, z->right);
				}
				else if (z->right == rb_tree_node_base::nil)
				{
					x = z->left;
					transplant(z, z->left);
				}
				else
				{
					y = z->right->min();
					orig_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else
					{
						transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				if (orig_color == rb_black)
					erase_fixup(x);
				--_size;
			}
			void erase_fixup(rb_tree_node_base* x)
			{
				rb_tree_node_base* w;
				while (x != _root && x->color != rb_black)
				{
					if (x == x->parent->left)
					{
						w = x->parent->right;
						if (w->color == rb_red)
						{
							w->color = rb_black;
							x->parent->color = rb_black;
							left_rotate(x->parent);
							w = x->parent->right;
						}
						if (w->left->color == rb_black && w->right->color == rb_black)
						{
							w->color = rb_red;
							x = x->parent;
						}
						else
						{
							if (w->right->color == rb_black)
							{
								w->left->color = rb_black;
								w->color = rb_red;
								right_rotate(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = rb_black;
							w->right->color = rb_black;
							left_rotate(x->parent);
							x = _root;
						}
					}
					else
					{
						w = x->parent->left;
						if (w->color == rb_red)
						{
							w->color = rb_black;
							x->parent->color = rb_black;
							right_rotate(x->parent);
							w = x->parent->left;
						}
						if (w->right->color == rb_black && w->left->color == rb_black)
						{
							w->color = rb_red;
							x = x->parent;
						}
						else
						{
							if (w->left->color == rb_black)
							{
								w->right->color = rb_black;
								w->color = rb_red;
								left_rotate(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = rb_black;
							w->left->color = rb_black;
							right_rotate(x->parent);
							x = _root;
						}

					}
				}
				x->color = rb_black;
			}

			void transplant(rb_tree_node_base* u, rb_tree_node_base* v)
			{
				if (u->parent == rb_tree_node_base::nil)
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}
			rb_tree_node_base* find(const key_type& data)
			{
				rb_tree_node_base* node = _root;
				while (node != rb_tree_node_base::nil)
				{
					rb_tree_node<value_type>* curr = static_cast<rb_tree_node<value_type>* >(node);
					if (!_comp(data, curr->data.first) && !_comp(curr->data.first, data))
						break;
					if (_comp(data.first, curr->data.first))
						node = node->left;
					else
						node = node->right;
				}
				return node;
			}
	};
}