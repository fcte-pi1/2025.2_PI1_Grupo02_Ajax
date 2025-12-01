
#ifndef BUZZERH
#define BUZZERH
#include "pitches.h"
#define BUZZZER_PIN  18 // sends tension via d18, by default. Override as needed. Other pin should go ground.

namespace buzzer{
    int melody1[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_B0, NOTE_B3, NOTE_C4,
    -1
    };
    int noteDurations1[] = {
    250, 125, 125, 250, 125, 50, 250, 250
    };
    void run_buzzer_melody1(int *melody, int *dur) {  
        for (int thisNote = 0; melody[thisNote] > -1; thisNote++) {
            tone(BUZZZER_PIN, melody[thisNote], dur[thisNote]);
            int pauseBetweenNotes = dur[thisNote] * 1.30;
            delay(pauseBetweenNotes);
            noTone(BUZZZER_PIN);
        }
    }
}

#endif