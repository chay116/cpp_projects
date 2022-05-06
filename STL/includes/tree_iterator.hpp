/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 07:45:04 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 02:24:42 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

# include "rbt_node.hpp"
# include "iterator.hpp"

namespace	ft
{
	template <typename T>
		struct tree_iterator : ft::iterator<bidirectional_iterator_tag, T>
		{
			public:
				typedef typename iterator<bidirectional_iterator_tag, T>::iterator_category		iterator_category;
				typedef typename iterator<bidirectional_iterator_tag, T>::value_type			value_type;
				typedef typename iterator<bidirectional_iterator_tag, T>::difference_type		difference_type;
				typedef typename iterator<bidirectional_iterator_tag, T>::pointer				pointer;
				typedef typename iterator<bidirectional_iterator_tag, T>::reference				reference;
				typedef RBT_Node<value_type>													*node_ptr;
				typedef RBT_Node<const value_type>												*const_node_ptr;

				tree_iterator(void) : NIL(nullptr), _root_Node(nullptr), _cur_Node(nullptr) {};
				tree_iterator(node_ptr NIL, node_ptr root, node_ptr node) : NIL(NIL), _root_Node(root), _cur_Node(node) {};
				operator tree_iterator<const T>() const { return (tree_iterator<const T>((const_node_ptr)&*NIL, (const_node_ptr)&* this->_root_Node, (const_node_ptr)&*this->_cur_Node)); };
				~tree_iterator() {}
				tree_iterator	&operator=(tree_iterator const &ref)
				{
					_cur_Node = ref._cur_Node;
					_root_Node = ref._root_Node;
					NIL = ref.NIL;
					return *this;
				};

				bool		operator==(const tree_iterator &ref) { return this->_cur_Node == ref._cur_Node; };
				bool		operator!=(const tree_iterator &ref) { return this->_cur_Node != ref._cur_Node; };


				reference operator*(void) const { return _cur_Node->value; }
				pointer operator->(void) const { return (&this->_cur_Node->value); }
				node_ptr base(void) const { return _cur_Node; }

				tree_iterator &operator++(void) {
					if (_cur_Node != NIL) _cur_Node = find_right(_cur_Node);
					return *this;
				}
				tree_iterator operator++(int) {
					tree_iterator tmp(*this);
					++(*this);
					return tmp;
				}
				tree_iterator &operator--(void) {
					if (_cur_Node != NIL) _cur_Node = find_left(_cur_Node);
					else {
						_cur_Node = _root_Node;
						while (_cur_Node->right != NIL)
							_cur_Node = _cur_Node->right;
					}
					return *this;
				}
				tree_iterator operator--(int) {
					tree_iterator tmp(*this);
					--(*this);
					return tmp;
				}

			private:
				node_ptr	NIL;
				node_ptr	_root_Node;
				node_ptr	_cur_Node;

				node_ptr	find_left(node_ptr target)
				{
					if (target->left != NIL) {
						target = target->left;
						while (target->right != NIL)
							target = target->right;
						return (target);
					}
					while (target->parent != NIL && target->parent->left == target) target = target->parent;
					return target->parent;
				}

				node_ptr	find_right(node_ptr target)
				{
					if (target->right != NIL) {
						target = target->right;
						while (target->left != NIL) target = target->left;
						return (target);
					}
					while (target != NIL && target->parent->right == target) target = target->parent;
					return target->parent;
				}
		};
}

#endif