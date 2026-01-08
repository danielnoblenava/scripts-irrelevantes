#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


//Brigada Número 2: PROYECTO FINAL

// Enumeraciones para las categorías
typedef enum {
    LONGITUD,
    MASA,
    VOLUMEN,
    TEMPERATURA,
    TIEMPO,
    AREA,
    VELOCIDAD,
    DESCONOCIDO
} Categoria;

// Estructura para almacenar la entrada
typedef struct {
    double cantidad;
    char unidad[10];
    Categoria categoria;
} Entrada;

//funciones lol
Categoria determinarCategoria(const char *unidad);
int unidadesCompatibles(Categoria cat1, Categoria cat2);
double convertirLongitud(double valor, const char *de, const char *a);
double convertirMasa(double valor, const char *de, const char *a);
double convertirVolumen(double valor, const char *de, const char *a);
double convertirTemperatura(double valor, const char *de, const char *a);
double convertirTiempo(double valor, const char *de, const char *a);
double convertirArea(double valor, const char *de, const char *a);
double convertirVelocidad(double valor, const char *de, const char *a);
void limpiarCadena(char *str);
void mostrarUnidadesDisponibles(Categoria cat);

int main() {
    char input[100];
    Entrada entrada;
    char unidadDestino[10];
    double resultado;
    
    printf("=== CONVERSOR DE UNIDADES ===\n");
    printf("Formato de entrada: cantidad(unidad)\n");
    printf("Ejemplo: 80(km) o 32.5(C)\n\n");
    printf("Ingrese la cantidad a convertir (o 'salir' para terminar): ");
    
    while (1) {
        fgets(input, sizeof(input), stdin);
        limpiarCadena(input);
        
        if (strcmp(input, "salir") == 0) {
            break;
        }
        
        // Parsear la entrada
        if (sscanf(input, "%lf(%9[^)])", &entrada.cantidad, entrada.unidad) != 2) {
            printf("Formato incorrecto. Use: cantidad(unidad)\n");
            printf("Ejemplo: 80(km) o 32.5(C)\n");
            continue;
        }
        
        // Determinar categoría de la unidad de entrada
        entrada.categoria = determinarCategoria(entrada.unidad);
        
        if (entrada.categoria == DESCONOCIDO) {
            printf("Unidad '%s' no reconocida.\n", entrada.unidad);
            continue;
        }
        
        // Mostrar unidades disponibles para esta categoría
        printf("\nUnidades disponibles para conversión en esta categoría:\n");
        mostrarUnidadesDisponibles(entrada.categoria);
        
        // Solicitar unidad destino
        printf("\nIngrese la unidad a la que desea convertir: ");
        fgets(unidadDestino, sizeof(unidadDestino), stdin);
        limpiarCadena(unidadDestino);
        
        // Determinar categoría de la unidad destino
        Categoria catDestino = determinarCategoria(unidadDestino);
        
        // Verificar compatibilidad
        if (catDestino == DESCONOCIDO) {
            printf("Unidad destino '%s' no reconocida.\n", unidadDestino);
            continue;
        }
        
        if (!unidadesCompatibles(entrada.categoria, catDestino)) {
            printf("Error: No se puede convertir %s a %s (categorías incompatibles)\n",
                   entrada.unidad, unidadDestino);
            continue;
        }
        
        // Realizar conversión según categoría
        switch (entrada.categoria) {
            case LONGITUD:
                resultado = convertirLongitud(entrada.cantidad, entrada.unidad, unidadDestino);
                break;
            case MASA:
                resultado = convertirMasa(entrada.cantidad, entrada.unidad, unidadDestino);
                break;
            case VOLUMEN:
                resultado = convertirVolumen(entrada.cantidad, entrada.unidad, unidadDestino);
                break;
            case TEMPERATURA:
                resultado = convertirTemperatura(entrada.cantidad, entrada.unidad, unidadDestino);
                break;
            case TIEMPO:
                resultado = convertirTiempo(entrada.cantidad, entrada.unidad, unidadDestino);
                break;
            case AREA:
                resultado = convertirArea(entrada.cantidad, entrada.unidad, unidadDestino);
                break;
            case VELOCIDAD:
                resultado = convertirVelocidad(entrada.cantidad, entrada.unidad, unidadDestino);
                break;
            default:
                printf("Error: Categoría no soportada\n");
                continue;
        }
        
        // Mostrar resultado
        printf("\nResultado: %.6f(%s)\n\n", resultado, unidadDestino);
        printf("Ingrese otra cantidad a convertir (o 'salir' para terminar): ");
    }
    
    printf("bye :v\n");
    return 0;
}

