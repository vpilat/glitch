// Generated by Glitch!
// Mon Apr 21 19:59:16 2025

void loop(void)
{
 int sensorValue  = analogRead(A0);
 float voltage  = ((sensorValue) * (((5.0) / (1023.0))));
 Serial.println(voltage);
}

void setup(void)
{
 Serial.begin(9600);
}
