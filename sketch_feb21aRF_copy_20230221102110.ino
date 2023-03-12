#include <iarduino_RF433_Transmitter.h>                   // Подключаем библиотеку для работы с передатчиком FS1000A
iarduino_RF433_Transmitter radio(12);                     // Создаём объект radio для работы с библиотекой iarduino_RF433, указывая номер вывода к которому подключён передатчик
int                        data[3];                       // Создаём массив для передачи данных
//int inPin = 5; 
void setup(){
    Serial.begin(9600);
   // pinMode(inPin, INPUT);    // sets the digital pin 5 as input
    radio.begin();                                        // Инициируем работу передатчика FS1000A (в качестве параметра можно указать скорость ЧИСЛО бит/сек, тогда можно не вызывать функцию setDataRate)
    radio.setDataRate     (i433_1KBPS);                   // Указываем скорость передачи данных (i433_5KBPS, i433_4KBPS, i433_3KBPS, i433_2KBPS, i433_1KBPS, i433_500BPS, i433_100BPS), i433_1KBPS - 1кбит/сек
    radio.openWritingPipe (5);                            // Открываем 5 трубу для передачи данных (передатчик может передавать данные только по одной из труб: 0...7)
}                                                         // Если повторно вызвать функцию openWritingPipe указав другой номер трубы, то передатчик начнёт передавать данные по вновь указанной трубе
void loop(){
    data[0] = analogRead(A1);                             // считываем показания Trema слайдера с вывода A1 и записываем их в 0 элемент массива data
    data[1] = analogRead(A2); // считываем показания Trema потенциометра с вывода A2 и записываем их в 1 элемент массива data
    data[2] = analogRead(A5);
    radio.write(&data, sizeof(data));                     // отправляем данные из массива data указывая сколько байт массива мы хотим отправить
    delay(10);    
    Serial.print(data[0]);
    Serial.println(data[1]);
       // digitalWrite(5, data[2]);
    Serial.println(data[2]);                                        
}
