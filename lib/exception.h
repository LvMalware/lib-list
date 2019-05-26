#ifndef _EXCEPTION_H
#define _EXCEPTION_H 1

#include <string>

class Exceptions //Classe utilizada para representar excessoes
{
private: //Atributos privados
	std::string msg;
	std::string filename;
	int line, column;
public: //Metodos publicos
	Exceptions(const char *smsg, const char* sfilename, int iline, int icolumn);
	void Msg();
};

#endif