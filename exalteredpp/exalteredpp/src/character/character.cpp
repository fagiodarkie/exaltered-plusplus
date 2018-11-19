#include "character.h"

namespace character
{
	character::character(std::string name) : _name(name)
	{

	};

	std::string character::getName() const
	{
		return _name;
	}
}