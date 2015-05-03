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

		bool hasValue(const T&) const;

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
		bool nodeHasValue(Node* const&, const T&) const;
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
	if(!hasValue(value)){
		addNode(this->root, value);
	}
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
bool BinarySearchTree<T>::hasValue(const T& value) const{
	return nodeHasValue(this->root, value);
}

template<class T>
bool BinarySearchTree<T>::nodeHasValue(Node* const& treeNode, const T& value) const{
	if(treeNode == NULL){
		return false;
	}
	else{
		if(treeNode->value == value){
			return true;
		}
		else{
			if(value < treeNode->value){
				return nodeHasValue(treeNode->left, value);
			}
			else{
				return nodeHasValue(treeNode->right, value);
			}
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
