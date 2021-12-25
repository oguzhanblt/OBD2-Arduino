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
  Serial.println("CAN Read");  
  delay(1000);
  
  if(Canbus.init(CANSPEED_500))  //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
    
  delay(1000);
}

//********************************Main Loop*********************************//

void loop(){
/*Canbus.ecu_req(ENGINE_RPM,buffer);
delay(100);
Serial.print("RPM: ");
Serial.println(buffer);
delay(100);*/
getRpm();
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

void getRpm(){
  tCAN message;
  int rpm;
  int engine_data;
  int timeout = 0;
  char message_ok = 0;
  // Prepair message
  message.id = PID_REQUEST;
  message.header.rtr = 0;
  message.header.length = 8;
  message.data[0] = 0x02;
  message.data[1] = 0x01;
  message.data[2] = 0x0C ;
  message.data[3] = 0x00;
  message.data[4] = 0x00;
  message.data[5] = 0x00;
  message.data[6] = 0x00;
  message.data[7] = 0x00;           
  
  mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
  mcp2515_send_message(&message);
  if (mcp2515_send_message(&message))
  {
    if (mcp2515_check_message()) 
    {
      if (mcp2515_get_message(&message)) 
      {
        if(message.id==PID_REPLY)
        {
          if(message.data[2]==0x0c)
          {   /* Details from http://en.wikipedia.org/wiki/OBD-II_PIDs */
                        //   ((A*256)+B)/4    [RPM]
            rpm =  ((message.data[3]*256) + message.data[4])/4;
            if(rpm=>700 && rpm<=6450){
              Serial.print(rpm);
              Serial.println("...rpm");
              delay(1000);
            }
          }
        }
      }
    }
  }
}
