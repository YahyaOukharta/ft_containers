#ifndef __AVL_HPP__
# define __AVL_HPP__

# include <iostream>
# include <string>
# define ABS(x) (x<0?-x:x)
# define MAX(a,b) (a<b?b:a)
# include "../Vector/Vector.hpp"
namespace ft
{
	template < class Pair, class Allocator = std::allocator<Pair> >
	class Node {

		public:
			typedef 			Pair 				pair_type;
			typedef	typename pair_type::first_type 	key_type;
			typedef	typename pair_type::second_type value_type;
			typedef						Allocator   allocator_type;

		private:
			pair_type *p;
			Node *children[2];
			Node *parent;
			int bf;
			int h;
			allocator_type alloc;

		public:

			Node(pair_type const &c)
			{
				p = alloc.allocate(1);
				alloc.construct(p, ft::pair<key_type,value_type>(c));
				
				children[0] = 0;
				children[1] = 0;
				parent = 0;
				h = 0;
				bf = 0;
			}

			Node()
			{
				p = 0;
				children[0] = 0;
				children[1] = 0;
				parent = 0;
				h = 0;
				bf = 0;
			}


			void init()
			{
				p = 0;
				children[0] = 0;
				children[1] = 0;
				parent = 0;
				h = 0;
				bf = 0;
			}

			void freeNode()
			{
				if(p)
					alloc.deallocate(p,1);
			}
			void setPair(pair_type const& con)
			{
				if (!p)
					p = alloc.allocate(1);
				alloc.construct(p, con);
			}
			

			pair_type &getPair(void)
			{
				return *p;
			}

			key_type &getKey()
			{
				return p->first;
			}

			value_type &getValue()
			{
				return p->second;
			}

			void setLeft(Node *l)
			{
				children[0] = l;
			}

			void setRight(Node *r)
			{
				children[1] = r;
			}

			void setParent(Node *_p)
			{
				parent = _p;
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
				int hl = (children[0] ? children[0]->calcHeight() : -1);
				int hr = (children[1] ? children[1]->calcHeight() : -1);
				bf = hr - hl;
				// if (parent)
				// 	parent->calcBF();
				return bf;
			}

			Node *getLowestChild(Node *n)
			{
				if (!n) return 0;
				Node *left = n->getChildren()[0];
				if (left)
					return getLowestChild(left);
				else return n;
			}

			Node *getLargestChild(Node *n)
			{
				if (!n) return 0;
				Node *right = n->getChildren()[1];
				if (right)
					return getLargestChild(right);
				else return n;
			}
			Node *next(){

				if (children[1])
					return (getLowestChild(children[1]));
				else{
					Node *tmp = this;
					while (tmp->parent && tmp->getKey() > tmp->parent->getKey())
					{
						tmp = tmp->parent;
					}
					if(!tmp->getParent())
						return (0);
					else return tmp->getParent();
				}
			}
			Node *previous(){
				if (children[0])
					return (getLargestChild(children[0]));
				else{
					Node *tmp = this;
					while (tmp->parent && tmp->getKey() < tmp->parent->getKey())
					{
						tmp = tmp->parent;
					}
					if(!tmp->getParent())
						return (0);
					else return tmp->getParent();
				}
			}

	};

	template< class Pair, class Allocator = std::allocator<Pair> >
	class BST
	{

		public:
		
		typedef 	Pair pair_type;
		typedef  	Node<pair_type, Allocator> node_type;
		typedef typename node_type::key_type key_type;
		typedef typename node_type::value_type value_type;
		
		typedef Allocator allocator_type;


		node_type *tree_root;
		size_t s;
		allocator_type alloc;

			BST(void){
				tree_root = 0;
				s=0;
			}
			BST(ft::Vector<pair_type> const &v)
			{
				tree_root = 0;
				s=0;
				fillFromVec(v);
			}

			~BST(){
				freeAll();
			}

			node_type *newNode(pair_type const &k) const 
			{
				typename allocator_type::template rebind<node_type>::other alloc_node;
				node_type *n = alloc_node.allocate(1);
				n->init();
				n->setPair(k);
				return n;
			}

