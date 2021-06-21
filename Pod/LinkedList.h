#include "Component.h"

struct Node
{
	Component* component;
	Node* next;
};

Node* createNode(Component* _component)
{
	Node* node = new Node;
	node->component = _component;
	node->next = NULL;
	return node;
}

class LinkedList
{
private:
	Node* head;
	Node* tail;
	int length;

public:
	void addHead(Component* _component);
	void addTail(Component* _component);
	bool removeHead();
	bool removeBy(Component* _component);
	bool removeBy(int _id);
	int getLength();
};