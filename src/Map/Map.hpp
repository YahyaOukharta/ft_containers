#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <string>
# include "AVLnew.hpp"
# include "../Utils/Utils.hpp"
# include "./Iterator.hpp"
# include "../Vector/Vector.hpp"

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

			typedef ft::MapIterator<value_type, key_compare>			iterator;
			typedef ft::MapIterator<value_type, key_compare>	const_iterator;
			typedef ft::reverse_iterator<iterator>		reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			typedef typename ft::BST<value_type,Compare,allocator_type>::node_type node_type;

			class value_compare:public std::binary_function<value_type,value_type,bool>
			{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				protected:
					Compare comp;
				public:
					
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

		private:
			ft::BST<value_type,Compare ,allocator_type> tree;	
			key_compare k_cmp;
			value_compare v_cmp;
			allocator_type alloc;

		public:

			Map() :v_cmp(Compare()){
				k_cmp = Compare();
			}

			Map( const Compare& comp, const Allocator& _alloc = Allocator() ) :v_cmp(Compare())
			{
				alloc = _alloc;
				k_cmp = comp;
			}

			template< class InputIt >
			Map( InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt())
				:v_cmp(Compare())
			{
				k_cmp = Compare();
				insert(first,last);
			}

			Map( Map const & other ) : v_cmp(Compare())
			{
				k_cmp = Compare();

				if(other.size())
					insert(other.begin(),other.end());
			}

			~Map(){

			}

			Map &		operator=( Map const & other ){
				clear();
				if (other.size())
					insert(other.begin(),other.end());
				return *this;
			}

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
				mapped_type &ref = (*((this->insert(ft::make_pair(key,mapped_type()))).first)).second;
				return ref;
			}

		//iterators
			iterator begin(){
				if(size())
				return iterator(tree.getLowestChild(tree.tree_root));
				return end();
			}	
			const_iterator begin() const{
				if(size())
					return const_iterator(tree.getLowestChild(tree.tree_root));
				return end();			}

			iterator end(){
				iterator it(tree.getLargestChild(tree.tree_root));
				it++;
				return it;
			}
			const_iterator end() const{
				iterator it(tree.getLargestChild(tree.tree_root));
				it++;
				return const_iterator(it);
			}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend(){ // to verify
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const{
			return const_reverse_iterator(begin());
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
				tree.s=0;
			}

			//insert
			ft::pair<iterator, bool> insert( const value_type & value ){
				
				size_type prev_s = size();
				iterator it(tree.insert(value));

				return (ft::make_pair<iterator,bool>(it, prev_s - size()));
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
			iterator erase( iterator pos ){

				iterator p = pos + 1;
				tree.deleteWithKey(pos->first);
				return p;
			}

			iterator erase( iterator first, iterator last ){
				if (!tree.tree_root)
					return (end());
				ft::Vector<key_type> v;
				while(first != last)
				{
					v.push_back(first->first);
					first++;
				}
				for(typename ft::Vector<key_type>::iterator it = v.begin(); it!=v.end(); ++it)
					erase(*it);
				return first;
			}

			size_type erase( const key_type& key ){
				size_type s = size();
				tree.deleteWithKey(key);
				return (s - size());
			}

			void setAttributes(node_type *tree_root, size_type s,allocator_type a)
			{
				tree.tree_root = tree_root;
				tree.s = s;
				alloc = a;
			}

			ft::BST<value_type,Compare,allocator_type> &getTree()
			{
				return tree;
			}

			//swap
			void swap( Map& other )
			{
				node_type *other_root = other.getTree().tree_root;
				allocator_type other_alloc = other.get_allocator();
				size_type other_s = other.getTree().s;
				// std::cout << "other root " << other.getTree().tree_root << std::endl;
				// std::cout << "this  root " << tree.tree_root << std::endl;

				other.setAttributes(tree.tree_root, tree.s, get_allocator());
				setAttributes(other_root, other_s, other_alloc);

				// std::cout << "other root " << other.getTree().tree_root << std::endl;
				// std::cout << "this  root " << tree.tree_root << std::endl;
			}

		// Lookup
			//count
			size_type count( const key_type& key ) const{
				if (tree.searchFor(key))
					return (1);
				return (0);
			}

			//find
			iterator find( const key_type& key ){
				node_type *n;
				if ((n = tree.searchFor(key)))
					return (iterator(n));
				return (end());
			}
			const_iterator find( const key_type& key ) const{
				node_type *n;
				if ((n = tree.searchFor(key)))
					return (const_iterator(n));
				return (end());
			}

			// //equal_range
			ft::pair<iterator,iterator> equal_range( const key_type& key ){
				node_type *n;
				if ((n = tree.searchFor(key)))
					return (ft::make_pair(lower_bound(key),upper_bound(key)));
				return (ft::make_pair(upper_bound(key),upper_bound(key)));
			}
			ft::pair<const_iterator,const_iterator> equal_range( const key_type& key ) const{
				node_type *n;
				if ((n = tree.searchFor(key)))
					return (ft::make_pair(lower_bound(key),upper_bound(key)));
				return (ft::make_pair(upper_bound(key),upper_bound(key)));
			}

			// //lower_bound
			iterator lower_bound(const key_type& key)
			{
				node_type *n = tree.tree_root;
				node_type *prev;
				while (n)
				{
					prev = n;
					if (k_cmp(n->getKey(), key))
						n = n->getChildren()[1];
					else if (k_cmp(key, n->getKey()))
						n = n->getChildren()[0];
					else return n;
				}
				while (prev->getKey() < key){
					prev = prev->getParent();
				}
				return prev;
			}
			const_iterator lower_bound( const key_type& key ) const{
				node_type *n = tree.tree_root;
				node_type *prev;
				while (n)
				{
					prev = n;
					if (k_cmp(n->getKey(), key))
						n = n->getChildren()[1];
					else if (k_cmp(key, n->getKey()))
						n = n->getChildren()[0];
					else return n;
				}
				while (k_cmp(prev->getKey(), key)){
					prev = prev->getParent();
				}
				return prev;
			}

			// //upper_bound
			iterator upper_bound( const key_type& key ){
				node_type *n = tree.tree_root;
				node_type *prev;
				while (n)
				{
					prev = n;
					if (k_cmp(n->getKey(), key))
						n = n->getChildren()[1];
					else if (k_cmp(key, n->getKey()))
						n = n->getChildren()[0];
					else break;
				}
				if(n) return n->next();
				while (!k_cmp(key, prev->getKey())){
					prev = prev->getParent();
				}
				return prev;

			}
			const_iterator upper_bound( const key_type& key ) const{
				node_type *n = tree.tree_root;
				node_type *prev;
				while (n)
				{
					prev = n;
					if (k_cmp(n->getKey(), key))
						n = n->getChildren()[1];
					else if (k_cmp(key, n->getKey()))
						n = n->getChildren()[0];
					else break;
				}
				if(n) return n->next();
				while (!k_cmp(key, prev->getKey())){
					prev = prev->getParent();
				}
				return prev;
			}

		//Observers
			//key_comp
			key_compare key_comp() const{
				return k_cmp;
			}
			//value_comp
			value_compare value_comp() const{
				return value_compare(k_cmp);
			}

		//Operators
		bool operator==(const Map& rhs ){
			if(size() != rhs.size())
                return false;
            return ft::equal(begin(),end(),rhs.begin());
		}

		bool operator!=(const Map& rhs ){
			return !operator==(rhs);
		}

		bool operator< (const Map& rhs ){
			if(size() != rhs.size())
				return size() < rhs.size();
			else return ft::lexicographical_compare(begin(),end(),rhs.begin(),rhs.end());
		}

		bool operator<=(const Map& rhs ){
			return (!operator>(rhs));
		}

		bool operator> (const Map& rhs )
		{
			if (size() != rhs.size())
				return size() > rhs.size();
			else return ft::lexicographical_compare(rhs.begin(), rhs.end(), begin(), end());
		}

		bool operator>=(const Map& rhs ){
			return (!operator<(rhs));
		}
	
		void print() const {
			tree.print();
		}
	};

	//swap (map specialization)
	template< class Key, class T, class Compare, class Alloc >
	void swap( Map<Key,T,Compare,Alloc>& lhs,
			Map<Key,T,Compare,Alloc>& rhs ){
				lhs.swap(rhs);
	}



}

#endif /* ************************************************************* MAP_H */