#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

// ============ ESTRUCTURAS ============

struct Usuario {
    int idUsuario;
    string nombre;
    string correoElectronico;
    string contrasena;
    string direccion;
    string metodoDePago;
};

struct Producto {
    int idProducto;
    string nombre;
    string descripcion;
    double precio;
    int stock;
};

struct Comentarios {
    int idComentario;
    string producto;
    string usuario;
    string comentario;
    string fecha;
};

struct CarritoDeCompras {
    int idCarrito;
    int idUsuario;
    vector<Producto> productos;
    double subtotal;
    double impuestos;
};

struct OrdenDeCompra {
    int idOrden;
    vector<Producto> productos;
    double subtotal;
    double impuestos;
    double envio;
    double total;
};

struct Categoria {
    int idCategoria;
    string nombre;
};

// ============ VECTORES GLOBALES ============
vector<Usuario> usuarios;
vector<Producto> productos;
vector<Comentarios> comentarios;
vector<CarritoDeCompras> carritos;
vector<OrdenDeCompra> ordenes;
vector<Categoria> categorias;

// ============ FUNCIONES DE CARGA DE ARCHIVOS ============

void cargarUsuarios() {
    ifstream archivo("Usuarios.txt");
    if (!archivo.is_open()) {
        cout << "? Error: No se pudo abrir el archivo Usuarios.txt\n";
        return;
    }
    
    string linea;
    getline(archivo, linea); // Leer encabezado
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;
        Usuario usuario;
        
        getline(ss, token, ',');
        usuario.idUsuario = stoi(token);
        
        getline(ss, usuario.nombre, ',');
        getline(ss, usuario.correoElectronico, ',');
        getline(ss, usuario.contrasena, ',');
        getline(ss, usuario.direccion, ',');
        getline(ss, usuario.metodoDePago, ',');
        
        usuarios.push_back(usuario);
    }
    
    archivo.close();
    cout << "? Usuarios cargados: " << usuarios.size() << " registros.\n";
}

void cargarProductos() {
    ifstream archivo("Productos.txt");
    if (!archivo.is_open()) {
        cout << "? Error: No se pudo abrir el archivo Productos.txt\n";
        return;
    }
    
    string linea;
    getline(archivo, linea); // Leer encabezado
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;
        Producto producto;
        
        getline(ss, token, ',');
        producto.idProducto = stoi(token);
        
        getline(ss, producto.nombre, ',');
        getline(ss, producto.descripcion, ',');
        
        getline(ss, token, ',');
        producto.precio = stod(token);
        
        getline(ss, token, ',');
        producto.stock = stoi(token);
        
        productos.push_back(producto);
    }
    
    archivo.close();
    cout << "? Productos cargados: " << productos.size() << " registros.\n";
}

void cargarComentarios() {
    ifstream archivo("Comentarios.txt");
    if (!archivo.is_open()) {
        cout << "? Error: No se pudo abrir el archivo Comentarios.txt\n";
        return;
    }
    
    string linea;
    getline(archivo, linea); // Leer encabezado
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;
        Comentarios comentario;
        
        getline(ss, token, ',');
        comentario.idComentario = stoi(token);
        
        getline(ss, comentario.producto, ',');
        getline(ss, comentario.usuario, ',');
        getline(ss, comentario.comentario, ',');
        getline(ss, comentario.fecha, ',');
        
        comentarios.push_back(comentario);
    }
    
    archivo.close();
    cout << "? Comentarios cargados: " << comentarios.size() << " registros.\n";
}

// ============ FUNCIONES DE UTILIDAD ============

string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

int obtenerUltimoIdCarrito() {
    if (carritos.empty()) return 0;
    int maxId = 0;
    for (const auto& carrito : carritos) {
        if (carrito.idCarrito > maxId) maxId = carrito.idCarrito;
    }
    return maxId;
}

bool compararFechas(const string& fecha1, const string& fecha2) {
    // Convertir fechas YYYY-MM-DD a formato comparable YYYYMMDD
    string f1 = fecha1.substr(0,4) + fecha1.substr(5,2) + fecha1.substr(8,2);
    string f2 = fecha2.substr(0,4) + fecha2.substr(5,2) + fecha2.substr(8,2);
    return f1 >= f2;
}

