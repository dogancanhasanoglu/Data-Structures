#ifndef MAX_CAPACITY 
#define MAX_CAPACITY 512 
#include <string>

struct memory_block{
	memory_block* right; 
	memory_block* left; 
	bool used;
	int size; 
	int starting_address; 

		memory_block::memory_block()  
	{}

		memory_block::memory_block(int block_size,memory_block * before, memory_block * after )   
			: size(block_size), left(before), right(after) //starting_address(before->starting_address+before->size)
	{}
};


class My_heap{
private:
	memory_block* heap_begin;
	memory_block* blk;
	int used_bytes;


public:
	My_heap();
	~My_heap();
	memory_block* bump_allocate(int num_bytes);
	memory_block* first_fit_allocate(int num_bytes);
	memory_block* best_fit_allocate(int num_bytes);
	memory_block* first_fit_split_allocate(int num_bytes);
	void deallocate(memory_block* block_address);
	void print_heap();
	float get_fragmantation();
};

#endif