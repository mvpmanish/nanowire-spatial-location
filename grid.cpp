//cpp file to define functions and variables in "grid.hpp"

#include "grid.hpp"

//Parameterised constructor using set of nanowires
grid::grid(nanowire_set &ns, int &size)
{
	std::cout << std:: endl << "Constructing grid..";
	//Calculate the number of x and y squares needed
	int xmax{ ns.max_x() }, xmin{ ns.min_x() };
	xnumbersq = (xmax-xmin) / size;
	if (size*xnumbersq < xmax - xmin){ xnumbersq++; } //If division does not result in larger integer then add 1

	int ymax{ ns.max_y() }, ymin{ ns.min_y() };
	ynumbersq = (ymax - ymin) / size;
	if (size*ynumbersq < ymax - ymin){ ynumbersq++; }

	//Create squares in x direction for every y interval
	for (int j{ 0 }; j < ynumbersq; j++)
	{
		for (int i{ 0 }; i < xnumbersq; i++)
		{
			int xval{ xmin + i*size }, yval{ ymin + j*size };
			square_ptr tempsq{ new square(xval, yval,size) };
			sqvect.push_back(move(tempsq));
		}
	}

	std::cout << std::endl << "Number of  x squares = " << xnumbersq << std::endl
		<< "Number of  y squares = " << ynumbersq << std::endl;
}