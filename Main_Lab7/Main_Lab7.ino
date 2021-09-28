/*------------------------------------------------------------------------------  
Archivo: Main_Lab7
Microcontrolador: TM4C123
Autor: Andy Bonilla
Compilador: Energia 1.8.11E23
Programa: laboratorio 7
Hardware: Launchpad Tiva C
    
Creado: 27 de septiembre de 2021    
Descripcion: un pequeño menu para leer imagenes en textos desde una sd
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 ----------------------------L I B R E R I A S---------------------------------
 -----------------------------------------------------------------------------*/
#include <SPI.h>
#include <SD.h>

/*-----------------------------------------------------------------------------
 -----------------V A R I A B L E S   A   I M P L E M T E N T A R--------------
 -----------------------------------------------------------------------------*/
//-------VARIABLES DE PROGRAMA
int menu;
File myFile;

/*-----------------------------------------------------------------------------
 ------------ P R O T O T I P O S   D E   F U N C I O N E S -------------------
 -----------------------------------------------------------------------------*/
void printDirectory(File dir, int numTabs); //informacion de directorio
void opcion1(void);                         //funcion para desplegar opcion 1
void opcion2(void);                         //funcion para desplegar opcion 2
void opcion3(void);                         //funcion para desplegar opcion 3
/*-----------------------------------------------------------------------------
 --------------------- I N T E R R U P C I O N E S ----------------------------
 -----------------------------------------------------------------------------*/
//de momento no hay interrupciones
/*-----------------------------------------------------------------------------
 ------------------------------ S E T   U P -----------------------------------
 -----------------------------------------------------------------------------*/
void setup()
{
  //-------ENTRADAS Y SALIDA
  pinMode(PA_3, OUTPUT);    //se define salida del CS para comunicacion con SD

  //-------INICIALIZACION DE PROTOCOLOS DE COMUNICACION
  Serial.begin(9600);       //UART para menu
  SPI.setModule(0);         //SPI para SD

  //-------MENSAJES DE INICIALIZACION DE COMUNICACION CON SD
  Serial.print("Inicializando tarjeta SD...");
 
  if (!SD.begin(PA_3)) {
    Serial.println("initialización fallida!");  //mensaje si hay algun error
    return;
  }
  Serial.println("initialización correcta.");   //mensaje si todo esta bien

  myFile = SD.open("/");                        //se abre el directorio de la SD
  printDirectory(myFile, 0);                    //se imprime el directorio de la SD

  //-------MENSAJES DE MENU AL INICIAR PROGRAMA
  Serial.println("done!");
  Serial.println("Escoger imagen 1, 2 o 3 ");
  Serial.println("1. antena.txt ");
  Serial.println("2. ramon.txt ");
  Serial.println("3. flophy.txt ");
}
/*-----------------------------------------------------------------------------
 -------------------------- M A I N   L O O P ---------------------------------
 -----------------------------------------------------------------------------*/
void loop()
{
  //-------SE LLAMAN FUNCIONES PARA NO SATURAR CON PROGRA EL LOOP
  menu = Serial.read();   //se toma como lectura serial
  opcion1();              //funcion para desplegar opciones de foto 1
  opcion2();              //funcion para desplegar opciones de foto 2
  opcion3();              //funcion para desplegar opciones de foto 3
 
}
/*-----------------------------------------------------------------------------
 ------------------------- F U N C I O N E S ----------------------------------
 -----------------------------------------------------------------------------*/
//-------FUNCION PARA MOSTRAR INFORMACION DE DIRECTORIO
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println(" ");

    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size());
    }
    entry.close();
  }
}
//-------FUNCION PARA DESPLEGAR LA PRIMER IMAGEN
void opcion1(void){
  if (menu == 49) {                   //lectura de foto1
    myFile = SD.open("antena.txt");   //se abre archivo de foto1
    if (myFile) {
      Serial.println("antena.txt:");  //se imprimer en monitor serial
      //leer linea por linea del archivo txt
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      //se cierra cuando termina de leer
      myFile.close();
    } 
    else {
      //otra vez el menu si hay un error
      Serial.println("Hubo un error, intento nuevamente");
      Serial.println("Escoger imagen 1, 2 o 3 ");
      Serial.println("1. antena.txt ");
      Serial.println("2. ramon.txt ");
      Serial.println("3. flophy.txt ");
    }
    Serial.println("Escoger imagen 1, 2 o 3 ");
    Serial.println("1. antena.txt ");
    Serial.println("2. ramon.txt ");
    Serial.println("3. flophy.txt ");
  }
}

//-------FUNCION PARA DESPLEGAR LA SEGUNDA IMAGEN
void opcion2(void){
  if (menu == 50) {
  
    myFile = SD.open("ramon.txt");
    if (myFile) {
      Serial.println("ramon.txt:");

      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());

      }
      // close the file:
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("Escoger imagen 1, 2 o 3 ");
      Serial.println("1. antena.txt ");
      Serial.println("2. ramon.txt ");
      Serial.println("3. flophy.txt ");


    }
    Serial.println("Escoger imagen 1, 2 o 3 ");
    Serial.println("1. antena.txt ");
    Serial.println("2. ramon.txt ");
    Serial.println("3. flophy.txt ");

  }
}

//-------FUNCION PARA DESPLEGAR LA TERCER IMAGEN
void opcion3(void){
  if (menu == 51) {
    // re-open the file for reading:
    myFile = SD.open("flophy.txt");
    if (myFile) {
      Serial.println("flophy.txt:");

      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());

      }
      // close the file:
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("Escoger imagen 1, 2 o 3 ");
      Serial.println("1. antena.txt ");
      Serial.println("2. ramon.txt ");
      Serial.println("3. flophy.txt ");


    }
    Serial.println("Escoger imagen 1, 2 o 3 ");
    Serial.println("1. antena.txt ");
    Serial.println("2. ramon.txt ");
    Serial.println("3. flophy.txt ");

  }
}
