/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chalim <42.4.chalim@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 19:31:49 by chalim            #+#    #+#             */
/*   Updated: 2022/03/22 02:30:07 by chalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_NODE_HPP
# define RBT_NODE_HPP

# include <iostream>
# include "utils.hpp"

namespace	ft
{
	typedef enum { BLACK, RED } RBT_Node_color;
	template <class T>
	class RBT_Node {
		public:
			typedef T		value_type;
			RBT_Node		*left;
			RBT_Node		*right;
			RBT_Node		*parent;
			RBT_Node_color	color;
			value_type		value;

			operator RBT_Node<const T>() const { return (RBT_Node<const T>(this->_node)); };
			RBT_Node () : left(NULL), right(NULL), parent(NULL), color(RED), value() {};
			RBT_Node (const T& _value) : left(NULL), right(NULL), parent(NULL), color(RED), value(_value) {};
			RBT_Node(RBT_Node const &ref) {
				this->left = ref.left;
				this->right = ref.right;
				this->parent = ref.parent;
				this->value = ref.value;
				this->color = ref.color;
			};

			~RBT_Node () {};
			RBT_Node	&operator=(RBT_Node const &ref) {
				this->left = ref.left;
				this->right = ref.right;
				this->parent = ref.parent;
				this->value = ref.value;
				this->color = ref.color;
				return (*this);
			};

			template<class T2>
			bool		operator==(const RBT_Node<T2>& ref) {
				if (value == ref.value) return (true);
				return (false);
			};

			RBT_Node	*find_grandparent(void)
			{
				return this->parent->parent;
			}

			RBT_Node	*find_uncle(void)
			{
				RBT_Node *grandparent = find_grandparent();
				if (grandparent->right == this->parent) return (grandparent->left);
				else return (grandparent->right);
			}
	};
}


#endif