// exalteredpp.cpp: definisce il punto di ingresso dell'applicazione.
//

#include "exalteredpp.h"
#include "character.h"

using std::cout;
using std::endl;

int main()
{
	character::character testCharacter("He Who Cries Silver Tears");
	cout << testCharacter.getName() << endl;
	character::attribute attribute("lol", 1);
	cout << "attribute " << (string)attribute << " has value " << (int)attribute << endl;
	return 0;
}
