#pragma once

#include "SelfVector.h"
#include "swap.h"
namespace SelfDefined {

	using SelfDefined::vector;
	template<typename Elem> class heap {
		vector<Elem> s;
	public:
		heap() {
			Elem e{};
			this->s.push_back(e);//Boundary
		}
		void insert(Elem e);
		Elem& top() { return this->s[1]; }
		void pop();
		size_t size() { return this->s.size() - 1; }
};


	template<typename Elem> void heap<Elem>::insert(Elem e) {
		this->s.push_back(e);
		for (size_t i = this->s.size() - 1; i > 1; i = i / 2)
			if (this->s[i] > this->s[i / 2])
				swap(this->s[i], this->s[i / 2]);
			else
				break;
	}

	template<typename Elem> void heap<Elem>::pop() {
		if (this->s.size() < 2)
			throw "Empty heap!";
		swap(this->s[1], this->s[this->s.size() - 1]);
		this->s.pop_back();
		size_t i = 1;
		auto& s = this->s;
		for (;;)
		{
			if ((i * 2) >= s.size())
				break;
			if ((i * 2 + 1) >= s.size())
			{
				if (s[i] < s[i * 2])
					swap(s[i], s[i * 2]);
				break;
			}
			if ((s[i * 2] >= s[i * 2 + 1])
				&&(s[i] < s[i * 2]))
			{
				swap(s[i], s[i * 2]);
				i = i * 2;
			}

			else if ((s[i * 2] < s[i * 2 + 1])
				&&(s[i] < s[i * 2+1]))
			{
				swap(s[i], s[i * 2+1]);
				i = i * 2 + 1;
			}
			else 
				break;
		}
	}
}
