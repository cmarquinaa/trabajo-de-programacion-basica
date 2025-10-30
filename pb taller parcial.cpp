#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>

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
    string productoNombre;
    string usuarioNombre;
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

// ============ VECTORES GLOBALES ============
vector<Usuario> usuarios;
vector<Producto> productos;
vector<Comentarios> comentarios;
vector<CarritoDeCompras> carritos;

// ============ FUNCIONES DE INICIALIZACIÓN ============

void inicializarUsuarios() {
    usuarios = {
        {1, "Juan Pérez", "juan.perez@email.com", "Qwerty123", "Carrera 45 #10-20", "Tarjeta de crédito"},
        {2, "Ana Gómez", "ana.gomez@email.com", "Pass456", "Calle 21 #35-50", "PayPal"},
        {3, "Carlos Ruiz", "carlos.ruiz@email.com", "Segura789", "Avenida Principal #100", "Transferencia bancaria"},
        {4, "Sofía Martínez", "sofia.martinez@email.com", "Clave987", "Calle 8 #20-30", "Efectivo"},
        {5, "Diego Fernández", "diego.fernandez@email.com", "Contra654", "Carrera 77 #40-60", "Tarjeta débito"}
    };
    cout << "✓ Usuarios inicializados: " << usuarios.size() << " registros cargados.\n";
}

void inicializarProductos() {
    productos = {
        {1, "Laptop", "Portátil con pantalla Full HD y SSD de 512GB", 89999, 10},
        {2, "Smartphone", "Teléfono con cámara de 108MP y carga rápida", 49950, 20},
        {3, "Tablet", "Dispositivo con pantalla táctil de 10 pulgadas", 29999, 15},
        {4, "Auriculares", "Audífonos inalámbricos con cancelación de ruido", 12999, 25},
        {5, "Teclado", "Teclado mecánico con iluminación RGB", 8999, 30},
        {6, "Mouse", "Ratón inalámbrico con sensor óptico de alta precisión", 5999, 50},
        {7, "Monitor", "Pantalla LED 4K de 27 pulgadas", 49900, 12},
        {8, "Impresora", "Láser multifuncional con Wi-Fi", 17999, 18},
        {9, "Cámara", "Cámara digital con lente profesional", 79999, 8},
        {10, "Smartwatch", "Reloj inteligente con GPS y monitoreo cardíaco", 19999, 22},
        {11, "Silla Gamer", "Silla ergonómica ajustable con soporte lumbar", 29999, 14},
        {12, "Microondas", "Horno microondas con múltiples funciones", 12999, 40},
        {13, "Refrigerador", "Frigorífico doble puerta con sistema No Frost", 119999, 5},
        {14, "Lavadora", "Lavadora automática con capacidad de 10kg", 59999, 7},
        {15, "Cafetera", "Cafetera express con vaporizador de leche", 14999, 35},
        {16, "Drone", "Drone con cámara 4K y estabilizador", 69999, 9},
        {17, "Bocina Bluetooth", "Altavoz portátil con sonido envolvente", 8999, 33},
        {18, "Videocámara", "Videocámara profesional con grabación en 4K", 99999, 6},
        {19, "TV LED", "Televisor inteligente de 55 pulgadas con HDR", 74999, 11},
        {20, "Batería Externa", "Batería de 20000mAh con carga rápida", 3999, 45},
        {21, "Disco Duro", "Disco duro externo de 2TB", 12999, 28},
        {22, "Memoria USB", "Pendrive de 128GB", 2999, 60},
        {23, "Router", "Router Wi-Fi 6 de alta velocidad", 19999, 16},
        {24, "Joystick", "Control inalámbrico para videojuegos", 7999, 20},
        {25, "Fuente de Poder", "Fuente de alimentación para PC de 750W", 8999, 17},
        {26, "SSD", "Unidad de almacenamiento SSD de 1TB", 14999, 32},
        {27, "Altavoces", "Par de bocinas estéreo con subwoofer", 13999, 23},
        {28, "Webcam", "Cámara web Full HD con micrófono integrado", 6999, 37},
        {29, "Procesador", "CPU Intel i7 de última generación", 34999, 9},
        {30, "Motherboard", "Placa base compatible con procesadores modernos", 19999, 13},
        {31, "Memoria RAM", "Módulo de RAM DDR4 de 16GB", 7999, 41},
        {32, "Fuente Solar", "Panel solar portátil con batería integrada", 24999, 4},
        {33, "Control Remoto", "Mando universal para TV y dispositivos", 2499, 50},
        {34, "Termostato", "Termostato digital programable", 9999, 22},
        {35, "Smart Lock", "Cerradura electrónica con huella digital", 19999, 6},
        {36, "Proyector", "Proyector LED con resolución Full HD", 29999, 12},
        {37, "Switch Ethernet", "Switch de red de 8 puertos", 5999, 38},
        {38, "Reloj Digital", "Reloj inteligente con pantalla AMOLED", 8999, 26},
        {39, "Luces LED", "Tiras LED RGB con control remoto", 3999, 55},
        {40, "Estabilizador", "Estabilizador de voltaje para dispositivos electrónicos", 15999, 10},
        {41, "Cargador Inalámbrico", "Base de carga inalámbrica rápida", 4999, 30},
        {42, "HDD Externo", "Disco duro portátil de 4TB", 17999, 15},
        {43, "Micrófono", "Micrófono profesional para grabación", 14999, 7},
        {44, "Altavoz Inteligente", "Asistente de voz con altavoz integrado", 12999, 20},
        {45, "Antena Wi-Fi", "Amplificador de señal inalámbrico", 7999, 33},
        {46, "Climatizador", "Aire acondicionado portátil con control remoto", 29999, 5},
        {47, "Raspberry Pi", "Kit de desarrollo con Raspberry Pi 4", 12999, 19},
        {48, "Capturadora", "Placa de captura de video en alta resolución", 19999, 8},
        {49, "Smart Plug", "Enchufe inteligente compatible con asistentes virtuales", 3999, 42},
        {50, "Timbre Inteligente", "Timbre con cámara y conexión a Wi-Fi", 14999, 10}
    };
    cout << "✓ Productos inicializados: " << productos.size() << " registros cargados.\n";
}

