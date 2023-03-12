#include <iarduino_RF433_Receiver.h>                      // Подключаем библиотеку для работы с приёмником MX-RM-5V
//#include <LiquidCrystal.h>  // Добавляем необходимую библиотеку
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // Подключение библиотеки
#include <Servo.h>
Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
LiquidCrystal_I2C lcd(0x27,16,2); // Указываем I2C адрес (наиболее распространенное значение), а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой 
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)  // Подключаем библиотеку для работы с четырёхразрядным LED индикатором
iarduino_RF433_Receiver radio(2);                         // Создаём объект radio для работы с библиотекой iarduino_RF433, указывая номер вывода к которому подключён приёмник (можно подключать только к выводам использующим внешние прерывания)
int val1, val2;    // variable to read the value from the analog pin     
int                     data[3];                          // Создаём массив для приёма данных
//const uint8_t           pinLED=11;                        // Создаём константу с указанием вывода ШИМ к которому подключён светодиод
void setup(){
    Serial.begin(9600);
    lcd.init();                      // Инициализация дисплея  
    lcd.backlight();                 // Подключение подсветки
    lcd.setCursor(5,0);              // Установка курсора в начало первой строки
    lcd.print("X");       // Набор текста на первой строке
    lcd.setCursor(12,0);              // Установка курсора в начало второй строки
    lcd.print("Y");       // Набор текста на второй строке                                    // Инициируем работу LED индикатора
     lcd.setCursor(4,1);              // Установка курсора в начало второй строки
    lcd.print("Sostoyanie d");       // Набор текста на второй строке                                    // Инициируем работу LED индикатора
    delay(100);
    myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
    myservo2.attach(10);  // attaches the servo on pin 9 to the servo object
    pinMode(5, OUTPUT);    // sets the digital pin 5 as output
    radio.begin();                                        // Инициируем работу приёмника MX-RM-5V (в качестве параметра можно указать скорость ЧИСЛО бит/сек, тогда можно не вызывать функцию setDataRate)
    radio.setDataRate     (i433_1KBPS);                   // Указываем скорость приёма данных (i433_5KBPS, i433_4KBPS, i433_3KBPS, i433_2KBPS, i433_1KBPS, i433_500BPS, i433_100BPS), i433_1KBPS - 1кбит/сек
    radio.openReadingPipe (5);                            // Открываем 5 трубу для приема данных (если вызвать функцию без параметра, то будут открыты все трубы сразу, от 0 до 7)
//  radio.openReadingPipe (2);                            // Открываем 2 трубу для приёма данных (таким образом можно прослушивать сразу несколько труб)
//  radio.closeReadingPipe(2);                            // Закрываем 2 трубу от  приёма данных (если вызвать функцию без параметра, то будут закрыты все трубы сразу, от 0 до 7)
    radio.startListening  ();                             // Включаем приемник, начинаем прослушивать открытую трубу
//  radio.stopListening   ();                             // Выключаем приёмник, если потребуется
    
}
void loop(){
    if(radio.available()){                                // Если в буфере имеются принятые данные
        radio.read(&data, sizeof(data));                  // Читаем данные в массив data и указываем сколько байт читать
        lcd.setCursor(0, 0);
        lcd.print(data[0]);        // Выводим показания Trema слайдера на индикатор
        val1 = data[0];            // reads the value of the potentiometer (value between 0 and 1023)
        val1 = map(val1, 0, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)
        myservo1.write(val1);                  // sets the servo position according to the scaled value
        val2 = data[1];            // reads the value of the potentiometer (value between 0 and 1023)
        val2 = map(val2, 0, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)
        myservo2.write(val2);  
        lcd.setCursor(7, 0);
        lcd.print(data[1]);        // Выводим показания Trema слайдера на индикатор
        Serial.print(data[0]);
        Serial.println(data[1]);
        lcd.setCursor(0, 1);
        lcd.print(data[2]);        // Выводим показания Trema слайдера на индикатор
        digitalWrite(5, data[2]);
        Serial.println(data[2]);
           }                    
         //else {
           //delay(5000);
            //digitalWrite(5, LOW); 
         //}
                               // Если вызвать функцию available с параметром в виде ссылки на переменную типа uint8_t, то мы получим номер трубы, по которой пришли данные (см. урок 26.5)
}