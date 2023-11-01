#ifndef _USUARIO_PEDIDO_HPP_
#define _USUARIO_PEDIDO_HPP_

#include <set>
#include <map>

class Usuario;
class Pedido;

class Usuario_Pedido{
	public:
		typedef std::set<Pedido*> Pedidos;
		//Asociaciones
		void asocia(Usuario& u, Pedido& p);
		void asocia(Pedido& p, Usuario& u);
		//Observadores
		Pedidos pedidos(const Usuario& u) const noexcept;
		const Usuario* cliente(const Pedido& u) noexcept;
		
	private:
		typedef std::map<Usuario*, Pedidos> UsuPed;
		typedef std::map<Pedido*, Usuario*> PedUsu;
		UsuPed up;
		PedUsu pu;
};
#endif
