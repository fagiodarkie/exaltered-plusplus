#pragma once

#include <string>
#include <map>
#include "attributeNames.h"

using std::string;

namespace character {
	class attribute {
	public:
		operator int() const;
		operator int&();

		operator string();

		attribute(string name);

		attribute(string name, int value);

	private:
		int _value;
		string _name;
	};

	typedef std::map<attributeName, attribute> attributes;
}