void inicializarComentarios() {
    comentarios = {
        {1, "Laptop", "Juan Pérez", "Excelente rendimiento; muy rápida. ¡Me encanta!", "1/05/2025"},
        {2, "Smartphone", "Ana Gómez", "Buena cámara pero la batería dura poco.", "3/05/2025"},
        {3, "Tablet", "Carlos Ruiz", "No me gustó; pantalla de baja calidad.", "5/05/2025"},
        {4, "Auriculares", "Sofía Martínez", "Sonido aceptable pero el material parece frágil.", "6/05/2025"},
        {5, "Teclado", "Diego Fernández", "Muy buen teclado mecánico; excelente respuesta.", "8/05/2025"},
        {6, "Mouse", "Ana Gómez", "El sensor no es tan preciso como esperaba.", "10/05/2025"},
        {7, "Monitor", "Carlos Ruiz", "Colores vibrantes y buena resolución. Muy satisfecho.", "12/05/2025"},
        {8, "Impresora", "Juan Pérez", "Tarda mucho en imprimir; no me convence.", "13/05/2025"},
        {9, "Cámara", "Sofía Martínez", "Increíble calidad de imagen; fotos súper nítidas.", "15/05/2025"},
        {10, "Smartwatch", "Diego Fernández", "Buena batería; pero la pantalla no es muy brillante.", "18/05/2025"},
        {11, "Silla Gamer", "Lucía Rodríguez", "Comodidad espectacular; perfecto para largas sesiones de juego.", "20/05/2025"},
        {12, "Microondas", "Andrés Ramírez", "Calienta bien pero hace mucho ruido.", "22/05/2025"},
        {13, "Refrigerador", "María García", "Espacioso y enfría rápido; muy recomendado.", "24/05/2025"},
        {14, "Lavadora", "Javier Martínez", "Lava bien pero el ciclo es muy largo.", "26/05/2025"},
        {15, "Cafetera", "Carolina López", "Hace café delicioso; fácil de usar.", "28/05/2025"},
        {16, "Drone", "Daniel Castro", "Muy divertido pero la batería dura poco.", "30/05/2025"},
        {17, "Bocina Bluetooth", "Paola Herrera", "Sonido potente y buena conexión Bluetooth.", "1/06/2025"},
        {18, "Videocámara", "Esteban Rojas", "Perfecta para grabaciones profesionales.", "3/06/2025"},
        {19, "TV LED", "Fernanda Sánchez", "Imagen excelente pero el sonido podría mejorar.", "5/06/2025"},
        {20, "Batería Externa", "Camilo Torres", "Carga bien pero es un poco pesada.", "7/06/2025"},
        {21, "Disco Duro", "Gabriela Suárez", "Gran capacidad de almacenamiento; funciona rápido.", "9/06/2025"},
        {22, "Memoria USB", "Raúl Espinosa", "Buen tamaño pero la velocidad de transferencia es baja.", "11/06/2025"},
        {23, "Router", "Verónica Mendoza", "Señal potente; cubre toda la casa.", "13/06/2025"},
        {24, "Joystick", "Fabio Jiménez", "Comodo y resistente; ideal para gaming.", "15/06/2025"},
        {25, "Fuente de Poder", "Ricardo Vargas", "Funciona bien pero los cables son muy cortos.", "17/06/2025"},
        {26, "SSD", "Silvia Gómez", "Velocidad increíble; mi PC va mucho más rápido ahora.", "19/06/2025"},
        {27, "Altavoces", "Martín Aguilar", "Sonido envolvente; muy buena compra.", "21/06/2025"},
        {28, "Webcam", "Valentina Pérez", "Imagen clara pero el micrófono es deficiente.", "23/06/2025"},
        {29, "Procesador", "José Ramírez", "Rendimiento impecable; ideal para gaming y diseño.", "25/06/2025"},
        {30, "Motherboard", "Natalia Correa", "Buenas prestaciones pero la instalación fue complicada.", "27/06/2025"},
        {31, "Memoria RAM", "Julio Fernández", "Expande muy bien el rendimiento del sistema.", "29/06/2025"},
        {32, "Fuente Solar", "Amanda Castro", "Energía confiable pero la batería es pequeña.", "1/07/2025"},
        {33, "Control Remoto", "Pedro Duarte", "Fácil de usar; reconoce muchos dispositivos.", "3/07/2025"},
        {34, "Termostato", "Isabela Medina", "Regula bien la temperatura; intuitivo de usar.", "5/07/2025"},
        {35, "Smart Lock", "Oscar Rodríguez", "Seguridad y tecnología en un solo dispositivo.", "7/07/2025"},
        {36, "Proyector", "Cristina Vargas", "Imagen nítida pero requiere una sala oscura.", "9/07/2025"},
        {37, "Switch Ethernet", "Mario Hernández", "Buena velocidad de conexión; estable.", "11/07/2025"},
        {38, "Reloj Digital", "Sofía Ramírez", "Pantalla atractiva pero la batería dura poco.", "13/07/2025"},
        {39, "Luces LED", "Andrea Gutiérrez", "Buenas opciones de colores; buen diseño.", "15/07/2025"},
        {40, "Estabilizador", "Pablo Medina", "Protege bien contra variaciones de voltaje.", "17/07/2025"},
        {41, "Cargador Inalámbrico", "Patricia López", "Carga rápido pero requiere posicionamiento preciso.", "19/07/2025"},
        {42, "HDD Externo", "Gonzalo Espinoza", "Mucho espacio; resistente y confiable.", "21/07/2025"},
        {43, "Micrófono", "Elena Herrera", "Calidad de sonido profesional; ideal para podcast.", "23/07/2025"},
        {44, "Altavoz Inteligente", "Diego Soto", "Responde bien a comandos de voz; útil en casa.", "25/07/2025"},
        {45, "Antena Wi-Fi", "Miguel Rojas", "Amplifica bien la señal pero el rango es limitado.", "27/07/2025"},
        {46, "Climatizador", "Estefanía Carrillo", "Enfría rápido pero es algo ruidoso.", "29/07/2025"},
        {47, "Raspberry Pi", "Manuel Vargas", "Perfecto para proyectos electrónicos y programación.", "31/07/2025"},
        {48, "Capturadora", "Luisa Mejía", "Ideal para streaming y grabaciones en alta calidad.", "2/08/2025"},
        {49, "Smart Plug", "Victoria Torres", "Muy práctico; fácil de conectar y configurar.", "4/08/2025"},
        {50, "Timbre Inteligente", "Federico Montoya", "Buena cámara; útil para seguridad.", "6/08/2025"}
    };
    cout << "✓ Comentarios inicializados: " << comentarios.size() << " registros cargados.\n";
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
    // Convertir fechas DD/MM/YYYY a formato comparable YYYYMMDD
    string f1 = fecha1.substr(6,4) + fecha1.substr(3,2) + fecha1.substr(0,2);
    string f2 = fecha2.substr(6,4) + fecha2.substr(3,2) + fecha2.substr(0,2);
    return f1 >= f2;
}

