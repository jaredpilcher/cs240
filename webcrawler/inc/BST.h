#ifndef CS240_BST_H
#define CS240_BST_H

#include <iostream>
using namespace std;

template<typename Type, typename Type2>
class BST;

//!  BSTNode<Type, Type2> implements a binary search tree node
template <typename Type, typename Type2>
class BSTNode {
		friend class BST<Type, Type2>;   //!< BST can access private members of BSTNode<Type, Type2>
	
	public:
		//!  Constructor
		BSTNode(const Type & k, const Type2 & v) :
		  key(k), value(v), left(NULL), right(NULL){
		}


		//! Copy Constructor (Type2 must have a deep copy constructor)
		BSTNode(const BSTNode & other) : 
		  key(other.key),value(other.value),left(other.left),right(other.right){
		}


		//!  Read-only public methods for use by clients of the BST class
		const Type & GetKey() const{
		  return key;
		}

		//! Returns actual object to be changed
		Type2 & GetValue(){
			return value;
		}



		BSTNode<Type, Type2> * GetLeft()const{
		  return left;
		}


		void GetRight()const{
		  return right;
		}

		void SetLeft(BSTNode<Type, Type2> * node){
		  left = node ;
		}


		BSTNode<Type, Type2> * SetRight(BSTNode<Type, Type2> * node){
		  right = node;
		}

		//! Assignment operator 
		BSTNode<Type, Type2> & operator=(const BSTNode<Type, Type2> & other){
			if(this!=&other){
				key=other.key;
				left=other.left;
				right=other.right;
			}

			return *this;
		}

		void print(){
			if(this==NULL){
				cout << "Node is empty" << endl;
				return;
			}
			cout << "Node has: " << endl;
			cout << ">>>>key: " << key << endl;
			cout << ">>>>value: " << value << endl;
			cout << ">>>>left: " << left << endl;
			cout << ">>>>right: " << right << endl;
			cout << ">>>>addr: " << this << endl;
		}

		BSTNode<Type, Type2>* Remove(Type search_key, BSTNode<Type, Type2> *parent) {
			if(search_key < key){
				if(left != NULL){
					return left->Remove(search_key, this);
				}
				else{
					return NULL;
				}
			}
			else if(search_key > this->key){
				if(right != NULL){
					return right->Remove(search_key, this);
				}
				else{
					return NULL;
				}
			}
			else{
				if(right != NULL && left != NULL){
					key = right->MinKey();
					value = right->MinValue();
					return right->Remove(key, this);
				}else if(parent->left == this){
					parent->left = (left != NULL) ? left : right;
					return this;
				}else if(parent->right == this){
					parent->right = (left != NULL) ? left : right;
					return this;
				}
			}
			return NULL;
		}

		Type MinKey(){
			if(left==NULL) return key;
			return left->MinKey();
		}

		Type2 MinValue(){
			if(left==NULL) return value;
			return left->MinValue();
		}
		 
		
	
	private:
		Type key;  //!< key stored in the node
		Type2 value;
		BSTNode<Type, Type2> * left;     //!< pointer to the node's left child
		BSTNode<Type, Type2> * right;    //!< pointer to the node's right child

};

//!  BSTNode<Type, Type2> implements a binary search tree
template <typename Type, typename Type2>
class BST {
	
	public:
		//!  No-arg constructor.  Initializes an empty BSTNode<Type, Type2>
		BST(): top(NULL), size(0){
		}


		//!  Copy constructor.  Makes a complete copy of its argument
		BST(const BST & other){
			top = copyTree(other.top);
			size=other.size;
		}


