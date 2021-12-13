#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
char buffer[456];
//********************************Setup Loop*********************************//
char pid;
void setup() {
  Serial.begin(9600); // For debug use
  Serial.println("CAN Read - Testing receival of CAN Bus message");  
  delay(1000);
  
  if(Canbus.init(CANSPEED_500))  //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
    
  delay(1000);
}

//********************************Main Loop*********************************//

void loop(){
Canbus.ecu_req(ENGINE_RPM,buffer);
delay(100);
Serial.print("RPM: ");
Serial.println(buffer);
delay(100);
Canbus.ecu_req(ENGINE_COOLANT_TEMP,buffer);
delay(100);
Serial.print("Coolant Temp: ");
Serial.println(buffer);
delay(100);
Canbus.ecu_req(THROTTLE,buffer);
delay(100);
Serial.print("Throttle: ");
Serial.println(buffer);
delay(100);
Canbus.ecu_req(ENGINE_LOAD,buffer);
delay(100);
Serial.print("Engine Load: ");
Serial.println(buffer);
delay(100);
Canbus.ecu_req(VEHICLE_SPEED,buffer);
delay(100);
Serial.print("Vehicle Speed: ");
Serial.println(buffer);
delay(100);

}
