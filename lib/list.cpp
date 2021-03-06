#include <iostream>
#include <stdlib.h>
#include "exception.h"
#include "list.h"

List::List(const char* lname) //Construtor da Classe (com parametro nome)
{
	//Inicializa atributos da classe

	name  = lname;
	count = 0;
	first = NULL;
}

List::List() //Construtor da Classe (com parametro nome)
{
	//Inicializa atributos da classe
	count = 0;
	first = NULL;
}

List::~List() //Destrutor da classe
{
	clear(); //Limpa todos os items alocados
}

List::Item*
List::getItemAt(int index) //Retorna um Item da Lista dado seu indice
{
	try { //Tratamento de excessoes
		if (index > count || count == 0 || index < 0){
	  		//Se o item nao estiver na lista, levanta-se uma excessao
			throw(Exceptions("indice requisitado esta fora do limite da lista", __FILE__, __LINE__, 0));
	  		//A execucao do bloco e interrompida aqui.
		}
		//Caso nenhuma exessao aconteca, a execucao continua aqui
		Item* elem = first;
		for (int i=0; i<index; i++) //Procura pelo Item na posicao index
			elem = elem->next;
		return elem; //retorna o item (um ponteiro para ele, na verdade)
	} catch (Exceptions e) {
		//Caso uma execao ocorra, sua mensagem sera exibida
		e.Msg();
	}
	return NULL;
}

TYPE&
List::getAt(int index) //Retorna o valor do dado guardado no Item dado seu indice
{
	return getItemAt(index)->data; //faz uso da funcao getItemAt para encontrar o item
}

void
List::insertAt(TYPE value, int index) //Insere um dado na posicao especificada
{
	if (index == 0){ //Se a posicao for 0, o item se torna o inicio da lista
		Item *item = new Item;
		item->data = value;
		item->next = first;
		first	   = item;
	} else { //Caso contrario, procura-se pelo item anterior a posicao desejada e insere o dado na frente dele
		Item *item = new Item;
		item->data = value;
		Item *back = getItemAt(index - 1);
		item->next = back->next;
		back->next = item;
	}
	count ++; //Incrementa o contador de tamanho da lista
}

void
List::removeAt(int index) //Remove um Item dado seu indice
{
	try { //Tratamento de excessoes
		if (index > count || count == 0 || index < 0){
	  		//Se o item nao estiver na lista, levanta-se uma excecao
			throw(Exceptions("indice requisitado esta fora do limite da lista", __FILE__, __LINE__, 0));
	  		//A execucao do bloco e interrompida aqui.
		}
		//Se nenhum excessao e levantada, a execucao continua aqui
		if (index == 0){
			//Deleta o item do inicio da lista
			Item *rmv = first;
			first = rmv->next;
			delete rmv;
		} else {
			//Procura pelo item anterior ao que se deseja remover e o faz apontar para o posterior
			Item *back = getItemAt(index-1);
			Item *remv = back->next;
			back->next = remv->next;
			delete remv;
		}
		count -- ; //Decrementa o tamanho da lista
	} catch (Exceptions e){
		//Caso uma execao ocorra, sua mensagem sera exibida
		e.Msg();
	}
}

void
List::clear() //Limpa a lista, desalocando todos os Items da memoria
{
	Item *start, *current = first;
	while (current){ //Continua ate que um ponteiro nulo seja encontrado
		start = current->next;
		delete current;
		current = start;
	}
	first = NULL;
	count = 0;
}

std::string
List::getName() //Retorna o nome da lista
{
	return name;
}

void
List::setName(const char* nname) //Define um nome para a lista
{
	name = nname;
}

void
List::show() //Exibe os dados armazenados na lista
{
	std::cout << name << (name.empty()?"":" = ") << "[  ";
	Item *current = first;
	while (current){
		std::cout << current->data << ", ";
		current = current->next;
	}
	std::cout << "\b\b  ]"<<std::endl;
}

void
List::insert(TYPE value) //Insere um valor no fim da lista
{
	insertAt(value, count);
}

void
List::array(TYPE *v) //Copia todos os dados da lista para um vetor v
{
	if (!v){ //Caso o vetor seja nulo, ele sera inicializado
		v = array();
		return ;
	}
	Item *start = first;
	for (int i=0; i<count; i++){
		v[i] = start->data;
		start=start->next;
	}
}

