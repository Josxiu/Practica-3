#include <iostream>
#include <fstream>
#include <bitset>
#include <string.h>
#include <string>

using namespace std;
// Funcion para pasar a binario una palabra
string palabra_binario(string);
string binario_letras(string);

// Funciones del metodo 1
string metodo1(string, int);
string cambios_metodo1(string, string);
string deco_metodo1(string, int);

// Funciones del metodo 2
string deco_metodo2(string, int);
string metodo2(string, int);
string mover_bits(string bits);
string devolver_bits(string);

string codificar(string, int, int);

void admin();
void registro_usuario();
bool repetido(string);

void ingreso_usuario();
void datos_usuario(string linea, string *datos);
void uso_cajero(string *datos);

int main()
{
    int opcion;
    while (true)
    {

        cout << "Bienvenido al servicio del cajero, a continuacion por favor indique que desea hacer\n";
        cout << "1)Retirar o consultar saldo\n"
             << "2)Agregar un nuevo usuario al sistema\n"
             << "3)Salir\n";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            ingreso_usuario();
            break;
        case 2:
            admin();
            break;
        case 3:
            cout << "Que tenga un buen dia!!";
            return 0;
            break;
        default:
            cout << "Opcion no valida";
            break;
        }
    }
    return 0;
}
// Funcion para convertir una cadena a binario
string palabra_binario(string palabra)
{
    bitset<8> byte; // Usaremos bitset para convertir los numeros a binarios
    string bytes_palabra;

    for (char letra : palabra)
    {
        byte = int(letra);                 // Convertimos el numero del codigo ascii a binario
        bytes_palabra += byte.to_string(); // Agregamos los bits a la variable que guarda la palabra convertida
    }

    return bytes_palabra;
}

// Funcion que devuelve el string con los bits despues de aplicar la codificacion siguiendo el primer metodo
string metodo1(string bytes, int semilla)
{
    const int num_bits = bytes.size() / semilla; // numero de grupos de n bits segun la semilla
    string bloques[num_bits];                    // arreglo de strings que contendra los grupos separados de n bits
    string metodo[num_bits];                     // arreglo que contiene los bits despues de aplicar el metodo
    string codificado;

    char grupo[semilla + 1]{}; // Arreglo char para almacenar un grupo de bits

    int contador = 1;
    int bloque = 0;
    for (char bit : bytes) // Ciclo para dividir los bytes en grupos de n bits
    {
        grupo[contador - 1] = bit;
        contador += 1;

        if (contador > semilla)
        {
            contador = 1;            // reiniciamos el contador cuando sea mayor que el numero de la semilla
            bloques[bloque] = grupo; // Pasamos el bloque de n bits al arreglo bloques
            bloque += 1;
        }
    }

    string anterior{};
    bloque = 1;
    for (string bits : bloques) // Ciclo para hacer el cambio en cada grupo
    {
        if (bloque == 1)
        {
            for (char bit : bits)
            { // Cambiamos el primer bloque de bits intercambiando los 1s por 0s y viceversa
                // Aqui uso una terna, si el bit es 1 pongo 0 y viceversa
                (bit == '1') ? metodo[bloque - 1] += '0'
                             : metodo[bloque - 1] += '1';
            }
        }

        else
        {
            anterior = bloques[bloque - 2];
            // llamo a una funcion para verificar que cambio hay que seguir segun la regla
            metodo[bloque - 1] = cambios_metodo1(anterior, bits); // Paso como parametro los bits del grupo anterior
        }

        bloque += 1;
        // cout << bits << endl;
    }
    cout << endl;
    for (string bits : metodo)
    {
        codificado += bits;
        // cout << bits << endl;
    }

    return codificado;
}

