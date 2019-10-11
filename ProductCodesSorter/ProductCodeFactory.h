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
	
	friend class ProductCodeFactory;
	std::wstring m_originalStr;
	std::vector<Block> m_blocks;

public:
	ProductCode(std::wstring&& originalStr, std::vector<Block>&& blocks) : m_originalStr(originalStr), m_blocks(blocks) {}
	const std::vector<Block>& GetBlocks() const { return m_blocks; }
};

/*class ProductCodeFactory
{
private:
	ProductCodeFactory() = default;
public:
	static std::unique_ptr<ProductCode> NewProductCode(const wchar_t* productCodeStr);
};*/

