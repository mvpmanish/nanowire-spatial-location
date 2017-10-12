//header file to define the "square" and "grid" class
#ifndef GRID_HPP
#define GRID_HPP

#include<vector>
#include<memory>

#include "nanowire.hpp"

//Square class to store a square's location, its size and how many quads inside of it
class square
{
private:
	int x, y, size, quadno; //x & y position of bottom left corner of square, size of square, number of quads in square
public:
	square(): size(0), x(0), y(0), quadno(0){}  //Default constrcutor
	square(int &xi, int &yi, int &sizei) : x(xi), y(yi), size(sizei), quadno(0){} //Constructor using only x,y and size (quadno = 0)
	~square(){}  //Destructor
	square(const square &sq) //Copy constructor
	{
		x = sq.x; y = sq.y; size = sq.size; quadno = sq.quadno;
	}

	std::unique_ptr<square> clone() const
	{
		return std::unique_ptr<square> (new square(*this));
	}

	//Access functions
	int getx() const { return x; }
	int gety() const { return y; }
	int getsize() const { return size; }
	int getquadno() const { return quadno; }

	//Functions to manipulate data members
	void setx(int &xi){ x = xi; }
	void sety(int &yi){ y = yi; }
	void setquadno(int &no){ quadno = no; }
	void addquad(){ quadno++; }

	//Function to find the midpoint of the square (mid_x, mid_y)
	std::pair<int, int> midpoint()
	{
		std::pair<int, int> mid;
		mid.first = (x + x + size) / 2;
		mid.second = (y + y + size) / 2;
		return mid;
	}
};

typedef std::unique_ptr<square> square_ptr;

//Class to create a grid of nanowires: consists of square pointers
class grid
{
private:
	std::vector<square_ptr> sqvect;
	int xnumbersq, ynumbersq; //Number of x and y squares the grid is composed of
public:
	grid() : xnumbersq(0), ynumbersq(0){} //Default constructor
	grid(nanowire_set &ns, int &size); //Constructor using a set of nanowires and size of the squares in grid
	~grid(){}

	//Access functions
	int getxnumbersq() const { return xnumbersq; }
	int getynumbersq() const { return ynumbersq; }
	int numbersq() const { return xnumbersq*ynumbersq; } //Total numbe rof squares
	std::vector<square_ptr>::iterator it(int i) //Iterator function
	{
		std::vector<square_ptr>::iterator itr{ sqvect.begin() + i };
		return itr;
	}

};

#endif 