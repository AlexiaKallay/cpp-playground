#pragma once
#include <string>

// not recommended to use "using namespace" in headers
// using namespace std;

#ifdef CLASS_CURS_5_EXPORT
#define CLASS_API __declspec(dllexport)
#else
#define CLASS_API __declspec(dllimport)
#endif


class CLASS_API Person
{
private:
	int age;
	std::string name;
public:
	Person() {};
	Person(int age, std::string name);

	std::string GetName();
	int GetAge();

	virtual bool Info();	// pur virtual classes and methods can't be directly exported from a DLL
							// we need an implementation for it in derived classes
};
