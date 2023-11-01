#include "articulo.hpp"
#include <iomanip>
//Clase Articulo
//Constructor
Articulo::Articulo(const Autores& a, const Cadena& c, const Cadena& t, const Fecha& f, double p, size_t u): cod_ref(c), titu(t), f_publ(f), coste(p), unidades(u), auts(a){
	//Comprobamos que tenga autores
	if(a.empty()){
		throw Articulo::Autores_vacios{};
	};
};

//Clase Autor
//Constructor
Autor::Autor(const Cadena& n, const Cadena& a, const Cadena& d): nom(n), apell(a), dir(d){};

//Clase Libro Digital
//Constructor
LibroDigital::LibroDigital(const Autores& a, const Cadena& r, const Cadena& t, const Fecha& f, double p, const Fecha& f_exp): Articulo(a, r, t, f, p), f_expir_(f_exp){};
//Impresión específica
void LibroDigital::impresion_especifica(std::ostream& os) const{
	os << "A la venta hasta el " << f_expir_ <<".";
}

//Clase Articulo Almacenable
//Constructor
ArticuloAlmacenable::ArticuloAlmacenable(const Autores& auts, const Cadena& r, const Cadena& t, const Fecha& f, double p, size_t s): Articulo(auts, r, t, f, p), stock_(s){};

//Clase Libro
//Constructor
Libro::Libro(const Autores& auts, const Cadena& r, const Cadena& t, const Fecha& f, double p, size_t pags, size_t s): ArticuloAlmacenable(auts, r, t, f, p, s), n_pag_(pags){};

//Impresión específica
void Libro::impresion_especifica(std::ostream& os) const{
	os << n_pag_ <<" págs., " << stock_ <<" unidades.";
}

//Clase Revista
Revista::Revista(const Autores& auts, const Cadena& r, const Cadena& t, const Fecha& f, double p, int n, int d,  size_t s ): ArticuloAlmacenable(auts, r, t, f, p, s), numero_(n), periodicidad_(d){};
//Impresión específica
void Revista::impresion_especifica(std::ostream& os) const{
	os << "Número: "<<numero_<<", Periodicidad: "<<periodicidad_<<" días.\n";
	os << "\tPróximo número a partir de: "<< f_publi() + periodicidad_ << ".";
}

//Operador de inserción de flujo
std::ostream& operator <<(std::ostream& os, const Articulo& art){
	std::locale::global(std::locale(""));
	//Referencia y título
	os <<"["<<art.referencia()<<"] \""<<art.titulo()<<"\", de ";
	//Imprimimos los autores
	auto auts = art.autores().begin();
	os <<(*auts)->apellidos();
	while( ++auts != art.autores().end()){
		os <<", "<<(*auts)->apellidos();
	};
	//Año de publicación y precio
	os << ". "<<art.f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<art.precio()<<" €"<<std::endl<<"\t";
	//Impresión específica del objeto
	art.impresion_especifica(os);
	return os;
};