void guardarCarritoEnArchivo(const CarritoDeCompras& carrito) {
    ofstream archivo("carrito_" + to_string(carrito.idUsuario) + ".txt");
    if (!archivo.is_open()) {
        cout << "? Error al crear archivo del carrito\n";
        return;
    }
    
    archivo << "ID Carrito: " << carrito.idCarrito << "\n";
    archivo << "ID Usuario: " << carrito.idUsuario << "\n";
    archivo << "Productos en el carrito:\n";
    archivo << "--------------------------------------------------------------------\n";
    
    for (const auto& producto : carrito.productos) {
        archivo << producto.nombre << " | Cantidad: " << producto.stock 
                << " | Precio: $" << fixed << setprecision(2) << producto.precio 
                << " | Subtotal: $" << fixed << setprecision(2) << (producto.precio * producto.stock) << "\n";
    }
    
    archivo << "--------------------------------------------------------------------\n";
    archivo << "Subtotal: $" << fixed << setprecision(2) << carrito.subtotal << "\n";
    archivo << "Impuestos (19%): $" << fixed << setprecision(2) << carrito.impuestos << "\n";
    archivo << "Total: $" << fixed << setprecision(2) << (carrito.subtotal + carrito.impuestos) << "\n";
    
    archivo.close();
    cout << "? Carrito guardado en archivo: carrito_" << carrito.idUsuario << ".txt\n";
}

// ============ NUEVAS FUNCIONES DE REPORTES ============

void mostrarProductosMenorStock() {
    cout << "\n+--------------------------------------------------------------------+\n";
    cout << "¦             5 PRODUCTOS CON MENOR STOCK (ASCENDENTE)              ¦\n";
    cout << "+--------------------------------------------------------------------+\n\n";
    
    // Crear copia de productos para ordenar
    vector<Producto> productosOrdenados = productos;
    
    // Ordenar por stock de forma ascendente
    sort(productosOrdenados.begin(), productosOrdenados.end(), 
         [](const Producto& a, const Producto& b) {
             return a.stock < b.stock;
         });
    
    cout << left << setw(12) << "idProducto" 
         << setw(30) << "Nombre" 
         << setw(10) << "Stock" << "\n";
    cout << "--------------------------------------------------------------------\n";
    
    int limite = min(5, (int)productosOrdenados.size());
    for (int i = 0; i < limite; i++) {
        cout << left << setw(12) << productosOrdenados[i].idProducto
             << setw(30) << productosOrdenados[i].nombre
             << setw(10) << productosOrdenados[i].stock << "\n";
    }
    
    cout << "--------------------------------------------------------------------\n";
    cout << "Total de productos mostrados: " << limite << "\n";
}

void mostrarComentariosPorFecha() {
    string fechaBuscada;
    
    cout << "\n+--------------------------------------------------------------------+\n";
    cout << "¦           CANTIDAD DE COMENTARIOS POR FECHA ESPECÍFICA            ¦\n";
    cout << "+--------------------------------------------------------------------+\n";
    
    cout << "\nIngrese fecha (formato YYYY-MM-DD): ";
    cin >> fechaBuscada;
    
    int contador = 0;
    
    // Contar comentarios en la fecha específica
    for (const auto& com : comentarios) {
        if (com.fecha == fechaBuscada) {
            contador++;
        }
    }
    
    cout << "\n-------------------------------------------------------------------\n";
    cout << "RESULTADO DE LA BÚSQUEDA:\n";
    cout << "-------------------------------------------------------------------\n\n";
    
    cout << "+--------------------------------------------------------+\n";
    cout << "¦  Fecha: " << fechaBuscada << string(40 - fechaBuscada.length(), ' ') << "¦\n";
    cout << "¦  Cantidad de comentarios: " << setw(24) << contador << "¦\n";
    cout << "+--------------------------------------------------------+\n";
    
    // Mostrar detalles de los comentarios si hay alguno
    if (contador > 0) {
        cout << "\nDetalles de los comentarios:\n";
        cout << "--------------------------------------------------------------------\n";
        for (const auto& com : comentarios) {
            if (com.fecha == fechaBuscada) {
                cout << "• " << com.usuario << " sobre " << com.producto << ": " 
                     << com.comentario << "\n";
            }
        }
    }
}