// Funcion que cambia los bits siguiendo las reglas del metodo 1
// Recibe un string con el grupo de bits anterior y segun su contenido se cambian los bits del grupo actual
string cambios_metodo1(string bits, string bits_cambio)
{
    string cambio; // Cadena donde se almacenan los bits codificados
    int ceros = 0, unos = 0;
    int Nbits = 1; // Variable para contar cuantos bits se han recorrido

    for (char bit : bits) // cuento cuandos ceros y unos hay en el grupo de bits anterior
        (bit == '1') ? unos += 1 : ceros += 1;

    // Si hay igual cantidad de unos y ceros se invierte cada bit
    if (unos == ceros)
        for (char bit : bits_cambio)
        { // uso una terna para cambiar los ceros y unos
            (bit == '1') ? cambio += '0'
                         : cambio += '1';
        }

    else if (unos < ceros) // si hay mas ceros que unos se invierte cada 2 bits
    {
        for (int bit = 0; bit < bits.size(); bit++)
        {
            if (Nbits == 2)
            { // Invertimos cada 2 bits
                (bits_cambio[bit] == '1') ? cambio += '0' : cambio += '1';
                Nbits = 0;
            }
            else
                cambio += bits_cambio[bit];

            Nbits += 1;
        }
    }

    else if (unos > ceros) // si hay mas unos que ceros se invierte cada 3 bits
    {
        for (int bit = 0; bit < bits.size(); bit++)
        {
            if (Nbits == 3)
            { // Invertimos cada 3 bits
                (bits_cambio[bit] == '1') ? cambio += '0' : cambio += '1';
                Nbits = 0;
            }
            else
                cambio += bits_cambio[bit];

            Nbits += 1;
        }
    }

    return cambio; // Se devuelven los bits codificados
}

string metodo2(string bytes, int semilla)
{
    const int num_bits = bytes.size() / semilla; // numero de grupos de n bits segun la semilla
    string bloques[num_bits];                    // arreglo de strings que contendra los grupos separados de n bits
    string metodo[num_bits];                     // arreglo que contiene los bits despues de aplicar el metodo
    string codificado;

    char grupo[semilla + 1]{};

    int contador = 1;
    int bloque = 0;
    for (char bit : bytes) // Ciclo para dividir los bytes en grupos de n bits
    {
        grupo[contador - 1] = bit;
        contador += 1;

        if (contador > semilla)
        {
            contador = 1;            // reiniciamos el contador cuando sea mayor que el numero de la semilla
            bloques[bloque] = grupo; // Pasamos el bloque de n bits al arreglo bloques
            bloque += 1;
        }
    }

    string cambio{}; // variable para guardar los grupos cambiados
    bloque = 0;
    for (string bytes : bloques) // Ciclo que recorre cada bloque separada de n bits para cambiarles el orden
    {

        cambio = mover_bits(bytes); // Se utiliza la funcion mover bits para codificar
        metodo[bloque] = cambio;    // Se guardan los grupos codificados
        cambio = "";
        bloque += 1;
    }

    for (string bits : metodo)
    {
        codificado += bits;
        // cout << bits << endl;
    }

    return codificado;
}

// funcion que mueve un lugar a la derecha cada bit del grupo
// devuelve un string con los bits reorganizados
string mover_bits(string bits)
{
    string movido{}; // String que almacena el grupo de bits despues de moverlos a todos una posicion a la derecha

    int largo = bits.length(); // longitud del grupo de bits
    movido += bits[largo - 1]; // En la primera posicion de movido colocamos el ultimo bit de la cadena sin codificar

    for (int i = 0; i < (largo - 1); i++) // Recorro el string con los bits para modificarlo
        movido += bits[i];                // Movemos cada bit a la derecha

    return movido;
}

