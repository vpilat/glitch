// Generated by Glitch!
// Sat Jul 9 19:58:45 2022

int led = 9;

int brightness = 0;

int fadeAmount = 5;

void loop(void)
{
	analogWrite(led, brightness);
	brightness = ((((brightness) + (fadeAmount))));
	delay(30);
}

void setup(void)
{
	pinMode(led, OUTPUT);
}
