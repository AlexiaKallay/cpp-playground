#include <iostream>

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cout << "No program arguments found." << "\n";
		return 1;
	}

    for (int index = 1; index < argc; ++index)
        std::cout << argv[index] << "\n";
    return 0;
}