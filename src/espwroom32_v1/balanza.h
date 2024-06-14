//balanza.h

//Función calibración
void calibration(LiquidCrystal_I2C &lcd, HX711 &balanza, int peso_calibracion, long &escala) { 
  boolean conf = true;
  long adc_lecture;

  // restamos el peso de la base de la balaza
  lcd.setCursor(0, 0);
  lcd.print("Calibrando base");
  lcd.setCursor(4, 1);
  lcd.print("Balanza");
  delay(3000);
  balanza.read();
  balanza.set_scale(); //La escala por defecto es 1
  balanza.tare(20);  //El peso actual es considerado zero.
  lcd.clear();

  //Iniciando calibración
  while (conf == true) {

    lcd.setCursor(0, 1);
    lcd.print("Peso referencial:");
    lcd.setCursor(1, 1);
    lcd.print(peso_calibracion);
    lcd.print(" g        ");
    delay(3000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Ponga el Peso");
    lcd.setCursor(1, 1);
    lcd.print("Referencial");
    delay(3000);

    //Lee el valor del HX711
    adc_lecture = balanza.get_value(100);

    //Calcula la escala con el valor leido dividiendo el peso conocido
    escala = adc_lecture / peso_calibracion;

    //Guarda la escala en la EEPROM
    EEPROM.put( 0, escala );
    delay(100);
    lcd.setCursor(1, 0);
    lcd.print("Retire el Peso");
    lcd.setCursor(1, 1);
    lcd.print("referencial");
    delay(3000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("READY!!....");
    delay(3000);
    lcd.clear();
    conf = false; //para salir de while
    lcd.clear();

  }
}


