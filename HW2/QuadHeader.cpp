#include "QuadHeader.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

	QuadTree::QuadTree()
	{
		root=nullptr;
		x_limit=0,y_limit=0;
	}

	QuadTree::~QuadTree()
	
	{
		make_Empty(root);
	}


	void QuadTree::insert_Tree (const std::string & name,const double & x,const double & y, QuadNode * &ptr)
	{
		if (x<0||x>x_limit||y<0||y>y_limit)
			return;

		if(ptr == NULL)

		{ 
			ptr = new QuadNode(x,y,name);
			ptr->SE = NULL;
			ptr->SW = NULL;
			ptr->NE = NULL;
			ptr->NW = NULL;
		
		}

		else if(x >= ptr->x_coor && y < ptr->y_coor)
		{
			insert_Tree(name, x,y, ptr->SE);
		}


		else if(x < ptr->x_coor && y <= ptr->y_coor)
		{
			insert_Tree(name, x,y, ptr->SW);
		}

		else if(x >= ptr->x_coor && y >= ptr->y_coor)
		{
			insert_Tree(name, x,y, ptr->NE);
	
		}
	
		else if(x < ptr->x_coor && y > ptr->y_coor)
		{
			insert_Tree(name, x,y, ptr->NW);
		}
		

	}

	void QuadTree::insert_Tree (const std::string & name,const double & x,const double & y)
	{
	
		insert_Tree(name,x,y,root);
	
	}



	void QuadTree::print_Tree () const
	{
		print_Tree(root);
	}

	void QuadTree::print_Tree (QuadNode * ptr) const
	{
		if(ptr!=nullptr)
		{
			cout<<ptr->cityname<<endl;
			print_Tree(ptr->SE);
			print_Tree(ptr->SW);
			print_Tree(ptr->NE);
			print_Tree(ptr->NW);
		}

	}


	vector<string> foundcities;
	vector<string> traversecities;
	int count1=0,count2=0;

	void QuadTree::search_Tree (double x, double y, double radius) const
	{
		search_Tree(x,y,radius,root);
		search_Traverse_Tree(x,y,radius,root);
		search_Tree_Print();
	
	}

	

	void QuadTree::search_Tree (double x, double y, double radius,QuadNode *  ptr) const
	{
		
		if(ptr!=nullptr)
		{
			if(pow(radius,2) >= (pow((ptr->x_coor - x),2) + pow((ptr->y_coor - y),2)))
			{
				foundcities.push_back(ptr->cityname);
			}
			search_Tree(x,y,radius,ptr->SE);
			search_Tree(x,y,radius,ptr->SW);
			search_Tree(x,y,radius,ptr->NE);
			search_Tree(x,y,radius,ptr->NW);

		}

	}
	void QuadTree::search_Traverse_Tree (double x, double y, double radius,QuadNode * ptr) const
	{
		if(ptr!=nullptr)
		{
			traversecities.push_back(ptr->cityname);
			int range = range_Calculator(x,y,radius,ptr);
		
			switch (range)
			{
			case 1:
				search_Traverse_Tree(x,y,radius,ptr->SE);
				break;
			case 2:
				search_Traverse_Tree(x,y,radius,ptr->SE);
				search_Traverse_Tree(x,y,radius,ptr->SW);
				break;
			case 3:
				search_Traverse_Tree(x,y,radius,ptr->SW);
				break;
			case 4:
				search_Traverse_Tree(x,y,radius,ptr->SE);
				search_Traverse_Tree(x,y,radius,ptr->NE);
				break;
			case 5:
				search_Traverse_Tree(x,y,radius,ptr->SW);
				search_Traverse_Tree(x,y,radius,ptr->NW);
				break;
			case 6:
				search_Traverse_Tree(x,y,radius,ptr->NE);
				break;
			case 7:
				search_Traverse_Tree(x,y,radius,ptr->NE);
				search_Traverse_Tree(x,y,radius,ptr->NW);
				break;
			case 8:
				search_Traverse_Tree(x,y,radius,ptr->NW);
				break;
			case 9:
				search_Traverse_Tree(x,y,radius,ptr->SE);
				search_Traverse_Tree(x,y,radius,ptr->SW);
				search_Traverse_Tree(x,y,radius,ptr->NE);

				break;
			case 10:
				search_Traverse_Tree(x,y,radius,ptr->SE);
				search_Traverse_Tree(x,y,radius,ptr->SW);
				search_Traverse_Tree(x,y,radius,ptr->NW);
				break;
			case 11:
				search_Traverse_Tree(x,y,radius,ptr->SE);
				search_Traverse_Tree(x,y,radius,ptr->NE);
				search_Traverse_Tree(x,y,radius,ptr->NW);
				break;
			case 12:
				search_Traverse_Tree(x,y,radius,ptr->SW);
				search_Traverse_Tree(x,y,radius,ptr->NE);
				search_Traverse_Tree(x,y,radius,ptr->NW);
				break;
			case 13:
				search_Traverse_Tree(x,y,radius,ptr->SE);
				search_Traverse_Tree(x,y,radius,ptr->SW);
				search_Traverse_Tree(x,y,radius,ptr->NE);
				search_Traverse_Tree(x,y,radius,ptr->NW);
				break;

			}
		}
	}
	void QuadTree::search_Tree_Print () const
	{
		if(count1==foundcities.size())
		{	cout<<"<None>\n"<<endl;}
	
		
		else
		{	for(unsigned int i =0+count1; i < foundcities.size()-1;i++)
			{
				cout<<foundcities[i]<<", ";
				count1++;
		
			}
			cout<<foundcities[foundcities.size()-1]<<"\n"<<endl;count1++;
		}
			

		for(unsigned int i =0+count2; i < traversecities.size()-1;i++)
		{
			cout<<traversecities[i]<<", ";
			count2++;
		
		}
		cout<<traversecities[traversecities.size()-1]<<"\n\n"<<endl;count2++;

	}


	void QuadTree::limit_Set (double x, double y)
	{
		x_limit=x;
		y_limit=y;
	}

	int QuadTree::range_Calculator(double x, double y, double r, const QuadNode *  ptr ) const
	{
		if(pow(r,2) >= (pow((ptr->x_coor - x),2) + pow((ptr->y_coor - y),2)))
			return 13;
		else
		{
			if(ptr->x_coor > (x + r))
			{
				if(ptr->y_coor > (y + r))
					return 3;
				else if(abs(ptr->y_coor - y )<= r)
					return 5;
				else
					return 8;
			}

			else if(abs(ptr->x_coor - x )<= r)
			{
			
				if(ptr->y_coor > (y + r))
					return 2;
				else if(ptr->y_coor < (y - r))
					return 7;
				else
				{
					if(ptr->x_coor < x && ptr->x_coor >= (x-r))
					{
						if(ptr->y_coor < y && ptr->y_coor >= (y-r))
							return 11;
						else if (ptr->y_coor >y && ptr->y_coor <= (y+r))
							return 9;
					}

					else if(ptr->x_coor > x && ptr->x_coor <= (x+r))
					{
						if(ptr->y_coor < y && ptr->y_coor >= (y-r))
							return 12;
						else if (ptr->y_coor >y && ptr->y_coor <= (y+r))
							return 10;
					}
				
				}
			}
			else
			{
				if(ptr->y_coor > (y + r))
					return 1;
				else if(abs(ptr->y_coor - y )<= r)
					return 4;
				else
					return 6;
			}
		}
	
	}

	void QuadTree::make_Empty (QuadNode * & ptr) const
	{
		if(ptr!=nullptr)
		{
			make_Empty(ptr->SE);
			make_Empty(ptr->SW);
			make_Empty(ptr->NE);
			make_Empty(ptr->NW);
			delete ptr;
		}
		ptr=nullptr;
	}
