#include "lib/list.h"
#include <iostream>

int
main()
{
	//TESTES
	List a("A"), b("B");
	a.randomFill(50,10);
	b.randomFill(50,5);
	a.show();
	b.show();
	a.concat(b);
	a.show();
	a.sort();
	a.show();
	return 0;
}
