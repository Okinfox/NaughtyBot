//#include <Servo.h>
#include <Wire.h> // bibliotheque pour la communication I2C
#include <Adafruit_GFX.h> // bibliotheque pour contrôler l'écran OLED.
#include <Adafruit_SSD1306.h> // pareil que celle d'au-dessus 

//#define SERVO_PIN 9   // Broche de contrôle du servomoteur

#define TRIG_PIN A0   // Broche Trig du capteur ultrasonique
#define ECHO_PIN A1   // Broche Echo du capteur ultrasonique

#define DETECTION_DISTANCE 50  // Distance en cm pour détecter une personne
#define NO_PERSON_THRESHOLD 3 // Nombre de lectures consécutives sans détection

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 // Pas de réinitialisation pour l'écran OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Servo myServo;  // Créer un objet Servo
//int noPersonCount = 0;

void setup() {
  /*myServo.attach(SERVO_PIN);  // Attache le servomoteur à la broche
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT); */
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // replace with your display's I2C address if different 
        // display initialization failed 
        for(;;); // don't proceed, loop forever 
    }

    Serial.begin(9600);  // Initialise la communication série
    display.clearDisplay(); // Efface l'écran
    display.setTextSize(2); // Taille du texte
    display.setTextColor(SSD1306_WHITE); // Couleur du texte
    display.setCursor(0, 0); // Position du curseur
    display.print("nana");
    display.display(); 

}

//Mesure distance à l'aide du capteur ultrasonique
float getDistance() {
    long duration;
    float distance;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration * 0.034) / 2;  // Calculer la distance en cm
    // 0.034 speed sound in air, 2 ultrasonic signal goes 2x the distance (going to and from object) 
    return distance;
}


void loop() {
  float distance = getDistance();
    Serial.print("Distance: ");
    Serial.println(distance);

    /*if (distance < DETECTION_DISTANCE) {
        // Personne détectée
        Serial.println("Personne détectée ! Arrêt du servomoteur.");
        myServo.write(90); // Position centrale (ou une position d'arrêt)
        delay(2000); // Attendre
    } else {
        noPersonCount++;
        if (noPersonCount >= NO_PERSON_THRESHOLD) {
            // Démarrer le servomoteur
            noPersonCount = 0;
            for (int angle = 0; angle <= 180; angle += 10) {
                myServo.write(angle);
                delay(20);
                distance = getDistance();
                if (distance < DETECTION_DISTANCE) {
                    Serial.println("Personne détectée pendant le mouvement ! Arrêt.");
                    myServo.write(90); // Arrêt
                    delay(2000);
                    break;
                }
            }
        }
      }
    delay(100); // Petite pause pour éviter les lectures trop rapides */

    display.clearDisplay();
    display.setCursor(0, 0);

    if (distance < 30) {
        display.clearDisplay();
        //display.setCursor(0, 0);
        display.print("recule, ton haleine...");
        //display.display(); 
    } 
    else if (distance < 60) {
        display.clearDisplay();
        //display.setCursor(0, 0);
        display.println("casse toi");
        //display.display();
    } 
    else {
        display.println("aucune detection"); 
    }
    
    display.display();
}
