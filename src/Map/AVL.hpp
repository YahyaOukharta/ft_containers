#ifndef __AVL_HPP__
# define __AVL_HPP__

# include <iostream>
# include <string>
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

			void setContent(key_type const& con)
			{
				content = con;
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
				int hl = (children[0] ? children[0]->calcHeight() : -1);
				int hr = (children[1] ? children[1]->calcHeight() : -1);
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
		size_t s;

		public:
			BST(void){
				s=0;
			}
			BST(ft::Vector<key_type> const &v)
			{
				s=0;
				fillFromVec(v);
			}
			~BST(){
				freeAll();
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
				s++;

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
						n->calcBF();
				}
			}

			void rebalanceFromNode(node_type *n){
				if(!n) return;
				rebalanceAtNode(n);
				rebalanceFromNode(n->getParent());
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
				rebalanceAtNode(n);
			}

			void singleLeftRotate(node_type *n)
			{
				node_type *init_parent = n->getParent();
				node_type *right = n->getChildren()[1];

				node_type *right_left_subtree = right->getChildren()[0];

				if (init_parent)
				{
					int dir = init_parent->getContent() < n->getContent();
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
					int dir = init_parent->getContent() < n->getContent();
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

			node_type *getLowestChild(node_type *n)
			{
				if (!n) return 0;
				node_type *left = n->getChildren()[0];
				if (left)
					return getLowestChild(left);
				else return n;
			}

			node_type *getLargestChild(node_type *n)
			{
				if (!n) return 0;
				node_type *right = n->getChildren()[1];
				if (right)
					return getLargestChild(right);
				else return n;
			}

			node_type *searchFor(key_type const &key){
				node_type *n=tree_root;
				while (n)
				{
					if (n->getContent() == key)
						return n;
					node_type **children = n->getChildren();
					int dir = n->getContent() < key;
					n = children[dir];
				}
				return (0);
			}

			void deleteWithKey(key_type const & k){
				node_type *node = searchFor(k);
				if(!node) return;
				std::cout << "deleting " << k << std::endl;
				node_type **children = node->getChildren();
				// successor
				if(children[1])
				{
					node_type *successor = getLowestChild(children[1]);
					std::cout << "successor is " << successor->getContent() << std::endl;
					node->setContent(successor->getContent());

					if(successor == node->getChildren()[1])
					{
						successor->getParent()->setRight(successor->getChildren()[1]);
						if(successor->getChildren()[1])
							successor->getChildren()[1]->setParent(node);
					}
					else
						successor->getParent()->setLeft(0);
					rebalanceFromNode(successor);
					delete successor;

					s--;
				}
				else if(children[0])
				{
					node_type *predecessor = getLargestChild(children[0]);
					std::cout << "predecessor is " << predecessor->getContent() << std::endl;
					node->setContent(predecessor->getContent());

					if(predecessor == node->getChildren()[0])
					{
						predecessor->getParent()->setLeft(predecessor->getChildren()[0]);
						if(predecessor->getChildren()[0])
							predecessor->getChildren()[0]->setParent(node);
					}
					else
						predecessor->getParent()->setLeft(0);
					rebalanceFromNode(predecessor);
					delete predecessor;
					s--;
				}
				else
				{
					std::cout << "node to delete is leaf" << std::endl;
					if (node->getParent())
					{
						std::cout << "node has parent " << node->getParent() << std::endl;

						if(node->getContent() > node->getParent()->getContent())
							node->getParent()->setRight(0);
						else 
							node->getParent()->setLeft(0);
						node->calcBF();
						rebalanceFromNode(node->getParent());
					}
					else
					{
						std::cout << "node has no parent" << std::endl;
						tree_root = 0;
					}
					delete node;

					s--;
				}

				//predecessor
			}
// Free
			void freeSubtree(node_type *n)
			{
				node_type **children = n->getChildren();
				if (children[0])
					freeSubtree(children[0]);
				if (children[1])
					freeSubtree(children[1]);
				delete n;
			}

			void freeAll(){
				if (tree_root)
					freeSubtree(tree_root);
			}

// Utils
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
				std::cout << n->getContent() << " - ";
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