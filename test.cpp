#include <iostream>

class AbstractParent
{
	//all variables in classes are private unless specified otherwise 
	int privateVar_ = 0; 
//Unlike Java you don't declare each field public individually but rather everything under public will be public
public: 
	//Regular function
	void hello() { std::cout << "Hello from Parent Class" << std::endl; }
	//Virtual Function can optionally be overridden
	virtual void virtualHello() { std::cout << "Virtual Hello from Parent Class" << std::endl; } 
	//When you set a virtual function equal to 0 like this it is a "pure virtual" function which is equivalent to an abstract method in Java
	//Because of this "Pure Virtual" function you cannot instantiate an instance of the Parent class like in Java with Abstract methods
	virtual void abstractHello() = 0; 
protected:
	int protectedVar = 2;
}; //Remember to put that semicolon at the end of the class definition

//You have to declare inheretence like this
//note the public keyword. If we didn't put public here Child would still 
//inheret from Parent but nobody outside of Child would be able see that
//so to the outside world it would be as if Child was unrelated to Parent
//but Child would still have access to all of parent's stuff
class Child : public AbstractParent
{
public:
	//Overriding parent methods: 
	void hello() { std::cout << "Hello from Child Class"  << std::endl; }
	//We don't have to override virtualHello if we don't want to
	void virtualHello() { std::cout << "Child says hello" << std::endl; }
	//AbstractHello MUST be overridden if we don't want Child to be abstract 
	void abstractHello() { std::cout << "Child implementation of Abstract Hello" << std::endl; }

	//Child has access to protect vars from Parent just like Java
	void printProtectedVar() { std::cout << protectedVar << std::endl; }
};

int main(int argc, char *argv[])
{
	Child child;

	child.hello();
	child.virtualHello();
	child.abstractHello();
	child.printProtectedVar();

	std::cout << "\n\n";

	//Because Parent is abstract we cannot instantiate it directly but we can create a pointer
	//to a Parent object and then assign it to a pointer of a child class
	AbstractParent* parent = &child;

	//Because hello() is not a virtual function it will call the Parent's hello and not the child's
	parent->hello();

	parent->virtualHello();
	//We can even call the abstract method from the Parent pointer and it will use the Child's method
	parent->abstractHello();
}
