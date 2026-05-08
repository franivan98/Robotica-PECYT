//Codigo para probar matries LCD 16x2 con I2C

/**
 * Para testear el lcd, tenes que conectar el LCD con i2c directamente a la placa, sin el shield:
 * Pin A3 -> VCC del LCD
 * Pin A2 -> GND del LCD
 * Pin A4 -> SDA del LCD
 * Pin A5 -> SCL del LCD
 * 
 * Luego, subis este codigo a la placa y deberias ver como se van llenando las celdas del LCD 
 * con asteriscos, y luego se muestra un mensaje de prueba.
 * Si el LCD no muestra nada, revisa las conexiones y asegurate de que el LCD esté funcionando correctamente.
 * 
 * Nota: Cada vez q cambies de LCD, tenes que reiniciar la placa para que vuelva a encender el LCD por software. 
 * (boton rojo de reset o desconectando y reconectando la alimentación)
 * 
 * Nota2: No te olvides de INCLUIR LAS LIBRERIAS DE I2C Y LCD EN EL PROYECTO, sino el codigo no va a compilar.
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección del LCD y tamaño

void setup() {
  // Encender alimentación por software
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);

  delay(500); 

  lcd.init();
  lcd.backlight();   
}

void loop() {
  // Aquí puedes agregar código para actualizar el LCD o realizar otras tareas
  // probar celda por celda
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 16; col++) {
        lcd.setCursor(col, row); // Establece el cursor en la posición (col, row)
        lcd.print("*"); // Imprime un asterisco en esa posición
        delay(50); // Espera un poco antes de imprimir el siguiente
        }
    }
    // Limpia el LCD después de probar todas las celdas
    delay(300); // Espera un momento antes de limpiar
    lcd.clear();
    // imprimir mensajes 
    lcd.setCursor(0, 0); // Establece el cursor en la primera fila
    lcd.print("Hola, Mundo!"); // Imprime un mensaje en la primera fila
    lcd.setCursor(0, 1); // Establece el cursor en la segunda fila
    lcd.print("LCD 16x2 I2C"); // Imprime un mensaje en la segunda fila
    delay(2000); // Espera un momento para que se pueda leer el mensaje
}