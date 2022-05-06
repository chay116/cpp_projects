/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 07:45:07 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 02:31:01 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace	ft
{
	template <class T, class Container = vector<T> >
		class	stack
		{
			public:
				typedef T									value_type;
				typedef Container							container_type;
				typedef typename Container::size_type		size_type;
				typedef typename Container::reference		reference;
				typedef typename Container::const_reference	const_reference;

			protected:
				container_type		c;

			public:
				// constrcutor
				explicit stack (const container_type& ctnr = container_type()) : c(ctnr) { };

				// deconstructor.
				~stack(){ };

				size_type		size(void) const			{ return this->c.size(); };
				bool			empty(void) const			{ return this->c.empty(); };
				reference		top(void)					{ return this->c.back(); };
				const_reference	top(void) const 			{ return this->c.back(); };
				void			push(const_reference val)	{ this->c.push_back(val); };
				void			pop(void)					{ this->c.pop_back(); };

			friend bool operator==(const stack& lhs, const stack& rhs) { return lhs.c == rhs.c; };
			friend bool operator!=(const stack& lhs, const stack& rhs)	{ return lhs.c != rhs.c; };
			friend bool operator<(const stack& lhs, const stack& rhs)	{ return lhs.c < rhs.c; };
			friend bool operator<=(const stack& lhs, const stack& rhs)	{ return lhs.c <= rhs.c; };
			friend bool operator>(const stack& lhs, const stack& rhs)	{ return lhs.c > rhs.c; };
			friend bool operator>=(const stack& lhs, const stack& rhs)	{ return lhs.c >= rhs.c; };
		};
}

#endif