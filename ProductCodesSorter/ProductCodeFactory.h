#pragma once
#include <memory>

class ProductCode
{
private:
	ProductCode() = default;
	friend class ProductCodeFactory;
public:
};

class ProductCodeFactory
{
private:
	ProductCodeFactory() = default;
public:
	static std::unique_ptr<ProductCode> NewProductCode(const wchar_t* productCodeStr);
};

