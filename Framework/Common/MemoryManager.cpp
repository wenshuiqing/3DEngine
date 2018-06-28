#include "MemoryManager.hpp"

#ifndef ALIGN
#define ALIGN(x, a)         (((x) + ((a) - 1)) & ~((a) - 1))
#endif

using namespace My;
namespace My {
	static const uint32_t kBlockSize[] = {
		//4
		4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,
		68,72,76,80,84,88,92,96,

		//32
		128,160,192,224,256,288,320,352,384,416,448,
		480,512,544,576,608,640,

		//64
		704,768,832,896,960,1024

	};

	static const uint32_t kNumBlocks = sizeof(kBlockSize) / sizeof(kBlockSize[0]);
	static const uint32_t kMaxBlockSize = kBlockSize[kNumBlocks - 1];
	static const uint32_t kPageSize = 8192;
	static const uint32_t kAlignment = 4;

	size_t*        MemoryManager::m_pBlockSizeLookup;
	Allocator*     MemoryManager::m_pAllocators;
}

int My::MemoryManager::Init() {

	static bool s_bInit = false;

	if (!s_bInit)
	{
		m_pBlockSizeLookup = new size_t[kMaxBlockSize + 1];//存放申请块大小的索引，比如申请大小为3的块，3<4，所以索引为0，最终给出的大小为4

		size_t j = 0;
		for (size_t i = 0; i < kMaxBlockSize; i++)
		{
			if (i > kBlockSize[j])j++;

			m_pBlockSizeLookup[i] = j;
		}

		m_pAllocators = new Allocator[kNumBlocks];
		for (size_t i = 0; i < kNumBlocks; i++)
		{
			m_pAllocators[i].Reset(kBlockSize[i], kPageSize, kAlignment);

		}
		s_bInit = true;
	}

	return 0;
}

void My::MemoryManager::Update() {

}

void My::MemoryManager::Destroy() {
	delete[] m_pAllocators;
	delete[] m_pBlockSizeLookup;
}

void* My::MemoryManager::Allocate(size_t size) {
	Allocator* pAllocator = LookUpAllocator(size);
	if (pAllocator)
	{
		return pAllocator->Allocate();
	}
	else
	{
		return malloc(size);
	}
}

void* My::MemoryManager::Allocate(size_t size, size_t alignment)
{
	uint8_t* p;
	size += alignment;
	Allocator* pAlloc = LookUpAllocator(size);
	if (pAlloc)
		p = reinterpret_cast<uint8_t*>(pAlloc->Allocate());
	else
		p = reinterpret_cast<uint8_t*>(malloc(size));

	p = reinterpret_cast<uint8_t*>(ALIGN(reinterpret_cast<size_t>(p), alignment));

	return static_cast<void*>(p);
}


void My::MemoryManager::Free(void* p, size_t size) {

	Allocator* pAllocator = LookUpAllocator(size);
	if (pAllocator)
	{
		pAllocator->Free(p);
	}
	else
	{
		free(p);
	}

}

 Allocator* My::MemoryManager::LookUpAllocator(size_t size) {

	if (size <= kMaxBlockSize)
	{
		return m_pAllocators + m_pBlockSizeLookup[size];
	}
	else
	{
		return nullptr;
	}
}