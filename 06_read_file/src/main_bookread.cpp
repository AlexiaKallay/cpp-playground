#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/**
	Define a simple book.
*/
class Book
{
public:
	std::string name;
	std::string authors;

	Book(const std::string& name, const std::string& authors) : name(name), authors(authors)
	{
	}

	void print()
	{
		std::cout << this->name << std::endl;
		std::cout << "\t(by " << this->authors << ")" << std::endl;
	}
};

/**
	Reads a vector of books from a text file.
	Note: the text file shall contain lines of text in pairs for the book name and authors
	E.g.
		BOOK 1
		AUTHOR 1
		BOOK 2
		AUTHOR 2
		BOOK 3
		AUTHOR 1, AUTHOR 2, AUTHOR 3
	@param file_name The name of the file to read from (must include path).
	@return Vector of books.
*/
std::vector<Book> readBooksFromTextFile(const std::string& file_name)
{
	std::vector<Book> results;
	std::ifstream file(file_name);

	if (file.is_open())
	{
		std::string line, bookName, authors;
		int lineNumber = 0;

		while (std::getline(file, line))
		{
			++lineNumber;
			std::istringstream ss(line);

			if (lineNumber % 2 == 0)
			{
				std::string token;
				while (std::getline(ss, token, ','))
				{
					authors.append(token);
					authors.append(",");
				}
				authors.replace(authors.end() - 1, authors.end(), "");

				Book* myBook = new Book(bookName, authors);
				results.emplace_back(*myBook);

				bookName = {};
				authors = {};
			}
			else
			{
				bookName.append(line);
			}
		}
		file.close();
	}
	else
	{
		std::cout << "Could not open the file.\n";
	}

	// E.g. Book myBook;
	//		...
	//		results.emplace_back(myBook);
	return results;
}

int main()
{
	// Read a collection of books from a file.
	// Simple examples can be found everywhere.
	// E.g. https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

	// Read the data
	std::string input_data("../../data/ermahgerd_berks.txt");
	std::cout << "Reading the data from " << input_data << std::endl;
	std::vector<Book> books_from_file = readBooksFromTextFile(input_data);

	// Print the data
	std::cout << "Here are all the books found in the data file..." << std::endl;
	for (auto book : books_from_file)
	{
		book.print();
	}

	return 0;
}
