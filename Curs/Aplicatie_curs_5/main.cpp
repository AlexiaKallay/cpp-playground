
// include user defined headers first
#include "Header.h"
#include "Student.h"
// include system headers second list
#include <iostream>

using namespace std;


class Student: public Person
{
private:
	std::string university;
public:
	Student() {};
	Student(std::string university, int age, std::string name)
		: university(university), Person(age, name)
	{};

	bool Info()
	{
		std::cout << "Info from student class" << std::endl;
		return true;
	}
};

class Teacher : public Person, public Student
{
private:
	std::string specialization;
public:
	Teacher() {}
	Teacher(int age, std::string name, std::string classes)
	{
		Person(age, name);
		specialization = classes;
	}

	bool Info()
	{
		std::cout << "info from teacher class";
		return false;
	};
};



int main()
{
	std::cout << "Hello, class app!" << std::endl;

	Person newPerson(20, "Mihai");
	cout << newPerson.GetAge() << " " << newPerson.GetName() << endl;


	Student aStudent("Transilvania", 20, "Andrei");
	int studentAge = aStudent.GetAge();
	string studentName = aStudent.GetName();

	aStudent.Info();

	Teacher newTeacher(24, "George", "CPP");
	newTeacher.Info();				// will cause ambiguity when no "info()" method is implemented in derived class
	newTeacher.Person::Info();
	newTeacher.Student::Info();

	return 0;
}
