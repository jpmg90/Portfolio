/*
 * Node.h 
 */

#ifndef NODE_H_
#define NODE_H_

#include "StandardIncludes.h"

template<class T>
class Node
{
public:
	Node(T data) : data(data), next(NULL){}
	virtual ~Node();
	T& getDataReference();
	T getData();
	void setData(T);
	Node* getNext();
	void setNext(Node*);
private:
	Node(const Node& toBeCopied);
	Node& operator=(const Node& rhs);
	T data;
	Node<T>* next;
};

// Constructor and Deconstructor
template<class T>
Node<T>::Node(const Node& toBeCoppied)
{
	setData(toBeCoppied.getData());
	setNext(toBeCoppied.getNext());
}

template<class T>
Node<T>::~Node<T>()
{
}

// Getters
template<class T>
T& Node<T>::getDataReference()
{
	return data;
}

template<class T>
T Node<T>::getData()
{
	return data;
}

template<class T>
Node<T>* Node<T>::getNext()
{
	return next;
}
// Setters
template<class T>
void Node<T>::setData(T tData)
{
	data = tData;
}

template<class T>
void Node<T>::setNext(Node<T>* node)
{
	next = node;
}


#endif /* NODE_H_ */