// ============ FUNCIÓN DE LOGIN ============

int iniciarSesion() {
    string correo, contrasena;
    
    cout << "\n╔════════════════════════════════════════╗\n";
    cout << "║        INICIO DE SESIÓN                ║\n";
    cout << "╚════════════════════════════════════════╝\n";
    
    cout << "\nCorreo electrónico: ";
    cin >> correo;
    cout << "Contraseña: ";
    cin >> contrasena;
    
    for (const auto& usuario : usuarios) {
        if (usuario.correoElectronico == correo && usuario.contrasena == contrasena) {
            cout << "\n┌────────────────────────────────────────┐\n";
            cout << "│  ✓ SESIÓN INICIADA EXITOSAMENTE       │\n";
            cout << "│  Bienvenido: " << usuario.nombre << string(23 - usuario.nombre.length(), ' ') << "│\n";
            cout << "└────────────────────────────────────────┘\n";
            return usuario.idUsuario;
        }
    }
    
    cout << "\n┌────────────────────────────────────────┐\n";
    cout << "│  ✗ USUARIO INVÁLIDO                    │\n";
    cout << "│  Correo o contraseña incorrectos       │\n";
    cout << "└────────────────────────────────────────┘\n";
    
    return -1;
}

// ============ FUNCIONES DE LISTADO ============

