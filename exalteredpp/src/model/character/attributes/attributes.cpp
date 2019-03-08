#include "attributes/attributes.h"

namespace character {
	attribute::attribute(string name) : _value(0), _name(name) {}

	attribute::attribute(string name, int value) : _value(value), _name(name) {}

	attribute::operator int() const {
		return _value;
	}

	attribute::operator string() const {
		return _name;
	}
}
