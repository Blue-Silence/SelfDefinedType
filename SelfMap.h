#pragma once

#include "RedBlack.h"

namespace SelfDefined {

	template<typename Key, typename Value> class map {
		class KV {
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

		RB<KV> t;
	public:
		bool contains(Key k) { Value e{}; return this->t.contains({ k,e }); }
		void remove(Key k) { Value e{}; this->t.remove({ k,e }); }
		Value& operator[](Key k) {
			KV *v;
			Value e{};
			if (!this->t.contains({ k,e}, &v))
			{
				this->t.insert({ k,e});
				this->t.contains({ k,e}, &v);
			}
			return v->v;
		}

		RB<KV>::Iterator begin() { return t.begin(); }
		RB<KV>::Iterator end() { return t.end(); }

		//void debug() { this->t.print(); }

	};

}
