/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 23:16:23 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 21:17:24 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include "reverse_iterator.hpp"
# include "tree_iterator.hpp"

namespace ft
{
	template < class T, class Compare, class Alloc = std::allocator<RBT_Node<T> > >
	class RB_Tree {
		public:
			typedef T																	value_type;
			typedef RBT_Node<value_type>												*node_ptr;
			typedef RBT_Node<const value_type>											*const_node_ptr;
			typedef Compare																value_compare;
			typedef Alloc																allocator_type;
			typedef typename allocator_type::reference									reference;
			typedef typename allocator_type::const_reference							const_reference;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;
			typedef tree_iterator<value_type>											iterator;
			typedef tree_iterator<const value_type>										const_iterator;
			typedef reverse_iterator<const_iterator>									const_reverse_iterator;
			typedef reverse_iterator<iterator>											reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type					difference_type;
			typedef typename allocator_type::size_type									size_type;


		private:
			node_ptr							NIL;
			node_ptr							_root_Node;
			allocator_type						_alloc;
			value_compare						_comp;
			size_type							_size;

			node_ptr	new_Node(const T& value)
			{
				_size += 1;
				node_ptr new_node = _alloc.allocate(1);
				_alloc.construct(new_node, value);
				new_node->parent = NIL;
				new_node->right = NIL;
				new_node->left = NIL;
				return new_node;
			}

			node_ptr	first(void) const
			{
				node_ptr _first = _root_Node;
				if (_first == NIL) return NIL;
				while (_first->left != NIL) _first = _first->left;
				return _first;
			}

			node_ptr	last(void) const
			{
				node_ptr _last = _root_Node;
				if (_last == NIL) return NIL;
				while (_last->right != NIL) _last = _last->right;
				return _last;
			}