// Determina la categoría de una unidad
Categoria determinarCategoria(const char *unidad) {
    // Conversión a minúsculas para comparación sin importar mayúsculas/minúsculas
    char unidadLower[10];
    int i;
    for (i = 0; unidad[i] && i < 9; i++) {
        unidadLower[i] = tolower(unidad[i]);
    }
    unidadLower[i] = '\0';
    
    // Longitud
    if (strcmp(unidadLower, "m") == 0 || strcmp(unidad, "metro") == 0 ||
        strcmp(unidadLower, "km") == 0 || strcmp(unidad, "kilometro") == 0 ||
        strcmp(unidadLower, "cm") == 0 || strcmp(unidad, "centimetro") == 0 ||
        strcmp(unidadLower, "mm") == 0 || strcmp(unidad, "milimetro") == 0 ||
        strcmp(unidadLower, "in") == 0 || strcmp(unidad, "pulgada") == 0 ||
        strcmp(unidadLower, "ft") == 0 || strcmp(unidad, "pie") == 0 ||
        strcmp(unidadLower, "mi") == 0 || strcmp(unidad, "milla") == 0) {
        return LONGITUD;
    }
    
    // Masa/Peso
    if (strcmp(unidadLower, "kg") == 0 || strcmp(unidad, "kilogramo") == 0 ||
        strcmp(unidadLower, "g") == 0 || strcmp(unidad, "gramo") == 0 ||
        strcmp(unidadLower, "lb") == 0 || strcmp(unidad, "libra") == 0 ||
        strcmp(unidadLower, "oz") == 0 || strcmp(unidad, "onza") == 0 ||
        strcmp(unidadLower, "t") == 0 || strcmp(unidad, "tonelada") == 0) {
        return MASA;
    }
    
    // Volumen
    if (strcmp(unidadLower, "l") == 0 || strcmp(unidad, "litro") == 0 ||
        strcmp(unidadLower, "ml") == 0 || strcmp(unidad, "mililitro") == 0 ||
        strcmp(unidadLower, "gal") == 0 || strcmp(unidad, "galon") == 0 ||
        strcmp(unidadLower, "m3") == 0 || strcmp(unidad, "metro cubico") == 0 ||
        strcmp(unidadLower, "pt") == 0 || strcmp(unidad, "pinta") == 0) {
        return VOLUMEN;
    }
    
    // Temperatura
    if (strcmp(unidadLower, "c") == 0 || strcmp(unidadLower, "ºc") == 0 ||
        strcmp(unidadLower, "f") == 0 || strcmp(unidadLower, "ºf") == 0 ||
        strcmp(unidadLower, "k") == 0 || strcmp(unidad, "kelvin") == 0) {
        return TEMPERATURA;
    }
    
    // Tiempo
    if (strcmp(unidadLower, "s") == 0 || strcmp(unidad, "segundo") == 0 ||
        strcmp(unidadLower, "min") == 0 || strcmp(unidad, "minuto") == 0 ||
        strcmp(unidadLower, "h") == 0 || strcmp(unidad, "hora") == 0 ||
        strcmp(unidadLower, "d") == 0 || strcmp(unidad, "dia") == 0 ||
        strcmp(unidadLower, "a") == 0 || strcmp(unidad, "año") == 0) {
        return TIEMPO;
    }
    
    // Área
    if (strcmp(unidadLower, "m2") == 0 || strcmp(unidad, "metro cuadrado") == 0 ||
        strcmp(unidadLower, "km2") == 0 || strcmp(unidad, "kilometro cuadrado") == 0 ||
        strcmp(unidadLower, "ha") == 0 || strcmp(unidad, "hectarea") == 0 ||
        strcmp(unidadLower, "ft2") == 0 || strcmp(unidad, "pie cuadrado") == 0) {
        return AREA;
    }
    
    // Velocidad
    if (strcmp(unidadLower, "km/h") == 0 || strcmp(unidadLower, "kmh") == 0 ||
        strcmp(unidadLower, "m/s") == 0 || strcmp(unidadLower, "ms") == 0 ||
        strcmp(unidadLower, "mph") == 0) {
        return VELOCIDAD;
    }
    
    return DESCONOCIDO;
}

