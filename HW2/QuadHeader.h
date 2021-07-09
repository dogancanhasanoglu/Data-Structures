#ifndef QUADHEADER_H
#define QUADHEADER_H


#include <iostream>
#include <string>



struct QuadNode{

	double x_coor,y_coor;
	QuadNode* SE;
	QuadNode* SW;
	QuadNode* NE;
	QuadNode* NW;
	std::string cityname;

	QuadNode::QuadNode()
	{}

	QuadNode::QuadNode(double x,double y,std::string str)
		:x_coor(x),y_coor(y),cityname(str)
	{}
};


class QuadTree
{
public:

	QuadTree();
	~QuadTree();

	void insert_Tree (const std::string & name,const double & x,const double & y);
	void print_Tree () const;
	void search_Tree_Print () const;
	void search_Tree (double x, double y, double radius) const;

	void limit_Set (double x, double y);
	int range_Calculator(double x, double y, double r, const QuadNode * ptr) const;


private:
	
	void insert_Tree (const std::string & name,const double & x,const double & y, QuadNode * & ptr);
	void print_Tree (QuadNode * ptr) const;
	void search_Tree(double x, double y, double radius,QuadNode * ptr) const;
	void search_Traverse_Tree (double x, double y, double radius,QuadNode * ptr) const;
	void make_Empty (QuadNode * & ptr) const;
	QuadNode* root;
	double x_limit,y_limit;
};
	



#endif