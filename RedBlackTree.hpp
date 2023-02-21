#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP


#include <iostream>
#include <queue>
#include <iomanip>

template<class KeyT, class ValueT, class Compare = std::less<KeyT>, class Allocator = std::allocator<std::pair<KeyT, ValueT> > >
class RedBlackTree
{
public:

private:

	enum Colors
	{
		BLACK = 0,
		RED = 1
	};

	class Node
	{
	public:
		KeyT key;
		ValueT value;
		bool color;
		Node *left, *right, *parent;
	};

	typedef typename std::allocator<Node> _Allocator;

//----PRIVATE ATTRIBUTES---
	Node *root;
	Node *NTREE;
	_Allocator alloc;
	bool	way;
	size_t	size;

//----PRIVATE FUNCTIONS---
	void rotLeft(Node *node);
	void rotRight(Node *node);

	Node* searchNode(const KeyT& to_find)
	{
		Node *ret = root;

		while (ret != NTREE)
		{
			if(ret->key == to_find)
				return (ret);
			if(Compare()(ret->key , to_find))
				ret = ret->right;
			else
				ret = ret->left;
		}
		return (NTREE);
	}

	void	insertFix(Node *node);
	void	deleteFix(Node *node);

	bool deleteNodeFunc(Node *node, const KeyT& key);

	Node * minNode(Node * node)
	{
		while (node->left != NTREE)
			node = node->left;
		return node;
	}

public:
	RedBlackTree();
	void	insert(const KeyT& key, const ValueT& val);
	bool	erase(const KeyT& key);



	//iterator++
	Node*	getBigger(Node *node)
	{
		if (way)
		{
			if (node->right != NTREE)
				return (node->right);
			Node *ret = node;
			if (ret->parent)
			{
				while (ret->parent != NULL && ret->key <= node->key)
				{
					ret = ret->parent;
				}
				if (ret->key > node->key)
					return (ret);
			}
		}
		else
		{
			if (node->left != NTREE)
				return (node->left);
			if (node->parent != NTREE)
				return (node->parent);
		}
		return (NULL);
	}

	//iterator--
	Node *getLesser(Node *node)
	{
		if (way)
		{
			if (node->left != NTREE)
				return (node->left);
			if (node->parent)
			{
				if (node->parent->right == node)
					return (node->parent);
			}
		}
		else
		{
			if (node->right != NTREE)
				return (node->right);
			if(node->parent)
			{
				if (node->parent->left == node)
					return (node->parent);
			}
		}
		return (NULL);
	}

	Node*	search(const KeyT& key)
	{
		return (searchNode(key));
	}

	size_t	getSize() const { return (this->size); }
	size_t	maxSize() const	{ return (alloc.max_size()); }



	void print (Node* node, int indent) const
	{
		if 	(node != NTREE)
		{
			print(node->right, indent + 4);
			if (indent)
				std::cout << std::setw(indent) << ' ';
			if 	(node->color == BLACK) {
				std::cout <<	node->key << ":" <<	node->value << " (BLACK)" << std::endl;
			}
			else
			{
				std::cout <<	node->key << ":" <<	node->value << " (RED)" << std::endl;
			}
			print(node->left, indent + 4);
		}
	}

	void	print() const
	{
		print(root, 0);
	}
};
// -------------------------------/ PRIVATE FUNCTIONS  /-------------------------------------

template<class KeyT, class ValueT, class Compare, class Allocator >
void	RedBlackTree<KeyT, ValueT, Compare, Allocator>::rotLeft(Node *node)
{
	Node * rightN = node->right;
	node->right = rightN->left;

	if (rightN->left != NTREE)
		rightN->left->parent = node;

	rightN->parent = node->parent;

	if(!node->parent)
		this->root = rightN;
	else if(node == node->parent->left)
		node->parent->left = rightN;
	else
		node->parent->right = rightN;
	rightN->left = node;
	node->parent = rightN;
}

