#pragma once

#include <string>
#include "character/attributes/attributes.h"

namespace character
{
	class character
	{
	public:
		character(std::string name);

		std::string getName() const;

		attributes getAttributes() const;

	private:
		std::string _name;
		attributes _attributes;

	};
}
