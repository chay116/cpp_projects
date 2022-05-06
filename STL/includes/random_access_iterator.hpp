/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 07:45:04 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 02:24:44 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"

namespace	ft
{

	template <typename T>
	struct const_random_access_iterator;

	template <typename T>
	struct random_access_iterator : ft::iterator<random_access_iterator_tag, T>
	{

		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;

		private:
			pointer	_node;

		public:
			pointer		base() const { return (this->_node); }
			// constructor, deconstructor
			random_access_iterator(void) : _node(nullptr) { };
			random_access_iterator(pointer p) : _node(p) { };

			operator random_access_iterator<const T>() const { return (random_access_iterator<const T>(this->_node)); };
			random_access_iterator	&operator=(random_access_iterator<T> const &ref)
			{
				this->_node = &*ref;
				return (*this);
			};

			virtual ~random_access_iterator() { };

			// about access
			reference const	operator*() const {	return *(this->_node); };
			pointer	const	operator->(void) const { return _node; };

			random_access_iterator&	operator+=(difference_type n)
			{
				_node += n;
				return (*this);
			};
			random_access_iterator&	operator++()
			{
				++this->_node;
				return (*this);
			};
			random_access_iterator	operator++(int)
			{
				random_access_iterator	tmp(*this);
				++this->_node;
				return (tmp);
			};

			random_access_iterator	&operator-=(difference_type n)
			{
				this->_node -= n;
				return (*this);
			};
			random_access_iterator	&operator--()
			{
				--this->_node;
				return (*this);
			};
			random_access_iterator	operator--(int)
			{
				pointer	tmp = this->_node;
				--this->_node;
				return random_access_iterator(tmp);
			};
			random_access_iterator	operator+(difference_type n)
			{
				return random_access_iterator(_node + n);
			};
			random_access_iterator	operator-(difference_type n)
			{
				return random_access_iterator(_node - n);
			};

			reference			operator[](difference_type n) const { return *(this->_node + n); };

			// relational operators
			friend bool operator== (const random_access_iterator& lhs, const random_access_iterator& rhs) { return lhs.base() == rhs.base(); };

			friend bool operator!= (const random_access_iterator& lhs, const random_access_iterator& rhs) { return lhs.base() != rhs.base(); };

			friend bool operator< (const random_access_iterator& lhs, const random_access_iterator& rhs) { return lhs.base() < rhs.base(); };

			friend bool operator<= (const random_access_iterator& lhs, const random_access_iterator& rhs) { return lhs.base() <= rhs.base(); };

			friend bool operator> (const random_access_iterator& lhs, const random_access_iterator& rhs) { return lhs.base() > rhs.base(); };

			friend bool operator>= (const random_access_iterator& lhs, const random_access_iterator& rhs) { return lhs.base() >= rhs.base(); };

			friend typename random_access_iterator::difference_type operator- (const random_access_iterator& lhs,	const random_access_iterator& rhs)
				{ return lhs.base() - rhs.base(); };

			friend random_access_iterator operator+ (typename random_access_iterator::difference_type n, const random_access_iterator& rev_it)
				{ return (rev_it.base() + n); };
	};
}

#endif
