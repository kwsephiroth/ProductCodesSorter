#include <iostream>
#include <string>
#include "../ProductCodesSorter.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "ERROR: Incorrect number of parameters. Please provide an input file name and an output file name." << std::endl;
		return -1;
	}

	ProductCodesSorter::SortProductCodesFromFile(argv[1], argv[2]);

	return 0;
}