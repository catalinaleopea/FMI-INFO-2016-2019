#include <iostream>
using namespace std;
#define SIZE 100
class stack{
int stck[SIZE];
int tos;
public:
    stack();//constructor
    ~stack();//destructor
	void push(int i);
	int pop();
};

stack::stack()
{
	tos=0;
	cout << "Stack Initialized\n";
}

stack::~stack()
{
   cout << "Stack Destroyed\n";
}

void stack::push(int i)//:: scope resolution operator
{
	if(tos==SIZE)
	{
		cout<<"Stack is full.\n";
		return;
	}
	stck[tos]=i;
	tos++;
}

int stack::pop()
{
	if(tos==0)
	{	cout<<"Stack underflow.\n";
		return 0;
	}
	tos--;
	return stck[tos];
}

int main()
{
	stack stack1, stack2; // create two stack objects
   stack1.push(1);
   stack2.push(2);
   stack1.push(3);
   stack2.push(4);
   cout << stack1.pop() << " ";
   cout << stack1.pop() << " ";
   cout << stack2.pop() << " ";
   cout << stack2.pop() << "\n";
   return 0;
}