TYPE*
List::array() //Retorna um vetor contento todos os elementos da lista (isto e, um ponteiro para o primeiro elemento do vetor)
{
	TYPE *vector = new TYPE[count];
	Item *start = first;
	for (int i=0; i<count; i++){
		vector[i] = start->data;
		start=start->next;
	}
	return vector;
}

int cmp1(const void *n1, const void *n2) //Funcao auxiliar utilizada para ordenar os dados de forma crescente
{
	int a = *((int *)n1),
		b = *((int *)n2);
	return a-b; //Retorna um valor positivo se a>b, zero se forem iguais e negativo e a<b
}

int cmp2(const void *n1, const void *n2) //Funcao auxiliar utilizada para odenar os dados de forma decrescente
{
	int a = *((int *)n1),
		b = *((int *)n2);
	return b-a;	//Retorna um valor negativo se a>b, zero se forem iguais e positivo e a<b
}

void
List::sort(bool asc) //Ordena a lista atraves da funcao qsort da biblioteca stdlib.h
{
	if (!count)
		return ;
	TYPE *vet = array(); //Copia todos os elementos da lista para um vetor (necessario pois a funcao qsort so ordena vetores)
	qsort(vet, count, sizeof(TYPE), (asc ? cmp1 : cmp2)); /*Chama a funcao qsort, se a lista deve ser ordenada de forma crescente (asc=true)
		entao a funcao cmp1 e utilizada, caso contrario utiliza-se cmp2
	*/
	Item *start = first;
	for (int i=0; i<count; i++){ //Copia cada dado do vetor de volta para a lista
		start->data = vet[i];
		start = start->next;
	}
	delete[] vet; //Desaloca a memoria utilizada pelo vetor
}

bool
List::empty(){ //Verifica se a lista esta vazia
	return count == 0;
}
void
randomize(){ //Esta funcao redefine a semente utilizada para gerar numeros aleatorios
	static bool alreadyDone = false; //Esta variavel indica se isto ja foi feito por essa mesma instancia
	if (!alreadyDone){ //Garante que a semente so sera redefinida uma vez por cada instancia de List
		srand(time(NULL));
		alreadyDone = true;
	}
}
void
List::randomFill(int max, int length) //Adiciona length Items a lista, contendo valores pseudo-aleatorios
{
	randomize(); //Redefine a semente para geracao dos numeros
	for (int i=0; i<length; i++)
		insert(rand()%max); //insere na lista
}

void
List::concat(const List &list) //Concatena uma lista a essa, copiando cada elemento para o final dela
{
	Item *item = list.first;
	while (item){
		insert(item->data);
		item = item->next;
	}
}

List
List::operator+(const List &list) //Sobrecarga do operador +, para concatenacao de listas
{
	List r; //Cria uma nova instancia de List
	r.concat(*this); //Copia cada elemento desta lista para a nova instancia
	r.concat(list); // ------------------- da lista list ------------------
	return r; //Retorna a lista resultante
}

List&
List::operator=(const List &list) //Sobrecarga do operador = para atribuicao de listas
{
	
	clear(); //Limpa a lista
	//concat(list); //Copia cada elemento da lista que esta sendo atribuida a esta
	Item *item = list.first;
	while (item){
		insert(item->data);
		item = item->next;
	}
	return *this; //Retorna esta lista
}
int
List::getCount() //Retorna o numero de elementos da lista
{
	return count;
}
TYPE&
List::operator[](int index) //Sobrecarga do operador [], tornando a lista indexavel
{
	return getAt(index);
}

std::string
List::toString() //Retorna uma string que representa a lista
{
	std::string list;
	if (!name.empty()) //Coloca o nome da lista caso este nao seja vazio
		list = name + " = ";
	list +="[  ";
	Item *i=first;
	while (i){
		list += std::to_string(i->data);
		if (i->next)
			list += ", ";
		i = i->next;
	}
	list += "  ]";
	return list;
}

List
List::operator<<(int n) //Desloca os elementos da lista n posicoes a esquerda
{
	List l;
	Item *start, *end;
	end = start = getItemAt(n%count); //Pega o n-esimo elemento da lista (imagine-a sendo circular)
	while (start){			//Enquanto o ponteiro nao for nulo (antes do fim da lista)
		l.insert(start->data); //Adiciona na lista l
		start=start->next; //Proximo elemento
	}
	start=first; //Comecando o primeiro elemento da lista
	while (start != end){ //Enquanto nao chegar ao n-esimo elemento
		l.insert(start->data);  //Adiciona o dado na lista l
		start=start->next;	//Proximo elemento
	}
	return l;
}