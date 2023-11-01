#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_
#include<iostream>
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<cstdlib>
#include<unistd.h>
#include<random>
#include<cstring>

class Numero;
class Tarjeta;

class Clave{
	public:
		//Tipo Razon
		enum Razon {CORTA, ERROR_CRYPT};
		//Constructor
		Clave(const char* c);
		//Observador
		inline Cadena clave() const noexcept{ return contra; };
		//Comparador
		bool verifica(const char* c) const;
		//Clase Incorrecta
		class Incorrecta{
			public:
				Incorrecta(Razon raz):r(raz){};
				Razon razon() const{return r;};
			private:
				Razon r;
		
		};
	private:
		Cadena contra;
};

class Usuario{
	public:
		//Tipos Tarjetas y Articulos
		typedef std::map<Numero, Tarjeta*> Tarjetas;
		typedef std::unordered_map<Articulo*, unsigned int> Articulos;
		//Constructor
		Usuario(const Cadena& i, const Cadena& n, const Cadena& a, const Cadena& d, const Clave& c);
		//Evitamos la copia de un usuario a otro así como  la asginación
		Usuario(const Usuario& u) = delete;
		Usuario& operator =(const Usuario& u) = delete;
		//Observadores
		inline const Cadena& id() const noexcept{ return identificador; };
		inline const Cadena& nombre() const noexcept{ return nom; };
		inline const Cadena& apellidos() const noexcept{ return apell; };
		inline const Cadena& direccion() const noexcept{ return direc; };
		inline const Tarjetas& tarjetas() const noexcept{ return ts; };
		inline const Articulos& compra() const noexcept{ return arts; };
		inline size_t n_articulos() const noexcept{ return arts.size(); };
		//Destructor
		~Usuario();
		//Metodos modificadores de las relaciones con tarjetas
		void es_titular_de(const Tarjeta& t);
		void no_es_titular_de(Tarjeta& t);
		//Metodos modificadores de las relaciones con articulos
		void compra(const Articulo& art, size_t cantidad=1);
		void vaciar_carro();
		//Para poder imprimir la clave, el operador de insercion ha de ser un método amigo
		friend std::ostream& operator <<(std::ostream& os, const Usuario& u) noexcept;
		//Clase Id_duplicado
		class Id_duplicado{
			public:
				Id_duplicado(const Cadena& i):id(i){};
				const Cadena& idd() const noexcept{ return id;};
			private:
				Cadena id;
		};
	private:
		const Cadena identificador;
		const Cadena nom;
		const Cadena apell;
		const Cadena direc;
		Tarjetas ts;
		Articulos arts;
		Clave contra;
		//Con el set vamos a almacenar todos los usuarios
		static std::unordered_set<Cadena> usuarios_;
};
//Funcion mostrar_carro()
void mostrar_carro(std::ostream& os, const Usuario& u) noexcept;
#endif
