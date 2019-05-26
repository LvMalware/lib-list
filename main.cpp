#include "lib/list.h"
#include <iostream>

int
main()
{
	//TESTES
	List a("A");
	a.randomFill(50,10);
	a.show();
	std::cout << "------ SORT ------ "<<std::endl;
	a.sort(true);
	a.show();
	return 0;
}
