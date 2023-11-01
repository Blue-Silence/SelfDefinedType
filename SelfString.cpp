#include "SelfString.h"
#include <ostream>
#include <istream>

namespace SelfDefined {


	using SelfDefined::string;

	char& string::operator[](size_t i) {
		return this->s[i];
	}

	const char& string::operator[](size_t i) const {
		return this->s[i];
	}

	size_t string::size() const {
		return this->s.size();
	}

	void string::getline(std::istream& is) {
		*this = string();
		while (!(is.peek() == '\n') && !is.eof())
			this->s.push_back(is.get());

	}


	std::ostream& operator<<(std::ostream& os, string& s) {
		for (int i = 0; i < s.size(); i++)
			os << s.s[i];
		return os;
	}

	std::istream& operator>>(std::istream& is, string& s) {
		if (!is.good())
			return is;
		s = string();
		while (std::isspace(is.peek()))
			is.get();
		while (!std::isspace(is.peek()) && !is.eof())
			s.s.push_back(is.get());
		return is;
	}
}