#pragma once

namespace SelfDefined {

	template<typename Elem> class stack {
		class Node {
			Elem e;
			Node* next;
			Node(Elem e) { this->e = e; this->next = nullptr; }
			friend class stack;
		};
		stack::Node* p;
		size_t len;
	public:
		stack() { this->p = nullptr; this->len = 0; }
		size_t size() const { return this->len; }
		const Elem& top() const {
			if (this->len == 0)
				throw "FATAL: Accessing empty stack.";
			return this->p->e;
		}
		void push(Elem e) {
			this->len++;
			auto np = new Node(e);
			np->next = this->p;
			this->p = np;
		}
		void pop() {
			if (this->len == 0)
				throw "FATAL: Accessing empty stack.";
			this->len--;
			auto np = this->p->next;
			delete this->p;
			this->p = np;
		}
	};

}
