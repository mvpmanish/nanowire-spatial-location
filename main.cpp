//cpp file to read in "secondary_datatset.txt" and translate it then find the translation using analytical techniques
//Manish Patel
//Last edited: 13/07/2016

#include "nanowire.hpp"
#include "quad.hpp"
#include "grid.hpp"
#include "kdtree.hpp"

std::string filename;
int startcut, endcut;
float pi{ static_cast<float>(3.1415926) };
int debugcount{ 0 };

int main()
{
	//Read in dataset from CSV text file and store in vector of nanowires
	filename = "example_dataset.txt";
	nanowire_set data{ filename };

	nanonode_ptr nanoroot{ makenanoroot(data) };

	makenanotree(nanoroot, data);

	
	
	
	//Copy the vector of nanowires and translate and rotate this copy
	//nanowire_set copy{ data };
	//copy.translate(300000, 200000); //Translate the data by dx = 0.3mm and dy = 0.2mm
	//copy.rotate(50); //Rotate by 30 degrees

	//nameofwritefile(); copy.writetofile(filename);
	
	//Construct a grid out of the data and the copy of the data
	//int sqsize{ 250000 };

	//int i{ 3 }, j{ 17 }, size{ 10000 };
	//std::vector<square_ptr> v;
	//v.push_back(square_ptr(new square(i, j, size, copy)));
	//std::cout << std::endl << v[0]->getx()<< std::endl;

	////Go through the original set of nanowires and construct quads and gemoetric hash codes for the nanowires
	////Store hash codes in a map (kd tree for faster look up if have time)
	/*std::map<quad, nanowire_set_ptr> datamap;
	int counter{ 0 };
	for (int k{ 0 }; k < 16; k++)
	{
		mapquads(data, sqsize, counter, datamap);
	}
	*/
	
	//datamap.begin()->second->print();
	//Construct quads in the copy and compute geometric hash codes

	//Look up nearest neighbour hash codes in map of hash codes

	//Determine if there is a matching quad independently from length/orien/area of nanowires

	//Transform the copy of nanowire set back to the original position


	std::cout << std::endl;
	system("PAUSE");
	return 0;
}