// Verifica si dos categorías son compatibles para conversión
int unidadesCompatibles(Categoria cat1, Categoria cat2) {
    return (cat1 == cat2);
}

// Conversiones de longitud
double convertirLongitud(double valor, const char *de, const char *a) {
    // Primero convertir todo a metros
    double enMetros;
    
    // Convertir de unidad de entrada a metros
    if (strcasecmp(de, "km") == 0 || strcasecmp(de, "kilometro") == 0) {
        enMetros = valor * 1000;
    } else if (strcasecmp(de, "m") == 0 || strcasecmp(de, "metro") == 0) {
        enMetros = valor;
    } else if (strcasecmp(de, "cm") == 0 || strcasecmp(de, "centimetro") == 0) {
        enMetros = valor / 100;
    } else if (strcasecmp(de, "mm") == 0 || strcasecmp(de, "milimetro") == 0) {
        enMetros = valor / 1000;
    } else if (strcasecmp(de, "in") == 0 || strcasecmp(de, "pulgada") == 0) {
        enMetros = valor * 0.0254;
    } else if (strcasecmp(de, "ft") == 0 || strcasecmp(de, "pie") == 0) {
        enMetros = valor * 0.3048;
    } else if (strcasecmp(de, "mi") == 0 || strcasecmp(de, "milla") == 0) {
        enMetros = valor * 1609.34;
    } else {
        return valor; // Si no se reconoce, devolver el valor original
    }
    
    // Convertir de metros a unidad destino
    if (strcasecmp(a, "km") == 0 || strcasecmp(a, "kilometro") == 0) {
        return enMetros / 1000;
    } else if (strcasecmp(a, "m") == 0 || strcasecmp(a, "metro") == 0) {
        return enMetros;
    } else if (strcasecmp(a, "cm") == 0 || strcasecmp(a, "centimetro") == 0) {
        return enMetros * 100;
    } else if (strcasecmp(a, "mm") == 0 || strcasecmp(a, "milimetro") == 0) {
        return enMetros * 1000;
    } else if (strcasecmp(a, "in") == 0 || strcasecmp(a, "pulgada") == 0) {
        return enMetros / 0.0254;
    } else if (strcasecmp(a, "ft") == 0 || strcasecmp(a, "pie") == 0) {
        return enMetros / 0.3048;
    } else if (strcasecmp(a, "mi") == 0 || strcasecmp(a, "milla") == 0) {
        return enMetros / 1609.34;
    }
    
    return valor;
}

// Conversiones de masa
double convertirMasa(double valor, const char *de, const char *a) {
    // Primero convertir todo a kilogramos
    double enKg;
    
    if (strcasecmp(de, "kg") == 0 || strcasecmp(de, "kilogramo") == 0) {
        enKg = valor;
    } else if (strcasecmp(de, "g") == 0 || strcasecmp(de, "gramo") == 0) {
        enKg = valor / 1000;
    } else if (strcasecmp(de, "lb") == 0 || strcasecmp(de, "libra") == 0) {
        enKg = valor * 0.453592;
    } else if (strcasecmp(de, "oz") == 0 || strcasecmp(de, "onza") == 0) {
        enKg = valor * 0.0283495;
    } else if (strcasecmp(de, "t") == 0 || strcasecmp(de, "tonelada") == 0) {
        enKg = valor * 1000;
    } else {
        return valor;
    }
    
    // Convertir de kilogramos a unidad destino
    if (strcasecmp(a, "kg") == 0 || strcasecmp(a, "kilogramo") == 0) {
        return enKg;
    } else if (strcasecmp(a, "g") == 0 || strcasecmp(a, "gramo") == 0) {
        return enKg * 1000;
    } else if (strcasecmp(a, "lb") == 0 || strcasecmp(a, "libra") == 0) {
        return enKg / 0.453592;
    } else if (strcasecmp(a, "oz") == 0 || strcasecmp(a, "onza") == 0) {
        return enKg / 0.0283495;
    } else if (strcasecmp(a, "t") == 0 || strcasecmp(a, "tonelada") == 0) {
        return enKg / 1000;
    }
    
    return valor;
}

