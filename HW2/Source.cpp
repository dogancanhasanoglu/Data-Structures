#include<iostream>
#include<fstream>
#include<sstream>
#include <vector>
#include "QuadHeader.h"

using namespace std;

int main()
{

	ifstream cities("cities.txt");
	ifstream queries("queries.txt");

	string line;

	vector<string> citiesinfo;
	
	while (getline (cities, line)) 
	{   
		istringstream ss (line);
		string mystr;
		while(ss>>mystr)
		{
			citiesinfo.push_back(mystr);

		}
	}
	QuadTree mytree;

	mytree.limit_Set(stod(citiesinfo[0]),stod(citiesinfo[1]));
	for(unsigned int i=2; i < citiesinfo.size();i+=3)
	{   
			mytree.insert_Tree(citiesinfo[i],stod(citiesinfo[i+1]),stod(citiesinfo[i+2]));
	}
	mytree.print_Tree();
	 cout<<"\n\n";
	vector<double> queriesinfo;

	while (getline (queries, line)) 
	{   

		istringstream ss (line);
		string mystr1,mystr2,mystr3;

		getline(ss,mystr1,',');queriesinfo.push_back(stod(mystr1));
		getline(ss,mystr2,',');queriesinfo.push_back(stod(mystr2));
		getline(ss,mystr3,',');queriesinfo.push_back(stod(mystr3));
	
	}
	for(unsigned int i=0; i < queriesinfo.size();i+=3)
	{
		mytree.search_Tree(queriesinfo[i],queriesinfo[i+1],queriesinfo[i+2]);
	}
 

	return 0;
}