void listarProductosBajoStock() {
    cout << "\n╔════════════════════════════════════════════════════════════════════╗\n";
    cout << "║        PRODUCTOS CON STOCK MENOR A 15 UNIDADES                    ║\n";
    cout << "╚════════════════════════════════════════════════════════════════════╝\n\n";
    
    cout << left << setw(5) << "ID" 
         << setw(25) << "Nombre" 
         << setw(15) << "Precio" 
         << setw(10) << "Stock" << "\n";
    cout << "────────────────────────────────────────────────────────────────────\n";
    
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
    
    cout << "────────────────────────────────────────────────────────────────────\n";
    
    if (!encontrado) {
        cout << "No hay productos con stock menor a 15 unidades.\n";
    } else {
        cout << "Total de productos encontrados: " << contador << "\n";
    }
}

void listarComentariosPorFecha() {
    string fechaIngresada;
    
    cout << "\n╔════════════════════════════════════════════════════════════════════╗\n";
    cout << "║              COMENTARIOS FILTRADOS POR FECHA                       ║\n";
    cout << "╚════════════════════════════════════════════════════════════════════╝\n";
    
    cout << "\nIngrese fecha (formato DD/MM/YYYY): ";
    cin >> fechaIngresada;
    
    cout << "\n═══════════════════════════════════════════════════════════════════\n";
    cout << "Comentarios desde " << fechaIngresada << " en adelante:\n";
    cout << "═══════════════════════════════════════════════════════════════════\n\n";
    
    bool encontrado = false;
    int contador = 0;
    
    for (const auto& com : comentarios) {
        if (compararFechas(com.fecha, fechaIngresada)) {
            cout << "┌─────────────────────────────────────────────────────────────┐\n";
            cout << "│ Comentario #" << com.idComentario << "\n";
            cout << "├─────────────────────────────────────────────────────────────┤\n";
            cout << "│ Producto:    " << com.productoNombre << "\n";
            cout << "│ Usuario:     " << com.usuarioNombre << "\n";
            cout << "│ Fecha:       " << com.fecha << "\n";
            cout << "│ Comentario:  " << com.comentario << "\n";
            cout << "└─────────────────────────────────────────────────────────────┘\n\n";
            encontrado = true;
            contador++;
        }
    }
    
    if (!encontrado) {
        cout << "No se encontraron comentarios desde la fecha indicada.\n";
    } else {
        cout << "═══════════════════════════════════════════════════════════════════\n";
        cout << "Total de comentarios encontrados: " << contador << "\n";
        cout << "═══════════════════════════════════════════════════════════════════\n";
    }
}