void mostrarPrecioMaximoMinimo() {
    cout << "\n+--------------------------------------------------------------------+\n";
    cout << "¦             PRECIO MÁXIMO Y MÍNIMO DE PRODUCTOS                   ¦\n";
    cout << "+--------------------------------------------------------------------+\n\n";
    
    if (productos.empty()) {
        cout << "No hay productos cargados.\n";
        return;
    }
    
    double precioMin = productos[0].precio;
    double precioMax = productos[0].precio;
    Producto productoMin = productos[0];
    Producto productoMax = productos[0];
    
    // Encontrar precios mínimo y máximo
    for (const auto& prod : productos) {
        if (prod.precio < precioMin) {
            precioMin = prod.precio;
            productoMin = prod;
        }
        if (prod.precio > precioMax) {
            precioMax = prod.precio;
            productoMax = prod;
        }
    }
    
    cout << "+--------------------------------------------------------------------+\n";
    cout << "¦  PRECIO MÍNIMO: $" << fixed << setprecision(2) << setw(10) << precioMin << "                          ¦\n";
    cout << "¦  Producto: " << left << setw(45) << productoMin.nombre << "¦\n";
    cout << "¦  ID: " << left << setw(49) << productoMin.idProducto << "¦\n";
    cout << "+--------------------------------------------------------------------¦\n";
    cout << "¦  PRECIO MÁXIMO: $" << fixed << setprecision(2) << setw(10) << precioMax << "                          ¦\n";
    cout << "¦  Producto: " << left << setw(45) << productoMax.nombre << "¦\n";
    cout << "¦  ID: " << left << setw(49) << productoMax.idProducto << "¦\n";
    cout << "+--------------------------------------------------------------------¦\n";
    cout << "¦  RANGO DE PRECIOS: $" << fixed << setprecision(2) << setw(10) << precioMax - precioMin << "                      ¦\n";
    cout << "¦  TOTAL PRODUCTOS: " << setw(35) << productos.size() << "¦\n";
    cout << "+--------------------------------------------------------------------+\n";
}

// ============ FUNCIÓN DE LOGIN ============

int iniciarSesion() {
    string correo, contrasena;
    
    cout << "\n+----------------------------------------+\n";
    cout << "¦        INICIO DE SESIÓN                ¦\n";
    cout << "+----------------------------------------+\n";
    
    cout << "\nCorreo electrónico: ";
    cin >> correo;
    cout << "Contraseña: ";
    cin >> contrasena;
    
    for (const auto& usuario : usuarios) {
        if (usuario.correoElectronico == correo && usuario.contrasena == contrasena) {
            cout << "\n+----------------------------------------+\n";
            cout << "¦  ? SESIÓN INICIADA EXITOSAMENTE       ¦\n";
            cout << "¦  Bienvenido: " << usuario.nombre << string(23 - usuario.nombre.length(), ' ') << "¦\n";
            cout << "+----------------------------------------+\n";
            return usuario.idUsuario;
        }
    }
    
    cout << "\n+----------------------------------------+\n";
    cout << "¦  ? USUARIO INVÁLIDO                    ¦\n";
    cout << "¦  Correo o contraseña incorrectos       ¦\n";
    cout << "+----------------------------------------+\n";
    
    return -1;
}

// ============ FUNCIONES DE LISTADO ============

void listarProductosBajoStock() {
    cout << "\n+--------------------------------------------------------------------+\n";
    cout << "¦        PRODUCTOS CON STOCK MENOR A 15 UNIDADES                    ¦\n";
    cout << "+--------------------------------------------------------------------+\n\n";
    
    cout << left << setw(5) << "ID" 
         << setw(25) << "Nombre" 
         << setw(15) << "Precio" 
         << setw(10) << "Stock" << "\n";
    cout << "--------------------------------------------------------------------\n";
    
    bool encontrado = false;
    int contador = 0;
    
    for (const auto& prod : productos) {
        if (prod.stock < 15) {
            cout << left << setw(5) << prod.idProducto
                 << setw(25) << prod.nombre
                 << "$" << fixed << setprecision(2) << setw(14) << prod.precio
                 << setw(10) << prod.stock << "\n";
            encontrado = true;
            contador++;
        }
    }
    
    cout << "--------------------------------------------------------------------\n";
    
    if (!encontrado) {
        cout << "No hay productos con stock menor a 15 unidades.\n";
    } else {
        cout << "Total de productos encontrados: " << contador << "\n";
    }
}

