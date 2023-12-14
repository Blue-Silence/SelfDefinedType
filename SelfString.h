#pragma once

#include "SelfVector.h"
#include <ostream>
#include <istream>

namespace SelfDefined {

	class string {
		vector<char> s;
		int cmp(const string& b) const {
			auto& a = *this;
			auto len = a.size() < b.size() ? a.size() : b.size();
			for (size_t i = 0; i < len; i++)
			{
				if (a.s[i] < b.s[i])
					return -1;
				if (a.s[i] > b.s[i])
					return 1;
			}
			if (a.size() < b.size())
				return-1;
			if (a.size() > b.size())
				return 1;
			return 0;
		}

	public:
		char& operator[](size_t i);
		const char& operator[](size_t i) const;
		size_t size() const;
		friend std::ostream& operator<<(std::ostream& os, string &s);
		friend std::istream& operator>>(std::istream& is, string &s);
		void getline(std::istream& is);

		
		bool operator>(const string& b) { return this->cmp(b) == 1; }
		bool operator<(const string& b) { return this->cmp(b) == -1; }
		bool operator>=(const string& b) { return this->cmp(b) != -1; }
		bool operator<=(const string& b) { return this->cmp(b) != 1; }
		bool operator==(const string& b) { return this->cmp(b) == 0; }
		bool operator!=(const string& b) { return this->cmp(b) != 0; };

	};


	inline char& string::operator[](size_t i) {
		return this->s[i];
	}

	inline const char& string::operator[](size_t i) const {
		return this->s[i];
	}

	inline size_t string::size() const {
		return this->s.size();
	}

	inline void string::getline(std::istream& is) {
		*this = string();
		while (!(is.peek() == '\n') && !is.eof())
			this->s.push_back(is.get());

	}


	inline std::ostream& operator<<(std::ostream& os, string& s) {
		for (int i = 0; i < s.size(); i++)
			os << s.s[i];
		return os;
	}

	inline std::istream& operator>>(std::istream& is, string& s) {
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

