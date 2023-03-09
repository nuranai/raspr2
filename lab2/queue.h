#pragma once
#include <iostream>
#include <mutex>

template <class T>
struct Node {
public:
	T key;
	Node* next, * prev;
};

template <class T>
class Queue
{
public:
	Queue();
	~Queue();
	void Push(T value);
	T Pop();
	bool isEmpty();
	int getLength() {
		return _length;
	}

private:
	int _length;
	Node<T>* _head, * _tail;
	std::mutex _mutex;
	std::mutex _popMutex;
	std::mutex _pushMutex;
};

template <class T> Queue<T>::Queue() {
	_head = nullptr;
	_tail = nullptr;
	_length = 0;
}

template <class T> Queue<T>::~Queue() {
	Node<T>* temp = _head;
	while (temp) {
		Node<T>* toDel = temp;
		temp = temp->next;
		delete toDel;
	}
}

template <class T> void Queue<T>::Push(T value) {
	Node<T>* toAdd = new Node<T>;/* = {value, nullptr, _tail}*/;
	toAdd->prev = _tail;
	toAdd->key = value;
	toAdd->next = nullptr;

	std::lock_guard<std::mutex> lock(_mutex);
	
	if (_tail) {
		_tail->next = toAdd;
	}
	if (!_head) {
		_head = toAdd;
	}
	_tail = toAdd;
	_length++;
}

template <class T> T Queue<T>::Pop() {

	std::lock_guard<std::mutex> lock(_mutex);
	T value = _head->key;
	if (_head->next)
		_head->next->prev = nullptr;
	Node<T>* toDel = _head;
	_head = _head->next;
	toDel->next = nullptr;
	_length--;

	delete toDel;
	return value;
}

template <class T> bool Queue<T>::isEmpty() {
	return _length == 0;
}