void listarUsuarios() {
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                      LISTA DE USUARIOS REGISTRADOS                           ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n\n";
    
    cout << left << setw(5) << "ID" 
         << setw(25) << "NOMBRE" 
         << setw(30) << "Correo Electrónico"
         << setw(25) << "Dirección" << "\n";
    cout << "────────────────────────────────────────────────────────────────────────────────\n";
    
    for (const auto& usuario : usuarios) {
        cout << left << setw(5) << usuario.idUsuario
             << setw(25) << toUpperCase(usuario.nombre)
             << setw(30) << usuario.correoElectronico
             << setw(25) << usuario.direccion << "\n";
    }
    
    cout << "────────────────────────────────────────────────────────────────────────────────\n";
    cout << "Total de usuarios: " << usuarios.size() << "\n";
}

// ============ FUNCIONES DEL CARRITO ============

void adicionarProductoAlCarrito(int idUsuario) {
    cout << "\n╔════════════════════════════════════════════════════════════════════╗\n";
    cout << "║              ADICIONAR PRODUCTO AL CARRITO                         ║\n";
    cout << "╚════════════════════════════════════════════════════════════════════╝\n";
    
    // Mostrar productos disponibles
    cout << "\nProductos disponibles:\n";
    cout << left << setw(5) << "ID"
         << setw(25) << "Nombre"
         << setw(15) << "Precio"
         << setw(10) << "Stock" << "\n";
    cout << "────────────────────────────────────────────────────────────────────\n";
    for (const auto& prod : productos) {
        if (prod.stock > 0) {
            cout << left << setw(5) << prod.idProducto
                 << setw(25) << prod.nombre
                 << "$" << fixed << setprecision(2) << setw(14) << prod.precio
                 << setw(10) << prod.stock << "\n";
        }
    }
    cout << "────────────────────────────────────────────────────────────────────\n";
    
    int idProducto, cantidad;
    cout << "\n➤ Ingrese ID del producto (0 para cancelar): ";
    cin >> idProducto;
    
    if (idProducto == 0) {
        cout << "✗ Operación cancelada.\n";
        return;
    }
    
    cout << "➤ Ingrese cantidad: ";
    cin >> cantidad;
    
    if (cantidad <= 0) {
        cout << "✗ Cantidad inválida.\n";
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
                        
                        cout << "\n✓ Producto agregado al carrito exitosamente.\n";
                        cout << "Stock restante: " << prod.stock << "\n";
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
                    
                    cout << "\n✓ Carrito creado y producto agregado exitosamente.\n";
                    cout << "Stock restante: " << prod.stock << "\n";
                }
            } else {
                cout << "\n✗ Stock insuficiente. Stock disponible: " << prod.stock << "\n";
            }
            break;
        }
    }
    
    if (!productoEncontrado) {
        cout << "\n✗ Producto no encontrado.\n";
    }
}

