// Generated by Glitch!
// Wed Aug 3 21:17:11 2022

int ReadSens_and_Condition(void)
{
	int i;
	int sval = 0;
	for(i = 0; i < 5; i++)
	{
		sval = ((sval) + (analogRead(0)));
	}
	sval = ((sval) / (5));
	sval = ((sval) / (4));
	sval = ((255) - (sval));
	return (sval);
}

void loop(void)
{
}

void setup(void)
{
}
