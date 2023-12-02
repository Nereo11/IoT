#include "Votaciones.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);




  Serial.println("Hello, ESP32!");
  myrtc.RTC_init();
  ACT.lcd_init();
  myMqtt.setup_WiFi ( );
  myMqtt.set_MQTT_server ( );
  myMqtt.set_MQTT_callback (  );
  
MSD.MicroSD_init();
proximity.init();
myMenu.initMenu();

}

void loop() {
  unsigned long currentTime = millis();

  TSK.actualizar_tareas();
  //TSK.tarea_fac();
 //TSK.tarea_msd();
  myMqtt.reconnect_MQTT();
  TSK.tarea_mqtt();
  myMenu.menuActions();
  proximity.read();
 // TSK.tarea_lcd();
  //TSK.tarea_rtc();
  // put your main code here, to run repeatedly:
   // this speeds up the simulation
}
