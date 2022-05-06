/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:24:35 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 02:24:43 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator.hpp"
# include "random_access_iterator.hpp"
namespace	ft
{
	template <typename Iterator>
	class reverse_iterator
	{
		public:
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		private:
			Iterator	_element;

		public:
			// base : Returns a copy of the base iterator
			Iterator	base() const { return (this->_element); };

			// constructor, deconstructor
			reverse_iterator(void) : _element() { };
			reverse_iterator(const Iterator &it): _element(it) {};
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _element(rev_it.base()) {};

			virtual ~reverse_iterator() { };

			reference	operator*() const
			{
				Iterator tmp = _element;
				return (*(--tmp));
			};
			// about operators with +
			reverse_iterator	operator+(difference_type n)
			{
				return reverse_iterator(_element - n);
			};
			reverse_iterator	&operator+=(difference_type n)
			{
				_element -= n;
				return (*this);
			};
			reverse_iterator	&operator++()
			{
				--_element;
				return (*this);
			};
			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp(*this);
				--_element;
				return (tmp);
			};

			// about operators with -
			reverse_iterator	operator-(difference_type n)
			{
				return reverse_iterator(_element + n);
			};
			reverse_iterator	&operator-=(difference_type n)
			{
				_element += n;
				return (*this);
			};
			reverse_iterator	&operator--()
			{
				++_element;
				return (*this);
			};
			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);
				++_element;
				return (tmp);
			};

			// about access
			pointer				operator->(void) const { return &(operator*()); };
			reference			operator[](difference_type n) const { return _element[-n-1]; };

		// relational operators
		template<class Iter>
		friend bool operator== (const reverse_iterator& lhs, const reverse_iterator<Iter>& rhs)	{ return lhs.base() == rhs.base(); };

		template<class Iter>
		friend bool operator!= (const reverse_iterator& lhs, const reverse_iterator<Iter>& rhs)	{ return lhs.base() != rhs.base(); };

		template<class Iter>
		friend bool operator< (const reverse_iterator& lhs, const reverse_iterator<Iter>& rhs)	{ return lhs.base() > rhs.base(); };

		template<class Iter>
		friend bool operator<= (const reverse_iterator& lhs, const reverse_iterator<Iter>& rhs)	{ return lhs.base() >= rhs.base(); };

		template<class Iter>
		friend bool operator> (const reverse_iterator& lhs, const reverse_iterator<Iter>& rhs)	{ return lhs.base() < rhs.base(); };

		template<class Iter>
		friend bool operator>= (const reverse_iterator& lhs, const reverse_iterator<Iter>& rhs)	{ return lhs.base() <= rhs.base(); };

		friend reverse_iterator operator+ (typename reverse_iterator::difference_type n, const reverse_iterator& rev_it)
			{ return reverse_iterator(rev_it.base() - n); };
	};
	template<class T>
	typename reverse_iterator<random_access_iterator<T> >::difference_type operator- (const reverse_iterator<random_access_iterator<T> >& lhs,	const reverse_iterator<random_access_iterator<T> >& rhs)
		{ return lhs.base() - rhs.base(); };

	template<class T>
	typename reverse_iterator<random_access_iterator<T> >::difference_type operator- (const reverse_iterator<random_access_iterator<const T> >& lhs,	const reverse_iterator<random_access_iterator<T> >& rhs)
		{ return rhs.base() - lhs.base(); };
}

#endif