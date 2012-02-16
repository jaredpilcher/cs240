#ifndef CS240_LINKED_LIST_H
#define CS240_LINKED_LIST_H

#include <string>
#include <iostream>
using namespace std;

//! LLNode implements a doubly-linked list node
template <typename Type>
class LLNode 
{		
		friend class LinkedList<Type>;  //!< LinkedList can access private members of LLNode
	public:
	
		//!  Constructor
		LLNode(const Type & v, LLNode * p, LLNode * n) : value(v), prev(p), next(n){
		}
		
		//! Copy Constructor 
		LLNode(const LLNode & other): value(other.value),prev(other.prev),next(other.next){
		}
	
		//!  Read-only public methods for use by clients of the LinkedList class
		const Type & GetValue() const{
 			return value;
		}
	
		LLNode * GetPrevious() const{
			return prev;
		}
	
		LLNode * GetNext() const{
			return next;
		}
		
		//! Assignment operator 
		LLNode & operator=(const LLNode & other){
			if(this!=&other){
				value=other.value;
				prev=other.prev;
				next=other.next;
			}
			return *this;
		}
		
		//print node in a nice fashion
		static void print(LLNode * Node){
			if(Node!=NULL){
				cout << "Node has: " << endl;
				cout << ">>>>value: " << Node->value << endl;
				cout << ">>>>next: " << Node->next << endl;
				cout << ">>>>prev: " << Node->prev << endl;
				cout << ">>>>addr: " << Node << endl;
			}
			else{
				cout << "Node is Null" << endl;
			}
		}

	
	private:
		Type value;        //!< value stored in the node
		LLNode * prev;            //!< pointer to previous node in the list
		LLNode * next;            //!< pointer to next node in the list
};

//! LinkedList implements a doubly-linked list
template <typename Type>
class LinkedList
{
	public:
	
		//!  No-arg constructor.  Initializes an empty linked list
		LinkedList(): top(NULL), bottom(NULL), size(0){
		}
	
	
		//!  Copy constructor.  Makes a complete copy of its argument
		LinkedList(const LinkedList & other){
			copyList(other);
		}
	
	
		//!  Destructor
		~LinkedList(){
			removeNodes(top);
			top=NULL;
			bottom=NULL;
		}

	
		//! Assignment operator.  Makes a complete copy of its argument
		//! @return A reference to oneself
		LinkedList& operator =(const LinkedList & other){
			if(this==&other) return *this;
			removeNodes(top);
			top=NULL;
			bottom=NULL;
			copyList(other);
			return *this;
		}
	
	
		//!  @return true if the list is empty, or false if the list is not empty
		bool IsEmpty() const{
			return top==NULL;	
		}
	
	
		//!  Removes all values from the list
		void Clear(){
			removeNodes(top);
			top=NULL;
			bottom=NULL;
			size=0;
		}
	
	
		//!  @return the number of values in the list
		int GetSize() const{
			return size;
		}
	
	
	
		//!  @return a pointer to the first node in the list, or NULL if the list is empty
		LLNode * GetFirst()const{
			return top;
		}

		//! @returns the first node in the list, or NULL if the list is empty
		LLNode Pop(){
			LLNode temp;
			temp = GetFirst();
			Remove(temp);
			return *temp;
		}
	
	
	
		//!  @returns a pointer to the last node in the list, or NULL if the list is empty
		LLNode * GetLast()const{
			return bottom;
		}
	
	
		//!  Inserts value v into the list after node n
		//!  
		//!  @param v The new value being inserted
		//!  @param n A node that is already in the list after which the new node should 
		//!      be inserted.
		//!      If n is NULL, the new node should be inserted at the beginning of the list.
		//!
		//!  @return a pointer to the newly inserted node
		LLNode * Insert(const Type & v, LLNode * n){
			LLNode * newNode;
			if(n==NULL){
				newNode = new LLNode<Type>(v, NULL, top);
				if(top==NULL) bottom = newNode;
				if(top!=NULL) top->prev = newNode;
				top = newNode;
			}
			else{
				newNode = new LLNode<Type>(v, n, n->next);
		
				if(n->next!=NULL){
					newNode->next->prev=newNode;
				}
				else{
					bottom = newNode;
				}
				n->next = newNode;
			}
			size++;
			return newNode;
		}
	
	
		//! Searches for the first occurrence of value v that appears in the list 
		//!   after node n
		//!   
		//!  @param v The value being searched for
		//!  @param n The node in the list after which the search should begin.
		//!      If n is NULL, the list should be searched from the beginning.
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not found
		LLNode * Find(const Type & v, LLNode * n) const{
			LLNode * returnNode=top;
			if(n!=NULL){
				returnNode = n->next;
			}	
			while(returnNode!=NULL){
				if(returnNode->value == v){
					break;
				}
				returnNode=returnNode->next;
			}
			return returnNode;
		}
	
	
		//!  Removes node n from the list
		//!  
		//!  @param n The node being removed from the list
		void Remove(LLNode * n){
			if(n==NULL) return;
			if(n->prev!=NULL){
				n->prev->next = n->next;
			}
			else{
				top=n->next;
			}
			if(n->next!=NULL){
				n->next->prev = n->prev;
			}
			else{
				bottom=n->prev;
			}
			size--;
			delete n;
		}
		
		//print entire list in a nice fashion
		static void printList(const LinkedList & List){
			int i=0;
			LLNode * Node;
			Node = List.top;
			cout << "\t\n" << endl;
			cout << "List top: " << List.top << endl;
			cout << "List bottom: " << List.bottom << endl;
			cout << "List size: " << List.size << endl;
			while(Node!=NULL){
				cout << "Node " << i << " has:" << endl;
				cout << ">>>>value: " << Node->value << endl;
				cout << ">>>>next: " << Node->next << endl;
				cout << ">>>>prev: " << Node->prev << endl;
				cout << ">>>>addr: " << Node << endl;
				Node=Node->next;
				i++;
			}
			if(i==0) cout << "Nothing in List" << endl;
		}
	
	private:
	LLNode * top;
	LLNode * bottom;
	int size;

	//Remove all nodes after and including this node
	void removeNodes(LLNode * Node){
		if(Node==NULL) return;
			LLNode * next = Node->next;
			delete Node;
			if(next!=NULL){
				removeNodes(next);
			}
	}

	//Copy all nodes starting from the top and place in this linked list
	void LinkedList::copyList(const LinkedList & other){
		LLNode * hisCurNode=other.top;
		LLNode * myCurNode = NULL;
		LLNode * myPrevNode = NULL;
		while(hisCurNode != NULL){
			myCurNode = new LLNode<Type>(hisCurNode->value, myPrevNode, NULL);
		
			if(myPrevNode!=NULL){
				myPrevNode->next = myCurNode;
			}
			myPrevNode = myCurNode;
			if(top==NULL){
				top = myCurNode;
			}
			if(hisCurNode->next == NULL){
				break;
			}
			hisCurNode = hisCurNode->next;
		}
		bottom = myCurNode;
		size = other.size;
	}
	
};


#endif

