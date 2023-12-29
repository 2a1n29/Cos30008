#pragma once
#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"
#include <stdexcept>
template<typename T>
class List
{
private:
	// auxiliary definition to simplify node usage
	using Node = DoublyLinkedList<T>;
	Node* fRoot; // the first element in the list
	size_t fCount; // number of elements in the list
public:
	// auxiliary definition to simplify iterator usage
	using Iterator = DoublyLinkedListIterator<T>;
	List() : fRoot(nullptr), fCount(0) {}; // default constructor
	List(const List& aOtherList) : fRoot(nullptr), fCount(0) { *this = aOtherList; }; // copy constructor
	List& operator=(const List& aOtherList)
	{
		if (&aOtherList != this) {
			this->~List();
			if (aOtherList.fRoot != nullptr) {
				fCount = 0;
				fRoot = nullptr;
				for (auto& a : aOtherList)
				{
					push_back(a);
				}
			}
			else {
				fRoot = nullptr;
			}
		}
		else {
			return *this;
		}
		return *this;
	}; // assignment operator
	~List() 
	{
		while (fRoot != nullptr)
		{
			if (fRoot != &fRoot->getPrevious())
			{
				Node* nNode = const_cast<Node*>(&fRoot->getPrevious());
				nNode->isolate();
				delete nNode;
			}
			else
			{
				delete fRoot;
				break;
			}
		}
	}; // destructor - frees all nodes
	bool empty() const 
	{
		if (fRoot == nullptr) { return true; }
		else { return false; }
	}; // Is list empty?
	size_t size() const { return fCount; }; // list size
	void push_front(const T& aElement) 
	{
		if (empty()) 
		{
			fRoot = new Node(aElement);
			fCount ++;
		}
		else 
		{
			Node* fPushedfront = new Node(aElement);
			fRoot->push_front(*fPushedfront);
			fRoot = fPushedfront;
			fCount ++;
		}
	}; // adds aElement at front
	void push_back(const T& aElement) 
	{
		if (empty()) 
		{
			fRoot = new Node(aElement);
			fCount ++;
		}
		else
		{
			Node* fPushedback = new Node(aElement);
			Node* fPreviousnode = const_cast<Node*>(&fRoot->getPrevious());
			fPreviousnode->push_back(*fPushedback);
			fCount ++;
		}
	}; // adds aElement at back
	void remove(const T& aElement) 
	{
		Node* nNode = fRoot;
		while (nNode != nullptr)
		{
			if (**nNode == aElement)
			{
				break;
			}
			if (nNode != &fRoot->getPrevious())
			{
				nNode = const_cast<Node*>(&nNode->getNext());
			}
			else
			{
				nNode = nullptr;
			}
		}
		if (nNode != nullptr)
		{
			if (fCount == 1)
			{
				fRoot = nullptr;
			}
			else
			{
				if (nNode == fRoot)
				{
					fRoot = const_cast<Node*>(&fRoot->getNext());
				}
			}
			nNode->isolate();
			delete nNode;
			fCount --;
		}
	}; // remove first match from list
	const T& operator[](size_t aIndex) const 
	{
		if (aIndex > size() - 1 || aIndex < 0)
		{
			throw std::out_of_range("Index out of bounds.");
		}
		else 
		{
			Iterator indexer = Iterator(fRoot);
			indexer.begin();
			for (int i = 0; i < aIndex; ++i) {
				indexer ++;
			}
			return *indexer;
		}
	}; // list indexer
	Iterator begin() const { return Iterator(fRoot).begin(); }; // return a forward iterator
	Iterator end() const { return Iterator(fRoot).end(); }; // return a forward end iterator
	Iterator rbegin() const { return Iterator(fRoot).rbegin(); }; // return a backwards iterator
	Iterator rend() const { return Iterator(fRoot).rend(); }; // return a backwards end iterator
	// move features
	List(List&& aOtherList) : fRoot(nullptr), fCount(0) { *this = std::move(aOtherList); }; // move constructor
	List& operator=(List&& aOtherList) {
		if (&aOtherList != this) {
			this->~List();
			if (aOtherList.fRoot != nullptr) {
				fRoot = aOtherList.fRoot;
				fCount = aOtherList.fCount;
				aOtherList.fCount = 0;
				aOtherList.fRoot = nullptr;
			}
			else {
				fRoot = nullptr;
			}
		}
		else {
			return *this;
		}
		return *this;
	}; // move assignment operator
	void push_front(T&& aElement) {
		if (empty())
		{
			fRoot = new Node(std::move(aElement));
			fCount++;
		}
		else
		{
			Node* fPushedfront = new Node(std::move(aElement));
			fRoot->push_front(*fPushedfront);
			fRoot = fPushedfront;
			fCount++;
		}
	}; // adds aElement at front
	void push_back(T&& aElement) {
		if (empty())
		{
			fRoot = new Node(aElement);
			fCount ++;
		}
		else
		{
			Node* fPushedback = new Node(aElement);
			Node* fPreviousnode = const_cast<Node*>(&fRoot->getPrevious());
			fPreviousnode->push_back(*fPushedback);
			fCount++;
		}
	}; // adds aElement at back
};