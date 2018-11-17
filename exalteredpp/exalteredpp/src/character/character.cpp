#include "../../headers/character/character.h"

namespace character
{
	character::character(std::string name) : m_name(name) {};

	std::string character::getName() const
	{
		return m_name;
	}
}