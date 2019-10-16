#include "mem_alloc.hh"

using namespace mem;

static inline uintptr_t get_mem_header_i(void* ent_mem, unsigned int index, unsigned int block_offset)
{
	return ((uintptr_t)ent_mem + block_offset * index);
}

static inline void* header_to_data(void* header_ptr, unsigned int header_size)
{
	return (void*)((uintptr_t)header_ptr + header_size);
}

static inline void* data_to_header(void* data_ptr, unsigned int header_size)
{
	return (void*)((uintptr_t)data_ptr + header_size);
}

block_allocator::block_allocator(unsigned int block_size, unsigned int num_blocks)
	: mem_offset(block_size + sizeof(header)), n_blocks(num_blocks)
{
	ent_mem = ::operator new(mem_offset * num_blocks);
	cursor = (header*)ent_mem;
	
	for(unsigned int i = 0; i < num_blocks; i++)
	{
		header* h = (header*)get_mem_header_i(ent_mem, i, mem_offset);
		//Boolean is just a number. :3
		//Also, this provides a *chance* to compiler do it in vectorized way (i hope)
		h->next   = (header*)(get_mem_header_i(ent_mem, i + 1, mem_offset) * !(i == num_blocks - 1));
		h->allocated = false;
	}
}

block_allocator::~block_allocator()
{
	::operator delete(ent_mem);
}

void* block_allocator::allocate()
{
	header* h = cursor;
	cursor = h->next;
	h->allocated = true;
	return header_to_data(h, sizeof(header));
}

void block_allocator::deallocate(void* ptr)
{
	header* h = (header*)data_to_header(ptr, sizeof(header));
	h->next = cursor;
	cursor = h;
	h->allocated = false;
}

void block_allocator::iterate(bool non_allocated, const iterate_function& fun)
{
	for(unsigned int i = 0; i < n_blocks; i++)
	{
		header* h = (header*)get_mem_header_i(ent_mem, i, mem_offset);
		if(non_allocated || h->allocated)
		{
			fun(header_to_data(h, sizeof(header)), i);
		}
	}
}
