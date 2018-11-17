#pragma once

#include <string>

namespace character
{
	class character
	{
	public:
		character(std::string name);

		std::string getName() const;

	private:
		std::string m_name;

	};
}