void listarProductosDelCarrito(int idUsuario) {
    cout << "\n╔════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                     MI CARRITO DE COMPRAS                          ║\n";
    cout << "╚════════════════════════════════════════════════════════════════════╝\n";
    
    bool carritoEncontrado = false;
    for (const auto& carrito : carritos) {
        if (carrito.idUsuario == idUsuario) {
            carritoEncontrado = true;
            
            cout << "\nID del Carrito: " << carrito.idCarrito << "\n\n";
            
            cout << left << setw(25) << "Producto"
                 << setw(15) << "Precio Unit."
                 << setw(12) << "Cantidad"
                 << setw(15) << "Subtotal" << "\n";
            cout << "────────────────────────────────────────────────────────────────────\n";
            
            for (const auto& prod : carrito.productos) {
                double subtotalProducto = prod.precio * prod.stock;
                cout << left << setw(25) << prod.nombre
                     << "$" << fixed << setprecision(2) << setw(14) << prod.precio
                     << setw(12) << prod.stock
                     << "$" << fixed << setprecision(2) << subtotalProducto << "\n";
            }
            
            cout << "────────────────────────────────────────────────────────────────────\n";
            cout << "════════════════════════════════════════════════════════════════════\n\n";
            
            double total = carrito.subtotal + carrito.impuestos;
            
            cout << "┌────────────────────────────────────────────────────────┐\n";
            cout << "│  RESUMEN DE LA COMPRA                                  │\n";
            cout << "├────────────────────────────────────────────────────────┤\n";
            cout << "│  Subtotal:         $" << fixed << setprecision(2) << setw(10) << carrito.subtotal << "                       │\n";
            cout << "│  Impuestos (19%):  $" << fixed << setprecision(2) << setw(10) << carrito.impuestos << "                       │\n";
            cout << "│  ──────────────────────────────────────────────────    │\n";
            cout << "│  TOTAL:            $" << fixed << setprecision(2) << setw(10) << total << "                       │\n";
            cout << "└────────────────────────────────────────────────────────┘\n";
            
            cout << "\nCantidad de productos: " << carrito.productos.size() << "\n";
            break;
        }
    }
    
    if (!carritoEncontrado) {
        cout << "\n┌────────────────────────────────────────┐\n";
        cout << "│  Su carrito está vacío                 │\n";
        cout << "│  Agregue productos desde el menú       │\n";
        cout << "└────────────────────────────────────────┘\n";
    }
}

// ============ MENÚ PRINCIPAL ============

void mostrarMenu(int idUsuario) {
    int opcion;
    
    do {
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║       MENÚ PRINCIPAL - E-COMMERCE      ║\n";
        cout << "╠════════════════════════════════════════╣\n";
        cout << "║ 1. Listar productos (stock bajo)      ║\n";
        cout << "║ 2. Ver comentarios por fecha          ║\n";
        cout << "║ 3. Listar usuarios registrados        ║\n";
        cout << "║ 4. Adicionar producto al carrito      ║\n";
        cout << "║ 5. Ver mi carrito de compras          ║\n";
        cout << "║ 0. Cerrar sesión                      ║\n";
        cout << "╚════════════════════════════════════════╝\n";
        cout << "\n➤ Seleccione una opción: ";
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
            case 0:
                cout << "\n┌────────────────────────────────────────┐\n";
                cout << "│  Cerrando sesión...                    │\n";
                cout << "│  ¡Hasta luego! Vuelve pronto 👋        │\n";
                cout << "└────────────────────────────────────────┘\n";
                break;
            default:
                cout << "\n✗ Opción inválida. Intente nuevamente.\n";
        }
        
        // Pausa para ver resultados
        if (opcion != 0 && opcion >= 1 && opcion <= 5) {
            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while(opcion != 0);
}

// ============ FUNCIÓN MAIN ============

int main() {
    // Banner inicial
    cout << "\n╔════════════════════════════════════════╗\n";
    cout << "║  SISTEMA DE COMERCIO ELECTRÓNICO      ║\n";
    cout << "║  Parcial II - Programación en C++     ║\n";
    cout << "╚════════════════════════════════════════╝\n";
    
    cout << "\nInicializando sistema...\n";
    
    // Cargar datos iniciales
    inicializarUsuarios();
    inicializarProductos();
    inicializarComentarios();
    
    cout << "\n✓ Sistema inicializado correctamente.\n";
    
    // Login
    int idUsuario = iniciarSesion();
    
    // Si el login fue exitoso, mostrar menú
    if (idUsuario != -1) {
        mostrarMenu(idUsuario);
    }
    
    cout << "\n╔════════════════════════════════════════╗\n";
    cout << "║  Programa finalizado. ¡Gracias!        ║\n";
    cout << "╚════════════════════════════════════════╝\n";
    
    return 0;
}