template<class KeyT, class ValueT, class Compare, class Allocator>
void	RedBlackTree<KeyT, ValueT, Compare, Allocator>::rotRight(Node *node)
{
	Node * leftN = node->left;
	node->left = leftN->right;

	if (leftN->right != NTREE)
		leftN->right->parent = node;

	leftN->parent = node->parent;
	if (!node->parent)
		this->root = leftN;
	else if(node == node->parent->right)
		node->parent->right = leftN;
	else
		node->parent->left = leftN;
	leftN->right = node;
	node->parent = leftN;
}

template<class KeyT, class ValueT, class Compare, class Allocator >
void RedBlackTree<KeyT, ValueT, Compare, Allocator>::insertFix(Node * node)
{
	Node * tempNode;
	//if node parents color equals to red, while block runs
	while (node->parent->color != BLACK)
	{
		//if node parents not equals to node grandparents right child
		if (node->parent != node->parent->parent->right)
		{
			//tempNode equals to nodes uncle
			tempNode = node->parent->parent->right;
			//if nodes uncles color equals to red, its color become black, nodes parent color become black
			// and grandparents color become red
			if (tempNode->color == RED)
			{

				tempNode->color = BLACK;
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else //if nodes uncles color equals to black
			{
				if (node == node->parent->right)
				{
					node = node->parent;
					//rotate left node
					rotLeft(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				//rotate right node
				rotRight(node->parent->parent);
			}
		}
		else
		{
			//tempNode equals to nodes uncle
			tempNode = node->parent->parent->left;
			//if nodes uncles color equals to black
			if (tempNode->color == BLACK)
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					rotRight(node);
				}
				// case 3.2.1
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotLeft(node->parent->parent);

			}
			else //if nodes uncles color equals to red
			{
				tempNode->color = BLACK;
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
		}
		if (node == root)
			break;
	}
	root->color = BLACK;
}


template<class KeyT, class ValueT, class Compare, class Allocator >
bool RedBlackTree<KeyT, ValueT, Compare, Allocator>::deleteNodeFunc(Node *node, const KeyT& key)
{
	Node * node1;
	Node * node2;
	Node * nil;

	//if nil equals to NTREE, node is not found
	if ((nil = searchNode(key)) == NTREE)
		return (0);

	node2 = nil;
	bool YMainColor = node2->color;

	////case-1: if nils left child equals to NTREE
	if (nil->left == NTREE)
	{
		node1 = nil->right;
		//transplant processes
		if(nil->parent == NULL)
			root = nil->right;
		else if(nil == nil->parent->left)
			nil->parent->left = nil->right;
		else
			nil->parent->right = nil->right;
		nil->right->parent = nil->parent;
	}
	else if(nil->right == NTREE) //case-2: if nils right child equals to NTREE
	{
		node1 = nil->left;
		//transplant processes
		if(nil->parent == NULL)
			root = nil->left;
		else if(nil == nil->parent->left)
			nil->parent->left = nil->left;
		else
			nil->parent->right = nil->left;
		nil->left->parent = nil->parent;
	}
	else //case-3
	{
		node2 = minNode(nil->right);
		YMainColor = node2->color;
		node1 = node2->right;
		if(node2->parent == nil)
			node1->parent = node2;
		else
		{
			//transplant processes
			if(node2->parent == NULL)
				root = node2->right;
			else if(node2 == node2->parent->left)
				node2->parent->left = node2->right;
			else
				node2->parent->right = node2->right;

			node2->right->parent = node2->parent;
			node2->right = nil->right;
			node2->right->parent = node2;
		}
		//transplant processes
		if(nil->parent == NULL)
			root = node2;
		else if(nil == nil->parent->left)
			nil->parent->left = node2;
		else
			nil->parent->right = node2;
		node2->parent = nil->parent;
		node2->left = nil->left;
		node2->left->parent = node2;
		node2->color = nil->color;
	}
	//delete nil node
	alloc.destroy(nil);
	alloc.deallocate(nil, 1);
	size--;
	//if y nodes first color is black, then deleteFix function call
	if (YMainColor == BLACK)
		deleteFix(node1);
	return (1);
}

template<class KeyT, class ValueT, class Compare, class Allocator>
void	RedBlackTree<KeyT, ValueT, Compare, Allocator>::deleteFix(Node *node)
{
	Node * tempN;

	while (node->color == BLACK && node != root )
	{
		//if node is left child
		if (node == node->parent->left)
		{
			//temp node is sibling
			if(node->parent->right)
				tempN = node->parent->right;
			if(tempN)
			{
				//case-1
				//if sibling is red
				if (tempN->color == RED)
				{

					tempN->color = BLACK;
					node->parent->color = RED;
					rotLeft(node->parent);
					tempN = node->parent->right;
				}
				//case-2
				//if sibling childs are black, its color become red
				if (tempN->left->color == BLACK && tempN->right->color == BLACK)
				{
					tempN->color = RED;
					node = node->parent;
				}
				else //case-3
				{
					//if only siblings right child is black
					if(tempN->right->color == BLACK)
					{
						tempN->left->color = BLACK;
						tempN->color = RED;
						rotRight(tempN);
						tempN = node->parent->right;
					}
					//case-4
					tempN->color = node->parent->color;
					node->parent->color = BLACK;
					tempN->right->color = BLACK;

					rotLeft(node->parent);
					node = root;
				}
			}

		}
		else //if node is right child
		{
			if(node->parent->left)
				tempN = node->parent->left;
			if(tempN){
				//case-1
				//if sibling is red
				if(tempN->color == RED)
				{
					tempN->color = BLACK;
					node->parent->color = RED;

					rotRight(node->parent);
					tempN = node->parent->left;
				}
				//case-2
				//if sibling childs are black, its color become red
				if (tempN->left->color == BLACK && tempN->right->color == BLACK)
				{
					tempN->color = RED;
					node = node->parent;
				}
				else //case-3
				{
					//if sibling left childs is black
					if(tempN->left->color == BLACK)
					{
						tempN->right->color = BLACK;
						tempN->color = RED;

						rotLeft(tempN);
						tempN = node->parent->left;
					}
					//case-4
					tempN->color = node->parent->color;
					node->parent->color = BLACK;
					tempN->left->color = BLACK;

					rotRight(node->parent);
					node = root;
				}
			}
		}
	}
	node->color = BLACK;
}

// -------------------------------/ PUBLIC FUNCTIONS  /-------------------------------------

//DEFAULT CONSTRUCTOR
template<class KeyT, class ValueT, class Compare, class Allocator >
RedBlackTree<KeyT, ValueT, Compare, Allocator>::RedBlackTree()
{
	NTREE = alloc.allocate(1);
	alloc.construct(NTREE);
	NTREE->color = BLACK;
	root = NTREE;
	way = Compare()(1,2) ? 1 : 0;
	size = 0;
}


template<class KeyT, class ValueT, class Compare, class Allocator >
void RedBlackTree<KeyT, ValueT, Compare, Allocator>::insert(const KeyT& key, const ValueT& val)
{
	// Ordinary Binary Search Insertion
	Node * node = alloc.allocate(1);
	alloc.construct(node);
	node->parent = NULL;
	node->key = key;
	node->value = val;
	node->left = NTREE;
	node->right = NTREE;
	node->color = RED; // new node must be red

	Node * y = NULL;
	//firstly tempRoot equals to root
	Node * tempRoot = this->root;

	//find appropriate place for new node
	while (tempRoot != NTREE) {
		y = tempRoot;
		if (Compare()(node->key, tempRoot->key))
			tempRoot = tempRoot->left;
		else
			tempRoot = tempRoot->right;
	}

	// y is parent of new node
	node->parent = y;
	// if parents of new node is null, the node will be root and its color become black, then return
	if (y == NULL)
	{
		root = node;
		node->color = BLACK;
		return;
	}
	else if (Compare()(node->key, y->key)) //new nodes data smaller than its parents data, the new node become parents left child
		y->left = node;
	else //new nodes data smaller than its parents data, the new node become parents right child
		y->right = node;

	if (node->parent->parent == NULL) // if the new node parents of parents is null, then return
		return;

	// call insertFix function
	insertFix(node);
}

template<class KeyT, class ValueT, class Compare, class Allocator >
bool	RedBlackTree<KeyT, ValueT, Compare, Allocator>::erase(const KeyT& key)
{
	if (deleteNodeFunc(this->root, key))
		return (1);
	return (0);
}

#endif