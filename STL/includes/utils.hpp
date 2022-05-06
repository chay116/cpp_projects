/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 08:45:42 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 02:24:41 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace	ft
{
	// true_type과 false_type의 is_integral 및 enable_if의 return 값으로 사용된다. overloading해서 사용
	// operator bool과 value값 둘 중 하나로 bool 값을 전달할 수 있다.
	struct true_type
	{
		static const bool value = true;
		operator bool() const { return value; }
	};

	struct false_type
	{
		static const bool value = false;
		operator bool() const { return value; }
	};

	// integral에 해당하는 경우(정수 계열의 값)에 대해서는 true_type 그 외의 경우에 대해서는 false_type으로 만들어준다.
	//template T의 무작위 값이 아닌 특정한 값이 들어온 경우 true_type, 그 외의 T 형식이 들어온 경우는 false_type이 된다.
	template <typename T>
	struct is_integral_base : false_type {};

	template <>
	struct is_integral_base<bool> : true_type {};
	template <>
	struct is_integral_base<char> : true_type {};
	template <>
	struct is_integral_base<signed char> : true_type {};
	template <>
	struct is_integral_base<short int> : true_type {};
	template <>
	struct is_integral_base<int> : true_type {};
	template <>
	struct is_integral_base<long int> : true_type {};
	template <>
	struct is_integral_base<long long int> : true_type {};
	template <>
	struct is_integral_base<unsigned short int> : true_type {};
	template <>
	struct is_integral_base<unsigned int> : true_type {};
	template <>
	struct is_integral_base<unsigned long int> : true_type {};
	template <>
	struct is_integral_base<unsigned long long int> : true_type {};

	template <typename T>
	struct is_integral : is_integral_base<T> {};

	// enable_if 는 sfinae를 통해서 조건에 맞지 않는 함수들을 오버로딩 후보군에서 쉽게 뺼 수 있도록 도와주는 간단한 템플릿 메타 함수이다.
	// 조건문인 Cond가 주어지고, 이에 만족한다면 type으로 bool을 return하게 하고, 그렇지 않은 경우는 type에 아무것도 들어가지 않게 된다.
	// 즉, 주어진 Type이 아닌 경우에 대해서는 error를 발생시킨다.
	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	// pair 클래스는 두 객체를 하나의 객체로 취급할 수 있도록 묶어주는 클래스로 STL에서 데이터 쌍을 표현할 떄 사용한다.
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		pair() : first(), second() {};
		template<class U, class V>
		pair(const pair<U, V> &ref) : first(ref.first), second(ref.second) {};
		pair(const first_type &a, const second_type &b) : first(a), second(b) {};

		operator pair<const T1, const T2>() const { return (pair<const T1, const T2>(first, second)); };
		pair& operator=(const pair& ref)
		{
			this->first = ref.first;
			this->second = ref.second;
			return *this;
		}
	};



	template< class T1, class T2 >
	bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return (lhs.first == rhs.first) && (rhs.second == rhs.second); }

	template< class T1, class T2 >
	bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !((lhs.first == rhs.first) && (rhs.second == rhs.second)); }

	template< class T1, class T2 >
	bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		if (lhs.first == rhs.first)
			return (lhs.second > rhs.second);
		return (lhs.first > rhs.first);
	}

	template< class T1, class T2 >
	bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		if (lhs.first == rhs.first)
			return (lhs.second >= rhs.second);
		return (lhs.first > rhs.first);
	}

	template< class T1, class T2 >
	bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(lhs >= rhs); }

	template< class T1, class T2 >
	bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(lhs > rhs); }





	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		/* The first argument type */
		typedef Arg1 first_argument_type;

		/* The second arguement type */
		typedef Arg2 second_argument_type;

		/* The result type */
		typedef Result result_type;
	};

	template <class T>
	struct less : binary_function<T, T, bool>
	{
		bool operator() (const T& x, const T& y) const { return (x < y); }
	};

	template <class T1, class T2>
	ft::pair<T1,T2> make_pair(T1 x, T2 y) { return ft::pair<T1, T2>(x, y); }

	// lexicographical compare(사전학적 비교)은 두 iterator에 대해서 first에서 last까지 순회하면서 크기를 비교하는 함수다.
	// 1과 2가 first부터 시작하여 비교하며 진행되는데, 차이가 존재한다면 return 해주고, 그렇지 않다면 끝까지 간다.
	// 일반적으로 비교값 혹은 comp에 의한 값이 1이 2보다 큰 경우에만 true를 리턴한다. 즉 >와 같이 작동한다.
	// 또한 길이가 짧은 것이 lexicographically 작은 것에 해당하므로, 1이 길이가 짧은 경우 ture에 해당한다.
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2,
								Compare comp)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
}

#endif