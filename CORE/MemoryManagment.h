#pragma once
#include <stack>

namespace Lobster
{
	class LinearAllocator
	{
	public:
		LinearAllocator(size_t size);
		~LinearAllocator();
		void* Allocate(size_t size);
		void Reset();
	private:
		char* _memory;
		char* _current;
	};

	class PoolAllocator
	{
	public:
		PoolAllocator(size_t chunk_size,size_t count);
		~PoolAllocator();
		void* Allocate();
		void Free(void* ptr);
	private:
		char* _memory;
		std::stack<char*> _free_list;
	};
}