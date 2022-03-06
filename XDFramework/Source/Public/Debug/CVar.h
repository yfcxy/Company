
#ifndef CLASS1_H_
#define CLASS1_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <utility>
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::istream;
using std::fstream;
using std::cin;
using std::forward;




class Alpha
{

public:
	Alpha() :index(0) {};

	Alpha(int a ):index(a) { 
		
		print();
	};

	void operator <<= (const Alpha& other)
	{
		
	}

	const Alpha&  operator + (const Alpha& other)const
	{
		cout << "this is operator";
		return other;
	}

	const Alpha& foo() 
	{ 
		
		cout <<"this is member methid"<< index << endl;
		return *this;
	}

	
	 void print()
	{
		cout << index << endl;
	}

protected:

	 int index;
};

class Beta :public Alpha
{
public:

	Beta() :Alpha(){}
	virtual void foo() { cout << "this is b"; }
};

class Gamma :public Beta
{
public:
	Gamma():Beta(){}
	virtual void foo() { cout << "this is c"; }

};


#endif;