#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_map> 
#include <vector>
#include <string>

using namespace std;

//*********************//
// Doðan Can Hasanoðlu //
// 26809               //
// CS300               //
// HW4                 //
//*********************//

static ofstream myfile("output.txt");

struct Customer{   //struct for customer map
	string Block;
	string Row;
	int Column;
};

struct Row{         //struct for my heap structure
	string Block;
	int Size;
};
  

struct numIndex{   // struct for block priority and indexing
	int index;
	int prior;
};

//********************************************************************************//
unordered_map<string, unordered_map<string, unordered_map<int, string> >> my_Umap;
unordered_map<string, Customer> customerMap;
unordered_map<string,vector<Row>> detectBlock;
unordered_map<string,unordered_map<string,numIndex>> detectLocation;
//********************************************************************//
vector <string> Blocks, Rows;
int columnNo;


//main functions
void print ();     //  O(B*R*C)
void reserve_seat_by_row (string customerName, string rowName);   //  O(LogB + C)
void reserve_seat (string customerName, string blockName, string rowName, int columnNumber);   //  O(LogB)
void get_seat (string customerName); //  O(1)
void cancel_reservation (string customerName);   //  O(LogB)

//helper functions
void percolateDown(string customerName);   //  O(LogB)
void percolateUp(string customerName);    //  O(LogB)
bool lessThanOperator(Row x, Row y,string row);  // to make comparison in percolateDown & percolateUp    



//--------------------------------------------------------------------------------//
int main()
{
	
	ifstream text("inputs.txt");
	string line;

	getline(text,line);
	istringstream ss (line);
	string temp;

	while(ss>>temp)   // reading the first line
	{
		my_Umap[temp];    // my stadium map
		Blocks.push_back(temp);

	}

	

	getline(text,line);
	istringstream ss1 (line);
	string temp1;



	while(ss1>>temp1)    // reading the second line
	{
		for(int i=0;i<Blocks.size();i++)
			my_Umap[Blocks[i]][temp1];    // my stadium map
		Rows.push_back(temp1);     
		detectBlock[temp1];    // constructing my heap
		detectLocation[temp1];    // indexes for my heap
		

	}

	getline(text,line);
	istringstream ss2 (line);
	string temp2;

	ss2>>temp2;
	columnNo=stoi(temp2);
	
	for(unsigned int i=0;i<Blocks.size();i++)
	{
		for(unsigned int j=0;j<Rows.size();j++)
		{
			for(unsigned int k=0;k<columnNo;k++)
				my_Umap[Blocks[i]][Rows[j]][k]="---";   // initializing my stadium

		
		}
	
	}
	
	for(unsigned int i=0;i<Rows.size();i++)
	{
		Row temp1;
		detectBlock[Rows[i]].push_back(temp1);

		for(unsigned int j=0;j<Blocks.size();j++)
		{
			Row temp;
			temp.Block=Blocks[j];
			temp.Size=0;
			detectBlock[Rows[i]].push_back(temp);     //  constructing my heap
			detectLocation[Rows[i]][Blocks[j]].index=j+1;    // index initialize 
			detectLocation[Rows[i]][Blocks[j]].prior=j;       // priority initalize (this is used to differentiate 
			                                                  //                    the block with the order they are read)
	
		
		}

	}
	
	while (getline (text, line))     // reading the rest of the file and calling the respective functions
	{   
		istringstream ss (line);
		string mystr;
		while(ss>>mystr)
		{
			if(mystr=="print")
			{	print();}
			else if(mystr=="reserve_seat_by_row")
			{
				string customerName, rowName;
				ss>>customerName>>rowName;
				reserve_seat_by_row(customerName,rowName);
			
			}

			else if(mystr=="reserve_seat")
			{
				string customerName, blockName, rowName;
				int columnNumber;
				ss>>customerName>>blockName>>rowName>>columnNumber;
				reserve_seat(customerName,blockName,rowName,columnNumber);

			}
			else if(mystr=="get_seat")
			{
				string customerName;
				ss>>customerName;
				get_seat(customerName);
			}
			else if(mystr=="cancel_reservation")
			{
				string customerName;
				ss>>customerName;
				cancel_reservation(customerName);
			}
			else
				continue;
		
		}
	}


	return 0;

}

//--------------------------------------------------------------------------------//

