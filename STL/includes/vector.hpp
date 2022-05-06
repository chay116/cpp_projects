/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 06:20:20 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 03:09:14 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"

namespace	ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class	vector
	{
		public:
			typedef T													value_type;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef random_access_iterator<value_type>					iterator;
			typedef random_access_iterator<const value_type>			const_iterator;
			typedef reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef reverse_iterator<iterator>							reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type	difference_type;
			typedef typename allocator_type::size_type					size_type;

		private:
			allocator_type	_alloc;
			pointer			_start;
			size_type		_size;
			size_type		_capacity;

			void _extend_capacity(void)
			{
				if (_capacity == 0)
					reserve(1);
				else
				{
					size_type new_capacity = _capacity * 2;
					reserve(new_capacity);
				}
			}

			void _extend_capacity(size_type n)
			{
				size_type new_capacity = _capacity + n;
				if (new_capacity == 0)
					reserve(1);
				reserve(new_capacity);
			}

			template <class InputIterator>
			size_type getSize(InputIterator first, InputIterator last)
			{
				size_type len = 0;
				for (InputIterator i = first; i != last; i++)
					len++;
				return len;
			}


		public:
			// 생성자: 벡터를 생성한다.
			explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _start(NULL), _size(0), _capacity(1)
			{
				_start = _alloc.allocate(1);
			};

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _start(NULL), _size(n), _capacity(n)
			{
				_start = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_start + i, val);
			};

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			: _alloc(alloc), _start(NULL), _size(0), _capacity(0)
			{
				_size = getSize<InputIterator>(first, last);
				_capacity = _size;
				_start = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_start + i, *(first++));
			};

			vector(const vector& ref) : _alloc(ref._alloc), _start(NULL), _size(ref._size), _capacity(ref._capacity)
			{
				if (ref._start)
				{
					_start = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_start + i, ref._start[i]);
				}
			}

			// operator= : 벡터의 내용을 복사한다.
			vector &operator=(const vector &ref)
			{
				if (&ref == this)
					return (*this);
				this->clear();
				this->insert(this->end(), ref.begin(), ref.end());
				return (*this);
			}

			// 소멸자 : 벡터를 소멸한다.
			~vector()
			{
				this->clear();
				_alloc.deallocate(this->_start, this->_capacity);
			};

			// Iterators
			// begin : Return iterator to beginning
			iterator				begin(void) { return iterator(this->_start); };
			const_iterator			begin(void) const { return const_iterator(this->_start); };
			// end : Return iterator to end
			iterator				end(void) { return iterator(this->_start + this->_size); };
			const_iterator			end(void) const { return const_iterator(this->_start + this->_size); };
			// rbegin : 역순으로 첫번째 (즉, 벡터의 마지막 원소) 를 가리키는 반복자를 리턴한다.
			reverse_iterator		rbegin(void) { return reverse_iterator(this->_start + this->_size); };
			const_reverse_iterator	rbegin(void) const { return const_reverse_iterator(this->_start + this->_size); };
			// rend : 역순으로 끝 부분 (즉, 벡터의 첫번째 원소 바로 이전) 을 가리키는 반복자를 리턴한다.
			reverse_iterator		rend(void) { return reverse_iterator(this->_start); };
			const_reverse_iterator	rend(void) const { return const_reverse_iterator(this->_start); };

			// Capacity
			// size : Return size
			size_type	size(void) const { return this->_size; };
			// max_size : Return maximum size
			size_type	max_size(void) const { return this->_alloc.max_size(); };
			// resize : Change size
			void		resize(size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw (std::length_error("vector::resize"));
				else if (n < this->_size)
				{
					for (pointer i = _start + _size - 1; i >= _start + n; i--)
						_alloc.destroy(i);
					_size = n;
				}
				else
					this->insert(this->end(), n - this->_size, val);
			}
			// capacity : 벡터에 할당된 전체 크기를 리턴한다.
			size_type	capacity(void) const { return this->_capacity; };
			// empty : 벡터가 비었는지 체크한다.
			bool		empty(void) const { return !_size; };
			// reserve : 벡터에 할당된 크기를 변경한다.
			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector exceeds the size of vector::max_size().");
				else if (n > _size) {
					value_type *tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; ++i)
						_alloc.construct(tmp + i, *(_start + i));
					for (size_type i = 0; i < _size; ++i)
						_alloc.destroy(_start + i);
					_alloc.deallocate(_start, _capacity);
					_start = tmp;
					_capacity = n;
				}
			}

			// Element access:
			// operator[] : 원소에 접근한다.
			reference		operator[](size_type n) { return *(this->_start + n); };
			const_reference	operator[](size_type n) const { return *(this->_start + n); };
			// at : 원소에 접근한다.
			reference		at(size_type n)
			{
				if (n > this->_size)
					throw (std::out_of_range("out of range"));
				return *(this->_start + n);
			};
			const_reference	at(size_type n) const
			{
				if (n > this->_size)
					throw (std::out_of_range("out of range"));
				return *(this->_start + n);
			};
			// front : Access first element
			reference		front(void) { return *(this->_start); };
			const_reference	front(void) const { return *(this->_start); };
			// back : Access last element
			reference		back(void) { return *(this->_start + _size - 1); };
			const_reference	back(void) const { return *(this->_start + _size - 1); };



			// Modifiers
			// assign : Assign vector content
			void		assign(size_type n, const value_type &val)
			{
				if (n > _capacity)
					reserve(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_start + i, val);
				_size = n;
			}

			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type diff = getSize<InputIterator>(first, last);
				if (diff > _capacity)
					reserve(diff);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				for (size_type i = 0; i < diff; i++)
					_alloc.construct(_start + i, *(first++));
				_size = diff;
			}

			// push_back: Add element at the end
			void		push_back(const value_type& val)
			{
				if (_size + 1 > _capacity)
					_extend_capacity();
				_alloc.construct(_start + _size, val);
				_size += 1;
			};
			// pop_back : 마지막 원소를 제거한다.
			void		pop_back(void)
			{
				_size -= 1;
				_alloc.destroy(_start + _size);
			};
			// insert : 벡터 중간에 원소를 추가한다.
			iterator	insert(iterator position, const value_type& val)
			{
				difference_type diff = &(*end()) - &(*position);
				if (_size + 1 > _capacity)
					_extend_capacity();
				for (pointer i = _start + _size - 1; i >= _start + _size - diff; i--)
				{
					_alloc.construct(i + 1, *i);
					_alloc.destroy(i);
				}
				_alloc.construct(_start + _size - diff, val);
				_size += 1;
				return (iterator(_start + _size - diff - 1));
			}
			void		insert(iterator position, size_type n, const value_type& val)
			{
				difference_type diff = &(*end()) - &(*position);
				if (_size + n > _capacity)
					_extend_capacity(_size + n);
				for (pointer i = _start + _size - 1; i >= _start + _size - diff; i--)
				{
					_alloc.construct(i + n, *i);
					_alloc.destroy(i);
				}
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_start + _size - diff + i, val);
				_size += n;
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				difference_type n = getSize<InputIterator>(first, last);
				difference_type diff = &(*end()) - &(*position);
				if (_size + n > _capacity)
					_extend_capacity(_size + n);
				for (pointer i = _start + _size - 1; i >= _start + _size - diff; i--)
				{
					_alloc.construct(i + n, *i);
					_alloc.destroy(i);
				}
				for (int i = 0; i < n; i++)
					_alloc.construct(_start + _size - diff + i, *(first++));
				_size += n;
			}

			// erase : 원소를 제거한다.
			iterator	erase(iterator position)
			{
				pointer p_pos = &(*position);
				_alloc.destroy(p_pos);
				for (pointer i = p_pos; i < _start + _size - 1; i++)
				{
					_alloc.construct(i, *(i + 1));
					_alloc.destroy(i + 1);
				}
				_size -= 1;
				return (iterator(p_pos));
			}

			iterator	erase(iterator first, iterator last)
			{
				pointer p_first = &(*first);
				pointer p_last = &(*last);
				for (pointer i = p_first; i != p_last; i++)
				{
					_alloc.destroy(i);
				}
				for (int i = 0; i < &*end() - p_last; i++)
				{
					_alloc.construct(p_first + i, *(p_last + i));
					_alloc.destroy(p_last + i);
				}
				_size -= p_last - p_first;
				return (iterator(p_first));
			}

			// swap : 다른 벡터와 원소를 바꿔치기 한다.
			void swap(vector &x)
			{
				std::swap(_start, x._start);
				std::swap(_size, x._size);
				std::swap(_capacity, x._capacity);
				std::swap(_alloc, x._alloc);
			}
			// clear : delete all elements and make size to 0
			void		clear(void)
			{
				for (size_type i=0; i < this->_size; i++)
					_alloc.destroy(_start + i);
				this->_size = 0;
			};


			// Allocator
			allocator_type	get_allocator() const { return this->_alloc; };

			template<typename U>
			friend bool operator== (const vector& lhs, const vector<U>& rhs)
			{
				const_iterator lhs_ite = lhs.begin();
				typename vector<U>::const_iterator rhs_ite = rhs.begin();
				while (1) {
					if (lhs_ite == lhs.end() && rhs_ite == rhs.end()) return true;
					if (lhs_ite == lhs.end()) return false;
					if (rhs_ite == rhs.end()) return false;
					if (*lhs_ite != *rhs_ite) return false;
					lhs_ite++;
					rhs_ite++;
				}
			};

			template<typename U>
			friend bool operator!= (const vector& lhs, const vector<U>& rhs)
			{
				return !(lhs == rhs);
			};


			template<typename U>
			friend bool operator< (const vector& lhs, const vector<U>& rhs)
			{
				const_iterator lhs_ite = lhs.begin();
				typename vector<U>::const_iterator rhs_ite = rhs.begin();
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

			template<typename U>
			friend bool operator<= (const vector& lhs, const vector<U>& rhs)
			{
				const_iterator lhs_ite = lhs.begin();
				typename vector<U>::const_iterator rhs_ite = rhs.begin();
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

			template<typename U>
			friend bool operator> (const vector& lhs, const vector<U>& rhs)
			{
				return !(lhs <= rhs);
			};

			template<typename U>
			friend bool operator>= (const vector& lhs, const vector<U>& rhs)
			{
				return !(lhs < rhs);
			};
	};
}



#endif