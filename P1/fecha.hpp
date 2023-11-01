#ifndef FECHA_HPP_
#define FECHA_HPP_
#include<ostream>
class Fecha{
	public:
	//Clase Inválida
	class Invalida{
		public:
			Invalida(const char* cadena):cad(cadena){};
			const char* por_que() const {return cad;};
		private:
			const char* cad;
	};
	//Constructores
	explicit Fecha(int d=0, int m=0, int a=0);
	Fecha(const char* fecha);
	//De copia y el operador de asignación sean por defecto
	Fecha(const Fecha& f) = default;
	Fecha& operator =(const Fecha& f) = default;
	//Conversor a const char*
	const char* cadena() const;
	//Observadores
	inline int dia() const noexcept{ return dia_;};
	inline int mes() const noexcept{return mes_;};
	inline int anno() const noexcept{return anno_;};
	//Operadores
	Fecha& operator +=(int);
	Fecha& operator -=(int);
	Fecha& operator ++();
	Fecha operator ++(int);
	Fecha& operator--();
	Fecha operator--(int);
	Fecha operator +(int i) const;
	Fecha operator -(int i) const;
	//Constantes para año mínimo y máximo
	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;
	private:
	int dia_, mes_, anno_;
	//Funciones auxiliares
	void fecha_correcta(int dia, int mes, int anno);
	void dia_actual(int &dia, int &mes, int &anno);
};
	//Operadores aritméticos
	
	//Operadores lógicos
	bool operator ==(const Fecha& f, const Fecha& f2);
	bool operator !=(const Fecha& f, const Fecha& f2);
	bool operator >=(const Fecha& f, const Fecha& f2);
	bool operator <=(const Fecha& f, const Fecha& f2);
	bool operator >(const Fecha& f, const Fecha& f2);
	bool operator <(const Fecha& f, const Fecha& f2);
	//Operadores de inserción y extracción de flujo
	std::ostream& operator<<(std::ostream& os, const Fecha& f) noexcept;
	std::istream& operator>>(std::istream& is, Fecha& f);
	
#endif
