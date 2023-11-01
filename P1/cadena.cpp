#include "cadena.hpp"
#include<cstring>
#include<stdexcept>
using namespace std;
//Constructores
Cadena::Cadena(unsigned int n, char c): s_(new char[n+1]), tam_(n){
	for(unsigned int i=0; i<tam_; ++i){
		s_[i]=c;
	};
	s_[tam_] = '\0';
};

//De copia
Cadena::Cadena(const Cadena& c): s_(new char[c.length()+1]), tam_(c.length()){
	for(unsigned int i=0; i<c.length(); i++){
		s_[i]=c[i];
	};
	s_[tam_]='\0';
};

//De movimiento
Cadena::Cadena(Cadena&& c): s_(c.s_), tam_(c.tam_){
	c.tam_=0;
	c.s_ = new char[1];
	c.s_[0]='\0';
};

//De const char a Cadena
Cadena::Cadena(const char *c): s_(new char [strlen(c)+1]), tam_(strlen(c)){
	//Copiamos de la cadena const char* a s_
	strncpy(s_, c, tam_+1);
};

//Destructor
Cadena::~Cadena(){
	delete[] s_;
};

//Operadores
Cadena Cadena:: operator =(const Cadena &c){
	//Comprobamos que no sea la misma cadena
	if(this != &c){
		tam_=c.length();
		delete[] s_;
		s_ = new char[tam_+1];
		strcpy(s_, c.s_);
	};
	return *this;
};	
Cadena Cadena:: operator =(Cadena&& c){
	//Comprobamos que no sea la misma cadena
	if( this != &c){
		delete[] s_;
		s_=c.s_;
		tam_=c.tam_;
		c.tam_=0;
		c.s_ = new char[1];
		c.s_[0]='\0';
	};
	return *this;
}
Cadena Cadena::operator =(const char *c){
	tam_ = strlen(c);
	delete[] s_;
	s_ = new char[tam_+1];
	strcpy(s_, c);
	return *this;
}
//Operadores [] y at
char& Cadena::operator[](unsigned int i) const{
	return s_[i];
};
char& Cadena::operator[](unsigned int i){
	return s_[i];
};		
char& Cadena::at(unsigned int i) const{
	//Comprobamos que el índice sea correcto
	if(i <tam_){
		return s_[i];
	}else{
		throw std::out_of_range("Fuera de rango");
	};
};
char& Cadena::at(unsigned int i){
	//Comprobamos que el índice sea correcto
	if(i <tam_){
		return s_[i];
	}else{
		throw std::out_of_range("Fuera de rango");
	};
};
//Método substr
Cadena Cadena::substr (unsigned int indice, unsigned int tam) const{
	//Comprobamos que el índice sea correcto
	if(tam>(length()-indice) || (indice > tam_ - 1)){
		throw::std::out_of_range("Indice fuera de rango");
	};
	Cadena copia(tam);
	strncpy(copia.s_, s_ + indice, tam);
	copia[tam]='\0';
	return copia;
};

//Operador de suma y asignación
Cadena Cadena::operator +=(const Cadena c){
	char* aux = new char[tam_+1];
	strcpy(aux, s_);
	delete[] s_;
	tam_+=c.length();
	s_ = new char[tam_ + 1];
	strcpy(s_, aux);
	delete[] aux;
	strcat(s_, c.s_);
	return *this;
};

//Operador de suma de dos cadenas
Cadena operator +(const Cadena &c1, const Cadena &c2){
	Cadena copia(c1);
	return copia+=c2;
};

//Operadores lógicos
bool operator <(const Cadena &c1, const Cadena &c2) noexcept {
	if(c1.length() < c2.length() ){
		return true;
	}else{
		if(c1.length() > c2.length()){
			return false;
		}else{
			for(unsigned int i=0; i<c1.length() ; i++){
				if(c1[i]<c2[i]){
					return true;
				}else{
					if(c1[i]>c2[i]){
						return false;
					};
				};
			};
			return false;
		};
	};
};
bool operator >(const Cadena &c1, const Cadena &c2) noexcept{
	return (!(c1<=c2));
};
bool operator >=(const Cadena &c1, const Cadena &c2) noexcept{
	return (!(c1<c2));
};
bool operator <=(const Cadena &c1, const Cadena &c2) noexcept{
	return ((c1 < c2) || (c1==c2));
};
bool operator ==(const Cadena &c1, const Cadena &c2) noexcept{
	if(c1.length() != c2.length() ){
		return false;
	}else{
		for(unsigned int i=0; i<c1.length() ; i++){
			if(c1[i]<c2[i] || c1[i] > c2[i]){
				return false;
			};
		};
		return true;
	};
};
bool operator !=(const Cadena &c1, const Cadena &c2) noexcept{
	return (!(c1==c2));
};

//Operador de inserción de flujo
std::ostream& operator<<(std::ostream& os, const Cadena& c) noexcept{
	os << static_cast<const char*>(c);
	return os;
};

//Operador de extracción de flujo
std::istream& operator>>(std::istream& is, Cadena& cadena){
	char c[33] = "";
	is.width(33);
	is >> c;
	cadena = c;
	return is;
};

//Conversor a const char
Cadena::operator const char*() const{
	return (const char*)s_;
};