// funcion que decodifica lo codificado con el primer metodo
string deco_metodo1(string bytes, int semilla)
{
    const int num_bits = bytes.size() / semilla; // numero de grupos de n bits segun la semilla
    string bloques[num_bits];                    // arreglo de strings que contendra los grupos separados de n bits
    string metodo[num_bits];                     // arreglo que contiene los bits despues de aplicar el metodo
    string decodificado;

    char grupo[semilla + 1]{}; // Arreglo char para almacenar un grupo de bits

    int contador = 1;
    int bloque = 0;
    for (char bit : bytes) // Ciclo para dividir los bytes en grupos de n bits
    {
        grupo[contador - 1] = bit;
        contador += 1;

        if (contador > semilla)
        {
            contador = 1;            // reiniciamos el contador cuando sea mayor que el numero de la semilla
            bloques[bloque] = grupo; // Pasamos el bloque de n bits al arreglo bloques
            bloque += 1;
        }
    }

    bloque = 1;
    for (string bits : bloques) // Ciclo para hacer el cambio en cada grupo
    {
        if (bloque == 1)
        {
            for (char bit : bits)
            { // Cambiamos el primer bloque de bits intercambiando los 1s por 0s y viceversa
                // Aqui uso una terna, si el bit es 1 pongo 0 y viceversa
                (bit == '1') ? metodo[bloque - 1] += '0'
                             : metodo[bloque - 1] += '1';
            }
        }

        else
        {
            // llamo a una funcion para verificar que cambio hay que seguir segun la regla
            metodo[bloque - 1] = cambios_metodo1(metodo[bloque - 2], bits); // Paso como parametro los bits del grupo anterior
        }

        bloque += 1;
        // cout << bits << endl;
    }
    cout << endl;
    for (string bits : metodo)
    {
        decodificado += bits;
        // cout << bits << endl;
    }

    return decodificado;
}

string devolver_bits(string bits)
{
    string movido{};           // String que almacena el grupo de bits despues de moverlos a todos a su posicion inicial
    int largo = bits.length(); // longitud del grupo de bits

    for (int i = 1; i < (largo); i++) // Recorro el string con los bits para modificarlo
        movido += bits[i];            // Movemos cada bit a la izquierda

    movido += bits[0]; // En la ultima posicion de movido colocamos el primer bit de la cadena codificada

    return movido;
}

string deco_metodo2(string bytes, int semilla)
{
    const int num_bits = bytes.size() / semilla; // numero de grupos de n bits segun la semilla
    string bloques[num_bits];                    // arreglo de strings que contendra los grupos separados de n bits
    string metodo[num_bits];                     // arreglo que contiene los bits despues de aplicar el metodo
    string decodificado;

    char grupo[semilla + 1]{};

    int contador = 1;
    int bloque = 0;
    for (char bit : bytes) // Ciclo para dividir los bytes en grupos de n bits
    {
        grupo[contador - 1] = bit;
        contador += 1;

        if (contador > semilla)
        {
            contador = 1;            // reiniciamos el contador cuando sea mayor que el numero de la semilla
            bloques[bloque] = grupo; // Pasamos el bloque de n bits al arreglo bloques
            bloque += 1;
        }
    }

    string cambio{}; // variable para guardar los grupos cambiados
    bloque = 0;
    for (string bytes : bloques) // Ciclo que recorre cada bloque separada de n bits para cambiarles el orden
    {

        cambio = devolver_bits(bytes); // Se utiliza la funcion devolver bits para decodificar
        metodo[bloque] = cambio;       // Se guardan los grupos decodificados
        cambio = "";
        bloque += 1;
    }

    for (string bits : metodo)
    {
        decodificado += bits;
        // cout << bits << endl;
    }

    return decodificado;
}
// funcion para acceder como administrador
void admin()
{
    bool acceso = 0;
    string info[2]{};
    size_t posicion;
    string datos;
    string contra;
    int contador = 0;
    cout << "Ingrese la clave de acceso: ";
    cin >> contra;

    string contra2; // = metodo2(contra,4);//codificamos la clave de acceso

    fstream archivo("sudo"); // Abrimos el archivo en modo lectura y escritura
    getline(archivo, datos); // obtenemos una linea
    if (datos == "\0")       // Si no existe el archivo se crea
    {
        datos = "admin " + metodo2(palabra_binario("admin2022"), 4) + " ";
        archivo << datos;
    }

    while ((posicion = datos.find(' ')) != string::npos)
    {
        info[contador] = datos.substr(0, posicion); // almacenamos el dato en info
        contador++;
        datos.erase(0, posicion + 1); // eliminamos el texto detras del separador
    }
    contra2 = binario_letras(deco_metodo2(info[1], 4)); // decodificamos la clave con el metodo 2

    for (string dato : info)
    {
        cout << dato << endl;
    }
    if (!(contra.compare(contra2))) // Se comprueba que la clave sea correcta
    {
        cout << "Ingreso exitoso\n";
        acceso = 1;
    }
    else
        cout << "Error, clave incorrecta\n";

    archivo.close();

    if (acceso == 1)
    {
        registro_usuario();
    }
}

