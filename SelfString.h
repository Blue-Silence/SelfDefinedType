#pragma once
#ifndef Self_String

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
}

#endif // !Self_String

