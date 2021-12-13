#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <string>
# include "AVL.hpp"
# include "../Utils/Utils.hpp"
# include "./Iterator.hpp"


# define ABS(x) (x<0?-x:x)

namespace ft{

	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class Map
	{
		public:
			typedef 								Key key_type;
			typedef 								T	mapped_type;
			typedef typename ft::pair<const Key, T> 	value_type;
			typedef size_t      						size_type;
			typedef ptrdiff_t 							difference_type;
			typedef Compare 							key_compare;
			typedef Allocator							allocator_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef typename Allocator::pointer 		pointer;
			typedef typename Allocator::const_pointer	const_pointer;

			typedef ft::MapIterator<value_type>			iterator;
			typedef ft::MapIterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>		reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			
			class value_compare
			{
					typedef bool 		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

				protected :
					Compare comp;

					value_compare( Compare c ): comp(c) {}
				
				public:
					result_type operator()( const first_argument_type& lhs, const second_argument_type& rhs ) const{
						return comp(lhs,rhs);
					}
			};

		private:
			ft::BST<value_type> tree;
		public:

			Map(){

			}

			template< class InputIt >
			Map( InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt())
			{

			}

			Map( Map const & other );

			~Map();

			Map &		operator=( Map const & other );

			allocator_type get_allocator() const;
		
		//Element access
			mapped_type& at( const key_type& key );
			const mapped_type& at( const key_type& key ) const;

			mapped_type& operator[]( const key_type& key );

		//iterators
		// iterator begin();
		// const_iterator begin() const;

		// iterator end();
		// const_iterator end() const;

		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;

		// reverse_iterator rend();
		// const_reverse_iterator rend() const;

		//Capacity
			bool empty() const;
			size_type size() const;
			size_type max_size() const;

		// Modifiers
			//clear
			void clear();

			//insert
			// std::pair<iterator, bool> insert( const value_type& value );
			// iterator insert( iterator hint, const value_type& value );
			template< class InputIt >
			void insert( InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt());

			//erase
			// void erase( iterator pos );
			// void erase( iterator first, iterator last );
			size_type erase( const key_type& key );
			
			//swap
			void swap( Map& other );

		// Lookup
			//count
			size_type count( const key_type& key ) const;

			//find
			// iterator find( const key_type& key );
			// iterator find( const key_type& key ) const;

			// //equal_range
			// std::pair<iterator,iterator> equal_range( const key_type& key );
			// std::pair<const_iterator,const_iterator> equal_range( const key_type& key ) const;

			// //lower_bound
			// iterator lower_bound( const key_type& key );
			// const_iterator lower_bound( const key_type& key ) const;

			// //upper_bound
			// iterator upper_bound( const key_type& key );
			// const_iterator upper_bound( const key_type& key ) const;

		//Observers
			//key_comp
			key_compare key_comp() const;
			//value_comp
			value_compare value_comp() const;

		//Operators
		bool operator==(const Map& rhs );

		bool operator!=(const Map& rhs );

		bool operator< (const Map& rhs );

		bool operator<=(const Map& rhs );

		bool operator> (const Map& rhs );

		bool operator>=(const Map& rhs );
	};

	//swap (map specialization)
	template< class Key, class T, class Compare, class Alloc >
	void swap( Map<Key,T,Compare,Alloc>& lhs,
			Map<Key,T,Compare,Alloc>& rhs );

}

#endif /* ************************************************************* MAP_H */