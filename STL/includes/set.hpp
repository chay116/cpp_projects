/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 02:34:23 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 02:24:43 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <stdlib.h>
# include <memory>
# include "rb_tree.hpp"
# include "utils.hpp"

namespace	ft
{
	template < class T, class Compare = less<T>, class Alloc = std::allocator<T> >
	class	set
	{
		public:
			typedef const T																key_type;
			typedef const T																value_type;
			typedef Compare																key_compare;
			typedef Compare																value_compare;
			typedef Alloc																allocator_type;
			typedef typename allocator_type::reference									reference;
			typedef typename allocator_type::const_reference							const_reference;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;
			typedef typename RB_Tree<const value_type, key_compare>::iterator			iterator;
			typedef typename RB_Tree<const value_type, key_compare>::const_iterator		const_iterator;
			typedef reverse_iterator<const_iterator>									const_reverse_iterator;
			typedef reverse_iterator<iterator>											reverse_iterator;
			typedef typename allocator_type::size_type									size_type;

		private:
			allocator_type						_alloc;
			key_compare						_key_comp;
			RB_Tree<value_type, key_compare>	_tree;

		public:
			// constrcutor - ongoing
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _key_comp(comp), _tree() { };
			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _key_comp(comp), _tree()
			{
				insert(first, last);
			}
			set (const set &ref) : _alloc(ref._alloc), _key_comp(ref._key_comp), _tree(ref._tree) { };

			~set() {};

			// operator=
			set& operator=(const set& ref)
			{
				_alloc = ref._alloc;
				_key_comp = ref._key_comp;
				_tree = ref._tree;
				return (*this);
			}

			// Iterators
			iterator				begin(void) { return _tree.begin(); };
			const_iterator			begin(void) const { return _tree.begin(); };
			iterator				end(void) { return _tree.end(); };
			const_iterator			end(void) const { return _tree.end(); };
			reverse_iterator		rbegin(void) { return _tree.rbegin(); };
			const_reverse_iterator	rbegin(void) const { return _tree.rbegin(); };
			reverse_iterator		rend(void) { return _tree.rend(); };
			const_reverse_iterator	rend(void) const { return _tree.rend(); };



			// Capacity
			bool			empty(void) const	{ return _tree.empty(); };
			size_type		size(void) const	{ return (_tree.size()); };
			size_type		max_size(void) const	{ return (_tree.max_size()); };



			// Modifiers
			// insert : 벡터 중간에 원소를 추가한다.
			pair<iterator,bool>	insert(const value_type& val) { return _tree.insert1(val); };
			iterator			insert(iterator position, const value_type& val) { return _tree.insert2(position, val); };
			template <class InputIterator>
			void				insert(InputIterator first, InputIterator last)
			{
				for (InputIterator i = first; i != last; i++)
					_tree.insert1(*i);
			};
			void				erase(iterator position) {_tree.erase(position); };
			size_type			erase(const value_type& k) {
				iterator result = find(k);
				if (result != _tree.end())
					return _tree.erase(find(k));
				return (0);
			};
			void				erase(iterator first, iterator last)
			{
				iterator i = first;
				while (i != last) _tree.erase(i++);
			};
			void				swap(set &x)
			{
				_tree.swap(x._tree);
				std::swap(_key_comp, x._key_comp);
				std::swap(_alloc, x._alloc);
			};
			void		clear(void) { _tree.clear(); };

			// observers
			value_compare	value_comp(void) const					{ return (this->_key_comp); };
			key_compare		key_comp(void) const					{ return (this->_key_comp); };


			// operations
			iterator		find(const value_type &key)				{ return (_tree.find(key)); };
			const_iterator	find(const value_type &key) const			{ return (_tree.find(key)); };
			size_type		count(const value_type &key) const
			{
				const_iterator lower = lower_bound(key);
				const_iterator upper = upper_bound(key);
				size_type i = 0;
				while (lower++ != upper) i++;
				return i;
			};
			iterator		lower_bound(const value_type &key)		{ return (_tree.lower_bound(key)); };
			const_iterator	lower_bound(const value_type &key) const	{ return (_tree.lower_bound(key)); };
			iterator		upper_bound(const value_type &key)		{ return (_tree.upper_bound(key)); };
			const_iterator	upper_bound(const value_type &key) const	{ return (_tree.upper_bound(key)); };
			pair<iterator, iterator>				equal_range(const value_type &key)
			{ return (pair<iterator, iterator>(this->lower_bound(key), this->upper_bound(key))); }
			pair<const_iterator, const_iterator>	equal_range(const value_type &key) const
			{ return (pair<const_iterator, const_iterator>(this->lower_bound(key), this->upper_bound(key))); }

			// Allocator
			Alloc		get_allocator() const { return this->_alloc; };


			template<typename T2>
			friend bool operator== (const set& lhs, const set<T2>& rhs)
			{
				const_iterator lhs_ite = lhs.begin();
				typename set<T2>::const_iterator rhs_ite = rhs.begin();
				while (1) {
					if (lhs_ite == lhs.end() && rhs_ite == rhs.end()) return true;
					if (lhs_ite == lhs.end()) return false;
					if (rhs_ite == rhs.end()) return false;
					if (*lhs_ite != *rhs_ite) return false;
					lhs_ite++;
					rhs_ite++;
				}
			};
			template<typename T2>
			friend bool operator!= (const set& lhs, const set<T2>& rhs)
			{
				return !(lhs == rhs);
			};

			template<typename T2>
			friend bool operator< (const set& lhs, const set<T2>& rhs)
			{
				const_iterator lhs_ite = lhs.begin();
				typename set<T2>::const_iterator rhs_ite = rhs.begin();
				while (1) {
					if (lhs_ite == lhs.end() && rhs_ite == rhs.end()) return false;
					if (lhs_ite == lhs.end()) return true;
					if (rhs_ite == rhs.end()) return false;
					if (*lhs_ite < *rhs_ite) return true;
					if (*lhs_ite > *rhs_ite) return false;
					lhs_ite++;
					rhs_ite++;
				}
			};

			template<typename T2>
			friend bool operator<= (const set& lhs, const set<T2>& rhs)
			{
				const_iterator lhs_ite = lhs.begin();
				typename set<T2>::const_iterator rhs_ite = rhs.begin();
				while (1) {
					if (lhs_ite == lhs.end() && rhs_ite == rhs.end()) return true;
					if (lhs_ite == lhs.end()) return true;
					if (rhs_ite == rhs.end()) return false;
					if (*lhs_ite < *rhs_ite) return true;
					if (*lhs_ite > *rhs_ite) return false;
					lhs_ite++;
					rhs_ite++;
				}
			};

			template<typename T2>
			friend bool operator> (const set& lhs, const set<T2>& rhs)
			{
				return !(lhs <= rhs);
			};

			template<typename T2>
			friend bool operator>= (const set& lhs, const set<T2>& rhs)
			{
				return !(lhs < rhs);
			};
	};
}

#endif
