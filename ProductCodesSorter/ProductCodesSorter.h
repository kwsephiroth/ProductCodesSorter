#pragma once
#include "ProductCodeFactory.h"
#include <fstream>
#include <iostream>
#include <locale>
#include <codecvt>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cwctype>
#include <clocale>

class ProductCodesSorter
{
private:	
	ProductCodesSorter() = default;
	
	using ProductCodeList = std::vector<std::unique_ptr<ProductCode>>;
	static void BuildProductCodeListFromFile(std::wifstream& inputFileStream, ProductCodeList& productCodeList, size_t& distinctCodesCount);
	static void SortProductCodeList(ProductCodeList& productCodeList);

public:
	static void SortProductCodesFromFile(const char* inputFileName, const char* outputFileName);
};

