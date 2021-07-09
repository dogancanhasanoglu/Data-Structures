#include "MPQ.h"
#include <iostream>
#include <vector>

using namespace std;

BinaryHeap::BinaryHeap(int size = 0)      //constructor with parameters for array and locations vector and default for current size (0)

	: array(size+1),locations(size+1), currentSize(0)

	{
	}

BinaryHeap::~BinaryHeap(){}            


void BinaryHeap::insert( const int & value, const int & label )    
{

	int hole = ++currentSize;    //create a hole and percolate 

	for (; hole > 1 && value > array[hole/2].value; hole /= 2)
	{
		array[hole].value = array[hole/2].value;
		array[hole].label = array[hole/2].label;

		//update the location in each time

		locations[array[hole].label] = hole;
	}


	//setting the values for the hole

	array[hole].value = value;
	array[hole].label = label;

	//update location
	locations[array[hole].label] = hole;
}


int BinaryHeap:: remove(int & label)
{
	
	if( !isEmpty( ) || locations[label] > 0 )
	{

		//swap the labeled item with the last item in the heap

		int value = array[locations[label]].value;

        value = array[locations[label]].value;
    
        array[locations[label]].value = array[ currentSize ].value;
        array[locations[label]].label = array[currentSize].label;

        currentSize--;

		//percolate down the item for correct position

        percolateDown(locations[label]);

		//update the location as 0

        locations[label] = 0;

		return value;
    }
    
	return -1;   //return -1 if the heap is empty or there doesn't exist the labeled item
}

const int BinaryHeap::getMax() const     //simple function
{
	//if empty return 0
	if (isEmpty())	{return 0;}
	//otherwise return the max value
	return array[1].value;
}


bool BinaryHeap::isEmpty() const       //simple function
{
	if (!currentSize)	
		return true;
	else			
		return false;
}


void BinaryHeap:: percolateDown(int hole)
{
	int child;
	
	int value = array[hole].value;
	int label = array[hole].label;

	for( ; hole * 2 <= currentSize; hole = child )
	{
		child = hole*2;

		//compare left and right child

		if (child != currentSize && array[child + 1].value > array[child].value)
			child++;   //child is the minimum of the children

		if (array[child].value > value)
		{
			array[hole].value = array[child].value;
			array[hole].label = array[child].label;    //swap hole and min child

			locations[array[hole].label] = hole;
		}
		else	
			break;
	}
	//set the values for the hole
	array[hole].value = value;
	array[hole].label = label;

	locations[array[hole].label] = hole;
	
}











