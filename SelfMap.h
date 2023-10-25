#pragma once

#include "RedBlack.h"

namespace Private_SelfMap {
	template<typename Key, typename Value> class KV {
	public:
		Key k;
		Value v;
		KV() {}
		KV(Key k, Value v) { this->k = k, this->v = v; }
		bool operator>(const KV& b) { return this->k > b.k; }
		bool operator<(const KV& b) { return this->k < b.k; }
		bool operator>=(const KV& b) { return this->k >= b.k; }
		bool operator<=(const KV& b) { return this->k <= b.k; }
		bool operator==(const KV& b) { return this->k == b.k; }
		bool operator!=(const KV& b) { return this->k != b.k; }
	};
}

namespace SelfDefined {
	using Private_SelfMap::KV;

	template<typename Key, typename Value> class map {
		RB<KV<Key, Value>> t;
	public:
		bool contains(Key k) { Value e{}; return this->t.contains({ k,e }); }
		void remove(Key k) { Value e{}; this->t.remove({ k,e }); }
		Value& operator[](Key k) {
			KV<Key,Value> *v;
			Value e{};
			if (!this->t.contains({ k,e}, &v))
			{
				this->t.insert({ k,e});
				this->t.contains({ k,e}, &v);
			}
			return v->v;

		}

		//void debug() { this->t.print(); }

	};

}
