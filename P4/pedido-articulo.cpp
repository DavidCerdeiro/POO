#include "pedido-articulo.hpp"
using namespace std;
//Clase LineaPedido
//Constructor
LineaPedido::LineaPedido(double p, unsigned c): precio(p), cant(c) {};

//Inserción en flujo LineaPedido
std::ostream& operator <<(std::ostream& os, const LineaPedido& l){
	locale::global(locale(""));
	os << fixed << setprecision(2) << l.precio_venta() << " €\t" << l.cantidad();
	return os;
}
//Clases de ordenación
bool OrdenaArticulos::operator()(const Articulo* a1, const Articulo* a2) const noexcept{
	return a1->referencia() < a2->referencia();
};
bool OrdenaPedidos::operator()(const Pedido* p1, const Pedido* p2) const noexcept{
	return p1->numero() < p2->numero();
};
//Clase Pedido-Articulo
//Metodos de asociacion
void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double pr, unsigned c){
	//Insertamos en el diccionario
	pa[&p].insert(make_pair(&a, LineaPedido(pr, c)));
	ap[&a].insert(make_pair(&p, LineaPedido(pr, c)));
};
void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double pr, unsigned c){
	//Llamamos a la otra función
	pedir(p, a, pr, c);
};
//Observadores
Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(const Pedido& p) const noexcept{
	auto x = pa.find((Pedido*)&p);
	//Comprobamos que el pedido esté
	if( x != pa.end()){
		return x->second;
	}else{
		return ItemsPedido{};
	};
};
Pedido_Articulo::Pedidos Pedido_Articulo::ventas(const Articulo& a) const noexcept{
	auto x = ap.find((Articulo*)&a);
	//Comprobamos que el articulo esté
	if( x != ap.end()){
		return x->second;
	}else{
		return Pedidos{};
	};
};

//Funciones mostrar
void Pedido_Articulo::mostrarDetallePedidos(std::ostream &os) const noexcept{
	double total = 0;
	for(auto& p:pa){
		os << "Pedido núm. " << p.first->numero() << std::endl;
		os << "Cliente: " << p.first->tarjeta()->titular()->id() << "\tFecha: " << p.first->fecha() << std::endl;
		os << detalle(*p.first);
		//Vamos calculando el total
		total += p.first->total();
	}
	os << std::endl << "TOTAL VENTAS " << total << " €" << std::endl;
}
void Pedido_Articulo::mostrarVentasArticulos(std::ostream &os) const noexcept{
	for(auto& a:ap){
		os << "Ventas de " << "[" << a.first->referencia() << "] " << a.first->titulo() << std::endl;
		os << ventas(*a.first);
	};
}

//Operadores de inserción de flujo
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido &ip){
	double total = 0;
	os << " PVP\tCantidad\tArtículo"<<std::endl;
	os << std::setfill('=') << std::setw(75) << " " <<std::endl;
	//Mostramos todos los artículos
	for(auto& item:ip){
		total+=(item.second.precio_venta() * item.second.cantidad());
		os << item.second << "\t\t";
		os << "[" << item.first->referencia() << "]" <<item.first->titulo() << std::endl;
	};
	os << std::setfill('=') << std::setw(75) << " " <<std::endl;
	os << "Total\t" << total << " €" << std::endl;
	return os;
};

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& p){
	double total = 0;
	int cant = 0;
	os << "[Pedidos: " << p.size() << "]" <<std::endl;
	os << std::setfill('=') << std::setw(75) << " " <<std::endl;
	os << " PVP\tCantidad\tFecha"<<std::endl;
	os << std::setfill('=') << std::setw(75) << " " <<std::endl;
	//Mostramos todos los pedidos
	for(auto item:p){
		total+=(item.second.precio_venta() * item.second.cantidad());
		cant+= item.second.cantidad();
		os << item.second << "\t\t" << item.first->fecha() <<std::endl;
	};
	os << std::setfill('=') << std::setw(75) << " " <<std::endl;
	os << total << " €\t" << cant << std::endl;
	return os;
}