			node_ptr	find_left(node_ptr target)
			{
				if (target->left) {
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
				if (target->right) {
					target = target->right;
					while (target->left != NIL) target = target->left;
					return (target);
				}
				while (target->parent != NIL && target->parent->right == target) target = target->parent;
				return target->parent;
			}

			void	_rotate_right (node_ptr target) {
				node_ptr left_node = target->left;
				target->left = left_node->right;
				if (left_node->right != NIL) left_node->right->parent = target;
				left_node->parent = target->parent;
				if (target->parent == NIL) _root_Node = left_node;
				else
					if (target == (target->parent)->right)
						target->parent->right = left_node;
					else
						target->parent->left = left_node;
				left_node->right = target;
				target->parent = left_node;
			}

			void	_rotate_left(node_ptr target) {
				node_ptr right_node = target->right;
				target->right = right_node->left;
				if (right_node->left != NIL) right_node->left->parent = target;
				right_node->parent = target->parent;
				if (target->parent == NIL) _root_Node = right_node;
				else
					if (target == (target->parent)->left)
						target->parent->left = right_node;
					else
						target->parent->right = right_node;
				right_node->left = target;
				target->parent = right_node;
			}

			pair<iterator, bool>	insert_recur(node_ptr current, const T&  value)
			{
				if (current->value == value) return pair<iterator, bool>(iterator(NIL, _root_Node, current), false);
				if (_comp(current->value, value)) {
					if (current->right != NIL) return insert_recur(current->right, value);
					current->right = new_Node(value);
					current->right->parent = current;
					return pair<iterator, bool>(iterator(NIL, _root_Node, current->right), true);
				} else {
					if (current->left != NIL) return insert_recur(current->left, value);
					current->left = new_Node(value);
					current->left->parent = current;
					return pair<iterator, bool>(iterator(NIL, _root_Node, current->left), true);
				}
			};

			void	erase_recur(node_ptr current)
			{
				if (current->left != NIL) erase_recur(current->left);
				if (current->right != NIL) erase_recur(current->right);
				_alloc.destroy(current);
				_alloc.deallocate(current, 1);
			};

			void	copy_recur(node_ptr current, node_ptr ref_NIL)
			{
				if (current == ref_NIL) return ;
				insert1(current->value);
				if (current->left != NIL) copy_recur(current->left, ref_NIL);
				if (current->right != NIL) copy_recur(current->right, ref_NIL);
			};

			void		connect_pointer(node_ptr x, node_ptr y)
			{
				if (x->parent == NIL) _root_Node = y;
				else if (x == x->parent->left) x->parent->left = y;
				else x->parent->right = y;
				if (y != NIL) y->parent = x->parent;
			}

			void		display(node_ptr x)
			{
				if (x == _root_Node) {
					std::cout << "size : " << _size<< std::endl;
					std::cout << std::endl << "Display :" << std::endl;
				}
				if (x->left != NIL) display(x->left);
				std::cout << "- " << x->value.first << " " << x->value.second << " " << x->color << std::endl;
				if (x->right != NIL) display(x->right);
			}

			void RB_Insert_Fixup(node_ptr target)
			{
				while (target->parent && target->parent->color == RED) {
					// we have a violation
					node_ptr uncle = target->find_uncle();
					if (uncle != NIL && uncle->color == RED) {
						target->parent->color = BLACK;
						uncle->color = BLACK;
						target->find_grandparent()->color = RED;
						target = target->find_grandparent();
					} else {
						if (target->parent == target->parent->parent->left) {
							if (target == target->parent->right) {
								target = target->parent;
								_rotate_left(target);
							}
							target->parent->color = BLACK;
							target->parent->parent->color = RED;
							_rotate_right(target->parent->parent);
						} else {
							if (target == target->parent->left) {
								target = target->parent;
								_rotate_right(target);
							}
							target->parent->color = BLACK;
							target->parent->parent->color = RED;
							_rotate_left(target->parent->parent);
						}
					}
				}
				_root_Node->color = BLACK;
			}

			void RB_Erase_Fixup (node_ptr x) {
				if (x == NIL) return;
				node_ptr x_parent = x->parent;
				while (x != _root_Node && (x->color == BLACK)) {
					if (x == x_parent->left) {
						node_ptr w = x_parent->right;
						if (w->color == RED) { //case 1
							w->color = BLACK;
							x_parent->color = RED;
							_rotate_left(x_parent);
							w = x_parent->right;
						}
						if (w == NIL) {
							x = x_parent;
							x_parent = x_parent->parent;
						}
						else if ((w->left->color == BLACK) && (w->right->color == BLACK)) { // case 2
							w->color = RED;
							x = x_parent;
							x_parent = x_parent->parent;
						}
						else {
							if (w->right->color == BLACK) { // case 3
								w->left->color = BLACK;
								w->color = RED;
								_rotate_right(w);
								w = x_parent->right;
							}
							w->color = x_parent->color; // case 4
							x_parent->color = BLACK;
							w->right->color = BLACK;
							_rotate_left(x_parent);
							break;
						}
					} else {
						node_ptr w = x_parent->left;
						if (w->color == RED) {
							w->color = BLACK;
							x_parent->color = RED;
							_rotate_right(x_parent);
							w = x_parent->left;
						}
						if (w == NIL) {
							x = x_parent;
							x_parent = x_parent->parent;
						}
						else if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
							w->color = RED;
							x = x_parent;
							x_parent = x_parent->parent;
						}
						else {
							if (w->left->color == BLACK) {
								w->right->color = BLACK;
								w->color = RED;
								_rotate_left(w);
								w = x_parent->left;
							}
							w->color = x_parent->color;
							x_parent->color = BLACK;
							w->left->color = BLACK;
							_rotate_right(x_parent);
							break ;
						}
					}
				}
				if (x == NIL)
					x->color = BLACK;
			}


		public:
			void swap(RB_Tree &ref) {
				node_ptr tmp;
				tmp = NIL; NIL = ref.NIL; ref.NIL = tmp;
				tmp = _root_Node; _root_Node = ref._root_Node; ref._root_Node = tmp;
				size_type tmp_size;
				tmp_size = _size; _size = ref._size; ref._size = tmp_size;
			}

			explicit RB_Tree (const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type())
			: _root_Node(nullptr), _alloc(alloc), _comp(comp), _size(-1)
			{
				NIL = new_Node(T());
				NIL->color = BLACK;
				_root_Node = NIL;
			};

			RB_Tree (const RB_Tree &ref) : _root_Node(nullptr), _alloc(allocator_type()), _comp(value_compare()), _size(-1)
			{
				NIL = new_Node(T());
				NIL->color = BLACK;
				_root_Node = NIL;
				copy_recur(ref._root_Node, ref.NIL);
			};

			RB_Tree& operator=(const RB_Tree &ref)
			{
				clear();
				copy_recur(ref._root_Node, ref.NIL);
				return (*this);
			}

			~RB_Tree()
			{
				if (_root_Node != NIL)
					erase_recur(_root_Node);
				_alloc.destroy(NIL);
				_alloc.deallocate(NIL, 1);
			};

			void	clear()
			{
				if (_root_Node != NIL)
					erase_recur(_root_Node);
				_root_Node = NIL;
				_size = 0;
			};