void print()    // print function prints my stadium with the respective order they are read
{
	
	
	 for(unsigned int i=0;i<Blocks.size();i++)    // (B)
		{
			myfile<<endl<<Blocks[i]<<"\n~~~~~~~"<<endl;
			for(unsigned int j=0;j<Rows.size();j++)    //(R)
			{
				myfile<<Rows[j]<<" : ";
				for(int k=0;k<columnNo;k++)    //(C)
				{
					myfile<<my_Umap[Blocks[i]][Rows[j]][k].substr(0,3)<<" ";
				}
				myfile<<endl;
			}
			myfile<<"=======\n"<<endl;                      // IN TOTAL 3 FOR LOOPS => O(B*R*C)
		}
	 	
}


void reserve_seat_by_row (string customerName, string rowName)   
{
	if(customerMap.find(customerName) != customerMap.end() )     // if such customer found then do not reserve
	{
		myfile<<customerName<<" could not reserve a seat!"<<endl;
		return;
	}
	// then selecting the first element from my minHeap which has the smallest size or 
	// has the priority due to reading order

	for(int i=1;i<detectBlock[rowName].size();i++)   // this for loop goes through all the columns in given block so => O(C)  
	{                                                   
		if(my_Umap[detectBlock[rowName][1].Block][rowName][i-1] == "---")   // checking whether the seat is vacant or not 
		{
			my_Umap[detectBlock[rowName][1].Block][rowName][i-1]=customerName;       // assigning
			Customer temp;
			temp.Block=detectBlock[rowName][1].Block;
			temp.Row=rowName;
			temp.Column=i-1;
			customerMap[customerName]=temp;

			detectBlock[rowName][detectLocation[rowName][temp.Block].index].Size++;     // updating my heap
		
			percolateDown(customerName);       // this part takes O(logN); so for B blocks => O(logB)

			myfile<<customerName<<" has reserved "<<temp.Block<<" "<<rowName<<"-"<<temp.Column<<" by emptiest block"<<endl;
			return;
		}     
		
		// IN TOTAL 1 PERCOLATE DOWN 1 TRAVERSING AMONG THE COLUMNS SO => O(logB + C)
	
	}

	myfile<<customerName<<" could not reserve a seat!"<<endl;   // if there is no seat for the customer
	

}

void reserve_seat (string customerName, string blockName, string rowName, int columnNumber)
{

	if((customerMap.find(customerName) == customerMap.end() )&& my_Umap[blockName][rowName][columnNumber] == "---")
	{      // checking whether the customer has reservation and the requested seat is vacant
		
		my_Umap[blockName][rowName][columnNumber] = customerName;   // assigning
		Customer temp;                    
		temp.Block=blockName;
		temp.Row=rowName;
		temp.Column=columnNumber;
		customerMap[customerName]=temp;

		detectBlock[rowName][detectLocation[rowName][blockName].index].Size++;   // updating my heap 

		percolateDown(customerName);      // this part takes O(logN); so for B blocks => O(logB)

		myfile<<customerName<<" has reserved "<<blockName<<" "<<rowName<<"-"<<columnNumber<<endl;
	   
		// IN TOTAL 1 PERCOLATE DOWN SO => O(logB)
	}

	else
	{
		myfile<<customerName<<" could not reserve a seat!"<<endl;
	}



}


void get_seat (string customerName)   
{
	if(customerMap.find(customerName) != customerMap.end())    // checking whether the customer has reservation - in my hashtable -
	{
		myfile<<"Found that "<<customerName<<" has a reservation in "<< customerMap[customerName].Block<<" "<<customerMap[customerName].Row<<"-"<<customerMap[customerName].Column<<endl;
	
	}
		// IN TOTAL FIND OPERATION WITH THE GIVEN KEY SO  => O(1)  -  CONSTANT TIME
	else
		myfile<<"There is no reservation made for "<<customerName<<"!"<<endl;

}


void cancel_reservation (string customerName)
{
	if(customerMap.find(customerName) != customerMap.end())   // checking whether the customer has reservation
	{
		
		myfile<<"Cancelled the reservation of "<<customerName<<endl;     // if so cancel the reservation 
		detectBlock[customerMap[customerName].Row][detectLocation[customerMap[customerName].Row][customerMap[customerName].Block].index].Size--;  
		// update the respective element in the heap
		percolateUp(customerName);    // this part takes O(logN); so for B blocks => O(logB)

		// **notice this time bubble up & percolateUp function**

		my_Umap[customerMap[customerName].Block][customerMap[customerName].Row][customerMap[customerName].Column]="---";  // update stadium seat plan
		customerMap.erase(customerName);   // add customer to the customer map
	}
        // IN TOTAL 1 PERCOLATE UP SO => O(logB)

	else
	{
		myfile<<"Could not cancel the reservation for "<<customerName<<"; no reservation found!"<<endl;
	}


}

