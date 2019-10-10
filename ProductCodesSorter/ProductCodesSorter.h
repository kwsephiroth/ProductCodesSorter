#pragma once
#include "ProductCode.h"
#include "ProductCodeFactory.h"
#include <fstream>
#include <iostream>
#include <locale>
#include <codecvt>
#include <sstream>

class ProductCodesSorter
{
private:	
	ProductCodesSorter() = default;

	static void BuildProductCodeList(std::wifstream& inputFileStream);
	static void SortProductCodeList();

public:
	~ProductCodesSorter() = default;
	static void SortProductCodesFromFile(const char* inputFileName, const char* outputFileName);
};

