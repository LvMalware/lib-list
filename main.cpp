#include "lib/list.h"
#include <iostream>
using std::cout;
using std::endl;

std::ostream&
operator<<(std::ostream &output, List &list) //Sobrecarga do operador << para compatibilidade com std::cout
{
	output << list.toString();
	return output;
}

int
main()
{
	//TESTES
	List a("A"), b("B"), c("C");
	a.randomFill(50,10);
	b.randomFill(50,5);
	
	a.show();
	b.show();

	c = a<<2;
	c.show();
	
	return 0;
}
