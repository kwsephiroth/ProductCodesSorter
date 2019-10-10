#include "../ProductCodesSorter.h"

void ProductCodesSorter::BuildProductCodeListFromFile(std::wifstream & inputFileStream, std::wostream& outputFileStream)//, ProductCodeList& productCodeList, size_t& distinctProductCodeCount)
{
	std::unordered_set<std::wstring> uniqueProductCodes;
	std::wstring uniqueProductCode;
	
	//std::wstringstream wss;
	//wss << inputFileStream.rdbuf();
	std::setlocale(LC_ALL, "en_US.utf8");
	
	std::wstring line;
	while (std::getline(inputFileStream, line))
	{
		for (wchar_t wch : line)
		{
			if (iswdigit(wch))
			{
				uniqueProductCode.push_back(wch);
			}
			else if (iswalpha(wch))
			{
				uniqueProductCode.push_back(towupper(wch));
			}
		}				

		uniqueProductCodes.insert(uniqueProductCode);
		uniqueProductCode.clear();
	}
	std::cout << "There are " << uniqueProductCodes.size() << " distinct product codes in the file." << std::endl;
	for (auto& wstr : uniqueProductCodes)
	{
		outputFileStream << wstr << L'\n';
	}
}

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

	// Read file in UTF-8
	std::wifstream inputFileStream;
	inputFileStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	inputFileStream.open(inputFileName, std::ios_base::binary | std::ios_base::in);

	if (inputFileStream.fail())
	{
		std::cout << "ERROR: Failed to open input file with name '" << inputFileName << "'. Please check if file exists and the name is correct." << std::endl;
		return;
	}

	// Write file in UTF-8
	std::wofstream outputFileStream;
	outputFileStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	outputFileStream.open(outputFileName, std::ios_base::binary | std::ios_base::out);

	if (outputFileStream.fail())
	{
		std::cout << "ERROR: Failed to open output file with name '" << outputFileName << "'. Please provide a valid output file name." << std::endl;
		return;
	}
	
	BuildProductCodeListFromFile(inputFileStream, outputFileStream);
}
