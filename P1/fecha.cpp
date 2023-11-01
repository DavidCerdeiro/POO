#include "fecha.hpp"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <locale.h>
using namespace std;
void Fecha::dia_actual(int &dia, int &mes, int &anno){
	//Obtenemos día, mes y año en el que nos encontramos
	std::time_t tiempo_calendario = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
	dia = tiempo_descompuesto->tm_mday;
	mes = tiempo_descompuesto->tm_mon + 1;
	anno = tiempo_descompuesto->tm_year + 1900;
};

//Constructor
Fecha::Fecha(int d, int m, int a): dia_(d), mes_(m), anno_(a){
	int dd, mm, aa;
	dia_actual(dd, mm, aa);
	//En caso de que sea 0, le asignamos la fecha actual
	if(dia_==0){
		dia_= dd;
	};
	if(mes_==0){
		mes_= mm;
	};
	if(anno_==0){
		anno_= aa;
	};
	//Comprobamos que la fecha sea correcta
	fecha_correcta(dia_, mes_, anno_);
};

//Constructor a partir de una cadena
Fecha:: Fecha(const char* fecha){
	int d, m, a, n_conv;
	n_conv = sscanf(fecha, "%d/%d/%d", &d, &m, &a);
	//En caso de que no sea el formato correcto, se lanza la excepción
	if(n_conv != 3){
		throw Invalida("Formato de fecha incorrecto");
	};
	int dd, mm, aa;
	dia_actual(dd, mm, aa);
	dia_ = d;
	mes_ = m;
	anno_ = a;
	//En caso de que sea 0, le asignamos la fecha actual
	if(dia_==0){
		dia_= dd;
	};
	if(mes_==0){
		mes_= mm;
	};
	if(anno_==0){
		anno_= aa;
	};
	//Comprobamos que la fecha sea correcta
	fecha_correcta(dia_, mes_, anno_);
};

//Comprobador de que la fecha sea correcta
void Fecha::fecha_correcta(int dia, int mes, int anno){
	//Comprobamos el año
	if(anno<Fecha::AnnoMinimo || anno>Fecha::AnnoMaximo){
		throw Invalida("anno no valido");
	};
	//Comprobamos que los meses sean correctos
	if(mes<1 || mes>12){
		throw Invalida("mes no valido");
	};
	//Dia superior a 0
	if(dia<1){
		throw Invalida("dia no valido");
	};
	//Febrero en año bisiesto
	if(anno % 4 == 0 && (anno % 400 == 0 || anno % 100 != 0)){
		if(mes==2 && dia>29){
			throw Invalida("Dia superior al maximo del mes");
		};
	}else{
		//Febrero en año no bisiesto
		if(mes == 2 && dia>28){
			throw Invalida("Dia superior al maximo del mes");
		};
	};
	//Comprobaciones del resto de meses
	if((mes==1 || mes == 3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) && dia>31){
		throw Invalida("dia no valido");
	};
	if((mes==4 || mes==6 || mes==9 || mes==11) && dia>30){
		throw Invalida("dia no valido");
	};
};

//Operadores
Fecha& Fecha::operator +=(int n){		
	tm fecha{};
	fecha.tm_year=anno_-1900;
	fecha.tm_mon=mes_-1;
	fecha.tm_mday=dia_+n;
	mktime(&fecha);
	anno_=fecha.tm_year+1900;
	mes_=fecha.tm_mon+1;
	dia_=fecha.tm_mday;
	fecha_correcta(dia_, mes_, anno_);
	return *this;
};
Fecha& Fecha::operator -=(int n){
	return *this+=-n;
};
Fecha& Fecha::operator ++(){
	return *this+=1;
};
Fecha Fecha::operator ++(int){
	Fecha f = *this;
	*this+=1;
	return f;
};
Fecha& Fecha::operator --(){
	return *this+=-1;
};
Fecha Fecha::operator --(int){
	Fecha f = *this;
	*this+= -1;
	return f;
};
Fecha Fecha::operator +(int i) const{
	Fecha copia(*this);
	return copia+=i;
};
Fecha Fecha::operator -(int i) const{
	Fecha copia(*this);
	return copia+=-i;
};

//Operadores booleanos
bool operator ==(const Fecha& f, const Fecha& f2){
	return(f.dia()==f2.dia() && f.mes()==f2.mes() && f.anno()==f2.anno());
};
bool operator !=(const Fecha& f, const Fecha& f2){
	return!(f==f2);
};
bool operator <(const Fecha& f, const Fecha& f2){
	if(f.anno() < f2.anno()){
		return true;
	}else{
		if(f.anno()>f2.anno()){
			return false;
		}else{
			if(f.mes() < f2.mes()){
				return true;
			}else{
				if(f.mes() < f2.mes()){
					return true;
				}else{
					if(f.mes() > f2.mes()){
						return false;
					}else{
						if(f.mes() > f2.mes()){
							return false;
						}else{
							if(f.dia()<f2.dia()){
								return true;
							}else{
								return false;
							};
						};
					};
				};
			};
		};
	};
};
bool operator >(const Fecha& f, const Fecha& f2){
	return (f2<f);
};
bool operator >=(const Fecha& f, const Fecha& f2){
	return !(f<f2);
};
bool operator <=(const Fecha& f, const Fecha& f2){
	return ((f<f2) || (f==f2));
};

//Conversor a const char*
const char* Fecha:: cadena() const{
	static char buffer[38];
 	setlocale(LC_ALL, "es_ES.UTF-8");
	//Creamos la estructura tm
	std::tm fecha = {};
	fecha.tm_year=anno_-1900;
	fecha.tm_mon=mes()-1;
	fecha.tm_mday=dia_;
	//Lo pasamos a time_t
	std::time_t t = std::mktime(&fecha);
	//Ahora sacamos la fecha en el formato que queremos
	strftime(buffer, 38, "%A %d de %B de %Y", localtime(&t));
	return buffer;
};

//Operador de inserción en flujo
std::ostream& operator<<(std::ostream& os, const Fecha& f) noexcept{
	os << f.cadena();
	return os;
};

//Operador de extracción de flujo
std::istream& operator>>(std::istream& is, Fecha& f){
	char fecha[11];
	is.getline(fecha, 11);
	try{
		f = fecha;
	}catch(Fecha::Invalida e){
		is.setstate(std::ios::failbit);
		throw e;
	};
	return is;
};

