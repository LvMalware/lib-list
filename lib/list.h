#ifndef _LIST_H

#define _LIST_H 1

#include <string>
#include <iostream>

typedef int TYPE; //Definição de TYPE como int, indica o tipo que a lista ira guardar

class List
{
private: //Metodos e atributos privados
	struct Item
	{
		TYPE data;
		Item *next;
	};
	Item *first;
	int count;
	std::string name;
	Item* getItemAt(int index);
public: //Metodos publicos
	List(const char* lname);
	List();
	~List();
	TYPE& getAt(int index);
	void insertAt(TYPE value, int index);
	void insert(TYPE value);
	void removeAt(int index);
	void clear();
	std::string getName();
	int getCount();
	void setName(const char* nname);
	void show();
	void array(TYPE *v);
	TYPE *array();
	void sort(bool asc = true);
	bool empty();
	void randomFill(int max, int length);
	void concat(const List &list);
	List operator+(const List &list);
	List &operator=(const List &list);
	TYPE& operator[](int index);
	std::string toString();
	List operator<<(int n);
};

#endif