// Conversiones de volumen
double convertirVolumen(double valor, const char *de, const char *a) {
    // Primero convertir todo a litros
    double enLitros;
    
    if (strcasecmp(de, "l") == 0 || strcasecmp(de, "litro") == 0) {
        enLitros = valor;
    } else if (strcasecmp(de, "ml") == 0 || strcasecmp(de, "mililitro") == 0) {
        enLitros = valor / 1000;
    } else if (strcasecmp(de, "gal") == 0 || strcasecmp(de, "galon") == 0) {
        enLitros = valor * 3.78541;
    } else if (strcasecmp(de, "m3") == 0 || strcasecmp(de, "metro cubico") == 0) {
        enLitros = valor * 1000;
    } else if (strcasecmp(de, "pt") == 0 || strcasecmp(de, "pinta") == 0) {
        enLitros = valor * 0.473176;
    } else {
        return valor;
    }
    
    // Convertir de litros a unidad destino
    if (strcasecmp(a, "l") == 0 || strcasecmp(a, "litro") == 0) {
        return enLitros;
    } else if (strcasecmp(a, "ml") == 0 || strcasecmp(a, "mililitro") == 0) {
        return enLitros * 1000;
    } else if (strcasecmp(a, "gal") == 0 || strcasecmp(a, "galon") == 0) {
        return enLitros / 3.78541;
    } else if (strcasecmp(a, "m3") == 0 || strcasecmp(a, "metro cubico") == 0) {
        return enLitros / 1000;
    } else if (strcasecmp(a, "pt") == 0 || strcasecmp(a, "pinta") == 0) {
        return enLitros / 0.473176;
    }
    
    return valor;
}

// Conversiones de temperatura
double convertirTemperatura(double valor, const char *de, const char *a) {
    // Primero convertir todo a Celsius
    double enCelsius;
    
    if (strcasecmp(de, "c") == 0 || strcasecmp(de, "ºC") == 0) {
        enCelsius = valor;
    } else if (strcasecmp(de, "f") == 0 || strcasecmp(de, "ºF") == 0) {
        enCelsius = (valor - 32) * 5 / 9;
    } else if (strcasecmp(de, "k") == 0 || strcasecmp(de, "kelvin") == 0) {
        enCelsius = valor - 273.15;
    } else {
        return valor;
    }
    
    // Convertir de Celsius a unidad destino
    if (strcasecmp(a, "c") == 0 || strcasecmp(a, "ºC") == 0) {
        return enCelsius;
    } else if (strcasecmp(a, "f") == 0 || strcasecmp(a, "ºF") == 0) {
        return (enCelsius * 9 / 5) + 32;
    } else if (strcasecmp(a, "k") == 0 || strcasecmp(a, "kelvin") == 0) {
        return enCelsius + 273.15;
    }
    
    return valor;
}

