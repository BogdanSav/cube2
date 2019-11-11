#include<ESP8266WebServer.h>
#include<ESP8266WiFi.h>
#include<Ticker1.h>

#include<SPI.h>
#include<FS.h>
#include<LedMatrix.h>


#define NUMBER_OF_DEVICES 1
#define CS_PIN 2
#define wheel_r_1 5
#define wheel_r_2 16
#define wheel_l_1 4
#define wheel_l_2 9

LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES,CS_PIN);
ESP8266WebServer HTTP(80);
File fsUploadFile;

//
int first;
int second;
//bool rst  =true;
//
String move_fow();
String move_back();
String move_left();
String move_right();
String inv_left();
String inv_right();
String move_fow_left();
String move_fow_right();
//String move_back_left();
//String move_back_right();
String _stop();
void t_left();
void t_right();
void inv_t_right();
void inv_t_left();
Ticker1 tr(t_right, 500);
Ticker1 tl(t_left, 500);
//Ticker1 inv_tr(inv_t_right, 1000);
//Ticker1 inv_tl(inv_t_left, 1000);


void setup() {

  WiFi.softAP("test");
  pinMode(wheel_r_1, OUTPUT);
  pinMode(wheel_r_2, OUTPUT);
  pinMode(wheel_l_1, OUTPUT);
  pinMode(wheel_r_2, OUTPUT);
  tr.start();
  tl.start();
//  inv_tr.start();
//  inv_tl.start();
ledMatrix.init();
  ledMatrix.commit();
  ledMatrix.clear();
  FS_init();
  
  Serial.begin(115200);
  
  HTTP.on("/sended", []()
  {
    HTTP.send(200, "text/html", "message recived");
    first  = HTTP.arg("first").toInt();
    second = HTTP.arg("second").toInt();

    setpixel(second, first);
  });
  HTTP.on("/clean", []()
  {

    HTTP.send(200, "text/html", clearpixel());

  });
  HTTP.on("/clearone", []()
  {
    first  = HTTP.arg("first").toInt();
    second = HTTP.arg("second").toInt();
    HTTP.send(200, "text/html", clearone(second, first));

  });
  HTTP.on("/fow", []() {
    HTTP.send(200, "text/html", move_fow());

  });
  HTTP.on("/back", []() {
    HTTP.send(200, "text/html", move_back());

  });
  HTTP.on("/left", []() {
    HTTP.send(200, "text/html", move_left());

  });
  HTTP.on("/right", []() {
    HTTP.send(200, "text/html", move_right());

  });
  HTTP.on("/stop", []() {
    HTTP.send(200, "text/html", _stop());

  });
  HTTP.on("/fow-right", []() {
    HTTP.send(200, "text/html", move_fow_right());

  });
  HTTP.on("/fow-left", []() {
    HTTP.send(200, "text/html", move_fow_left());

  });
//  HTTP.on("/back-right", []() {
//    HTTP.send(200, "text/html", move_back_right());
//
//  });
//  HTTP.on("/back-left", []() {
//    HTTP.send(200, "text/html", move_back_left());
//
//  });
// 


  HTTP.begin();
}


String setpixel(int first, int second)
{


  ledMatrix.setPixel(first, second);
  ledMatrix.commit();
  return "done";
  Serial.println("pixel set");


}
String clearpixel()
{
  ledMatrix.clear();
  ledMatrix.commit();
  Serial.println("allclear  ");
  return "done";
}
String clearone(int first, int second)
{
  Serial.println(first);
  Serial.println(second);
  ledMatrix.clearPixel(first, second);
  ledMatrix.commit();
  Serial.println("pixel clear");
  return "done";

}
void loop() {

  HTTP.handleClient();
//  tr.update();
//  tl.update();
//  inv_tr.update();
//  inv_tl.update();



}
String move_fow()
{
  digitalWrite(wheel_r_1, HIGH);
  digitalWrite(wheel_r_2, LOW);
  digitalWrite(wheel_l_1, HIGH);
  digitalWrite(wheel_l_2, LOW);
  Serial.println("fow");
  return "fow";

}
String move_back()
{
  digitalWrite(wheel_r_1, LOW);
  digitalWrite(wheel_r_2, HIGH);
  digitalWrite(wheel_l_1, LOW);
  digitalWrite(wheel_l_2, HIGH);
  Serial.println("Back");
  return "back";
}
String move_left()
{
  digitalWrite(wheel_r_1, HIGH);
  digitalWrite(wheel_r_2, LOW);
  digitalWrite(wheel_l_1, LOW);
  digitalWrite(wheel_l_2, LOW);
  Serial.println("left");
  return "left";
}
String move_right()
{
  digitalWrite(wheel_r_1, LOW);
  digitalWrite(wheel_r_2, LOW);
  digitalWrite(wheel_l_1, HIGH);
  digitalWrite(wheel_l_2, LOW);
  Serial.println("right");
  return "right";
}
String _stop()
{
  digitalWrite(wheel_r_1, LOW);
  digitalWrite(wheel_r_2, LOW);
  digitalWrite(wheel_l_1, LOW);
  digitalWrite(wheel_l_2, LOW);
  return "stop";



}
String inv_left()
{
  digitalWrite(wheel_r_1, LOW);
  digitalWrite(wheel_r_2, HIGH);
  digitalWrite(wheel_l_1, LOW);
  digitalWrite(wheel_l_2, LOW);
  Serial.println("left");
  return"ileft";
}
String inv_right()
{
  digitalWrite(wheel_r_1, LOW);
  digitalWrite(wheel_r_2, LOW);
  digitalWrite(wheel_l_1, LOW);
  digitalWrite(wheel_l_2, HIGH);

  return "iright";


}

String move_fow_left()
{
  move_left();
  tr.update();

  //t_right();
  return "done";

}
String move_fow_right()
{
  move_right();
  tl.update();
 // t_left();
  return "done";

}
//String move_back_left()
//{
//  inv_left();
//  inv_t_right();
//
//  return "done";
//
//}
//String move_back_right()
//{
//  inv_right();
//  inv_t_left();
//  return "done";
//}
void t_left() {
  move_left();
}
void t_right() {
  move_right();
}
//void inv_t_right()
//{
//  inv_right();
//}
//void inv_t_left()
//{
//  inv_left();
//}
