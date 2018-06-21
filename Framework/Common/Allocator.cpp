#include "Allocator.hpp"
#include <cassert>
#include <cstring>

#ifndef ALIGN
#define ALIGN(x, a)         (((x) + ((a) - 1)) & ~((a) - 1))
#endif

My::Allocator::Allocator(size_t data_size, size_t page_size, size_t alignment) {
	Reset(data_size, page_size, alignment);
}

My::Allocator::~Allocator() {
	FreeAll();
}

void My::Allocator::Reset(size_t data_size, size_t page_size, size_t alignment) {
	FreeAll();

	m_szDataSize = data_size;
	m_szPageSize = page_size;

	size_t minimal_size = sizeof(BlockHeader) > m_szDataSize ? sizeof(BlockHeader) : data_size;

#if defined(_DEBUG)
	assert(alignment > 0 && alignment&(alignment - 1) == 0);
#endif

	m_szBlockSize = ALIGN(minimal_size, alignment);

	m_szAlignmentSize = m_szBlockSize - minimal_size;

	m_nBlocksPerPage = (m_szPageSize - sizeof(PageHeader)) / m_szBlockSize;
}


void* My::Allocator::Allocate() {
	if (!m_pFreeList)
	{
		PageHeader* pNewPage = reinterpret_cast<PageHeader*>(new uint8_t[m_szPageSize]);
		++m_nPages;
		m_nBlocks += m_nBlocksPerPage;
		m_nFreeBlocks += m_nBlocksPerPage;

#if defined(_DEBUG)
		FillFreePage(pNewPage);
#endif

		if (m_pPageList)
		{
			pNewPage->pNext = m_pPageList;
		}

		m_pPageList = pNewPage;

		BlockHeader* pBlock = pNewPage->Blocks();
		for (uint32_t i = 0; i < m_nBlocksPerPage; i++)
		{
			pBlock->pNext = NextBlock(pBlock);
			pBlock = NextBlock(pBlock);
		}
		pBlock->pNext = nullptr;


		m_pFreeList = pNewPage->Blocks();
	}

	BlockHeader* pFreeBlock = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	--m_nFreeBlocks;

#if defined(_DEBUG)
	FillAllocatedBlock(pFreeBlock);
#endif


	return reinterpret_cast<void*>(pFreeBlock);

}


void My::Allocator::Free(void* p) {
	BlockHeader* pBlock = reinterpret_cast<BlockHeader*>(p);

#if defined(_DEBUG)
	FillFreeBlock(pBlock);
#endif

	pBlock->pNext = m_pFreeList;
	m_pFreeList = pBlock;
	++m_nFreeBlocks;
}


void My::Allocator::FreeAll() {

	PageHeader* pPage = m_pPageList;

	while (pPage)
	{
		PageHeader* _p = pPage;

		pPage = pPage->pNext;

		delete[] reinterpret_cast<uint8_t*>(_p);
	}

	m_pPageList = nullptr;
	m_pFreeList = nullptr;
	m_nPages = 0;
	m_nBlocks = 0;
	m_nFreeBlocks = 0;
}

#if defined(_DEBUG)
void My::Allocator::FillFreePage(PageHeader *pPage)
{
	// page header
	pPage->pNext = nullptr;

	// blocks
	BlockHeader *pBlock = pPage->Blocks();
	for (uint32_t i = 0; i < m_nBlocksPerPage; i++)
	{
		FillFreeBlock(pBlock);
		pBlock = NextBlock(pBlock);
	}
}

void My::Allocator::FillFreeBlock(BlockHeader *pBlock)
{
	// block header + data
	std::memset(pBlock, PATTERN_FREE, m_szBlockSize - m_szAlignmentSize);

	// alignment
	std::memset(reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize - m_szAlignmentSize,
		PATTERN_ALIGN, m_szAlignmentSize);
}

void My::Allocator::FillAllocatedBlock(BlockHeader *pBlock)
{
	// block header + data
	std::memset(pBlock, PATTERN_ALLOC, m_szBlockSize - m_szAlignmentSize);

	// alignment
	std::memset(reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize - m_szAlignmentSize,
		PATTERN_ALIGN, m_szAlignmentSize);
}
#endif
My::BlockHeader* My::Allocator::NextBlock(BlockHeader *pBlock)
{
	return reinterpret_cast<BlockHeader *>(reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize);
}