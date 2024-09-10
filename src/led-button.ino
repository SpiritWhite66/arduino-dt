const int led = 2; 
const int bouton = 3; // un bouton sur la broche 3
int etat; 
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(bouton, INPUT);
  digitalWrite(bouton, HIGH);

}

void loop() {
  etat = digitalRead(bouton);

  if(etat == HIGH) {
    digitalWrite(led, LOW); 
  } else {
    digitalWrite(led, HIGH); 
  }
}
