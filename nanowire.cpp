//File defines function declared in "nanowire.hpp"

#include "nanowire.hpp"

//-------------------------------------------FUNCTION DEFINITIONS------------------------------------------
//Function to set the filename that data is being read in from
void nameofreadfile()
{
	std::cout <<"\nWhat is the name of the file that you want data to be read from?: ";
	std::cin >> filename;
}

void nameofwritefile()
{
	std::cout << "\nWhat is the name of the file that you want to write data to?: ";
	std::cin >> filename;
}

//Parameterised constructor using data from a file: function to read in data from a CSV file and return a vector of nanowires
nanowire_set::nanowire_set(std::string &filename)
{
	std::vector<int> tempintvect; //Create a vector of ints to push data into from file
	std::string tempstr; //Dummy string
	float j; //Dummy variable
	int k;
	size = 0;

	std::ifstream file{ filename }; //Opens file for reading
	if (file.fail())
	{
		std::cout << "Error: could not open file of this name \n";
		std::cin.ignore();
		exit(1);
	}

	while (getline(file, tempstr)) //While reading in a line from the file input line of data into tempvect
	{
		if (tempstr.at(0) == '#' || tempstr.empty()) //If the first charcater of the string is '#' or there is an empty line then clear string and getline again
		{
			tempstr.clear();
			getline(file, tempstr);
		}

		std::stringstream ss(tempstr); //Push string into string stream

		while (ss >> j) //Insert number into dummy variable
		{

			if (ss.peek() == ','){ ss.ignore(); } //If a ',' is found ignore and continue
			k = j * 1000000; //Convert the float numbers into integers by multiplying by 10^6
			tempintvect.push_back(k); //Insert the numbers into a vector
		}

		//Create a temporary ptr to a nanowire and move values from vector to construct nanowire
		nanowire_ptr temp_ptr(new nanowire(std::move(tempintvect[0]), std::move(tempintvect[1]), std::move(tempintvect[2]), std::move(tempintvect[3]), std::move(tempintvect[4]), std::move(tempintvect[5])));
		vect.push_back(move(temp_ptr)); //Move the ptr onto the vector
		size++;

		tempintvect.clear();

	}

	file.close(); //Close file
	std::cout << "\nSuccessfully read data from " << filename;
}

// Function to write nanowires data to a file
void nanowire_set::writetofile(std::string &filename)
{
	std::ofstream file; //Define file to write to
	file.open(filename); //Open file
	if (file.fail())
	{
		std::cout << "Error: could not open file of this name\n";
		exit(1);
	}

	//Define iterators
	std::vector<nanowire_ptr>::iterator itbegin(vect.begin()), itend(vect.end()), itcurrent;

	//Loop over iterators, writing each nanowire to file with a single space separating each value
	for (itcurrent = itbegin; itcurrent < itend; itcurrent++)
	{
		if (itcurrent == itbegin) //For the first line write headings
		{
			file << "#Index x(nm) y(nm) Length(pm) Angle(10^-6*degrees) Area(arbitrary)\n";
		}

		file << (*itcurrent)->getindex() << ' ' << (*itcurrent)->getx() << ' ' << (*itcurrent)->gety() << ' ' //Write data on a single line
			<< (*itcurrent)->getlength() << ' ' << (*itcurrent)->getangle() << ' ' << (*itcurrent)->getarea();

		if (!(itcurrent == itend - 1)){ file << std::endl; } //Create a new line except when last line of data generated 
	}

	file.close(); //Close file
	std::cout << "\nSuccessfully wrote data to " << filename;
}

//Find the maximum x value of nanowires in set
int nanowire_set::max_x()
{
	std::vector<int> xvalues;
	xvalues.push_back(vect[0]->getx());
	for (int i{ 1 }; i < size; i++)
	{
		if ((*it(i))->getx() > xvalues.back()) //If last current value > last element then push back current value
		{ 
			xvalues.push_back((*it(i))->getx());
		}
	}
	
	return xvalues.back();
}

int nanowire_set::max_y()
{
	std::vector<int> yvalues;
	yvalues.push_back(vect[0]->getx());
	for (int i{ 1 }; i < size; i++)
	{
		if ((*it(i))->getx() > yvalues.back()) //If last current value > last element then push back current value
		{
			yvalues.push_back((*it(i))->getx());
		}
	}

	return yvalues.back();
}

int nanowire_set::min_x()
{
	std::vector<int> xvalues;
	xvalues.push_back(vect[0]->getx());
	for (int i{ 1 }; i < size; i++)
	{
		if ((*it(i))->getx() < xvalues.back()) //If last current value < last element then push back current value
		{
			xvalues.push_back((*it(i))->getx());
		}
	}

	return xvalues.back();
}

int nanowire_set::min_y()
{
	std::vector<int> yvalues;
	yvalues.push_back(vect[0]->getx());
	for (int i{ 1 }; i < size; i++)
	{
		if ((*it(i))->getx() < yvalues.back()) //If last current value < last element then push back current value
		{
			yvalues.push_back((*it(i))->getx());
		}
	}

	return yvalues.back();
}

//Function to print the values of all the nanowires in a nanowire vector
void nanowire_set::print()
{
	//Define iterators
	std::vector<nanowire_ptr>::iterator itbegin(vect.begin()), itend(vect.end()), itcurrent;

	//Loop over iterators, printing out value of each nanowire
	std::cout << "\n";
	for (itcurrent = itbegin; itcurrent < itend; itcurrent++)
	{
		(*itcurrent)->printvalues();
		std::cout << "\n";
	}
}

//Function to translate the nanowires( dx and dy are in nm)
void nanowire_set::translate(int dx, int dy)
{
	for (std::vector<nanowire_ptr>::iterator it{ vect.begin() }; it < vect.end(); it++)
	{
		(*it)->translate(dx, dy);
	}
}

//Function to find the centre position (C_x, C_y) of the set of nanowires
std::pair<int, int> const nanowire_set::getcentre()
{

	int C_x = (max_x() + min_x()) / 2, C_y = (max_y() + min_y()) / 2;

	return std::pair<int, int>(C_x, C_y);
}

//Function to rotate the set of nanowires anticlockwise about its centre (o is in degrees)
void nanowire_set::rotate(int o)
{
	
	//Find centre of naowire set
	std::pair<int, int> centre{ getcentre() };
	
	//Convert o into radians
	// r= o*pi/180
	float r{ o*pi / 180 };
	std::cout << "\nRotating nanowires about (" << centre.first << ", " << centre.second << ") by " << o << " deg.." ;
	//Rotate each nanowire individually about the centre (C_x,C_y)
	for (std::vector<nanowire_ptr>::iterator it{ vect.begin() }; it < vect.end(); it++)
	{
		(*it)->rotate(r, centre.first, centre.second);
	}
}

//Function to return the distance between two nanowires
int dist(nanowire_ptr &n1, nanowire_ptr &n2)
{
	//d = sqrt((x1-x2)^2+(y1-y2)^2)
	return pow(pow(n1->getx() - n2->getx(), 2) + pow(n1->gety() - n2->gety(), 2), 0.5);
}