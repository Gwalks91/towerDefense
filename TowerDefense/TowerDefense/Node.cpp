#include "Node.h"

template <class T> 
Node<T>::Node()
{

}
	
template <class T> 
Node<T>::Node(const T* item, Node<T>* ptrNext = nullptr)
	:data(item), next(ptrNext)
{
}
	
template <class T> 
void Node<T>::InsertAfter(Node<T>* p)
{
	p->next = this.next;
	this.next = p;
}
	
template <class T> 
Node<T>* Node<T>::Delete()
{
	//Copy the data for current node that will be deleted
	Node<T>* toDelete = this;

	//Transfer the data and next node from the node after one to delete
	this->data = this->next->data;
	this->next = this->next->next;

	//Delete the old next node
	delete toDelete->next;

	return toDelete;
}
