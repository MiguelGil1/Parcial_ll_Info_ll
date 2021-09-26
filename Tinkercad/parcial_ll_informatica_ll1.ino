#include <Adafruit_NeoPixel.h>
#define LED_PIN 2
#define LED_COUNT 256

Adafruit_NeoPixel leds(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// C++ code
//

//PROTOTIPO DE FUNCIONES
void cleanMatrix();
void mostrarBandera();
void mostrarBandera2D();
//FIN DECLARACION PROTOTIPO DE FUNCIONES

//DELCARACION DE VARIABLES
//Nota importante: Ponga aca el contenido del archivo de texto resultante al
//aplicar el algoritmo de redimensioamiento
//De lo contrario no se asegura un correcto funcionamiento en el programa


//FIN DECLARACION DE VARIABLES

void setup(){
  leds.begin();
  Serial.begin(9600);
  mostrarBandera();
  //cleanMatrix();
  //mostrarBandera2D();
}

void loop(){}

void mostrarBandera(){
  uint8_t R = 0;
  uint8_t G = 0;
  uint8_t B = 0;
  for(int i = 0; i < LED_COUNT; i++){
    R = RedMatrix[i];
    G = GreenMatrix[i];
    B = BlueMatrix[i];
    leds.setPixelColor(i,R,G,B);
    Serial.print(i+1);
    Serial.print(".) ");
    Serial.print("{");
    Serial.print(R); 
    Serial.print(" , ");
    Serial.print(G);
    Serial.print(" , ");
    Serial.print(B);
    Serial.println("}");
    
  }
  Serial.print("\nSe termina de configurar la matriz");
  leds.show();
}
/*void mostrarBandera2D(){
  uint8_t R = 0;
  uint8_t G = 0;
  uint8_t B = 0;
  int cont = 0;
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      R = RedMatrix2D[i][j];
      G = GreenMatrix2D[i][j];
      B = BlueMatrix2D[i][j];
      leds.setPixelColor(cont,R,G,B);
      Serial.print(cont+1);
      Serial.print(".) ");
      Serial.print("{");
      Serial.print(R); 
      Serial.print(" , ");
      Serial.print(G);
      Serial.print(" , ");
      Serial.print(B);
      Serial.println("}");
      cont += 1;
    } 
  }
  Serial.print("\nSe termina de configurar la matriz");
  leds.show();
}*/

/*void cleanMatrix(){
  Serial.print("\nLimpiando Matriz");
  for(int i = 0; i < LED_COUNT; i++){
    leds.setPixelColor(i,0,0,0);    
  }
  leds.show(); 
  Serial.print("\nMatriz limpia");
}*/