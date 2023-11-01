#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_
#include<iostream>
#include<locale>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include<set>
#include<iomanip>
class Autor{
	public:
		//Constructor
		Autor(const Cadena& n, const Cadena& a, const Cadena& d);
		
		//Observadores
		inline const Cadena& nombre() const noexcept { return nom; };
		inline const Cadena& direccion() const noexcept { return dir; };
		inline const Cadena& apellidos() const noexcept { return apell; };
	private:
		Cadena nom;
		Cadena apell;
		Cadena dir;
};

class Articulo{
	public:
		typedef std::set<Autor*> Autores;
		//Constructor
		Articulo(const Autores& a, const Cadena& c, const Cadena& t, const Fecha& f, double p, size_t u=0);
		//Observadores
		inline const Cadena& referencia() const noexcept{ return cod_ref; };
		inline const Cadena& titulo() const noexcept { return titu; };
		inline const Fecha& f_publi() const noexcept { return f_publ; };
		inline double precio() const noexcept { return coste; };
		inline size_t stock() const noexcept { return unidades; };
		inline const Autores& autores() const noexcept { return auts; };
		//Modificadores
		inline double& precio() noexcept { return coste; };
		inline size_t& stock() noexcept{ return unidades; };
		//Clase Autores vacios
		class Autores_vacios{};
		//Virtuales
		virtual void impresion_especifica(std::ostream& os) const = 0;
		virtual ~Articulo(){};
	private:
		const Cadena cod_ref;
		const Cadena titu;
		const Fecha f_publ;
		double coste;
		size_t unidades;
		const Autores auts;
		
};

class LibroDigital: public Articulo{
	public: 
		//Constructor
		LibroDigital(const Autores& auts, const Cadena& r, const Cadena& t, const Fecha& f, double p, const Fecha& f_exp);
		
		//Observador
		inline const Fecha& f_expir() const noexcept { return f_expir_; };
		
		//Impresión de libro digital
		void impresion_especifica(std::ostream& os) const;
	private:
		const Fecha f_expir_;
};

class ArticuloAlmacenable: public Articulo{
	public:
		//Constructor
		ArticuloAlmacenable(const Autores& auts, const Cadena& r, const Cadena& t, const Fecha& f, double p, size_t s = 0);
		
		//Observador
		size_t stock() const noexcept { return stock_; };
		
		//Modficador
		size_t& stock() noexcept { return stock_; };
	protected:
		size_t stock_;
};

class Libro: public ArticuloAlmacenable{
	public:
		//Constructor
		Libro(const Autores& auts, const Cadena& r, const Cadena& t, const Fecha& f, double p, size_t pags, size_t s = 0);
		
		//Observador
		inline size_t n_pag() const noexcept{ return n_pag_; };
		
		//Impresión de Libro
		void impresion_especifica(std::ostream& os) const;	
	private:
		const size_t n_pag_;
};

class Revista: public ArticuloAlmacenable{
	public:
		//Constructor
		Revista(const Autores& auts, const Cadena& r, const Cadena& t, const Fecha& f, double p, int n, int d, size_t s = 0);
		
		//Observadores
		inline int numero() const noexcept{ return numero_; };
		inline int periodicidad() const noexcept{ return periodicidad_; };
		
		//Impresión de Revista
		void impresion_especifica(std::ostream& os) const;
		
	private:
		const int numero_;
		const int periodicidad_;
	

};
//Operador de inserción de flujo de artículos
std::ostream& operator <<(std::ostream& os, const Articulo& art);
#endif