void listarComentariosPorFecha() {
    string fechaIngresada;
    
    cout << "\n+--------------------------------------------------------------------+\n";
    cout << "¦              COMENTARIOS FILTRADOS POR FECHA                       ¦\n";
    cout << "+--------------------------------------------------------------------+\n";
    
    cout << "\nIngrese fecha (formato YYYY-MM-DD): ";
    cin >> fechaIngresada;
    
    cout << "\n-------------------------------------------------------------------\n";
    cout << "Comentarios desde " << fechaIngresada << " en adelante:\n";
    cout << "-------------------------------------------------------------------\n\n";
    
    bool encontrado = false;
    int contador = 0;
    
    for (const auto& com : comentarios) {
        if (compararFechas(com.fecha, fechaIngresada)) {
            cout << "+-------------------------------------------------------------+\n";
            cout << "¦ Comentario #" << com.idComentario << "\n";
            cout << "+-------------------------------------------------------------¦\n";
            cout << "¦ Producto:    " << com.producto << "\n";
            cout << "¦ Usuario:     " << com.usuario << "\n";
            cout << "¦ Fecha:       " << com.fecha << "\n";
            cout << "¦ Comentario:  " << com.comentario << "\n";
            cout << "+-------------------------------------------------------------+\n\n";
            encontrado = true;
            contador++;
        }
    }
    
    if (!encontrado) {
        cout << "No se encontraron comentarios desde la fecha indicada.\n";
    } else {
        cout << "-------------------------------------------------------------------\n";
        cout << "Total de comentarios encontrados: " << contador << "\n";
        cout << "-------------------------------------------------------------------\n";
    }
}

void listarUsuarios() {
    cout << "\n+------------------------------------------------------------------------------+\n";
    cout << "¦                      LISTA DE USUARIOS REGISTRADOS                           ¦\n";
    cout << "+------------------------------------------------------------------------------+\n\n";
    
    cout << left << setw(5) << "ID" 
         << setw(25) << "NOMBRE" 
         << setw(30) << "Correo Electrónico"
         << setw(25) << "Dirección" 
         << setw(20) << "Método de Pago" << "\n";
    cout << "--------------------------------------------------------------------------------\n";
    
    for (const auto& usuario : usuarios) {
        cout << left << setw(5) << usuario.idUsuario
             << setw(25) << toUpperCase(usuario.nombre)
             << setw(30) << usuario.correoElectronico
             << setw(25) << usuario.direccion 
             << setw(20) << usuario.metodoDePago << "\n";
    }
    
    cout << "--------------------------------------------------------------------------------\n";
    cout << "Total de usuarios: " << usuarios.size() << "\n";
}

// ============ FUNCIONES DEL CARRITO ============

