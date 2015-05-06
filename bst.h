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

		void remove(const T&);

		bool hasValue(const T&) const;

		bool isEmpty() const;

		int getHeight() const;

		bool operator==(const BinarySearchTree<T>&) const;

		ostream& show(ostream&) const;

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
		int height;

		void addNode(Node*&, const T&, const int&);
		bool nodeHasValue(Node* const&, const T&) const;
		Node* findParentNode(Node* const&, const T&) const;
		Node* findParentPredecessor(Node* const&) const;
		void removeNode(Node*&);
		void deleteNodes(Node*&);
		void copyNodes(Node*&, Node* const&);
		bool sameNodes(Node* const&, Node* const&) const;
		string inorder(Node* const&) const;
};

#endif //BST_H_

template<class T>
ostream& operator<<(ostream& out, const BinarySearchTree<T>& a) {
	return a.show(out);
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(){
	this->root = NULL;
	this->height = 0;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& bst){
	copyNodes(this->root, bst.root);
}

template<class T>
void BinarySearchTree<T>::copyNodes(Node*& treeNode, Node* const& originalNode){
	if(originalNode != NULL){
		treeNode = new Node(originalNode->value);
		copyNodes(treeNode->left, originalNode->left);
		copyNodes(treeNode->right, originalNode->right);
	}
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree(){
	deleteNodes(this->root);
}

template<class T>
void BinarySearchTree<T>::deleteNodes(Node*& treeNode){
	if(treeNode != NULL){
		Node* leftNode = treeNode->left;
		Node* rightNode = treeNode->right;

		delete treeNode;

		deleteNodes(leftNode);
		deleteNodes(rightNode);
	}
}

template<class T>
void BinarySearchTree<T>::add(const T& value){
	if(!hasValue(value)){
		addNode(this->root, value, 0);
	}
}

template<class T>
void BinarySearchTree<T>::addNode(Node*& treeNode, const T& value, const int& height){
	if(treeNode == NULL){
		int nodeHeight = height + 1;

		treeNode = new Node(value);

		if(nodeHeight > this->height){
			this->height = nodeHeight;
		}
	}
	else{
		if(value < treeNode->value){
			addNode(treeNode->left, value, height + 1);
		}
		else{
			addNode(treeNode->right, value, height + 1);
		}
	}
}

template<class T>
void BinarySearchTree<T>::remove(const T& value){
	if(this->root->value == value){
		removeNode(this->root);
	}
	else{
		Node* parentNode = findParentNode(this->root, value);

		if(value < parentNode->value){
			removeNode(parentNode->left);
		}
		else{
			removeNode(parentNode->right);
		}
	}
}

template<class T>
void BinarySearchTree<T>::removeNode(Node*& parentNode){
	Node* targetNode = parentNode;
	if(targetNode->left == NULL && targetNode->right == NULL){
		parentNode = NULL;
		delete targetNode;
	}
	else if((targetNode->left != NULL && targetNode->right == NULL) ||
			(targetNode->left == NULL && targetNode->right != NULL)){
		if(targetNode->left != NULL){
			parentNode = targetNode->left;
			delete targetNode;
		}
		else{
			parentNode = targetNode->right;
			delete targetNode;
		}
	}
	else{
		if(targetNode->left->right == NULL){
			parentNode->value = T(targetNode->left->value);
			removeNode(targetNode->left);
		}
		else{
			targetNode = findParentPredecessor(parentNode->left);
			parentNode->value = T(targetNode->right->value);
			removeNode(targetNode->right);
		}
	}
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findParentNode(Node* const& treeNode, const T& value) const{
	if(value < treeNode->value){
		if(treeNode->left->value == value){
			return treeNode;
		}
		else{
			return findParentNode(treeNode->left, value);
		}
	}
	else{
		if(treeNode->right->value == value){
			return treeNode;
		}
		else{
			return findParentNode(treeNode->right, value);
		}
	}
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findParentPredecessor(Node* const& treeNode) const{
	if(treeNode->right->right == NULL){
		return treeNode;
	}
	else{
		return findParentPredecessor(treeNode->right);
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
bool BinarySearchTree<T>::isEmpty() const{
	return this->height == 0;
}

template<class T>
int BinarySearchTree<T>::getHeight() const{
	return this->height;
}

template<class T>
bool BinarySearchTree<T>::operator==(const BinarySearchTree<T>& bst) const{
	if(!(this->isEmpty() == bst.isEmpty() && this->getHeight() == bst.getHeight())){
		return false;
	}

	return sameNodes(this->root, bst.root);
}

template<class T>
bool BinarySearchTree<T>::sameNodes(Node* const& treeNode, Node* const& otherTreeNode) const{
	if(treeNode == NULL && otherTreeNode == NULL){
		return true;
	}
	else if(treeNode != NULL && otherTreeNode != NULL){
		if(treeNode->value == otherTreeNode->value){
			return sameNodes(treeNode->left, otherTreeNode->left) &&
				sameNodes(treeNode->right, otherTreeNode->right);
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

template<class T>
ostream& BinarySearchTree<T>::show(ostream& o) const{
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
