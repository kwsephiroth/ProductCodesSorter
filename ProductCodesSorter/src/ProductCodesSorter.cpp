#include "../ProductCodesSorter.h"

void ProductCodesSorter::SortProductCodesFromFile(const char * inputFileName, const char * outputFileName)
{
	//Try to open the files using the user-provided file names
	if (!inputFileName || inputFileName[0] == '\0')
	{
		std::cout << "ERROR: Input file name is empty. Please provide a valid input file name." << std::endl;
		return;
	}

	if (!outputFileName || outputFileName[0] == '\0')
	{
		std::cout << "ERROR: Output file name is empty. Please provide a valid input file name." << std::endl;
		return;
	}

	std::ifstream inputFileStream(inputFileName);

	if (inputFileStream.fail())
	{
		std::cout << "ERROR: Failed to open input file with name '" << inputFileName << "'. Please provide a valid input file name." << std::endl;
		return;
	}

	std::ofstream outputFileStream(outputFileName);

	if (outputFileStream.fail())
	{
		std::cout << "ERROR: Failed to open output file with name '" << outputFileName << "'. Please provide a valid output file name." << std::endl;
		return;
	}
}