		//!  Destructor
		~BST(){
			Clear();
		}


		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		BSTNode<Type, Type2>& operator =(const BSTNode<Type, Type2> & other){
			if(this!=&other){
				removeNodes(top);
				top = copyTree(other.top);
				size = other.size;
			}
			return *this;
		}

		
		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for BSTNode<Type, Type2> clients that need to traverse the tree.)
		BSTNode<Type, Type2> * GetRoot()const{
			return top;
		}


		//!  @return true if the BSTNode<Type, Type2> is empty, 
		//!  or false if the BSTNode<Type, Type2> is not empty
		bool IsEmpty() const{
			return top == NULL;
		}


		//!  Removes all keys from the BSTNode<Type, Type2>
		void Clear(){
			removeNodes(top);
			size = 0;
			top=NULL;
		}

		

		//!  @return the number of keys in the BSTNode<Type, Type2>
		int GetSize() const{
			return size;
		}


		//!  Inserts key k into the BSTNode<Type, Type2>
		//!  
		//!  @param k The new key being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if k was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		BSTNode<Type, Type2> * Insert(const Type & k, const Type2 & v){	
			if(Find(k)!=NULL) return NULL;
			BSTNode<Type, Type2> * Node;
			Node = new BSTNode<Type, Type2>(k,v);
			insertNode(top,Node);
			size++;
			return Node;
		}

		


		//!  Searches the tree for key k
		//!  
		//!  @param k The new key being searched for
		//!
		//!  @return a pointer to the node containing k, or NULL if k is not in the tree
		BSTNode<Type, Type2> * Find(const Type & k) const{
			return findNode(top, k);
		}

		

		void print() const{
			printTree(top);
		}

		//!  Removes key k from the tree
		//!  
		//!  @param k The key being removed from the tree
		//!
		//!  @return true if k was removed from the tree, or false if k was not in the tree
		bool Remove(const Type & k){
			if(top==NULL) return false;
			if(top->GetKey()==k){
				BSTNode<Type, Type2> aux_top(top->GetKey(), top->GetValue());
				aux_top.SetLeft(top);
				BSTNode<Type, Type2> * removed_node = top->Remove(k,&aux_top);
				top=aux_top.GetLeft();
				if(removed_node != NULL){
					delete removed_node;
					--size;
					return true;
				}
				else{
					return false;
				}		
			}
			else{
				BSTNode<Type, Type2> * removed_node = top->Remove(k,NULL);
				if(removed_node != NULL){
					delete removed_node;
					--size;
					return true;
				}
				else{
					return false;
				}
		
			}

		}


		

		//! @returns the smallest key in the tree
		//! WARNING: Does not check to see that top is not NULL, must check first!!!
		Type PopKey(){
			BSTNode<Type,Type2> * node = getSoloNode(top,NULL);
			Type key = node->key;
			delete node;
			return key;
		}

		Type2 PopValue(){
			return Pop();
		}

		Type2 Pop(){
			BSTNode<Type,Type2> * node = getSoloNode(top,NULL);
			cout << "here3" << endl;
			Type2 value = node->value;
			delete node;
			return value;
		}

		Type2 PopVandK(Type & key){
			BSTNode<Type,Type2> * node = getSoloNode(top,NULL);
			Type2 value = node->value;
			key = node->key;
			delete node;
			return value;
		}

		//! @returns the smallest key in the list, or NULL if the list is empty
		//! used for pointers stored in the keys of the nodes
		Type PopPtr(){
			if(top==NULL) return NULL;
			return PopKey();
		}

	
	private:
		BSTNode<Type, Type2> * top;
		int size;

		void insertNode(BSTNode<Type, Type2>* &prevNode, BSTNode<Type, Type2> * inNode){
			if(prevNode==NULL){
				prevNode=inNode;
			}
			else if(prevNode->key > inNode->key){
				insertNode(prevNode->left, inNode);
			}
			else{
				insertNode(prevNode->right, inNode);
			}
		}

		void printTree(BSTNode<Type, Type2>* Node) const{
			if(Node==NULL){
				cout << "Tree is Empty" << endl;
				return;
			}
			if(Node->left!=NULL){
				printTree(Node->left);
			}
			Node->print();
			if(Node->right!=NULL){
				printTree(Node->right);
			}
		}

		BSTNode<Type, Type2> * findNode(BSTNode<Type, Type2> * Node, const Type & k) const{
			if(Node==NULL){
				return NULL;
			}
			else if(Node->key < k){
				return findNode(Node->right,k);
			}
			else if(Node->key > k){
				return findNode(Node->left,k);
			}
			else{
				return Node;
			}

	
		}

		void removeNodes(BSTNode<Type, Type2> * Node){
			if(Node==NULL) return;
			removeNodes(Node->left);
			removeNodes(Node->right);
			delete Node;
		}

		BSTNode<Type, Type2> * copyTree(BSTNode<Type, Type2>* otherNode){
			if(otherNode==NULL){
				return NULL;
			}
			BSTNode<Type, Type2>* Node = new BSTNode<Type, Type2>(otherNode->key);
			Node->left = copyTree(otherNode->left);
			Node->right = copyTree(otherNode->right);
			return Node;	
		}

		BSTNode<Type, Type2> * getSoloNode(BSTNode<Type,Type2>*current,BSTNode<Type,Type2>*parent){
			cout << "in getSoloNode()" << endl;
			cout << current << endl;
			if(current->left!=NULL){// && current->left!=(BSTNode<Type,Type2>*)0xffffffff){
				//cout << current->left << endl;
				return getSoloNode(current->left,current);
			}
			if(current->right!=NULL){// && current->right!=(BSTNode<Type,Type2>*)0xffffffff){
				cout << current->right << endl;
				return getSoloNode(current->right,current);
			}
			if(parent==NULL){
				cout << "parent is null" << endl;
				return current;
			}
			if(parent->left == current){
				parent->left = NULL;
			}
			if(parent->right == current){
				parent->right = NULL;
			}
			return current;
			
		}
		
 

};


#endif