void adicionarProductoAlCarrito(int idUsuario) {
    cout << "\n+--------------------------------------------------------------------+\n";
    cout << "¦              ADICIONAR PRODUCTO AL CARRITO                         ¦\n";
    cout << "+--------------------------------------------------------------------+\n";
    
    // Mostrar productos disponibles
    cout << "\nProductos disponibles:\n";
    cout << left << setw(5) << "ID"
         << setw(25) << "Nombre"
         << setw(15) << "Precio"
         << setw(10) << "Stock" << "\n";
    cout << "--------------------------------------------------------------------\n";
    for (const auto& prod : productos) {
        if (prod.stock > 0) {
            cout << left << setw(5) << prod.idProducto
                 << setw(25) << prod.nombre
                 << "$" << fixed << setprecision(2) << setw(14) << prod.precio
                 << setw(10) << prod.stock << "\n";
        }
    }
    cout << "--------------------------------------------------------------------\n";
    
    int idProducto, cantidad;
    cout << "\n? Ingrese ID del producto (0 para cancelar): ";
    cin >> idProducto;
    
    if (idProducto == 0) {
        cout << "? Operación cancelada.\n";
        return;
    }
    
    cout << "? Ingrese cantidad: ";
    cin >> cantidad;
    
    if (cantidad <= 0) {
        cout << "? Cantidad inválida.\n";
        return;
    }
    
    // Buscar producto
    bool productoEncontrado = false;
    for (auto& prod : productos) {
        if (prod.idProducto == idProducto) {
            productoEncontrado = true;
            
            if (prod.stock >= cantidad) {
                // Buscar o crear carrito para este usuario
                bool carritoEncontrado = false;
                for (auto& carrito : carritos) {
                    if (carrito.idUsuario == idUsuario) {
                        carritoEncontrado = true;
                        
                        // Agregar producto al carrito
                        Producto prodCarrito = prod;
                        prodCarrito.stock = cantidad;
                        carrito.productos.push_back(prodCarrito);
                        
                        // Actualizar subtotal e impuestos
                        carrito.subtotal += prod.precio * cantidad;
                        carrito.impuestos = carrito.subtotal * 0.19;
                        
                        // Descontar del stock
                        prod.stock -= cantidad;
                        
                        cout << "\n? Producto agregado al carrito exitosamente.\n";
                        cout << "Stock restante: " << prod.stock << "\n";
                        
                        // Guardar carrito en archivo
                        guardarCarritoEnArchivo(carrito);
                        break;
                    }
                }
                
                if (!carritoEncontrado) {
                    // Crear nuevo carrito
                    CarritoDeCompras nuevoCarrito;
                    nuevoCarrito.idCarrito = obtenerUltimoIdCarrito() + 1;
                    nuevoCarrito.idUsuario = idUsuario;
                    
                    Producto prodCarrito = prod;
                    prodCarrito.stock = cantidad;
                    nuevoCarrito.productos.push_back(prodCarrito);
                    
                    nuevoCarrito.subtotal = prod.precio * cantidad;
                    nuevoCarrito.impuestos = nuevoCarrito.subtotal * 0.19;
                    
                    carritos.push_back(nuevoCarrito);
                    
                    // Descontar del stock
                    prod.stock -= cantidad;
                    
                    cout << "\n? Carrito creado y producto agregado exitosamente.\n";
                    cout << "Stock restante: " << prod.stock << "\n";
                    
                    // Guardar carrito en archivo
                    guardarCarritoEnArchivo(nuevoCarrito);
                }
            } else {
                cout << "\n? Stock insuficiente. Stock disponible: " << prod.stock << "\n";
            }
            break;
        }
    }
    
    if (!productoEncontrado) {
        cout << "\n? Producto no encontrado.\n";
    }
}

void listarProductosDelCarrito(int idUsuario) {
    cout << "\n+--------------------------------------------------------------------+\n";
    cout << "¦                     MI CARRITO DE COMPRAS                          ¦\n";
    cout << "+--------------------------------------------------------------------+\n";
    
    bool carritoEncontrado = false;
    for (const auto& carrito : carritos) {
        if (carrito.idUsuario == idUsuario) {
            carritoEncontrado = true;
            
            cout << "\nID del Carrito: " << carrito.idCarrito << "\n\n";
            
            cout << left << setw(25) << "Producto"
                 << setw(15) << "Precio Unit."
                 << setw(12) << "Cantidad"
                 << setw(15) << "Subtotal" << "\n";
            cout << "--------------------------------------------------------------------\n";
            
            for (const auto& prod : carrito.productos) {
                double subtotalProducto = prod.precio * prod.stock;
                cout << left << setw(25) << prod.nombre
                     << "$" << fixed << setprecision(2) << setw(14) << prod.precio
                     << setw(12) << prod.stock
                     << "$" << fixed << setprecision(2) << subtotalProducto << "\n";
            }
            
            cout << "--------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------\n\n";
            
            double total = carrito.subtotal + carrito.impuestos;
            
            cout << "+--------------------------------------------------------+\n";
            cout << "¦  RESUMEN DE LA COMPRA                                  ¦\n";
            cout << "+--------------------------------------------------------¦\n";
            cout << "¦  Subtotal:         $" << fixed << setprecision(2) << setw(10) << carrito.subtotal << "                       ¦\n";
            cout << "¦  Impuestos (19%):  $" << fixed << setprecision(2) << setw(10) << carrito.impuestos << "                       ¦\n";
            cout << "¦  --------------------------------------------------    ¦\n";
            cout << "¦  TOTAL:            $" << fixed << setprecision(2) << setw(10) << total << "                       ¦\n";
            cout << "+--------------------------------------------------------+\n";
            
            cout << "\nCantidad de productos: " << carrito.productos.size() << "\n";
            break;
        }
    }
    
    if (!carritoEncontrado) {
        cout << "\n+----------------------------------------+\n";
        cout << "¦  Su carrito está vacío                 ¦\n";
        cout << "¦  Agregue productos desde el menú       ¦\n";
        cout << "+----------------------------------------+\n";
    }
}

