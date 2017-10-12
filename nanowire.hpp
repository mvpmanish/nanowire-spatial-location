//Header file to declare the "nanowire" class and the "nanowire_set" class


#ifndef NANOWIRE_HPP //Header guard
#define NANOWIRE_HPP

#include<iostream>
#include<memory>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>

//-------------------------------------------DECLARATION OF VARIABLES-----------------------------------------
extern std::string filename;
extern int startcut, endcut;
extern float pi; 

//-----------------------------------------------------CLASSES------------------------------------------------------
//Nanowire class
class nanowire
{
private:
	int index, x, y, length, angle, area;
public:
	//Constructors and destructors
	nanowire() : index(0), x(0), y(0), length(0), angle(0), area(0){} //Default constructor
	nanowire(int indexi, int xi, int yi, int lengthi, int anglei, int areai) //Parameterised constructor
	{
		index = indexi;
		x = xi;
		y = yi;
		length = lengthi;
		angle = anglei;
		area = areai;
	}

	~nanowire(){} //Destructor

	std::unique_ptr<nanowire> clone() const //Clone function to create a new object and a pointer to the new object
	{
		return std::unique_ptr<nanowire> (new nanowire(*this));
	}

	//Access functions to return data members of a nanowire
	int getindex() const { return index; }
	int getx() const { return x; }
	int gety() const { return y; }
	int getlength() const { return length; }
	int getangle() const { return angle; }
	int getarea() const { return area; }

	//Function to print values for a single nanowire
	void printvalues() const { std::cout << index << ' ' << x << ' ' << y << ' ' << length << ' ' << angle << ' ' << area; }

	//Function to translate a nanowire's position
	void translate (int dx, int dy)
	{
		x = x + dx;
		y = y + dy;
	}

	//Function to rotate a nanowire's position about a centre (cx,cy) anticlockwise (r is in radians)
	//x' = (x-C_x)cos(o) + (y-C_y)sin(o) + C_x 
	//y' = -(x-C_x)sin(o) + (y-C_y)cos(o) + C_y
	void rotate(float r, int cx, int cy)
	{
		//Define xp and yp as the rotated positions
		int xp{ static_cast<int>((x-cx)*cos(r) + (y-cy)*sin(r)) }, yp{ static_cast<int>(-(x-cx)*sin(r) + (y-cy)*cos(r)) };
		//Equate the rotated positions to x,y of nanowire
		x = xp+cx;
		y = yp+cy;
	}

	//Deep copy by assignment
	nanowire& operator=(nanowire &tempnano)
	{
		if (&tempnano == this){ return *this; }
		index = tempnano.index;
		x = tempnano.x;
		y = tempnano.y;
		length = tempnano.length;
		angle = tempnano.length;
		area = tempnano.area;
	}
};

typedef std::unique_ptr<nanowire> nanowire_ptr; //Define a type: unique pointer to a nanowire

//Nanowire set class
class nanowire_set
{
private:
	std::vector<nanowire_ptr> vect; //Vector of unqique pointers to nanowires
	int size; //size of vector
public:
	//Default constructor
	nanowire_set(){ size = 0; }
	//Parameterised constructor using data from a file
	nanowire_set(std::string &filename);
	//Parameterised constructor using one nanowire_ptr
	nanowire_set(nanowire_ptr &n)
	{
		vect.push_back(move(n));
		size = 1;
	}
	//Destructor
	~nanowire_set(){}
	//Copy constructor
	nanowire_set(nanowire_set &ns)
	{
		size = ns.size;
		for (std::vector<nanowire_ptr>::iterator it{ ns.vect.begin() }; it < ns.vect.end(); it++)
		{
			vect.push_back((*it)->clone()); //Clone every element of ns and store in new vector
		}
	}
	//Move constructor
	nanowire_set(nanowire_set &&ns)
	{
		std::swap(size, ns.size);
		for (std::vector<nanowire_ptr>::iterator it{ ns.vect.begin() }; it < ns.vect.end(); it++)
		{
			vect.push_back(move(*it)); //Move every element of ns in new vector
		}
	}

	//Access functions
	//Function to return iterator to the vector of nanowires
	std::vector<nanowire_ptr>::iterator it(int i)
	{
		std::vector<nanowire_ptr>::iterator itr(vect.begin() + i);
		return itr;
	}
	//Function to find and return the centre of the set of nanowires
	std::pair<int, int> const getcentre();
	
	//Function to print data of set of nanowires
	void print();

	//Function to get the size of the nanowire set
	int getsize() const{ return size; };

	//Function to write data to a file
	void writetofile(std::string &filename);

	//Functions to find min and max x and y values in set
	int max_x();
	int max_y();
	int min_x();
	int min_y();

	//Functions to manipulate data
	void translate(int dx, int dy); //Function to translate the nanowires
	void rotate(int dangle); //Function to rotate the nanowires
	void add(nanowire_ptr &n){ vect.push_back(n->clone()); size++; } //Function to add a nanowire to the set
	void decrementsize(){ size--; } //Function to decrement the size of the set

	//Deep copy by assignment
	nanowire_set &operator=(const nanowire_set &ns)
	{
		vect.clear();
		for (std::vector<nanowire_ptr>::const_iterator it{ ns.vect.begin() }; it < ns.vect.end(); it++)
		{
			vect.push_back((*it)->clone()); //Clone every element of ns
		}
		size = ns.size;
	}
};

typedef std::unique_ptr<nanowire_set> nanowire_set_ptr;

//----------------------------------------------DECLARATION OF FUNCTIONS-----------------------------------------------
//File functions to ask what the name of the file you want to read from /write to
void nameofreadfile();
void nameofwritefile();

//Function to calculate the distance between two nanowires
int dist(nanowire_ptr &n1, nanowire_ptr &n2);

#endif