// funcion para registrar un nuevo usuario
// Esta funcion agrega al final del archivo usuario los datos del nuevo usuario a registrar
void registro_usuario()
{
    bool usuario_repetido;
    string usuario, clave, confirmar;
    long long saldo;
    cout << "Ingrese los siguientes datos a continuacion para registrar la cuenta del usuario\n";

    do
    {
        cout << "Nombre del usuario: ";
        cin >> usuario;
        usuario_repetido = repetido(usuario); // Verificamos que el nombre de usuario no se encuentre registrado
    } while (usuario_repetido);

    do // Se pide ingresar la clave dos veces para confirmar
    {
        cout << "Clave del usuario: ";
        cin >> clave;
        cout << "Confirme la clave ingresada: ";
        cin >> confirmar;
    } while (clave != confirmar);

    clave = codificar(clave, 1, 4); // se cifra la clave con el metodo uno y la semilla sera el numero 4 por defecto

    cout << "Saldo inicial: ";
    cin >> saldo;
    cin.clear();
    cin.ignore();

    ofstream agregar("usuarios", ios::app);
    agregar << usuario << " " << clave << " " << saldo << " "
            << "\n"; // Se agregan los datos del nuevo usuario al sistema
    agregar.close();
    cout << "Usuario registrado exitosamente\n";
}

// Funcion para codificar segun el metodo que se elija
// Se usan las funciones previamente hechas para codificar
string codificar(string palabra, int metodo, int semilla)
{
    if (metodo == 1)
    {
        string binario = palabra_binario(palabra);     // se convierte primero a binario
        string codificado = metodo1(binario, semilla); // Se codifica usando el metodo 1 y la semilla
        return codificado;
    }
    else
    {
        string binario = palabra_binario(palabra);     // se convierte primero a binario
        string codificado = metodo2(binario, semilla); // Se codifica usando el metodo 2 y la semilla
        return codificado;
    }
}

// Funcion para saber si el usuario ingresado ya se encuentra en el archivo
bool repetido(string usuario)
{
    fstream archivo("usuarios");
    string linea, user; // user sera el nombre de usuario que hay en la linea
    while (!archivo.eof())
    {                            // Aqui revisamos linea a linea para verificar que no este repetido el usuario
        getline(archivo, linea); // se lee una linea
        if (linea != "\0")       // Se verifica que el archivo no este vacio
        {
            user = linea.substr(0, linea.find(' ')); // se almacena el nombre de usuario de la linea en la que estamos
            if (usuario == user)
            {
                cout << "El nombre de usuario ya se encuentra registrado\n";
                return 1;
            }
        }
        else
        {
            archivo.close();
            return 0;
        }
    }
    archivo.close();
    return 0; // No esta repetido
}

// funcion para pasar de binario a letras
string binario_letras(string binario)
{
    string palabra;
    bitset<8> bits;
    for (int i = 0; i < binario.length(); i += 8) // Ciclo para recorrer de a 8 bits
    {
        bits = bitset<8>(binario, i, 8);
        palabra += char(bits.to_ulong()); // Convertir el byte en letra y guardar en palabra
    }

    return palabra;
}

