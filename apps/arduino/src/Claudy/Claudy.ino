/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  */

#include "Display_SPD2010.h"
#include "LVGL_Driver.h"
#include "claude_face_config.h"
#include "claude_face.h"
#include "claude_face_v2.h"

/* Serial command input: type a face state key (start/attention/idle/done/
 * fail/danger/ratelimit/subagent/end) into the Serial Monitor and press
 * Enter. */
void Handle_Serial_Command()
{
  if (!Serial.available()) return;
  String cmd = Serial.readStringUntil('\n');
  cmd.trim();
  if (cmd.length() == 0) return;
  cmd.toLowerCase();

  printf("Serial command: \"%s\"\r\n", cmd.c_str());
  claude_face_cycle(false);
  claude_face_set_state(claude_face_from_key(cmd.c_str()));
}

void Driver_Init()
{
  I2C_Init();
  TCA9554PWR_Init(0x00);
  Backlight_Init();
  Set_Backlight(50);      //0~100
}

void setup()
{
  Serial.begin(115200);

  Driver_Init();
  LCD_Init();
  Lvgl_Init();

  claude_face_create(NULL);
  claude_face_set_state(CF_STATE_DONE);   // pin to a single face instead of cycling
}

void loop() {
  Lvgl_Loop();
  Handle_Serial_Command();
  vTaskDelay(pdMS_TO_TICKS(5));
}
