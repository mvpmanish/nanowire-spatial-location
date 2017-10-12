//header file to declare the "quad" class

#ifndef QUAD_HPP //Header guard
#define QUAD_HPP

#include<map>
#include<memory>
#include<random>

#include "nanowire.hpp"
#include "kdtree.hpp"
#include "grid.hpp"

class quad
{
private:
	float xc, yc, xd, yd;
public:
	//Default constructor
	quad() : xc(0), yc(0), xd(0), yd(0){}
	//Parameterised constructor
	quad(float xci, float yci, float xdi, float ydi)
	{
		xc = xci;
		yc = yci;
		xd = xci;
		yd = ydi;
	}
	//Destructor
	~quad(){}
	
	/*//Copy constructor  //Don't need
	quad(quad &q)
	{
		xc = q.xc;
		yc = q.yc;
		xd = q.xd;
		yd = q.yd;
	}
	//Move constructor
	quad(quad &&moveq)
	{
		xc = moveq.xc;
		yc = moveq.yc;
		xd = moveq.xd;
		yd = moveq.yd;
		moveq.xc = moveq.yc = moveq.xc = moveq.yd = 0;
	} */

	//Access functions 
	float getxc() const { return xc; }
	float getyc() const { return yc; }
	float getxd() const { return xd; }
	float getyd() const { return yd; }
	void print() const { std::cout << "(" << xc << "," << yc << "," << xd << "," << yd << ")"; }
	//Deep copy by assignment
	quad& operator=(quad &q)
	{
		xc = q.xc; yc = q.yc;
		xd = q.xd; yd = q.yd;
	}

	//Less than operator
	bool operator<(const quad &q) const
	{
		return xc < q.xc;
	}
		 
	/*//Move assignment  //Don't need for now
	quad& operator=(quad &&moveq)
	{
		std::swap(xc, moveq.xc);
		std::swap(yc, moveq.yc);
		std::swap(xd, moveq.xd);
		std::swap(yd, moveq.yd);
	} */

	
};

typedef std::unique_ptr<quad> quad_ptr;

//Function to map four nanowires onto a quad with the quad being the key
void mapquads(nanonode_ptr &root, grid &nanogrid, std::map<quad, nanowire_set_ptr> &hashmap);

#endif