// ============ MENÚ PRINCIPAL ============

void mostrarMenu(int idUsuario) {
    int opcion;
    
    do {
        cout << "\n+----------------------------------------+\n";
        cout << "¦       MENÚ PRINCIPAL - E-COMMERCE      ¦\n";
        cout << "¦----------------------------------------¦\n";
        cout << "¦ 1. Listar productos (stock bajo)       ¦\n";
        cout << "¦ 2. Ver comentarios por fecha           ¦\n";
        cout << "¦ 3. Listar usuarios registrados         ¦\n";
        cout << "¦ 4. Adicionar producto al carrito       ¦\n";
        cout << "¦ 5. Ver mi carrito de compras           ¦\n";
        cout << "¦ 6. REPORTES ADICIONALES                ¦\n";
        cout << "¦ 0. Cerrar sesión                       ¦\n";
        cout << "+----------------------------------------+\n";
        cout << "\n? Seleccione una opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                listarProductosBajoStock();
                break;
            case 2:
                listarComentariosPorFecha();
                break;
            case 3:
                listarUsuarios();
                break;
            case 4:
                adicionarProductoAlCarrito(idUsuario);
                break;
            case 5:
                listarProductosDelCarrito(idUsuario);
                break;
            case 6:
                {
                    int opcionReporte;
                    cout << "\n+----------------------------------------+\n";
                    cout << "¦          REPORTES ADICIONALES          ¦\n";
                    cout << "¦----------------------------------------¦\n";
                    cout << "¦ 1. 5 productos con menor stock         ¦\n";
                    cout << "¦ 2. Comentarios por fecha específica    ¦\n";
                    cout << "¦ 3. Precio máximo y mínimo              ¦\n";
                    cout << "¦ 0. Volver al menú principal            ¦\n";
                    cout << "+----------------------------------------+\n";
                    cout << "\n? Seleccione un reporte: ";
                    cin >> opcionReporte;
                    
                    switch(opcionReporte) {
                        case 1:
                            mostrarProductosMenorStock();
                            break;
                        case 2:
                            mostrarComentariosPorFecha();
                            break;
                        case 3:
                            mostrarPrecioMaximoMinimo();
                            break;
                        case 0:
                            cout << "Volviendo al menú principal...\n";
                            break;
                        default:
                            cout << "? Opción inválida.\n";
                    }
                }
                break;
            case 0:
                cout << "\n+----------------------------------------+\n";
                cout << "¦  Cerrando sesión...                    ¦\n";
                cout << "¦  ¡Hasta luego! Vuelve pronto ??        ¦\n";
                cout << "+----------------------------------------+\n";
                break;
            default:
                cout << "\n? Opción inválida. Intente nuevamente.\n";
        }
        
        // Pausa para ver resultados
        if (opcion != 0 && opcion >= 1 && opcion <= 6) {
            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while(opcion != 0);
}

// ============ FUNCIÓN MAIN ============

int main() {
    // Banner inicial
    cout << "\n+----------------------------------------+\n";
    cout << "¦  SISTEMA DE COMERCIO ELECTRÓNICO      ¦\n";
    cout << "¦  Parcial Final - Programación en C++  ¦\n";
    cout << "+----------------------------------------+\n";
    
    cout << "\nCargando datos del sistema...\n";
    
    // Cargar datos desde archivos
    cargarUsuarios();
    cargarProductos();
    cargarComentarios();
    
    cout << "\n? Sistema cargado correctamente.\n";
    
    // Login
    int idUsuario = iniciarSesion();
    
    // Si el login fue exitoso, mostrar menú
    if (idUsuario != -1) {
        mostrarMenu(idUsuario);
    }
    
    cout << "\n+----------------------------------------+\n";
    cout << "¦  Programa finalizado. ¡Gracias!        ¦\n";
    cout << "+----------------------------------------+\n";
    
    return 0;
}
