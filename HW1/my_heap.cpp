#include "my_heap.h"
#include <iostream>
#include <string>


	My_heap::My_heap()
	{	
		heap_begin=NULL;
		blk=NULL;
		used_bytes=0;
	}
	My_heap::~My_heap()
	{
		
		int leak = 0;
		while (heap_begin!=blk)
		{   memory_block * temp;
			leak += heap_begin->size;
			
			temp=heap_begin->right;
			delete heap_begin;
			heap_begin=temp;
		}

		leak+=blk->size;
		delete blk;

		printf("At destruction, the heap had a memory leak of %d bytes.\n",leak);
	

	}
	memory_block* My_heap::bump_allocate(int num_bytes)
	{
	
		memory_block * block;

		if(heap_begin == NULL)
		{
			block= new memory_block(num_bytes,nullptr,nullptr);
			block->used=true;
			block->starting_address=0;
			heap_begin=block;
			blk=block;
			used_bytes+=block->size;
		}

		else
		{   
			int memory=0;
			memory_block * temp = heap_begin;
			while (temp!=blk->right)
			{  
				memory+=temp->size;
				temp=temp->right;
			}

			if(MAX_CAPACITY-memory >= num_bytes)
			{
				block = new memory_block(num_bytes,blk,nullptr);
				block->used=true;
				block->starting_address=blk->starting_address+blk->size;
				blk=block;
				blk->left->right=block;
				used_bytes+=block->size;

			}
			else
				return nullptr;
		
		}

		return block;

	}

	memory_block* My_heap::first_fit_allocate(int num_bytes)
	{
		memory_block * temp = heap_begin;
		while (temp!=blk->right)
		{   
			if(!temp->used && temp->size>=num_bytes)
				{
					temp->used=true;
					used_bytes+=temp->size;
					return temp;
				}
			
			temp=temp->right;
		}
		return bump_allocate(num_bytes);
	}

	memory_block* My_heap::best_fit_allocate(int num_bytes)
	{
		int free_space=0;
		memory_block * temp = heap_begin;
		while (temp!=blk->right)
		{   
			if(!temp->used && temp->size>=num_bytes)
				{
					if(!free_space)
						free_space=temp->size-num_bytes;
					else if (temp->size - num_bytes < free_space)
						free_space=temp->size-num_bytes;
				}
			temp=temp->right;
		}
		temp = heap_begin;
		while (temp!=blk->right)
		{
			if(!temp->used && temp->size-num_bytes==free_space)
			{
				temp->used=true;
				used_bytes+=temp->size;
				return temp;
			}

			temp=temp->right;
		}
		return bump_allocate(num_bytes);
	}

	memory_block* My_heap::first_fit_split_allocate(int num_bytes)
	{
		memory_block * temp = heap_begin;
		while (temp!=blk->right)
		{   
			if(!temp->used && temp->size==num_bytes)
			{
				temp->used=true;
				return temp;
			}
			else if(!temp->used && temp->size>num_bytes)
			{
				temp->used=true;
				memory_block * temp_free = new memory_block(temp->size-num_bytes,temp,temp->right);
				temp->right->left=temp_free;
				temp->right=temp_free;
				temp_free->starting_address=temp->starting_address+num_bytes;
				temp_free->used=false;
				temp->size=num_bytes;
				used_bytes+=temp->size;
				
				return temp;
			}
				temp=temp->right;
		}
		return bump_allocate(num_bytes);
	}
	void My_heap::deallocate(memory_block* block_address)
	{
		used_bytes-=block_address->size;
		if(heap_begin==block_address)
			block_address->used=false;
		if(blk==block_address)
			block_address->used=false;
		if(block_address->left!=nullptr && !block_address->left->used)
		{   
			block_address->used=false;
			block_address->starting_address = block_address->left->starting_address;
			block_address->size+=block_address->left->size;
			block_address->left=block_address->left->left;
			if(block_address->left!=nullptr)
				block_address->left->right=block_address;

		}
		if(block_address->right!=nullptr && !block_address->right->used)
		{
			block_address->used=false;
			block_address->size+=block_address->right->size;
			block_address->right=block_address->right->right;
			if(block_address->right!=nullptr)
				block_address->right->left=block_address;
	
		}
		else
		{
			block_address->used=false;
		}
		
		
	}
	
	
	void My_heap::print_heap()
	{
		printf("Maximum capacity of heap: %s \n", "512B");

		memory_block * temp = heap_begin;
		int count=0,memory=0,used=0;

		while (temp!=blk->right)
		{   
			
			count++;
			if(temp->used)
				used++;

			temp=temp->right;
		}
		printf("Currently used memory (B): %d \n", used_bytes);
		printf("Total memory blocks: %d \n", count);
		printf("Total used memory blocks: %d \n", used);
		printf("Total free memory blocks: %d \n", (count-used));
		printf("Fragmentation:  %f %s \n------------------------------\n",get_fragmantation(),"%");

		temp=heap_begin;
		for(int i=0; i < count;i++)
		{

			printf("Block %d \t\t Used: %s \t Size (B): %d \t Starting Address: 0x%02x \n", i, temp->used ? "True" : "False", temp->size, temp->starting_address);
			temp=temp->right;
		}
		printf("------------------------------ \n------------------------------\n");

		return;
	}



	float My_heap::get_fragmantation()
	{   float result;
		memory_block * temp = heap_begin;
		int count=0,free=0,max_big=0;

		while (temp!=blk->right)
		{   
			count+=temp->size;
			if(!temp->used)
			{	free+=temp->size;
				if((temp->size) > max_big)
					max_big=temp->size;
			}
			temp=temp->right;
		}

		int total_free=MAX_CAPACITY-count+free;
		if(total_free-free>max_big)
		{	max_big=total_free-free;
			result=(float(total_free-max_big)*100/total_free);
		}
		else
			result =(float(total_free-max_big)*100/total_free);

	
	return result;
	}