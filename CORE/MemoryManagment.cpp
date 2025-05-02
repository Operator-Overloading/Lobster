#include "MemoryManagment.h"

#include <malloc.h>

namespace Lobster
{
	LinearAllocator::LinearAllocator(size_t size)
	{
		_memory = static_cast<char*>(malloc(size));
		_current = _memory;
	}

	LinearAllocator::~LinearAllocator()
	{
		free(_memory);
	}

	void* LinearAllocator::Allocate(size_t size)
	{
		void* ptr = _current;
		_current += size;
		return ptr;
	}

	void LinearAllocator::Reset()
	{
		_current = _memory;
	}

	PoolAllocator::PoolAllocator(size_t chunk_size,size_t count)
	{
		_memory = static_cast<char*>(malloc(chunk_size * count));

		for(size_t i = 0; i < count; ++i)
		{
			_free_list.push(_memory + i * chunk_size);
		}
	}

	PoolAllocator::~PoolAllocator()
	{
		free(_memory);
	}

	void* PoolAllocator::Allocate()
	{
		if(_free_list.empty())
			return nullptr;

		void* ptr = _free_list.top();
		_free_list.pop();

		return ptr;
	}

	void PoolAllocator::Free(void* ptr)
	{
		_free_list.push(static_cast<char*>(ptr));
	}
}