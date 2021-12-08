#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <string>
#include "../Vector/Vector.hpp"

namespace ft
{
	template<
		class T,
		class Container = ft::Vector<T>
	> 
	class Stack
	{

		public:
			typedef 		 Container					container_type;	
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference const_reference;

		protected:
			container_type c;
			
		public:

			Stack( const Container& cont = Container() ){
				c = cont;
			}

			Stack( Stack const & other ){
				c = other.c;
			}

			~Stack(){

			}

			Stack &		operator=( Stack const & rhs ){
				c = rhs.c;
			}


			//Element access
			reference top(){
				return c[c.size()-1];
			}
			const_reference top() const{
				return c[c.size()-1];
			}

			//Capacity
			size_type size() const{
				return (c.size());
			}
			bool empty() const{
				return size() <= 0;
			}

			//Modifiers
			void push( const value_type& value ){
				c.push_back(value);
			}
			void pop(){
				c.pop_back();
			}
		
			// relational operators
			bool operator==( const Stack<T,Container>& rhs )
			{
				return c == rhs.c;
			}

			bool operator!=( const Stack<T,Container>& rhs )
			{
				return c != rhs.c;
			}

			bool operator<( const Stack<T,Container>& rhs )
			{
				return c < rhs.c;
			}

			bool operator<=( const Stack<T,Container>& rhs )
			{
				return c <= rhs.c;
			}

			bool operator>( const Stack<T,Container>& rhs )
			{
				return c > rhs.c;
			}

			bool operator>=( const Stack<T,Container>& rhs )
			{
				return c >= rhs.c;
			}
		

	};

}


#endif /* *********************************************************** STACK_H */	