#ifndef MEM_ALLOC_HH
#define MEM_ALLOC_HH

#include <utility>
#include <functional>

namespace mem {
	class block_allocator {
	public:
		using iterate_function = std::function<void(void*, unsigned int)>;
		block_allocator(unsigned int block_size, unsigned int num_blocks);
		
		~block_allocator();	
		
		void* allocate();
		void  deallocate(void* ptr);
		void  iterate(bool non_allocated, const iterate_function& fun);
	private:
		struct header {
			bool allocated;
			header* next;
		};
		unsigned int n_blocks;
		header* cursor;
		void*   ent_mem;
		unsigned int mem_offset;
	};
}
#endif
