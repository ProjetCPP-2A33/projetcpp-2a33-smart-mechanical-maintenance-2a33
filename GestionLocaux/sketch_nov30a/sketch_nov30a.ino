// Définir le pin pour le ventilateur (ou une LED)
const int fanPin = 9;

void setup() {
    // Configurer le pin du ventilateur comme sortie
    pinMode(fanPin, OUTPUT);
    digitalWrite(fanPin, LOW); // Assurer que le ventilateur est éteint au démarrage

    // Initialiser la communication série
    Serial.begin(9600);
}

void loop() {
    // Vérifier si des données sont reçues depuis Qt
    if (Serial.available() > 0) {
        char command = Serial.read(); // Lire la commande envoyée par Qt

        if (command == '1') {
            // Activer le ventilateur
            digitalWrite(fanPin, HIGH);
        } else if (command == '0') {
            // Désactiver le ventilateur
            digitalWrite(fanPin, LOW);
        }}
    }
    

    
