#pragma once
#ifndef Self_Map

#include "SelfVector.h"

namespace Private_SelfMap {
	template<typename Key, typename Value>
	class Pair {
	public:
		Key k;
		Value v;
	};
}

namespace SelfDefined {


template<typename Key, typename Value> 
class map {
	SelfDefined::vector<Private_SelfMap::Pair<Key, Value>> s;

public:
	//map(map& other);
	Value& operator[](Key k);
	bool isElem(Key k);
	void deleteK(Key k);

};
template<typename Key, typename Value> Value& map<Key, Value>::operator[](Key k){
	for (int i = 0; i < this->s.size(); i++)
		if (this->s[i].k == k)
			return this->s[i].v;
	this->s.push_back(Private_SelfMap::Pair{ k, Value() });
	return this->s[this->s.size() - 1].v;
}

template<typename Key, typename Value> bool map<Key, Value>::isElem(Key k) {
	for (int i = 0; i < this->s.size(); i++)
		if (this->s[i].k = k)
			return true;
	return false;
}

template<typename Key, typename Value> void map<Key, Value>::deleteK(Key k) {
	for (int i = 0; i < this->s.size(); i++)
		if (this->s[i].k = k)
		{
			this->s[i] = this->s[this->s.size() - 1];
			this->s.pop_back();
		}

}
}


#endif // !Self_Map
