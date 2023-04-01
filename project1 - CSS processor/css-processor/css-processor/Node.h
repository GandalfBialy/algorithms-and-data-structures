#pragma once


#include <iostream>


#include "String.h"


template <typename T>
class Node 
{
public:
	T data;
	Node<T>* next;
	//Node<T>* previous;

	Node(T data) {
		this->data = data;
		next = nullptr;
	}
};
