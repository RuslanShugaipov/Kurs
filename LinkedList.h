#pragma once
#include <string>
using namespace std;

class LinkedList
{
public:
	//Constructor and Destructor
	LinkedList();
	~LinkedList();
	//Methods for working with Linked List
	void push_back(string newEl);
	void push_front(string newEl);
	void pop_back();
	void pop_front();
	void insert(string newEl, size_t index);
	string at(size_t index) const;
	void remove(size_t index);
	size_t get_size();
	void print_to_console();
	void clear();
	void set(size_t index, string newData);
	bool isEmpty();
	size_t find_first(LinkedList *list);

	bool isPrinted();

private:
	class Node
	{
		public:
			Node(string data, Node* next = nullptr, Node* prev =nullptr)
			{
				this->data = data;
				this->next = next;
				this->prev = prev;
			}
			string data;
			Node* next;
			Node* prev;
	};
	
	Node* head;
	Node* tail;
	size_t size;
};