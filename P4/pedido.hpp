#ifndef _PEDIDO_HPP_
#define _PEDIDO_HPP_
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include <iomanip>
#include <iostream>

class Pedido_Articulo;
class Tarjeta;
class Usuario_Pedido;
class Pedido {
	public:
		//Constructor
		Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f = Fecha());
		//Observadores
		inline int numero() const noexcept {return id; };
		inline const Tarjeta* tarjeta() const noexcept {return tarjeta_; };
		inline const Fecha fecha() const noexcept {return fPedido; };
		inline double total() const noexcept {return imp; };
		inline static unsigned n_total_pedidos() noexcept {return npedidos; };
		//clase Vacio
		class Vacio
   		{
			public:
				Vacio(Usuario const* usu) : u(usu) {};
				Usuario const& usuario() const noexcept { return *u; }
			private:
				const Usuario* u;
		};
		//clase Impostor
		class Impostor{
			public:
				Impostor(Usuario* usu): u(usu) {};
				Usuario& usuario() const {return *u;};
			private:
				Usuario *u;
		};
		//clase SinStock
		class SinStock{
			public:
				SinStock(Articulo *art): a(art) {};
				Articulo& articulo() const { return *a;};
			private:
				Articulo *a;
		};
	private:
		int id;
		const Tarjeta* tarjeta_;
		Fecha fPedido;
		double imp;
		static int npedidos;
};
//Operador de inserción de flujo
std::ostream& operator <<(std::ostream& os, const Pedido& p);

#endif
