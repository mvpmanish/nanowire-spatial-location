//cpp file to define functions in "quad.hpp"

#include "quad.hpp"

//Function to map quads of nanowires in a nanowire set
void mapquads(nanonode_ptr &root, grid &nanogrid, std::map<quad, nanowire_set_ptr> &hashmap)
{
	int maxsize{ static_cast<int>(pow(2,0.5)*((*nanogrid.it(0))->getsize())) };  //Max size of quads = sqrt(2)*square_size
	int minsize{ static_cast<int>(0.8*(*nanogrid.it(0))->getsize()) };  //Min size of quads

	//Loop over each grid cell
	for (int i{ 0 }; i < nanogrid.numbersq(); i++)
	{
		//Find nanowires close to the midpoint of the square cell with range of +/-(maxsize of quad)/2
		nanowire_set nanobox;
		int x{ (*nanogrid.it(i))->midpoint().first }, y{ (*nanogrid.it(i))->midpoint().second };
		int dx, dy;
		dx = dy = maxsize;
		root->rangesearch(nanobox, x, dx, y, dy);
		
		//Choose four random nanowires from close to the midpoint i.e. iterate randomly through nanobox
		//Generate a random number between 0 and (number of nanowires in box - 1)
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distr1(0, nanobox.getsize() - 1);
		int randno{ distr1(generator) };  //generates numbers
		nanowire_ptr a(move((*nanobox.it(randno))));
		nanobox.decrementsize();  //Decrement the size
		
		std::uniform_int_distribution<int> distr2(0, nanobox.getsize() - 1); randno = distr2(generator);  //generate number again as size of nanobox has changed
		nanowire_ptr b(move((*nanobox.it(randno))));
		nanobox.decrementsize();

		std::uniform_int_distribution<int> distr3(0, nanobox.getsize() - 1); randno = distr3(generator);  
		nanowire_ptr c(move((*nanobox.it(randno))));
		nanobox.decrementsize();
		
		std::uniform_int_distribution<int> distr4(0, nanobox.getsize() - 1); randno = distr4(generator);  
		nanowire_ptr d(move((*nanobox.it(randno))));
		nanobox.decrementsize();

		//Check for conditions for quad to be craeted:
		//A and B is pair with largest distance
		int Ax{ 0 }, Ay{ 0 }, Bx{ 0 }, By{ 0 }, Cx{ 0 }, Cy{ 0 }, Dx{ 0 }, Dy{ 0 };
		std::vector<int> v{ dist(a, b), dist(b, c), dist(c, d), dist(d, a), dist(a, c), dist(b, d) };
		int diameter{ *max_element(v.begin(), v.end()) };

		//Condition for quad to form: quad must have diameter < maxsize
		if (diameter < maxsize){ return; }

		//Quad must have a diameter > minsize
		if (diameter > minsize){ return; }

		if (diameter == v[0])  //A=a, B=b
		{
			Ax = a->getx(); Ay = a->gety();
			Bx = b->gety(); Bx = b->gety();
			Cx = c->getx(); Cy = c->gety();
			Dx = d->getx(); Dy = d->gety();
		}
		if (diameter == v[1])  //A=b, B=c
		{
			Ax = b->getx(); Ay = b->gety();
			Bx = c->getx(); By = c->gety();
			Cx = a->getx(); Cy = a->gety();
			Dx = d->getx(); Dy = d->gety();
		}
		if (diameter == v[2])  //A=c, B=d
		{
			Ax = c->getx(); Ay = c->gety();
			Bx = d->getx(); By = d->gety();
			Cx = a->getx(); Cy = a->gety();
			Dx = b->getx(); Dy = b->gety();
		}
		if (diameter == v[3])  //A=d, B=a
		{
			Ax = d->getx(); Ay = d->gety();
			Bx = a->getx(); By = a->gety();
			Cx = c->getx(); Cy = c->gety();
			Dx = b->getx(); Dy = b->gety();
		}
		if (diameter == v[4]) //A=a, B=c
		{
			Ax = a->getx(); Ay = a->gety();
			Bx = c->getx(); By = c->gety();
			Cx = b->getx(); Cy = b->gety();
			Dx = d->getx(); Dy = d->gety();
		}
		if (diameter == v[5]) //A=b, B=d
		{
			Ax = b->getx(); Ay = b->gety();
			Bx = d->getx(); By = d->gety();
			Cx = c->getx(); Cy = c->gety();
			Dx = a->getx(); Dy = a->gety();
		}
		//Check C and D are within the circle which has A & B's midpoint as its centre
		// (x-cx)^2+(y-cx)^2 <= r^2
		int midx{ (Ax + Bx) / 2 }, midy{ (Ay + By) / 2 }; //midpoint of A and B
		if (pow(Cx - midx, 2) + pow(Cy - midy, 2) > diameter / 2
			|| pow(Dx - midx, 2) + pow(Dy - midy, 2) > diameter / 2)
		{
			return;
		}

		//Make sure that Ax < Bx to keep quads consistent
		if (Ax > Bx) //if Ax !< Bx then swap A and B
		{
			std::swap(Ax, Bx); std::swap(Ay, By);
		}

		//Calculate x_c, y_c, x_d, y_d the coordinates of C and D with respect to A and B
		//Cast to float with (float)
		float x_c{ (float)(Cx - Ax) / (float)abs(Ax - Bx) }, x_d{ (float)(Dx - Ax) / (float)abs(Ax - Bx) };

		//Ensure that x_c+x_d <=1
		if (x_c + x_d > 1){ return; }


		float y_c{ (float)(Cy - Ay) / (float)abs(Ay - By) }, y_d{ (float)(Dy - Ay) / (float)abs(Ay - By) };

		//Reorder c and d so that x_c <= x_d
		if (x_c > x_d) //Switch variables if true
		{
			std::swap(x_c, x_d);
			std::swap(y_c, y_d);
		}

		nanowire_set tempset(a); tempset.add(b); tempset.add(c); tempset.add(d); //Make set out of the 4 nanowires
		quad tempquad(x_c, y_c, x_d, y_d);

		std::cout << "\nquad created";
		//Insert tempquad and ptr to tempset in map with quad as key
		hashmap.insert(std::make_pair(quad(tempquad), nanowire_set_ptr(new nanowire_set(std::move(tempset)))));
	}
}