void ingreso_usuario()
{
    string datos[3];
    bool existe = 0;
    string usuario, texto, clave, linea, deco_clave;
    ifstream lectura("usuarios");
    if (lectura.fail())
    {
        cout << "Error, ningun usuario esta registrado en el sistema\n\n";
        return;
    }

    int intentos = 5;
    cout << "Ingrese su nombre de usuario sin espacios: ";
    cin >> usuario;
    fflush(stdin);
    cout << "Ingrese su clave de acceso: ";
    cin >> clave;

    while (!lectura.eof())
    {
        getline(lectura, linea);

        datos[0] = linea.substr(0, linea.find(' ')); // se almacena el nombre de usuario de la linea en la que estamos

        if (usuario == datos[0])
        {
            existe = 1; // Se confirma que el usuario si existe

            datos_usuario(linea, datos); // se guardan los datos del usuario en el arreglo datos

            deco_clave = binario_letras(deco_metodo1(datos[1], 4)); // decodificamos la clave con el metodo 1

            while ((clave.compare(deco_clave)) && intentos != 0)
            {

                cout << "le quedan " << intentos << " intentos\n";
                cout << "Clave incorrecta por favor intente otra vez: ";
                cin >> clave;
                intentos--; // Reducimos los intentos

                if (intentos == 0)
                {
                    cout << "Demasiados intentos fallidos, intentelo de nuevo mas tarde\n";
                    lectura.close();
                    return;
                }
            }

            uso_cajero(datos); // Se realiza la operacion que el usuario desee con el cajero y se actualiza la variable datos

            linea = datos[0] + ' ' + datos[1] + ' ' + datos[2] + ' '; // Se guardan los cambios en la linea
        }
        if (linea != "\0")
            texto += linea + '\n'; // Vamos agregando todas las lineas a un solo string
        else
            texto += linea; // Vamos agregando todas las lineas a un solo string
    }

    if (existe == 0)
    {
        cout << "El usuario ingresado no existe, verifique que el usuario ingresado este registrado\n\n";
        return;
    }

    lectura.close();
    ofstream escribir("usuarios");
    escribir << texto; // Se actualiza la informacion
    escribir.close();  // cerramos el archivo
}

void datos_usuario(string linea, string *datos)
{

    int contador = 1;
    string dato;
    linea.erase(0, linea.find(' ') + 1);
    while ((linea.find(' ')) != string::npos)
    {
        dato = linea.substr(0, linea.find(' '));
        datos[contador] = dato;
        contador++;
        linea.erase(0, linea.find(' ') + 1);
    }
}

void uso_cajero(string *datos)
{
    int opcion;
    do
    {
        cout << "Ingrese la operacion deseada, tenga en cuenta que se descontaran mil pesos\n"
             << "1)Consultar saldo\n"
             << "2)Retirar saldo\n"
             << "3)Salir\n";
        cin >> opcion;
    } while (opcion > 2 || opcion < 1);

    int retiro; // variable para almacenar la cantidad a retirar
    string cuenta = datos[2];
    int saldo = stoi(cuenta);
    switch (opcion)
    {
    case 1:
        if (saldo >= 0 && saldo < 1000)
            cout << "El saldo en su cuenta es de: " << datos[2] << '\n\n';
        else
        {
            saldo -= 1000;
            datos[2] = to_string(saldo);
            cout << "El saldo en su cuenta es de: " << saldo << '\n\n';
        }
        break;

    case 2:
        cout << "Ingrese la cantidad que desea retirar: ";
        cin >> retiro;

        if (saldo < retiro)
            cout << "El saldo en su cuenta es de: " << datos[2] << "no puede retirar mas de lo que tiene\n\n";
        else
        {
            saldo -= retiro + 1000;      // actualizamos el saldo de la cuenta
            datos[2] = to_string(saldo); // Se retira el dinero y se descuentan mil pesos
            cout << "El saldo restante en su cuenta es de: " << datos[2] << '\n\n';
        }
        break;
    case 3:
        cout << "¡¡Que tenga un buen dia!!";
        break;
    }
}
