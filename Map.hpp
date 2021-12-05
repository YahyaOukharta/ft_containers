#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <string>
#include "Utils.hpp"
# include "Vector.hpp"
# define ABS(x) (x<0?-x:x)
# define MAX(a,b) (a<b?b:a)
namespace ft
{
	template < class Key>
	class Node {
		public:
			typedef 	Key key_type;

		private:
			key_type content;
			Node *children[2];
			Node *parent;
			int bf;
			int h;
			
		public:
			Node(key_type const &c)
			{
				content = c;
				children[0] = 0;
				children[1] = 0;
				parent = 0;
				h = 0;
				bf = 0;
			}

			void setLeft(Node *l)
			{
				children[0] = l;
			}
			void setRight(Node *r)
			{
				children[1] = r;
			}
			void setParent(Node *p)
			{
				parent = p;
			}

			key_type &getContent(void)
			{
				return content;
			}
			Node **getChildren(void){
				return children;
			}
			Node *getParent(void){
				return parent;
			}

			int getHeight()
			{
				return h;
			}
			int getBF()
			{
				return bf;
			}

			int calcHeight(){
				int hl = (children[0] ? children[0]->calcHeight() : -1);
				int hr = (children[1] ? children[1]->calcHeight() : -1);
				h = MAX(hl,hr) + 1;
				return h;
			}

			int calcBF(){
				int hl = (children[0] ? children[0]->getHeight() : -1);
				int hr = (children[1] ? children[1]->getHeight() : -1);
				bf = hr - hl;
				if (parent)
					parent->calcBF();
				return bf;
			}
	};

	template< class Key>
	class BST
	{

		typedef 	Key key_type;
		typedef  	Node<key_type> node_type;

		node_type *tree_root;

		public:
			BST(void){

			}
			BST(ft::Vector<key_type> const &v)
			{
				fillFromVec(v);
			}
			~BST(){
				
			}

			node_type *newNode(key_type const &k) const 
			{
				return new node_type(k);
			}

			void fillFromVec(ft::Vector<key_type> const &v){
				for(typename ft::Vector<key_type>::iterator it = v.begin(); it!= v.end(); it++){
					insert(*it);
				}
			}

			void insert(key_type const &v)
			{
				if (tree_root)
					insertAtNode(tree_root, v);
				else
					tree_root = newNode(v);
			}

			void insertAtNode(node_type *n, key_type v)
			{
				if(!n)
					return;
				if (v == n->getContent())
					return;
				ptrdiff_t diff = v - n->getContent();
				int dir = ((diff/ABS(diff))+1)/2;
				node_type **children = n->getChildren();
				if(!children[dir])
				{
					children[dir] = newNode(v);
					children[dir]->setParent(n);
				}
				else
					insertAtNode(children[dir], v);
				n->calcHeight();
				int bf = n->calcBF();
				if (ABS(bf) > 1)
				{
					if (bf > 0)
					{	
						singleLeftRotate(n->getChildren()[1]);
						//print();
					}
				}
			}

			void singleLeftRotate(node_type *n){
				node_type *initial_parent = n->getParent();

				n->setParent(initial_parent->getParent());

				int dir = -1;
				if(initial_parent->getParent())
				{
					dir = initial_parent->getParent()->getContent() > initial_parent->getContent();
					initial_parent->getParent()->getChildren()[dir] = n;
				}
				else
					tree_root = n;
				n->setLeft(initial_parent);
				initial_parent->setParent(n);

				initial_parent->setRight(0);
			}

			void print(const std::string& prefix, node_type* node, bool isLeft)
			{
				if(node)
				{
					std::cout << prefix;
					std::cout << (isLeft ? "├──" : "└──" );
					std::cout << node->getContent() << " " << node->getBF() << std::endl;
					print( prefix + (isLeft ? "│   " : "    "), node->getChildren()[1], true);
					print( prefix + (isLeft ? "│   " : "    "), node->getChildren()[0], false);
				}
			}

			void print()
			{
				if(tree_root)
					print("", tree_root, false);    
			}

// pass the root node of your binary tree
	};

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

			// typedef ft::MapIterator<value_type>			iterator;
			// typedef ft::MapIterator<const value_type>	const_iterator;
			// typedef ft::reverse_iterator<iterator>		reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			
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