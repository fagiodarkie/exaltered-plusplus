// exalteredpp.cpp: definisce il punto di ingresso dell'applicazione.
//

#include "exalteredpp.h"
#include "headers/character/character.h"

using namespace std;

int main()
{
	character::character testCharacter("He Who Cries Silver Tears");
	cout << testCharacter.getName() << endl;
	return 0;
}
