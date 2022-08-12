#include <iostream>
#include <fstream>
#include <bitset>
#include <string.h>

using namespace std;

string palabra_binario(string);
string metodo1(string, int);
string cambios_metodo1(string, string);

string metodo2(string,int);

string codificar(string, int, int);

int main()
{
    string bytes;
    bytes = palabra_binario("AbCd");
    cout << bytes.size() << endl;
    string codificado;
    codificado = metodo1(bytes, 4);
    codificado = metodo2(bytes,4);

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

    string anterior{};
    bloque = 1;
    for (string bits : bloques)//Ciclo para hacer el cambio en cada grupo
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
        cout << bits << endl;
    }
    cout << endl;
    for (string bits : metodo)
    {
        codificado+=bits;
        cout << bits << endl;
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


string metodo2(string bytes, int semilla){
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

    string cambio;
    bloque = 0;
    int cambiar = semilla -1;
    for(string bytes:bloques){
        
        while(semilla!=(semilla-2))
        if(cambiar==(semilla-1)){
            cambio+= bytes[cambiar];
            cambiar = 0;
        }
        else{
            cambio +=bytes[cambiar];
            if(semilla!=semilla-2)
                cambiar+=1;
        }
        cout<<cambio<<endl;
        metodo[bloque] = cambio;
        cambio ="";
        cambiar+=1;
        
    }
    

    return " ";
}