void percolateUp(string customerName)
{
	// this function has the same structure as in the heap insert (or bubble up)

	//PERCOLATE UP TAKES O(logN)

	Row temp;
	temp.Size=detectBlock[customerMap[customerName].Row][detectLocation[customerMap[customerName].Row][customerMap[customerName].Block].index].Size;
	temp.Block=detectBlock[customerMap[customerName].Row][detectLocation[customerMap[customerName].Row][customerMap[customerName].Block].index].Block;
	// creating temp 

	int currentSize=detectBlock[customerMap[customerName].Row].size();  // for easy implementation


	int hole = detectLocation[customerMap[customerName].Row][customerMap[customerName].Block].index;  // hole is the index of element I want to change
	
	for( ; hole > 1 && lessThanOperator(temp,detectBlock[customerMap[customerName].Row][hole/2],customerMap[customerName].Row); hole /= 2 )
    {          
		 detectBlock[customerMap[customerName].Row][hole] = detectBlock[customerMap[customerName].Row][hole/2];
		 detectLocation[customerMap[customerName].Row][detectBlock[customerMap[customerName].Row][hole].Block].index=hole;

				// now hole th element in my heap = hole/2 th element in my heap and assigning
	}
		  detectBlock[customerMap[customerName].Row][hole] = temp;
		  detectLocation[customerMap[customerName].Row][detectBlock[customerMap[customerName].Row][hole].Block].index=hole;

		  // hole th element in my heap = the temp I created at the beginning and assigning

}

void percolateDown(string customerName)    // has the same logic as stated in the slides 
{
	//PERCOLATE DOWN TAKES O(logN)

	int child;
	
	Row temp;
	temp.Size=detectBlock[customerMap[customerName].Row][detectLocation[customerMap[customerName].Row][customerMap[customerName].Block].index].Size;
	temp.Block=detectBlock[customerMap[customerName].Row][detectLocation[customerMap[customerName].Row][customerMap[customerName].Block].index].Block;
	//creating temp 

    int currentSize=detectBlock[customerMap[customerName].Row].size();  // for easy implementation

	int hole=detectLocation[customerMap[customerName].Row][customerMap[customerName].Block].index;  // hole is the index of element I want to change

	for( ; hole * 2  < currentSize; hole = child )
    {
        child = hole * 2 ;
		if( child != currentSize-1 && lessThanOperator(detectBlock[customerMap[customerName].Row][child+1],detectBlock[customerMap[customerName].Row][child],customerMap[customerName].Row))
		{	
			child++;   // if next element to child is less than the child move on and increment the child  
		}  
		
		if( lessThanOperator(detectBlock[customerMap[customerName].Row][child],temp,customerMap[customerName].Row) )
		{
			// now child is less than the temp so I'm good to go.

			detectBlock[customerMap[customerName].Row][hole]=detectBlock[customerMap[customerName].Row][child];  // assigning
			detectLocation[customerMap[customerName].Row][detectBlock[customerMap[customerName].Row][hole].Block].index=hole;

			// now hole th element in my heap = child th element in my heap and assigning
		}
            
        else
            break;
    }
	
	detectBlock[customerMap[customerName].Row][hole]=temp;
	detectLocation[customerMap[customerName].Row][detectBlock[customerMap[customerName].Row][hole].Block].index=hole;

	// hole th element in my heap = the temp I created at the beginning and assigning


}

bool lessThanOperator(Row x, Row y,string row)    // for easier comparion in percolateDown & percolateUp
{
	if(x.Size<y.Size)     // if size is less than the other one
		return true;
	else if(x.Size==y.Size && detectLocation[row][x.Block].prior<detectLocation[row][y.Block].prior)   // if their size is equal but first block has priority
		return true;                                                                                   // for example in inputs1.txt assume 
	else                                                                                               // KONYA=1 BURSA=1 KONYA comes first
		return false;
}