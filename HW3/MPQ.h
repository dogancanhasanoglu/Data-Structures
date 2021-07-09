#ifndef MPQ_H
#define MPQ_H

#include <vector>

using namespace std;


struct element			
{
    int value;
    int label;
};


class BinaryHeap
{
	public:
		BinaryHeap(int size);      // constructor
    
		~BinaryHeap();             //destructor

		void insert(const int & value, const int & label);   //insert function (not object return type instead void)

		int remove (int & label);							//remove function (not object return type instead int)

		const int getMax() const;                           //function that gets the maximum value

		bool isEmpty() const;                               //function to check whether it is empty or not
    
    
    
    
	private:

		int currentSize;                            //to store the current size of heap
    
		vector<element> array;                      //to store the struct objects for heap
		vector<int> locations;                      //to store the coordinates
    
		void percolateDown(int hole);              //percolateDown for Heap
};



#endif

