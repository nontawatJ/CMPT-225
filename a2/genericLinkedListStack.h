#include <string>
#include <iostream>
using namespace std;

class RuntimeException { // generic run-time exception
private:
  string errorMsg;
public:
  RuntimeException(const string& err) { errorMsg = err; }
  string getMessage() const { return errorMsg; }
};
// Exception thrown on performing top or pop of an empty stack. 
class StackEmpty : public RuntimeException { 
public: 
  StackEmpty(const string& err) : RuntimeException(err) {} 
};
// Exception thrown on performing top or pop of an empty stack. 
class StackFull : public RuntimeException { 
public: 
  StackFull(const string& err) : RuntimeException(err) {} 
};

template <typename E>
class Node 
{ 
public: 
	E elem; 
	Node<E>* next; 
	Node<E>* previous;
};
template <typename E>
class SLinkedList 
{
private:
	Node<E>* head;
public:
	SLinkedList()
	{
		head = NULL;
	}
	bool empty() const
	{
		return head == NULL;
	}
	const E& front() const
	{
		return head->elem;
	}
	void addFront(const E& e)
	{
		Node<E>* v = new Node<E>;
		v->elem = e;
		v->next = head;
		head = v;
	}
	void removeFront()
	{
		Node<E>* old = head;
		head = old->next;
		delete old;
	}
	~SLinkedList()
	{
		while(!empty())
			removeFront();
	}
	void print1()
	{
		Node<E>* v = head;
		while(v!=NULL)
		{
			cout << v->elem << " ";
			v = v->next;
		}
		cout << endl;
	}
};
template <typename E>
class  genericLinkedListStack
{
private:
	SLinkedList<E> S;
	int n;
public:
	genericLinkedListStack() : S(), n(0) {}
	int size() const {return n;}
	bool empty() const {return n==0;}
	const E& top() const throw(StackEmpty)
	{
		if (empty())
			throw StackEmpty("Top of empty stack");
		return S.front();
	}
	void push(const E& e)
	{
		++n;
		S.addFront(e);
	}
	void pop() throw(StackEmpty)
	{
		if (empty())
			throw StackEmpty("Pop from empty stack");
		--n;
		S.removeFront();
	}
	void print()
	{
		S.print1();
	}
};