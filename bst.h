#ifndef BST_H_
#define BST_H_

#include <iostream>
using namespace std;

template<typename T>
class BinarySearchTree{

	public:

		BinarySearchTree();

		BinarySearchTree(const BinarySearchTree<T>&);

		~BinarySearchTree();

		void add(const T&);

		bool operator==(const BinarySearchTree<T>&) const;

		ostream& mostrarBinarySearchTree(ostream&) const;

	private:

		struct Node{
			T value;
			Node* left;
			Node* right;
			Node(){};
			Node(const T& value){
				this->value = T(value);
				this->left = NULL;
				this->right = NULL;
			};
		};

		Node* root;

		void addNode(Node*&, const T&);
		string inorder(Node* const&) const;
};

#endif //BST_H_

template<class T>
ostream& operator<<(ostream& out, const BinarySearchTree<T>& a) {
	return a.mostrarBinarySearchTree(out);
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(){
	this->root = NULL;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& bst){
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree(){
}

template<class T>
void BinarySearchTree<T>::add(const T& value){
	addNode(this->root, value);
}

template<class T>
void BinarySearchTree<T>::addNode(Node*& treeNode, const T& value){
	if(treeNode == NULL){
		treeNode = new Node(value);
	}
	else{
		if(value < treeNode->value){
			addNode(treeNode->left, value);
		}
		else{
			addNode(treeNode->right, value);
		}
	}
}

template<class T>
bool BinarySearchTree<T>::operator==(const BinarySearchTree<T>& bst) const{
	return false;
}

template<class T>
ostream& BinarySearchTree<T>::mostrarBinarySearchTree(ostream& o) const{
	o << "[";
	o << inorder(this->root);
	o << "]";
	return o;
}

template<class T>
string BinarySearchTree<T>::inorder(Node* const& treeNode) const{
	ostringstream o;
	if(treeNode != NULL){
		if(treeNode->left != NULL){
			o << inorder(treeNode->left) << ", ";
		}

		o << treeNode->value;

		if(treeNode->right != NULL){
			o << ", " << inorder(treeNode->right);
		}
	}
	return o.str();
}
