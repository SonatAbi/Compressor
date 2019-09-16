#ifndef _TREAP_BST_H_
#define _TREAP_BST_H_

#include <random>
#include "abstract_bst.h"

template<typename KeyType, typename ValueType>
class TreapBST : public AbstractBST<typename KeyType, typename ValueType> {
public:
	TreapBST();

	TreapBST(const TreapBST &x);

	TreapBST& operator=(TreapBST &x);

	void swap(TreapBST &x, TreapBST &y);

	~TreapBST();

	bool empty();
	
	ValueType search(const KeyType& key, bool& found);

	void insert(const KeyType& key, const ValueType& value);

	void remove(const KeyType& key);

private:
	std::mt19937 rndgen;

	template<typename K, typename V>
	struct Node 
	{
		K key;
		V data;
		std::mt19937::result_type priority;
		Node* parent;
		Node* childl;
		Node* childr;

		Node(const K& k, const V& d, Node* p = nullptr): key(k), data(d), parent(p), childr(nullptr), childl(nullptr)
		{
		}
	};
	typedef Node<KeyType, ValueType>* NodePtr;

	void addleaf(const KeyType & key, const ValueType & value, NodePtr &ptr);

	ValueType sHelp(const KeyType& key, bool& found, NodePtr &ptr);

	void rotateRight(NodePtr &node);

	void rotateLeft(NodePtr &node);
		
	void clear(NodePtr &ptr);

	void copy(NodePtr & a, NodePtr & b);

	NodePtr root;
};

#include "treap_bst.txx"

#endif // !_TREAP_BST_H_
