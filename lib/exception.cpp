#include <iostream>
#include "exception.h"

Exceptions::Exceptions(const char *smsg, const char *sfilename, int iline, int icolumn){ //Construtor da classe
	msg 	   = smsg; //Mensagem de erro
	filename = sfilename; //Nome do arquivo onde o erro ocorreu
	line 	   = iline; //Linha onde o erro ocorreu
	column   = icolumn; //Coluna --//--
}

void
Exceptions::Msg() //Exibe a mensagem de erro
{
	std::cout << filename << ":" << line << ":" << column << ": " << msg << std::endl;
}