			pair<iterator, bool>	insert1(const T& value)
			{
				if (_root_Node == NIL) {
					_root_Node = new_Node(value);
					_root_Node->color = BLACK;
					return pair<iterator, bool>(begin(), true);
				}
				pair<iterator, bool> result = insert_recur(_root_Node, value);
				if (result.second == true)
					RB_Insert_Fixup(result.first.base());
				return result;
			};

			iterator	insert2(iterator hint, const T& value)
			{
				iterator next = hint;
				next++;
				return insert1(value).first;
			};

			size_type	erase(iterator position_iter)
			{
				node_ptr position = position_iter.base();
				if (position == NIL) return 0;
				node_ptr x;
				if (position->left == NIL && position->right == NIL) {
					if (position == _root_Node) _root_Node = NIL;
					else if (position->parent->right == position) position->parent->right = NIL;
					else position->parent->left = NIL;
					x = NIL;
				} else if (position->left == NIL) {
					x = position->right;
					connect_pointer(position, position->right);
				} else if (position->right == NIL) {
					x = position->left;
					connect_pointer(position, position->left);
				} else {
					position_iter++;
					node_ptr next = position_iter.base();
					x = next->right;
					next->color = position->color;
					connect_pointer(next, next->right);
					connect_pointer(position, next);
					next->right = position->right;
					next->left = position->left;
					next->right->parent = next;
					next->left->parent = next;
				}
				if (position->color == BLACK)
					RB_Erase_Fixup(x);
				_alloc.destroy(position);
				_alloc.deallocate(position, 1);
				_size--;
				// display(_root_Node);
				return 1;
			}

			bool					empty(void) const { return (_root_Node == NIL); };
			size_type				size(void) const	{ return _size; };
			size_type				max_size(void) const	{ return _alloc.max_size(); };

			iterator				begin(void) { return iterator(NIL, _root_Node, first()); };
			const_iterator			begin(void) const { return const_iterator((const_node_ptr)&*NIL, (const_node_ptr)&*_root_Node, (const_node_ptr)&*first()); };
			iterator				end(void) { return iterator(NIL, _root_Node, NIL); };
			const_iterator			end(void) const { return const_iterator((const_node_ptr)&*NIL, (const_node_ptr)&*_root_Node, (const_node_ptr)&*NIL); };
			reverse_iterator		rbegin(void) { return reverse_iterator(end());	};
			const_reverse_iterator	rbegin(void) const { return const_reverse_iterator(end()); };
			reverse_iterator		rend(void) { return reverse_iterator(begin());	};
			const_reverse_iterator	rend(void) const { return const_reverse_iterator(begin()); };


			iterator		find(const T& value)
			{
				node_ptr cur = _root_Node;
				while(cur != NIL) {
					if (_comp(value, cur->value)) {
						cur = cur->left;
					} else if (_comp(cur->value, value)) {
						cur = cur->right;
					} else return iterator(NIL, _root_Node, cur);
				}
				return iterator(NIL, _root_Node, NIL);
			};
			const_iterator	find(const T& value) const
			{
				node_ptr cur = _root_Node;
				while(cur != NIL) {
					if (_comp(value, cur->value)) {
						cur = cur->left;
					} else if (_comp(cur->value, value)) {
						cur = cur->right;
					} else return const_iterator((const_node_ptr)&*NIL, (const_node_ptr)&*_root_Node, (const_node_ptr)&*cur);
				}
				return const_iterator((const_node_ptr)&*NIL, (const_node_ptr)&*_root_Node, (const_node_ptr)&*NIL);
			};
			iterator		lower_bound(const T& value)
			{
				for (iterator it = begin(); it != end(); it++)
					if (_comp(value, *it) || _comp(*it, value) == 0)
						return it;
				return iterator(NIL, _root_Node, NIL);
			};
			const_iterator	lower_bound(const T& value) const
			{
				for (const_iterator it = begin(); it != end(); it++)
					if (_comp(value, *it) || _comp(*it, value) == 0)
						return it;
				return const_iterator((const_node_ptr)&*NIL, (const_node_ptr)&*_root_Node, (const_node_ptr)&*NIL);
			};
			iterator	upper_bound(const T& value)
			{
				for (iterator it = begin(); it != end(); it++)
					if (_comp(value, *it))
						return it;
				return iterator(NIL, _root_Node, NIL);
			};
			const_iterator	upper_bound(const T& value) const
			{
				for (const_iterator it = begin(); it != end(); it++)
					if (_comp(value, *it))
						return it;
				return const_iterator((const_node_ptr)&*NIL, (const_node_ptr)&*_root_Node, (const_node_ptr)&*NIL);
			};
	};
}

#endif