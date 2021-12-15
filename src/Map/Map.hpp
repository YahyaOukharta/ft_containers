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
			typedef ft::MapIterator<value_type>	const_iterator;
			typedef ft::map_reverse_iterator<iterator>		reverse_iterator;
			typedef ft::map_reverse_iterator<const_iterator> const_reverse_iterator;

			typedef typename ft::BST<value_type>::node_type node_type;

			class value_compare
			{
					typedef bool 		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

				protected :
					Compare comp;

					value_compare( Compare c): comp(c) {}
				
				public:
					result_type operator()( const first_argument_type& lhs, const second_argument_type& rhs ) const{
						return comp(lhs,rhs);
					}
			};

		private:
			ft::BST<value_type> tree;
			key_compare cmp;
			allocator_type alloc;
		public:

			Map() {

			}

			Map( const Compare& comp, const Allocator& alloc = Allocator() ){
				cmp = comp;
			}

			template< class InputIt >
			Map( InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt())
			{

			}

			Map( Map const & other );

			~Map(){

			}

			Map &		operator=( Map const & other );

			allocator_type get_allocator() const{
				return alloc;
			}
		
		//Element access
			mapped_type& at( const key_type& key ){
				return tree.searchFor(key)->getValue();
			}
			const mapped_type& at( const key_type& key ) const{
				return tree.searchFor(key)->getValue();
			}

			mapped_type& operator[]( const key_type& key ){
				return tree.searchFor(key)->getValue();
			}

		//iterators
			iterator begin(){
				return iterator(tree.getLowestChild(tree.tree_root));
			}
			const_iterator begin() const{
				return const_iterator(tree.getLowestChild(tree.tree_root));
			}

			iterator end(){
				return iterator(0);
			}
			const_iterator end() const{
				return const_iterator(0);
			}

		reverse_iterator rbegin()
		{
			iterator it(tree.getLargestChild(tree.tree_root));
			return reverse_iterator(it);
		}
		const_reverse_iterator rbegin() const
		{
			iterator it(tree.getLargestChild(tree.tree_root));
			return const_reverse_iterator(it);
		}

		reverse_iterator rend(){
			return reverse_iterator(0);
		}
		const_reverse_iterator rend() const{
			return const_reverse_iterator(0);

		}

		//Capacity
			bool empty() const {
				return tree.s == 0;
			}
			size_type size() const{
				return tree.s;
			}
			size_type max_size() const{
				return alloc.max_size();
			}

		// Modifiers
			//clear
			void clear(){
				tree.freeAll();
			}

			//insert
			ft::pair<iterator, bool> insert( const value_type & value ){
				
				node_type *n;
				
				if((n = tree.searchFor(value.first)))
					return ft::make_pair(iterator(n),false);
				tree.insert(value);
				return ft::make_pair(iterator(tree.searchFor(value.first)),true);
			}
			iterator insert( iterator hint, const value_type& value ){
				(void)hint;
				return insert(value).first;
			}
			template< class InputIt >
			void insert( InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt()){
				while (first != last){
					insert(*first);
					first++;
				}
			}

			//erase
			void erase( iterator pos );
			void erase( iterator first, iterator last );
			size_type erase( const key_type& key );
			
			//swap
			void swap( Map& other );

		// Lookup
			//count
			size_type count( const key_type& key ) const;

			//find
			iterator find( const key_type& key );
			iterator find( const key_type& key ) const;

			// //equal_range
			std::pair<iterator,iterator> equal_range( const key_type& key );
			std::pair<const_iterator,const_iterator> equal_range( const key_type& key ) const;

			// //lower_bound
			iterator lower_bound( const key_type& key );
			const_iterator lower_bound( const key_type& key ) const;

			// //upper_bound
			iterator upper_bound( const key_type& key );
			const_iterator upper_bound( const key_type& key ) const;

		//Observers
			//key_comp
			key_compare key_comp() const{
				return key_compare();
			}
			//value_comp
			value_compare value_comp() const{
				return value_compare();
			}

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