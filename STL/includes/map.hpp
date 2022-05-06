/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 02:34:23 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 03:18:46 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <stdlib.h>
# include <memory>
# include "rb_tree.hpp"
# include "utils.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<Key,T> > >
	class	map
	{
		public:
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef pair<const key_type,mapped_type>									value_type;
			typedef Compare																key_compare;
			typedef Alloc																allocator_type;
			typedef typename allocator_type::reference									reference;
			typedef typename allocator_type::const_reference							const_reference;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;
			class value_compare
			{
				friend class map;
				public:
					bool operator()(const value_type &a, const value_type &b) const
					{
						return (key_compare()(a.first, b.first));
					}
				value_compare &operator=(const value_compare &) { return *this; }
			};
			typedef typename RB_Tree<value_type, value_compare>::iterator					iterator;
			typedef typename RB_Tree<value_type, value_compare>::const_iterator				const_iterator;
			typedef reverse_iterator<const_iterator>										const_reverse_iterator;
			typedef reverse_iterator<iterator>												reverse_iterator;
			typedef typename allocator_type::size_type										size_type;

		private:
			allocator_type						_alloc;
			key_compare							_key_comp;
			value_compare						_value_comp;
			RB_Tree<value_type, value_compare>	_tree;

		public:
			// constrcutor - ongoing
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _key_comp(comp), _value_comp(value_compare()), _tree() { };
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _key_comp(comp), _value_comp(value_compare()), _tree()
			{
				insert(first, last);
			}
			map (const map &ref) : _alloc(ref._alloc), _key_comp(ref._key_comp), _value_comp(ref._value_comp), _tree(ref._tree) { };

			// deconstructor - ongoing
			~map() {};

			// operator=
			map& operator=(const map& ref)
			{
				_alloc = ref._alloc;
				_key_comp = ref._key_comp;
				_value_comp = ref._value_comp;
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



			// Element access:
			// operator[] : 원소에 접근한다.
			mapped_type&	operator[](const key_type& k)
			{
				iterator tmp = find(k);
				if (tmp == (_tree.end())) {
					return (*(insert(value_type(k, mapped_type())).first)).second;
				}
				return ((*tmp).second);
			};



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
			size_type			erase(const key_type& k) {
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
			void				swap(map &x)
			{
				_tree.swap(x._tree);
				std::swap(_key_comp, x._key_comp);
				std::swap(_value_comp, x._value_comp);
				std::swap(_alloc, x._alloc);
			};
			void		clear(void) { _tree.clear(); };



			// observers
			key_compare		key_comp(void) const					{ return (this->_key_comp); };
			value_compare	value_comp(void) const					{ return (this->_value_comp); };



			// operations
			iterator		find(const key_type &key)				{ return (_tree.find(value_type(key, mapped_type()))); };
			const_iterator	find(const key_type &key) const			{ return (_tree.find(value_type(key, mapped_type()))); };
			size_type		count(const key_type &key) const
			{
				const_iterator lower = lower_bound(key);
				const_iterator upper = upper_bound(key);
				size_type i = 0;
				while (lower++ != upper) i++;
				return i;
			};
			iterator		lower_bound(const key_type &key)		{ return (_tree.lower_bound(value_type(key, mapped_type()))); };
			const_iterator	lower_bound(const key_type &key) const	{ return (_tree.lower_bound(value_type(key, mapped_type()))); };
			iterator		upper_bound(const key_type &key)		{ return (_tree.upper_bound(value_type(key, mapped_type()))); };
			const_iterator	upper_bound(const key_type &key) const	{ return (_tree.upper_bound(value_type(key, mapped_type()))); };
			pair<iterator, iterator>				equal_range(const key_type &key)
			{ return (pair<iterator, iterator>(this->lower_bound(key), this->upper_bound(key))); }
			pair<const_iterator, const_iterator>	equal_range(const key_type &key) const
			{ return (pair<const_iterator, const_iterator>(this->lower_bound(key), this->upper_bound(key))); }

			// Allocator
			Alloc		get_allocator() const { return this->_alloc; };


			template<typename U, typename K>
			friend bool operator== (const map& lhs, const map<U, K>& rhs)
			{
				const_iterator lhs_ite = lhs.begin();
				typename map<U, K>::const_iterator rhs_ite = rhs.begin();
				while (1) {
					if (lhs_ite == lhs.end() && rhs_ite == rhs.end()) return true;
					if (lhs_ite == lhs.end()) return false;
					if (rhs_ite == rhs.end()) return false;
					if (*lhs_ite != *rhs_ite) return false;
					lhs_ite++;
					rhs_ite++;
				}
			};
			template<typename U, typename K>
			friend bool operator!= (const map& lhs, const map<U, K>& rhs)
			{
				return !(lhs == rhs);
			};

			template<typename U, typename K>
			friend bool operator< (const map& lhs, const map<U, K>& rhs)
			{
				const_iterator lhs_ite = lhs.begin();
				typename map<U, K>::const_iterator rhs_ite = rhs.begin();
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

			template<typename U, typename K>
			friend bool operator<= (const map& lhs, const map<U, K>& rhs)
			{
				const_iterator lhs_ite = lhs.begin();
				typename map<U, K>::const_iterator rhs_ite = rhs.begin();
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

			template<typename U, typename K>
			friend bool operator> (const map& lhs, const map<U, K>& rhs)
			{
				return !(lhs <= rhs);
			};

			template<typename U, typename K>
			friend bool operator>= (const map& lhs, const map<U, K>& rhs)
			{
				return !(lhs < rhs);
			};
	};
}

#endif
