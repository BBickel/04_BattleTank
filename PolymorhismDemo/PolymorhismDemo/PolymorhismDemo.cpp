// PolymorhismDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace::std;

//Ad-hoc Polymorphism (Overloading) = Same function, different implementations per signature
int GetSize(int x)
{
	return x;
}
int GetSize(string x)
{
	return x.length();
}


//Subtype Polymorphism (Subclassing and Virtual) aka Runtime Polymorphism
class Animal
{
public:
	virtual void MakeNoise()
	{
		cout << "Animal Noise" << endl;
	}
};
class Dog : public Animal
{
public:
	void MakeNoise() override
	{
		cout << "Woof" << endl;
	}
};
class Cat : public Animal
{
public:
	void MakeNoise() override
	{
		cout << "Meow" << endl;
	}
};
void Stroke(Animal* animal)//Pointer Example (also works for Reference & )
{
	animal->MakeNoise();
}
void Stroke(Animal animal)//Value example
{
	animal.MakeNoise();
}

int main()
{
	//Ad Hoc Example
	cout << "Ad Hoc Example" << endl;
	cout << GetSize(5) << endl;//prints 5
	cout << GetSize("hello world") << endl;//prints 11
	
	cout << endl;

	//Subtype Example
	cout << "Subtype Example" << endl;
	Dog dog;
	Cat cat;
	Stroke(&dog);//pass pointer, prints "Woof"
	Stroke(dog);//pass reference to copy, prints "Animal Noise"
	Stroke(&cat);//pass pointer, prints "Meow"
	Stroke(cat);//pass reference to copy, prints "Animal Noise"

	cout << endl;
	
	return 0;
}

