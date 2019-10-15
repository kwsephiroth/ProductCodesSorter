#pragma once
#include <vector>

struct Block
{
	std::wstring m_contents;
	bool m_isNum = false;
};

class ProductCode
{
private:
	std::wstring m_originalStr;
	std::vector<Block> m_blocks;

public:
	ProductCode(std::wstring&& originalStr, std::vector<Block>&& blocks) : m_originalStr(originalStr), m_blocks(blocks) {}
	const std::vector<Block>& GetBlocks() const { return m_blocks; }
	const std::wstring& GetOriginalString() const { return m_originalStr; }
};