			void fillFromVec(ft::Vector<pair_type> const &v){
				for(typename ft::Vector<pair_type>::iterator it = v.begin(); it!= v.end(); it++){
					insert(*it);
				}
			}

			node_type *insert(pair_type const &v)
			{
				return insertAtNode(tree_root, v);
			}
			
            void rebalanceAtNode(node_type *n)
			{
				int bf = n->calcBF();
				if (ABS(bf) > 1)
				{
					if (bf > 0)
					{
						if (n->getChildren()[1] && n->getChildren()[1]->getBF() < 0)
							singleRightRotate(n->getChildren()[1]);
						singleLeftRotate(n);
					}
					else
					{
						if (n->getChildren()[0] && n->getChildren()[0]->getBF() > 0)
							singleLeftRotate(n->getChildren()[0]);
						singleRightRotate(n);
					}
					// n->calcBF();
				}
			}

			void rebalanceFromNode(node_type *n){
				if(!n) return;
				rebalanceAtNode(n);
				rebalanceFromNode(n->getParent());
			}

			node_type *insertAtNode(node_type *n, pair_type v)
			{
				if(!n)
				{
					s++;
					return (tree_root=newNode(v));
				}

				// if (v.first == n->getKey())
				// 	return;
				// ptrdiff_t diff = (v.first > n->getKey() ? 1 : -1);
				// int dir = ((diff/ABS(diff))+1)/2;
				// node_type **children = n->getChildren();
				// if(!children[dir])
				// {
				// 	children[dir] = newNode(v);
				// 	children[dir]->setParent(n);
				// }
				// else
				// 	insertAtNode(children[dir], v);
				// rebalanceAtNode(n);

				node_type *tmp = n;
				while (v.first != tmp->getKey())
				{
					ptrdiff_t diff = (v.first > tmp->getKey() ? 1 : -1);
					int dir = ((diff/ABS(diff))+1)/2;
					node_type **children = tmp->getChildren();
					if(!children[dir])
					{
						children[dir] = newNode(v);
						children[dir]->setParent(tmp);
						s++;
						rebalanceFromNode(tmp); // 9210
						tmp = children[dir];
						break;
					}
					else
						tmp = children[dir];
				}
				return tmp;
			}

			void singleLeftRotate(node_type *n)
			{
				node_type *init_parent = n->getParent();
				node_type *right = n->getChildren()[1];

				node_type *right_left_subtree = right->getChildren()[0];

				if (init_parent)
				{
					int dir = init_parent->getKey() < n->getKey();
					init_parent->getChildren()[dir] = right;
				}
				else
					tree_root = right;

				right->setLeft(n);
				right->setParent(init_parent);

				n->setParent(right);

				n->setRight(right_left_subtree);
				if(right_left_subtree)
					right_left_subtree->setParent(n);
		
			}

			void singleRightRotate(node_type *n)
			{
				node_type  *init_parent = n->getParent();
				node_type *left = n->getChildren()[0];

				node_type *left_right_subtree = left->getChildren()[1];
				if (init_parent)
				{
					int dir = init_parent->getKey() < n->getKey();
					init_parent->getChildren()[dir] = left;
				}
				else
					tree_root = left;

				left->setRight(n);
				left->setParent(init_parent);

				n->setParent(left);

				n->setLeft(left_right_subtree);
				if(left_right_subtree)
					left_right_subtree->setParent(n);

			}

			node_type *getLowestChild(node_type *n) const
			{
				if (!n) return 0;
				node_type *left = n->getChildren()[0];
				if (left)
					return getLowestChild(left);
				else return n;
			}

			node_type *getLargestChild(node_type *n) const
			{
				if (!n) return 0;
				node_type *right = n->getChildren()[1];
				if (right)
					return getLargestChild(right);
				else return n;
			}

			node_type *searchFor(key_type const &key) const
			{
				node_type *n=tree_root;
				while (n)
				{
					if (n->getKey() == key)
						return n;
					node_type **children = n->getChildren();
					int dir = n->getKey() < key;
					n = children[dir];
				}
				return (0);
			}

