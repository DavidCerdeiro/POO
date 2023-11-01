#ifndef _PEDIDO_ARTICULO_HPP_
#define _PEDIDO_ARTICULO_HPP_
#include <iostream>
#include <iomanip>
#include <map>
#include "pedido.hpp"
#include "articulo.hpp"

class Pedido;

class LineaPedido{
	public:
		//Constructor
		explicit LineaPedido(double p, unsigned c = 1);
		//Observadores
		inline double precio_venta() const noexcept { return precio; };
		inline unsigned cantidad() const noexcept {return cant; };
	private:
		double precio;
		double cant;
};

//Operador de inserción en flujo
std::ostream& operator <<(std::ostream& os, const LineaPedido& l);
//Clases de ordenación
class OrdenaArticulos: public std::binary_function<Articulo*, Articulo*,bool>{
	public:
		bool operator()(const Articulo* a1, const Articulo* a2) const noexcept;
};
class OrdenaPedidos: public std::binary_function<Pedido*, Pedido*,bool>{
	public:
		bool operator()(const Pedido* p1, const Pedido* p2) const noexcept;
};

class Pedido_Articulo{
	public:
		//Tipos de la clase
		typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
		typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
		//Asociaciones
		void pedir(Pedido& p, Articulo& a, double pr, unsigned c = 1);
		void pedir(Articulo& a, Pedido& p, double pr, unsigned c = 1);
		//Observadores
		ItemsPedido detalle(const Pedido& p) const noexcept;
		Pedidos ventas(const Articulo& a) const noexcept;
		//Métodos mostrar
		void mostrarDetallePedidos(std::ostream& os) const noexcept;
		void mostrarVentasArticulos(std::ostream& os) const noexcept;
	private:
		//Diccionarios
		typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
		typedef std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;
		PedArt pa;
		ArtPed ap;
};
//Operadores de inserción de flujo
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& i);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& p);
#endif
