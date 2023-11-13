#pragma once

namespace SelfDefined {

	template<typename Elem> class stack {
		class Node {
			Elem e;
			Node* next;
			Node(Elem e) { this->e = e; this->next = nullptr; }
			Node* copy() const {
				auto newN = new Node{ this->e };
				newN->next = (this->next != nullptr ? this->next->copy() : nullptr);
				return newN;
			}
			void delAll() {
				if (this->next != nullptr)
					delete this->next;
			}
			friend class stack;
		};
		stack::Node* p;
		size_t len;
	public:
		stack() { this->p = nullptr; this->len = 0; }
		size_t size() const { return this->len; }
		const Elem& top() const { // Accessing the top
			if (this->len == 0)
				throw "FATAL: Accessing empty stack.";
			return this->p->e;
		}
		Elem& top() {
			if (this->len == 0)
				throw "FATAL: Accessing empty stack.";
			return this->p->e;
		}
		void push(Elem e) { //Push elem into stack
			this->len++;
			auto np = new Node(e);
			np->next = this->p;
			this->p = np;
		}
		void pop() { //Pop out the top element
			if (this->len == 0)
				throw "FATAL: Accessing empty stack.";
			this->len--;
			auto np = this->p->next;
			delete this->p;
			this->p = np;
		}
		stack& operator=(const stack& from) {
			if (this->p != nullptr)
			{
				this->p->delAll();
				delete this->p;
			}
			this->len = from.len;
			if (from.p != nullptr)
				this->p = from.p->copy();
			return *this;
		}
		stack(const stack& from) {
			this->len = 0;
			this->p = nullptr;
			*this = from;
		}

		~stack() {
			if (this->p != nullptr)
			{
				this->p->delAll();
				delete this->p;
			}
				
		}
		
	};

}
