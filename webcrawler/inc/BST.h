#ifndef CS240_BST_H
#define CS240_BST_H

#include <iostream>
using namespace std;

template<typename Type>
class BST;

//!  BSTNode<Type> implements a binary search tree node
template <typename Type>
class BSTNode 
{
		friend class BST<Type>;   //!< BST can access private members of BSTNode<Type>
	
	public:
		//!  Constructor
		BSTNode(const Type & v) :
		  value(v), left(NULL), right(NULL){
		}

		//! Copy Constructor
		BSTNode(const BSTNode & other) : 
		  value(other.value),left(other.left),right(other.right){
		}


		//!  Read-only public methods for use by clients of the BST class
		const Type & GetValue() const{
		  return value;
		}



		BSTNode<Type> * GetLeft()const{
		  return left;
		}


		void GetRight()const{
		  return right;
		}

		void SetLeft(BSTNode<Type> * node){
		  left = node ;
		}


		BSTNode<Type> * SetRight(BSTNode<Type> * node){
		  right = node;
		}

		//! Assignment operator 
		BSTNode<Type> & operator=(const BSTNode<Type> & other){
			if(this!=&other){
				value=other.value;
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
			cout << ">>>>value: " << value << endl;
			cout << ">>>>left: " << left << endl;
			cout << ">>>>right: " << right << endl;
			cout << ">>>>addr: " << this << endl;
		}

		BSTNode<Type>* Remove(Type search_value, BSTNode<Type> *parent) {
			if(search_value < value){
				if(left != NULL){
					return left->Remove(search_value, this);
				}
				else{
					return NULL;
				}
			}
			else if(search_value > this->value){
				if(right != NULL){
					return right->Remove(search_value, this);
				}
				else{
					return NULL;
				}
			}
			else{
				if(right != NULL && left != NULL){
					value = right->MinValue();
					return right->Remove(value, this);
				}
				if(parent->left == this){
					parent->left = (left != NULL) ? left : right;
					return this;
				}
				if(parent->right == this){
					parent->right = (left != NULL) ? left : right;
					return this;
				}
			}
			return NULL;
		}

		Type MinValue(){
			if(left==NULL) return value;
			return left->MinValue();
		}
		 
		
	
	private:
		Type value;  //!< value stored in the node
		BSTNode<Type> * left;     //!< pointer to the node's left child
		BSTNode<Type> * right;    //!< pointer to the node's right child

};

//!  BST<Type> implements a binary search tree
template <typename Type>
class BST 
{
	
	public:
		//!  No-arg constructor.  Initializes an empty BST<Type>
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
		BST<Type>& operator =(const BST<Type> & other){
			if(this!=&other){
				removeNodes(top);
				top = copyTree(other.top);
				size = other.size;
			}
			return *this;
		}

		
		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for BST<Type> clients that need to traverse the tree.)
		BSTNode<Type> * GetRoot()const{
			return top;
		}


		//!  @return true if the BST<Type> is empty, or false if the BST<Type> is not empty
		bool IsEmpty() const{
			return top == NULL;
		}


		//!  Removes all values from the BST<Type>
		void Clear(){
			removeNodes(top);
			size = 0;
			top=NULL;
		}

		

		//!  @return the number of values in the BST<Type>
		int GetSize() const{
			return size;
		}


		//!  Inserts value v into the BST<Type>
		//!  
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		BSTNode<Type> * Insert(const Type & v){	
			if(Find(v)) return NULL;
			BSTNode<Type> * Node;
			Node = new BSTNode<Type>(v);
			insertNode(top,Node);
			size++;
			return Node;
		}

		


		//!  Searches the tree for value v
		//!  
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		BSTNode<Type> * Find(const Type & v) const{
			return findNode(top, v);
		}

		

		void print() const{
			printTree(top);
		}

		//!  Removes value v from the tree
		//!  
		//!  @param v The value being removed from the tree
		//!
		//!  @return true if v was removed from the tree, or false if v was not in the tree
		bool Remove(const Type & v){
			if(top==NULL) return false;
			if(top->GetValue()==v){
				BSTNode<Type> aux_top(0);
				aux_top.SetLeft(top);
				BSTNode<Type> * removed_node = top->Remove(v,&aux_top);
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
				BSTNode<Type> * removed_node = top->Remove(v,NULL);
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

		//!  Pops next value from the tree
		//!
		//!  @return pointer to next Type on tree
		//!  returns NULL if nothing on tree
		Type Pop(){
			if(top==NULL) return NULL;
			Type min_value = top->MinValue();
			Remove(min_value);
			return min_value;
		}

	
	private:
		BSTNode<Type> * top;
		int size;

		void insertNode(BSTNode<Type>* &prevNode, BSTNode<Type> * inNode){
			if(prevNode==NULL){
				prevNode=inNode;
			}
			else if(prevNode->value > inNode->value){
				insertNode(prevNode->left, inNode);
			}
			else{
				insertNode(prevNode->right, inNode);
			}
		}

		void printTree(BSTNode<Type>* Node) const{
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

		BSTNode<Type> * findNode(BSTNode<Type> * Node, const Type & v) const{
			if(Node==NULL){
				return NULL;
			}
			else if(Node->value < v){
				return findNode(Node->right,v);
			}
			else if(Node->value > v){
				return findNode(Node->left,v);
			}
			else{
				return Node;
			}

	
		}

		void removeNodes(BSTNode<Type> * Node){
			if(Node==NULL) return;
			removeNodes(Node->left);
			removeNodes(Node->right);
			delete Node;
		}

		BSTNode<Type> * copyTree(BSTNode<Type>* otherNode){
			if(otherNode==NULL){
				return NULL;
			}
			BSTNode<Type>* Node = new BSTNode<Type>(otherNode->value);
			Node->left = copyTree(otherNode->left);
			Node->right = copyTree(otherNode->right);
			return Node;	
		}
		
 

};


#endif
