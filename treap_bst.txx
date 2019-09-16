#include "treap_bst.h"

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST() : root(nullptr) {
	std::random_device rd;
	rndgen.seed(42);
}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST(const TreapBST & x)
{
	if (x.root != nullptr) {
		NodePtr a = x.root;
		root = new Node<KeyType, ValueType>(a->key, a->data);
		root->parent = a->parent;
		root->priority = a->priority;
		NodePtr b = root;
		copy(a, b);
	}
	else {
		root = nullptr;
	}
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::copy(NodePtr & a, NodePtr & b)
{
	NodePtr c = b;
	if (a->childl != nullptr) {
		a = a->childl;
		b = b->childl;
		b = new Node<KeyType, ValueType>(a->key, a->data);
		b->priority = a->priority;
		c->childl = b;
		b->parent = c;
		copy(a, b);
	}
	if (a->childr != nullptr) {
		a = a->childr;
		b = b->childr;
		b = new Node<KeyType, ValueType>(a->key, a->data);
		b->priority = a->priority;
		c->childr = b;
		b->parent = c;
		copy(a, b);
	}
}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType> & TreapBST<KeyType, ValueType>::operator=(TreapBST<KeyType, ValueType>& x)
{
	swap(*this, x);
	return *this;
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::swap(TreapBST & x, TreapBST & y)
{
	std::swap(x.root, y.root);
}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::~TreapBST()
{
	clear(root);
}

template<typename KeyType, typename ValueType>
bool TreapBST<KeyType, ValueType>::empty()
{
	if (root == nullptr) {
		return true;
	}
	else{
		return false;
	}
}

template<typename KeyType, typename ValueType>
ValueType TreapBST<KeyType, ValueType>::search(const KeyType & key, bool & found)
{
	found = false;
	if (!empty()) {
		NodePtr a = root;
		KeyType x = a->key;
		if (a->key == key) {
			found = true;
			return a->data;
		}
		while (x != key && a != nullptr) {
			if (a->key < key) {
				a = a->childr;
				if (a != nullptr) {
					x = a->key;
				}
			}
			else if (a->key > key) {
				a = a->childl;
				if (a != nullptr) {
					x = a->key;
				}
			}
		}
		if (a != nullptr) {
			if (a->key == key) {
				found = true;
				return a->data;
			}
		}
	}
	return ValueType();
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::insert(const KeyType & key, const ValueType & value)
{
	NodePtr node;
	addleaf(key, value,node);
	if (node->parent != nullptr) 
	{
		while ((node->parent != nullptr) && (node->parent->priority < node->priority)) {
			if (node == node->parent->childl) {
				NodePtr temp = node->parent;
				rotateRight(temp);
				
			}
			else {
				NodePtr temp = node->parent;
				rotateLeft(temp);
				
			}
		}
	}
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::addleaf(const KeyType & key, const ValueType & value, NodePtr &ptr)
{
	bool check;
	search(key, check);
	if (check == true) {
		throw std::logic_error("Logic Error");
	}
	else {
		NodePtr a = root;
		KeyType x = KeyType();
		if (empty())
		{
			NodePtr node = new Node<KeyType, ValueType>(key, value);
			node->priority = rndgen();
			root = node;
			ptr = node;
		}
		else 
		{
			while (x != key && a != nullptr) 
			{
				if (a->key < key) 
				{
					if (a->childr == nullptr) {
						NodePtr node = new Node<KeyType, ValueType>(key, value);
						node->priority = rndgen();
						a->childr = node;
						node->parent = a;
						ptr = node;
						x = key;
					}
					else {
						a = a->childr;
						x = a->key;
					}
				}
				else if (a->key > key) 
				{
					if (a->childl == nullptr) {
						NodePtr node = new Node<KeyType, ValueType>(key, value);
						node->priority = rndgen();
						a->childl = node;
						node->parent = a;
						ptr = node;
						x = key;
					}
					else {
						a = a->childl;
						x = a->key;
					}
				}
			}
		}
	}
}

template<typename KeyType, typename ValueType>
ValueType TreapBST<KeyType, ValueType>::sHelp(const KeyType & key, bool & found, NodePtr & ptr)
{
	if (!empty()) {
		found = false;
		NodePtr a = root;
		KeyType x = a->key;
		if (a->key == key) {
			found = true;
			ptr = a;
			return a->data;
		}
		while (x != key && a != nullptr) {
			if (a->key < key) {
				if (a->childr != nullptr) {
					a = a->childr;
					x = a->key;
				}
				else {
					x = key;
				}
			}
			else if (a->key > key) {
				if (a->childl != nullptr) {
					a = a->childl;
					x = a->key;
				}
				else {
					x = key;
				}
			}
		}
		if (a->key == key) {
			found = true;
			ptr = a;
			return a->data;
		}
	}
	return ValueType();
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::rotateRight(NodePtr & node)
{
	NodePtr a;
	NodePtr b;

	a = node->childl;
	b = node;

	if (root == b) {
		root = a;
		root->parent = nullptr;
	}
	else {
		if (b == ((b->parent)->childl)) //node is left child
			(b->parent)->childl = a;
		else                              //node is right child
			(b->parent)->childr = a;
		a->parent = b->parent;
	}

	//move left child's right subtree to node's left subtree
	b->childl = a->childr;
	if (a->childr != nullptr)
		(a->childr)->parent = b;

	//make node the right child of the former left child
	a->childr = b;
	b->parent = a;
	node = a;
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::rotateLeft(NodePtr & node)
{
	NodePtr a;
	NodePtr b;

	a = node->childr;
	b = node;

	if (root == b) {
		root = a;
		root->parent = nullptr;
	}
	else {
		if (b == ((b->parent)->childr)) //node is right child
			(b->parent)->childr = a;
		else                              //node is left child
			(b->parent)->childl = a;
		a->parent = b->parent;
	}

	//move right child's left subtree to node's right subtree
	b->childr = a->childl;
	if (a->childl != nullptr)
		(a->childl)->parent = b;

	//make node the left child of the former right child
	a->childl = b;
	b->parent = a;
	node = a;
}



template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::clear(NodePtr & ptr)
{
	if (!empty()) {
		NodePtr n = ptr;
		if (n->childl != nullptr) {
			clear(n->childl);
		}
		if (n->childr != nullptr) {
			clear(n->childr);
		}
		delete n;
	}
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::remove(const KeyType & key)
{
	bool check = false;
	NodePtr a;
	sHelp(key, check, a);
	if (check==true) 
	{
		if ((a->childl != nullptr) && (a->childr != nullptr)) 
		{
			while ((a->childl != nullptr) && (a->childr != nullptr)) 
			{
				if (a->childl->priority < a->childr->priority) {
					rotateLeft(a);
					a = a->childl;
				}
				else if (a->childl->priority > a->childr->priority) {
					rotateRight(a);
					a = a->childr;
				}
			}
			///////////////////////////////////////////////////////////////
			if (a->childl == nullptr)//Replace with right child
			{
				if (a->parent == nullptr) {//a is root
					a->childr->parent = nullptr;
					root = a->childr;
					delete a;
				}
				else if (a->parent->childr == a) {//a is right child
					a->childr->parent = a->parent;
					a->parent->childr = a->childr;
					delete a;
				}
				else if (a->parent->childl == a) {//a is left child
					a->childr->parent = a->parent;
					a->parent->childl = a->childr;
					delete a;
				}
			}
			///////////////////////////////////////////////////////////////
			else //replace with left child
			{
				if (a->parent == nullptr) {//a is root
					a->childl->parent = nullptr;
					root = a->childl;
					delete a;
				}
				else if (a->parent->childr == a) {//a is right child
					a->childl->parent = a->parent;
					a->parent->childr = a->childl;
					delete a;
				}
				else if (a->parent->childl == a) {//ais left child
					a->childl->parent = a->parent;
					a->parent->childl = a->childl;
					delete a;
				}
			}
			//////////////////////////////////////////////////////////////
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if ((a->childl != nullptr) || (a->childr != nullptr)) //1 child
		{
			///////////////////////////////////////////////////////////////
			if (a->childl == nullptr)//Replace with right child
			{
				if (a->parent == nullptr) {//a is root
					a->childr->parent = nullptr;
					root = a->childr;
					delete a;
				}
				else if (a->parent->childr==a) {//a is right child
					a->childr->parent = a->parent;
					a->parent->childr = a->childr;
					delete a;
				}
				else if (a->parent->childl==a) {//a is left child
					a->childr->parent = a->parent;
					a->parent->childl = a->childr;
					delete a;
				}
			}
			///////////////////////////////////////////////////////////////
			else //replace with left child
			{
				if (a->parent == nullptr) {//a is root
					a->childl->parent = nullptr;
					root = a->childl;
					delete a;
				}
				else if (a->parent->childr==a) {//a is right child
					a->childl->parent = a->parent;
					a->parent->childr = a->childl;
					delete a;
				}
				else if (a->parent->childl==a) {//ais left child
					a->childl->parent = a->parent;
					a->parent->childl = a->childl;
					delete a;
				}
			}
			//////////////////////////////////////////////////////////////
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if ( (a->childl == nullptr) && (a->childr == nullptr) && (a != nullptr) )//leaf
		{
			if (a->parent == nullptr) {
				delete a;
				root = nullptr;
			}
			else {
				if (a->parent->childl == a) {
					a->parent->childl = nullptr;
				}
				else {
					a->parent->childr = nullptr;
				}
				delete a;
			}
		}
	}
	else {
		throw std::logic_error("Logic Error");
	}
}
