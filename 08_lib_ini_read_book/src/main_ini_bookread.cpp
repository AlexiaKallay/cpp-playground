// Includes

// C++ system headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// 3rd party libs headers
#include <SimpleIni.h>

/**
	Define a simple book.
*/
class Book
{
public:
	std::string name;
	std::string authors;

	Book(const std::string& name, const std::string& authors)
		: name(name),
		  authors(authors)
	{
	}

	void print()
	{
		std::cout << this->name << std::endl;
		std::cout << "\t(by " << this->authors << ")" << std::endl;
	}
};

/**
	Reads a vector of books from an INI file.
	Note: the INI file shall contain a general books section with the number of books contained,
	and another INI section for each book, named [book.N], where N is a number/counter

	[books]
	count = 2;

	[book.1]
	name=The origin of truth
	author=Gusti
	[book.2]
	name  = Arhanghelul Raul
	author=Ovidiu Eftimie

	@param file_name The name of the file to read from (must include path).
	@return Vector of books.
*/
std::vector<Book> readBooksFromIniFile(const std::string& file_name)
{
	std::vector<Book> results;
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(file_name.c_str());

	CSimpleIniA::TNamesDepend sections;
	ini.GetAllSections(sections);

	for (const auto& section : sections)
	{
		CSimpleIniA::TNamesDepend keys;
		ini.GetAllKeys(section.pItem, keys);
		
		if (keys.size() == 1)
			continue;

		const char* nameValue = ini.GetValue(section.pItem, "name");
		const char* authorsValue = ini.GetValue(section.pItem, "author");

		Book* myBook = new Book(nameValue, authorsValue);
		
		results.emplace_back(*myBook);
	}
	return results;
}

int main()
{
	// Read a collection of books from an INI file.
	// Using the SimpleINI C++ Lib: https://github.com/brofield/simpleini

	// Read the data
	std::string input_data("../../data/ermahgerd_berks.ini");
	std::cout << "Reading the data from " << input_data << std::endl;
	std::vector<Book> books_from_file = readBooksFromIniFile(input_data);

	// Print the data
	std::cout << "Here are all the books found in the data file..." << std::endl;
	for (auto book : books_from_file)
	{
		book.print();
	}
	return 0;
}