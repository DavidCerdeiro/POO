# POO
Este proyecto se trata de las prácticas de la asignatura de Programación Orientada a Objetos de la Universidad de Cádiz, en el cual se nos plantea el siguiente problema:

Una librería desea ofrecer su catálogo de libros y revistas a la venta por Internet. Para ello, se nos ha solicitado el desarrollo de una librería virtual que más adelante se utilizará para construir una aplicación Web. La librería virtual debe ser capaz de gestionar los pedidos y el carro de la compra, así como el catálogo en general. En lo que sigue, se describen casos de uso típicos, con funcionalidades que deberán implementarse., los cuales, son los siguientes:

## Caso de uso 1
De cada usuario se debe guardar su nombre y apellidos, así como su dirección postal. El usuario elegirá un nombre de usuario que debe ser único, y una contraseña que debe poseer cierta longitud mínima predefinida y estar compuesta por letras y números. Se deberá guardar información de una o más tarjetas de crédito que el usuario podrá elegir para pagar los diferentes pedidos que realice. De las tarjetas se guardará su tipo, número, titular (según aparece en la tarjeta), y fecha de expiración (mes/año).
## Caso de uso 2
Cada cuenta de usuario tiene asociada una cesta o «carro de la compra virtual», en el que el usuario puede ir añadiendo artículos que desea comprar. Este puede adquirir varias unidades de un mismo artículo, especificándolo al añadirlo al carro. En este punto, no se comprobarán las existencias de dichos artículos, pudiéndose añadir cuantas unidades se desee.

### Diagrama de clases de los casos de uso 1 y 2

## Caso de uso 3
#### Facturación de la compra a partir de los contenidos del carro
Cuando el usuario pasa a facturar la compra (checkout), el carro «se vacía» y se genera un pedido. El usuario deberá elegir la tarjeta de crédito con la que pagará el pedido. Se guardará además la fecha del pedido. En este momento se asocia el pedido con la tarjeta de crédito y se actualizan las existencias disponibles de cada artículo. Es decir, si bien se puede ir añadiendo al carro lo que se desee, para finalizar la compra se han de comprobar y ajustar las existencias. En caso de que no haya suficientes existencias de algún producto, se debe generar un error y vaciar el carro, dejando sin efecto la compra.
#### Listado del histórico de compras
Se permitirá listar todos los pedidos realizados hasta la fecha, ordenados y agrupados por nombre de artículo o fecha de compra, a elección del usuario, incluyendo la suma total de los importes de venta, bien sea por artículo o por fecha, según se elija. Nótese que debe contemplarse el hecho de que los precios de venta de los artículos pueden ser diferentes de sus precios actuales.
### Diagrama de clases del caso de uso 3
### Caso de uso 4
Se pueden añadir al catálogo tres tipos de artículos: libros, revistas y libros digitales. Todos ellos tienen un código de referencia interno, un precio actual, un título y una fecha de publicación, pero solo de los libros y revistas hay que almacenar el número de artículos disponibles (sus existencias o stock), ya que los libros digitales se distribuyen mediante su descarga a través de Internet. De todos los artículos también se guardan los autores, que puede ser uno o varios, y que se emplearán como criterio de búsqueda. Los libros digitales tienen además una fecha de expiración en la que dejan de venderse, ya que se consideran obsoletos. De los libros se almacena el número de páginas, y de las revistas, su número y periodicidad.
### Diagrama de clases del caso de uso 4

Para esto, aparte de las clases indicadas en los casos de uso, que se declaran en *P4*, en *P1* se definen las siguientes clases:
### Clase Cadena
Se trata de hacer una clase general para trabajar con cadenas de caracteres (char), como una paupérrima imitación de std::string de la biblioteca estándar, por defecto, al definir un objeto de esta se nos creará con la fecha actual del sistema. En resumen, cuenta con operadores de asignación, concatenación, subcadena, operadores de índice y se puede trabajar con ella mediante iteradores.
### Clase Fecha
Nos permite trabajar  con fechas en español mientras sea compredida entre 1902 y 2037, por defecto, al definir un objeto de esta se nos creará con la fecha actual del sistema. En resumen, cuenta con operadores para sumar y resta días a una fecha, operadores de inserción y extracción de flujo y conversión a una cadena de formato "DIASEM DD de MES de AAAA", donde DIASEM es el nombre del día de la semana en español, DD es el día del mes con 1 o 2 dígitos, MES es el nombre del mes en español y AAAA es el año expresado con 4 dígitos. 