			node_type *deleteWithKey(key_type const & k){
				node_type *node = searchFor(k);
				if(!node) return 0;
				//std::cout << "deleting " << k << std::endl;
				node_type **children = node->getChildren();
				typename allocator_type::template rebind<node_type>::other alloc_node;

				// successor
				if(children[1])
				{
					node_type *successor = getLowestChild(children[1]);
					//std::cout << "successor is " << successor->getKey() << std::endl;
					node->setPair(successor->getPair());

					if(successor == node->getChildren()[1])
					{
						successor->getParent()->setRight(successor->getChildren()[1]);
						if(successor->getChildren()[1])
							successor->getChildren()[1]->setParent(node);
					}
					else
						successor->getParent()->setLeft(0);
					rebalanceFromNode(successor);
					//delete successor node
					successor->freeNode();
					alloc_node.deallocate(successor, 1);
					s--;
					return node;
				}
				else if(children[0])
				{
					node_type *predecessor = getLargestChild(children[0]);
					//std::cout << "predecessor is " << predecessor->getKey() << std::endl;
					node->setPair(predecessor->getPair());

					if(predecessor == node->getChildren()[0])
					{
						predecessor->getParent()->setLeft(predecessor->getChildren()[0]);
						if(predecessor->getChildren()[0])
							predecessor->getChildren()[0]->setParent(node);
					}
					else
						predecessor->getParent()->setLeft(0);
					rebalanceFromNode(predecessor);
					//delete predecessor node
					predecessor->freeNode();
					alloc_node.deallocate(predecessor, 1);
					s--;
					return node;
				}
				else
				{
					//std::cout << "node to delete is leaf" << std::endl;
					if (node->getParent())
					{
						//std::cout << "node has parent " << node->getParent() << std::endl;

						if(node->getKey() > node->getParent()->getKey())
							node->getParent()->setRight(0);
						else 
							node->getParent()->setLeft(0);
						node->getParent()->calcBF();
						rebalanceFromNode(node->getParent());
					}
					else
					{
						//std::cout << "node has no parent" << std::endl;
						tree_root = 0;
					}
					//delete leaf node
					node_type *n = tree_root ? node->getParent() : 0;
					node->freeNode();
					alloc_node.deallocate(node, 1);
					s--;
					return n;
				}
			}

			node_type *first(){
				if (tree_root)
					return getLowestChild(tree_root);
				else
					return (0);
			}
			node_type *last(){
				if (tree_root)
					return getLargestChild(tree_root);
				else
					return (0);
			}

// Free
			void freeSubtree(node_type *n)
			{
				node_type **children = n->getChildren();
				if (children[0])
					freeSubtree(children[0]);
				if (children[1])
					freeSubtree(children[1]);
				n->freeNode();
				delete n;
				
			}

			void freeAll(){
				if (tree_root)
					freeSubtree(tree_root);
				tree_root = 0;
			}

// Utils
			void print(const std::string& prefix, node_type* node, bool isLeft)
			{
				if(node)
				{
					std::cout << prefix;
					std::cout << (isLeft ? "├──" : "└──" );
					std::cout << "<"<<node->getKey() << ", "<<node->getValue()<<"> " << node->getBF() << std::endl;
					print( prefix + (isLeft ? "│   " : "    "), node->getChildren()[1], true);
					print( prefix + (isLeft ? "│   " : "    "), node->getChildren()[0], false);
				}
			}

			void print()
			{
				if (tree_root)
				{
					print("", tree_root, false);
					std::cout << "height : " << tree_root->calcHeight() << " for " << s << " elements" <<std::endl;
				}
			}

			void traverse(node_type *n)
			{
				if(!n)
					return;
				traverse(n->getChildren()[0]);
				std::cout << "<"<<n->getKey() << ", "<<n->getValue()<<"> - ";
				traverse(n->getChildren()[1]);
			}

			void inOrderPrint(){
				traverse(tree_root);
				std::cout << std::endl;
				std::cout << std::endl;
				
			}
    };
};
#endif