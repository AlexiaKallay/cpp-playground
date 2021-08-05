#include "Header.h"
#include <iostream>

using namespace std;

Person::Person(int age, std::string name) : age(age), name(name)
{
	std::cout << "Constructor clasa Person" << std::endl;
}

std::string Person::GetName()
{
	return this->name;
}

int Person::GetAge()
{
	return this->age;
}

bool Person::Info()
{
	cout << "Info from class Person";
	return true;
}