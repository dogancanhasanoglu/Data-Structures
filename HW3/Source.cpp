#include <iostream>
#include <fstream>
#include <vector>
#include "MPQ.h"

using namespace std;

struct buildingCoordinate{
	 int buildingID, buildingSide, Coordinate, Height;
};


//function prototypes, definitons are below

void percolateDown(vector<buildingCoordinate> & myVector,int hole, int currentSize);    //percolate down for the main
void heapSort( vector<buildingCoordinate> & myVector);                                  //sorting the heap
bool lessThanOperator(buildingCoordinate & coor1, buildingCoordinate & coor2);      //checks the whether given coordinate is less than the other or not




//------------------------------------------------------------------------------------//




int main()
{
	ifstream text;
    text.open("input.txt");
    
	// reading the # of buildings

	int buildingNumber, left, buildingHeight, right, iterator= 0;
	text >> buildingNumber;

	
    
	vector<buildingCoordinate> Coordinates(buildingNumber * 2);   //vector for buildings


	for(int i = 1; i <= buildingNumber; i++ )    // for loop for reading the text file
	{
		text >> left >> buildingHeight >> right;
        
		Coordinates[iterator].buildingID = i;
		Coordinates[iterator].buildingSide = 0; 
        Coordinates[iterator].Coordinate = left;
		Coordinates[iterator].Height = buildingHeight;
		
        
        iterator++;
        
       	Coordinates[iterator].buildingID = i;
		Coordinates[iterator].buildingSide = 1; 
        Coordinates[iterator].Coordinate = right;
		Coordinates[iterator].Height = buildingHeight;

        iterator++;
    }


	heapSort(Coordinates);     //now sorts the vector for buildings


    
	BinaryHeap myHeap(buildingNumber);     // creating a heap object wiith size(buildingNumber)


	//in case of there is no building at 0

	if (Coordinates[0].Coordinate)
	 {
		  cout << 0 << "  " << 0 << "\n-----"<< endl;
		
	 }

	int currentMax = -1;

	for(unsigned int i = 0; i < Coordinates.size();i++)
	{
		 //if the coordinate is left

		if(Coordinates[i].buildingSide == 0)      
		{ 
			myHeap.insert(Coordinates[i].Height, Coordinates[i].buildingID);
        }

		//if the coordinate is right

        else
		{
			myHeap.remove(Coordinates[i].buildingID);
        }

		//for the height changes

		if(myHeap.getMax() != currentMax)
		{ 
			currentMax = myHeap.getMax();
			cout << Coordinates[i].Coordinate << "  " <<currentMax << "\n-----"<< endl;
			
        }
    }


	text.close();


	return 0;

}

//------------------------------------------------------------------------------------//

void percolateDown(vector<buildingCoordinate> & myVector,int hole, int currentSize)
{
	int child;
    
	//temp is the item to be percolated
	buildingCoordinate temp;
    

	temp.buildingID = myVector[hole].buildingID;
	temp.buildingSide = myVector[hole].buildingSide;
	temp.Coordinate = myVector[hole].Coordinate;
	temp.Height = myVector[hole].Height;
	
    
    for( ; hole * 2  < currentSize; hole = child )
    {
        child = hole * 2 ;    //left child
		if( child != currentSize-1 && lessThanOperator(myVector[ child ], myVector[ child + 1]) )
		{
			child++;    //child is the maximum of the children 
		}  
		//if necessary then percolate
		if( lessThanOperator( temp , myVector[ child ]) )
		{
			myVector[hole].buildingID=myVector[child].buildingID;
		    myVector[hole].buildingSide=myVector[child].buildingSide;
	        myVector[hole].Coordinate=myVector[child].Coordinate;
	        myVector[hole].Height=myVector[child].Height;
		}
            
        else
            break;
    }
	//transfer the temp
	myVector[hole].buildingID=temp.buildingID;
	myVector[hole].buildingSide=temp.buildingSide;
	myVector[hole].Coordinate=temp.Coordinate;
	myVector[hole].Height=temp.Height;
}


void heapSort( vector<buildingCoordinate> & myVector)
{

	for( int i = myVector.size() / 2; i >= 0; i-- )
	{
		percolateDown( myVector, i, myVector.size());    //building the heap
	}	

    for (int i=myVector.size()-1 ; i > 0; i--)
    {
        //swapping the maximum element with the i th one
		buildingCoordinate temp;
		temp.buildingID = myVector[0].buildingID;
		temp.buildingSide = myVector[0].buildingSide;
		temp.Coordinate = myVector[0].Coordinate;
		temp.Height = myVector[0].Height;
	

        myVector[0].buildingID=myVector[i].buildingID;
		myVector[0].buildingSide=myVector[i].buildingSide;
	    myVector[0].Coordinate=myVector[i].Coordinate;
		myVector[0].Height=myVector[i].Height;

        myVector[i].buildingID=temp.buildingID;
		myVector[i].buildingSide=temp.buildingSide;
		myVector[i].Coordinate=temp.Coordinate;
		myVector[i].Height=temp.Height;


		//percolate down first element
        percolateDown(myVector, 0, i);
    }


}


bool lessThanOperator(buildingCoordinate & coor1, buildingCoordinate & coor2) 
{
	if (coor1.Coordinate < coor2.Coordinate)     //if coor1 is less than coor2
		return true;

	else if (coor1.Coordinate == coor2.Coordinate && coor1.buildingSide < coor2.buildingSide)   //when they are equal but building side is left for coor1
		return true;

	//when they are equal for coordinate and both side left but height of coor1 is greater than coor2

	else if (coor1.Coordinate == coor2.Coordinate && coor1.buildingSide == coor2.buildingSide && coor1.buildingSide == 0 && coor1.Height > coor2.Height)  
		return true;

	//when they are equal for coordinate and both side right but height of coor1 is less than coor2

	else if (coor1.Coordinate == coor2.Coordinate && coor1.buildingSide == coor2.buildingSide && coor1.buildingSide == 1 && coor1.Height < coor2.Height)
		return true;

	else
		return false;

}



