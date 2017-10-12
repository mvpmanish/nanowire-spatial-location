//hpp file to declare a kd tree for the nanowire and quad classes
//A kd tree is a tree structure used for searching for nearest neighbours
//To make the tree you partition the space by finding medians along dimensions, storing the median value in a node of the tree
//All values lower than this median go to the left of the node and everything higher goes to teh right of the node
//Split the space along another dimension and repeat process for left and right nodes until every point is split by a median

#ifndef KDTREE_HPP
#define KDTREE_HPP

#include<vector>
#include<memory>

#include "quad.hpp"
#include "nanowire.hpp"

extern int debugcount;

//node of the nanowire kd tree
class nanonode 
{
private:
	char type; //character to show what split the kd tree is
	nanowire_ptr nano; //nanowire contained in this node
	std::shared_ptr<nanonode> left, right; //pointer to the left or right of the node
public:
	//Constructors and destructor
	nanonode()
	{
		left = nullptr;
		right = nullptr;
	};
	
	nanonode(nanonode &node) //Copy constructor
	{
		type = node.type;
		nano = move(node.nano);
		left = move(left);
		right = move(right);
	}
	
	~nanonode(){};
	
	//Access functions
	char gettype() const { return type; }
	int getx() const { return nano->getx(); }
	int gety() const { return nano->gety(); }

	//Set functions
	void settype(char c){ type = c; }
	void setnode(nanowire_ptr &nanowire){ nano = move(nanowire->clone()); } 
	void movenano(nanowire_ptr &nanowire){ nanowire = move(nano); } //Moves the node's nanowire ptr to another location
	void setleft(std::shared_ptr<nanonode> &nl){ left = nl; }
	void setright(std::shared_ptr<nanonode> &nr){ right = nr; }

	//Range search function
	void rangesearch(nanowire_set &nanoset, int &x, int &dx, int &y, int &dy); //Searches for nanowires in the range +/-dx,dy around x,y

};

typedef std::shared_ptr<nanonode> nanonode_ptr;

//Function to compare x values of nanowires and return true if a.x < b.x
//inline functions can be defined in header (quicker for small functions as no need to call function)
inline bool comp_x(nanowire_ptr &a, nanowire_ptr &b)
{
	return a->getx() < b->getx();
}

//Function to compare y values of nanowires and return true if a.y < b.y
inline bool comp_y(nanowire_ptr &a, nanowire_ptr &b)
{
	return a->gety() < b->gety();
}

//Function to sort the vector to make the nanowire with the median x value at the centre of the vector
inline void medianx(nanowire_set &nanoset)
{
	//Use nth element to sort vector by size compared to the middle value
	std::nth_element(nanoset.it(0), nanoset.it( nanoset.getsize() / 2), nanoset.it(nanoset.getsize()), comp_x);
}

//Function to find the nanowire with median y value
inline void mediany(nanowire_set &nanoset)
{
	//Use nth element to sort vector by size compared to the midlle value
	std::nth_element(nanoset.it(0), nanoset.it(nanoset.getsize() / 2), nanoset.it(nanoset.getsize()), comp_y);
}

//Function to make the root of the tree
nanonode_ptr makenanoroot(nanowire_set &nanoset);

//Function to make the tree
nanonode_ptr makenanotree(nanonode_ptr &arg_node, nanowire_set &nanoset);


#endif