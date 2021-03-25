#ifndef LIGHT_FLASH_H
#define LIGHT_FLASH_H
#include <arduino.h>
void light_flash_count(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(13, 1);
    delay(200);
    digitalWrite(13, 0);
    delay(200);
  }
}
void light_flash_morse_code(String morse_code) {
  // DASH == -
  // DOT == x

int n = morse_code.length();
int j = 500;
for (int i = 0; i < n; i++) {
  if ((String)morse_code[i] == "x") {
    // DOT
    j = 1500;
  } else {
    // DASH
    j = 500;
  }
  digitalWrite(13, 1);
  delay(j);
  digitalWrite(13, 0);
  delay(500);
}
}
#endif
