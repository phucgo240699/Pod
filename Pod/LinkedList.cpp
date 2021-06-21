#include "LinkedList.h"

void LinkedList::addHead(Component* _component)
{
	Node* node = createNode(_component);

	if (this->head == NULL)
	{
		this->head = node;
		this->tail = node;
	}
	else
	{
		node->next = this->head;
		this->head = node;
	}

	this->length++;
}

void LinkedList::addTail(Component* _component)
{
	Node* node = createNode(_component);

	if (this->head == NULL)
	{
		this->head = node;
		this->tail = node;
	}
	else
	{
		this->tail->next = node;
		this->tail = node;
	}

	this->length++;
}

bool LinkedList::removeHead()
{
	if (head == nullptr)
		return false;
	Node* temp = head;
	head = head->next;
	delete temp;

	this->length--;
	return true;
}

bool LinkedList::removeBy(Component* _component)
{
	Node* current = head;
	Node* previous;

	while (current != NULL)
	{
		if (current->component == _component) {
			Node* temp = current;
			previous->next = current->next;
			delete temp;
			return true;
		}
		previous = current;
		current = current->next;
	}

	return false;
}

bool LinkedList::removeBy(int _id)
{
	Node* current = head;
	Node* previous;

	while (current != NULL)
	{
		if (current->component->getId() == _id) {
			Node* temp = current;
			previous->next = current->next;
			delete temp;
			return true;
		}
		previous = current;
		current = current->next;
	}

	return false;
}

int LinkedList::getLength()
{
	return this->length;
}
