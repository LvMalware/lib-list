#include "lib/list.h"
#include <iostream>

int
main()
{
	//TESTES
	List a("A"), b("B"), c("C");
	a.randomFill(50,10);
	b.randomFill(50,5);
	
	a.show();
	b.show();

	c = a; //C esta sendo destruindo depois do operador = (WTF????????)
	c.show();
	
	return 0;
}