// Conversiones de tiempo
double convertirTiempo(double valor, const char *de, const char *a) {
    // Primero convertir todo a segundos
    double enSegundos;
    
    if (strcasecmp(de, "s") == 0 || strcasecmp(de, "segundo") == 0) {
        enSegundos = valor;
    } else if (strcasecmp(de, "min") == 0 || strcasecmp(de, "minuto") == 0) {
        enSegundos = valor * 60;
    } else if (strcasecmp(de, "h") == 0 || strcasecmp(de, "hora") == 0) {
        enSegundos = valor * 3600;
    } else if (strcasecmp(de, "d") == 0 || strcasecmp(de, "dia") == 0) {
        enSegundos = valor * 86400;
    } else if (strcasecmp(de, "a") == 0 || strcasecmp(de, "año") == 0) {
        enSegundos = valor * 31536000; // 365 días
    } else {
        return valor;
    }
    
    // Convertir de segundos a unidad destino
    if (strcasecmp(a, "s") == 0 || strcasecmp(a, "segundo") == 0) {
        return enSegundos;
    } else if (strcasecmp(a, "min") == 0 || strcasecmp(a, "minuto") == 0) {
        return enSegundos / 60;
    } else if (strcasecmp(a, "h") == 0 || strcasecmp(a, "hora") == 0) {
        return enSegundos / 3600;
    } else if (strcasecmp(a, "d") == 0 || strcasecmp(a, "dia") == 0) {
        return enSegundos / 86400;
    } else if (strcasecmp(a, "a") == 0 || strcasecmp(a, "año") == 0) {
        return enSegundos / 31536000;
    }
    
    return valor;
}

// Conversiones de área
double convertirArea(double valor, const char *de, const char *a) {
    // Primero convertir todo a metros cuadrados
    double enM2;
    
    if (strcasecmp(de, "m2") == 0 || strcasecmp(de, "metro cuadrado") == 0) {
        enM2 = valor;
    } else if (strcasecmp(de, "km2") == 0 || strcasecmp(de, "kilometro cuadrado") == 0) {
        enM2 = valor * 1000000;
    } else if (strcasecmp(de, "ha") == 0 || strcasecmp(de, "hectarea") == 0) {
        enM2 = valor * 10000;
    } else if (strcasecmp(de, "ft2") == 0 || strcasecmp(de, "pie cuadrado") == 0) {
        enM2 = valor * 0.092903;
    } else {
        return valor;
    }
    
    // Convertir de metros cuadrados a unidad destino
    if (strcasecmp(a, "m2") == 0 || strcasecmp(a, "metro cuadrado") == 0) {
        return enM2;
    } else if (strcasecmp(a, "km2") == 0 || strcasecmp(a, "kilometro cuadrado") == 0) {
        return enM2 / 1000000;
    } else if (strcasecmp(a, "ha") == 0 || strcasecmp(a, "hectarea") == 0) {
        return enM2 / 10000;
    } else if (strcasecmp(a, "ft2") == 0 || strcasecmp(a, "pie cuadrado") == 0) {
        return enM2 / 0.092903;
    }
    
    return valor;
}

// Conversiones de velocidad
double convertirVelocidad(double valor, const char *de, const char *a) {
    // Primero convertir todo a m/s
    double enMs;
    
    if (strcasecmp(de, "m/s") == 0 || strcasecmp(de, "ms") == 0) {
        enMs = valor;
    } else if (strcasecmp(de, "km/h") == 0 || strcasecmp(de, "kmh") == 0) {
        enMs = valor * 0.277778;
    } else if (strcasecmp(de, "mph") == 0) {
        enMs = valor * 0.44704;
    } else {
        return valor;
    }
    
    // Convertir de m/s a unidad destino
    if (strcasecmp(a, "m/s") == 0 || strcasecmp(a, "ms") == 0) {
        return enMs;
    } else if (strcasecmp(a, "km/h") == 0 || strcasecmp(a, "kmh") == 0) {
        return enMs / 0.277778;
    } else if (strcasecmp(a, "mph") == 0) {
        return enMs / 0.44704;
    }
    
    return valor;
}

// Función para limpiar cadenas (eliminar saltos de línea)
void limpiarCadena(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

// Mostrar unidades disponibles para una categoría
void mostrarUnidadesDisponibles(Categoria cat) {
    switch (cat) {
        case LONGITUD:
            printf("m, km, cm, mm, in, ft, mi");
            break;
        case MASA:
            printf("kg, g, lb, oz, t");
            break;
        case VOLUMEN:
            printf("L, mL, gal, m3, pt");
            break;
        case TEMPERATURA:
            printf("C, F, K");
            break;
        case TIEMPO:
            printf("s, min, h, d, a");
            break;
        case AREA:
            printf("m2, km2, ha, ft2");
            break;
        case VELOCIDAD:
            printf("km/h, m/s, mph");
            break;
        default:
            printf("No hay unidades disponibles");
    }
    printf("\n");
}