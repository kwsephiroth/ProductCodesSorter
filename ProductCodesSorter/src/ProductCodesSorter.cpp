#include "../ProductCodesSorter.h"


static bool ComesBefore(const std::unique_ptr<ProductCode>& pc1, const std::unique_ptr<ProductCode>& pc2)
{
	//std::cout << "here1" << std::endl;
	auto& pc1Blocks = pc1->GetBlocks(); //std::cout << "here2" << std::endl;
	auto& pc2Blocks = pc2->GetBlocks(); //std::cout << "here3" << std::endl;
	auto pc1BlockCount = pc1Blocks.size();// std::cout << "here4" << std::endl;
	auto pc2BlockCount = pc2Blocks.size();	//std::cout << "here5" << std::endl;

	if (pc1BlockCount <= 0)
		return false;

	if (pc2BlockCount <= 0)
		return true;

	auto maxIterations = std::min(pc1BlockCount, pc2BlockCount); //std::cout << "here6" << std::endl;

	for (size_t i = 0; i < maxIterations; ++i)
	{
		//std::cout << "here7" << std::endl;
		if (i < pc1BlockCount && i < pc2BlockCount)//Make sure index is in range first
		{
			//std::cout << "here8" << std::endl;
			auto& blk1 = pc1Blocks[i]; //std::cout << "here9" << std::endl;
			auto& blk2 = pc2Blocks[i];
			//std::cout << "here10" << std::endl;
			//std::cout << blk1.m_isNum << " " << blk2.m_isNum << std::endl;
			if (blk1.m_isNum && blk2.m_isNum)//If block contents are both number strings, 
											 //convert to numbers then compare
			{
				try
				{
					//std::wcout << "blk1.m_contents = " << blk1.m_contents << std::endl;
					auto num1 = std::stol(blk1.m_contents); //std::cout << "here11" << std::endl;
					//std::wcout << "blk2.m_contents = " << blk1.m_contents << std::endl;
					auto num2 = std::stol(blk2.m_contents); //std::cout << "here12" << std::endl;	
					if (num1 == num2)//Check if block contents are equal
					{
						continue;//Continue past equivalent blocks
					}
					return (num1 < num2 ? true : false);
				}
				catch (std::exception& e)
				{
					std::cout << "ERROR: Exception encountered during string to integer conversion: " << e.what() << std::endl;
				}
			}
			else if(blk1.m_isNum && !blk2.m_isNum)
			{
				//std::cout << "here13" << std::endl;
				return true;//Number blocks always come before non-digits
			}
			else if(!blk1.m_isNum && blk2.m_isNum)
			{
				//std::cout << "here14" << std::endl;
				return false;
			}
			else//Neither block is a number so they both are alphabetic(only letters)
			{
				//std::cout << "here14" << std::endl;
				if (blk1.m_contents == blk2.m_contents)//Check if block contents are equal
				{
					//std::cout << "here15" << std::endl;
					continue;//Continue past equivalent blocks
				}
				//std::cout << "here16" << std::endl;
				auto retVal = (blk1.m_contents < blk2.m_contents ? true : false);
				//std::cout << "here17" << std::endl;
				return retVal;
			}
		}
	}

	//All blocks matched up to the smallest number of blocks,
	//so, the product code with the smaller number of blocks comes first
	//Also, if the block counts are equal, order should match order of input file.
	//std::cout << "here18" << std::endl;
	return (pc1BlockCount < pc2BlockCount ? true : false);
}

void ProductCodesSorter::BuildProductCodeListFromFile(std::wifstream & inputFileStream, ProductCodeList& productCodeList, size_t& distinctCodesCount)
{
	std::unordered_set<std::wstring> uniqueProductCodes;

	std::setlocale(LC_ALL, "en_US.utf8");//TODO: Determine if this is correct. it seems to be needed for towupper to work correctly
	
	std::wstring line;

	while (std::getline(inputFileStream, line))
	{	
		Block currentBlock;
		std::vector<Block> currentBlocks;
		std::wstring currentBlockContents;
		std::wstring uniqueProductCode;

		for (wchar_t& wch : line)
		{
			if (iswdigit(wch))
			{
				if (!currentBlockContents.empty() && iswalpha(currentBlockContents.back()))
				{
					//outStream << currentBlockContents << L'\n';
					currentBlock.m_contents = currentBlockContents;
					currentBlock.m_isNum = false;
					currentBlocks.push_back(currentBlock);
					currentBlockContents.clear();
				}
				uniqueProductCode.push_back(wch);
				currentBlockContents.push_back(wch);
			}
			else if (iswalpha(wch))
			{
				if (!currentBlockContents.empty() && iswdigit(currentBlockContents.back()))
				{
					//outStream << currentBlockContents << L'\n';
					currentBlock.m_contents = currentBlockContents;
					currentBlock.m_isNum = true;
					currentBlocks.push_back(currentBlock);
					currentBlockContents.clear();
				}
				uniqueProductCode.push_back(towupper(wch));
				currentBlockContents.push_back(towupper(wch));
			}
		}	
		if (!currentBlockContents.empty())
		{
			//outStream << currentBlockContents << L'\n';
			currentBlock.m_contents = currentBlockContents;
			currentBlock.m_isNum = iswdigit(currentBlockContents.back());
			currentBlocks.push_back(currentBlock);
		}

		//std::cout << "Number of blocks: " << currentBlocks.size() << std::endl;
		uniqueProductCodes.insert(uniqueProductCode);
		std::unique_ptr<ProductCode> currentProduct(new ProductCode( std::move(line), std::move(currentBlocks)));
		productCodeList.push_back(std::move(currentProduct));
	}
	//std::cout << "There are " << uniqueProductCodes.size() << " distinct product codes in the file." << std::endl;
	distinctCodesCount = uniqueProductCodes.size();
	//std::cout << "There are " << productCodeList.size() << " ProductCode objects in the list." << std::endl;
	//for (auto& p : productCodeList)
		//outStream << p->GetOriginalString() << L'\n';
}

void ProductCodesSorter::SortProductCodeList(ProductCodeList& productCodeList)
{
	if (productCodeList.empty())
		return;

	std::sort(productCodeList.begin(), productCodeList.end(), ComesBefore);
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
	
	ProductCodeList pcList;
	size_t distinctCodesCount;
	BuildProductCodeListFromFile(inputFileStream, pcList, distinctCodesCount);
	SortProductCodeList(pcList);
	for (auto& product : pcList)
	{
		outputFileStream << product->GetOriginalString() << L'\n';
	}
	std::cout << "There are " << distinctCodesCount << " distinct product codes in the file." << std::endl;
}
