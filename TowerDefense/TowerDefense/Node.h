#pragma once

template <class T>
class Node
{
public: 
	Node<T>* next;

	Node();
	Node(const T* item, Node<T>* ptrNext = nullptr);
	~Node();
	T* data;
	void InsertAfter(Node<T>* p);
	Node<T>* Delete();
};