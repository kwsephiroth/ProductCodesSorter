#pragma once
#include <memory>
#include <vector>

struct Block
{
	std::wstring m_contents;
	bool m_isNum;
};
class ProductCode
{
private:
	ProductCode() = default;
	friend class ProductCodeFactory;

	std::vector<Block> m_blocks;
public:
	const std::vector<Block>& GetBlocks() const { return m_blocks; }
};

class ProductCodeFactory
{
private:
	ProductCodeFactory() = default;
public:
	static std::unique_ptr<ProductCode> NewProductCode(const wchar_t* productCodeStr);
};

