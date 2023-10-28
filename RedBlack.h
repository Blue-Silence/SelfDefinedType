#pragma once

#include <tuple>

#include "Tree_Iterator.h"

namespace SelfDefined {

	template<typename Elem>
	class RB {
	private:
		/////////////////////////////////////////////////////////////////////
		
		// Nested class that represnent the node in tree
		class Node {
			static const int L = 1, M = 2, R = 3, FST = -1, SND = -2;

			RB::Node* left, * right;
		public:
			Elem e;
		private:
			bool slave;

			friend class RB;
			Node(Elem e);
			void delAll();
			Node* copy();
			int nodeSize();
			int posInNode(Elem e);
			Elem* getE(int pos);
			Node** getP(int pos);
			std::tuple<RB::Node*, bool> toLeft();
			std::tuple<RB::Node*, bool> toRight();

			RB::Node* insert(Elem e);
			std::tuple<RB::Node*, bool> remove(Elem e);
			bool contains(Elem e, Elem** rp);

			int print();
			void linear_print();


			friend class BSTIterator<Node>;
		};
		/////////////////////////////////////////////////////////////////////
		
		/// Nested class that represnent the interator
		class Iterator : public BSTIterator<Node> {
		public:
			Elem& operator*() { return this->now->e; }
		};

		
		/////////////////////////////////////////////////////////////////////
		
		/// Tree as a whole
	
		Node* t; // Root node
	public:
		RB();
		~RB();
		void insert(Elem e);
		void remove(Elem e);
		bool contains(Elem e, Elem** rp = nullptr);
		RB& operator=(const RB& from);
		RB(const RB& from);

		void print();	//Call Node::print() to print out Graphviz script that correspond to tree graph. Help understand and debug.
						//An online Graphviz website: dreampuf.github.io
						//Use std::format, so C++ 20 is required.
		void linear_print();
						//Required by course


		Iterator begin() { return Iterator(this->t); }
		Iterator end() { return static_cast<Iterator>((Iterator::end)(this->t)); }

	};


	template<typename Elem> RB<Elem>::Node::Node(Elem e) {
		this->e = e;
		this->left = nullptr;
		this->right = nullptr;
		this->slave = false;
	}

	template<typename Elem> void RB<Elem>::Node::delAll() {
		if (this->left != nullptr)
		{
			this->left->delAll();
			delete this->left;
		}
		if (this->right != nullptr)
		{
			this->right->delAll();
			delete this->right;
		}
	}

	template<typename Elem> typename RB<Elem>::Node* RB<Elem>::Node::copy() {
		auto n = new Node{ this->e };
		n->slave = this->slave;
		if (this->left != nullptr)
			n->left = this->left->copy();
		if (this->right != nullptr)
			n->right = this->right->copy();
		return n;
	}



	template<typename Elem> int RB<Elem>::Node::nodeSize() {
		int c = 1;
		for (auto p = this->left; p != nullptr && p->slave; p = p->left)
			c++;
		return c;
	}

	template<typename Elem> int RB<Elem>::Node::posInNode(Elem e) {
		if (this->e == e)
			return FST;
		if (this->e < e)
			return R;
		if (this->left == nullptr || !this->left->slave)
			return L;

		if (this->left->e == e)
			return SND;
		if (this->left->e < e)
			return M;
		return L;
	}

	template<typename Elem> Elem* RB<Elem>::Node::getE(int pos) {
		switch (pos) {
		case FST:
			return &(this->e);
		case SND:
			if (this->left != nullptr && this->left->slave)
				return &(this->left->e);
		}
		throw "Value position not valid";
	}

	template<typename Elem> std::tuple<typename RB<Elem>::Node*, bool> RB<Elem>::Node::toLeft() {
		if (this->left == nullptr)
			return{ this,false };
		if (this->left->nodeSize() == 2)
		{
			auto newRoot = this->left;
			this->left->slave = false;
			this->left->left->slave = false;
			this->left = newRoot->right;
			newRoot->right = this;
			return { newRoot,true };
		}
		this->left->slave = true;
		return { this,false };
	}

	template<typename Elem> std::tuple<typename RB<Elem>::Node*, bool> RB<Elem>::Node::toRight() {
		if (this->right == nullptr)
			return{ this,false };
		if (this->right->nodeSize() == 2)
		{
			auto newRoot = this->right->left;
			this->slave = this->right->slave = this->right->left->slave = false;
			this->right->left = newRoot->right;
			newRoot->right = this->right;
			this->right = newRoot->left;
			newRoot->left = this;
			return { newRoot,true };
		}
		auto newRoot = this->right;
		newRoot->slave = false;
		this->slave = true;
		this->right = newRoot->left;
		newRoot->left = this;
		return { newRoot,false };
	}

	template<typename Elem> typename RB<Elem>::Node** RB<Elem>::Node::getP(int pos) {
		//std::cout << "getP in:" << this->e << "\n";
		if (pos == R)
		{
			//std::cout << "B1\n";
			return &(this->right);
		}

		if (this->left != nullptr && this->left->slave)
		{
			switch (pos) {
			case L:
				//std::cout << "B2\n";
				return &(this->left->left);
			case M:
				//std::cout << "B3\n";
				return &(this->left->right);
			}
		}
		if (pos == L)
			return &(this->left);
		throw "Pointer position not valid";
	}

	template<typename Elem> typename RB<Elem>::Node* RB<Elem>::Node::insert(Elem e) {
		auto pos = this->posInNode(e);
		if (pos < 0)
		{
			*(this->getE(pos)) = e;
			return this;
		}
		auto p = this->getP(pos);
		if (*p == nullptr)
		{
			auto np = new Node{ e };
			switch (pos)
			{
			case M:
				//std::cout << "A\n";
				np->slave = true;
				np->left = this->left;
				this->left = np;
				return this;
			case R:
				//std::cout << "B\n";
				this->slave = true;
				np->left = this;
				return np;
			case L:
				//std::cout << "C\n";
				np->slave = true;
				*p = np;
				return this;
			}
			//*p = np;
			//this->print();
			//std::cout <<"left:"<<&(this->left) <<"  right:"<<&(this->right) << "  p:" << p << "\n";
			return this;
		}
		*p = (*p)->insert(e);
		if ((*p)->nodeSize() < 3)
			return this;
		//std::cout << "M4\n";

		Node* n = *p;
		Node* newH = n->left;
		n->slave = n->left->slave = n->left->left->slave = false;
		n->left = newH->right;
		newH->right = n;

		switch (pos) {
		case L:
			newH->slave = true;
			*p = newH;
			return this;
		case M:
			//	Node* n = p;
			newH->slave = true;
			(*p) = newH->left;
			newH->left = this->left;
			this->left = newH;
			return this;
		case R:
			this->slave = true;
			this->right = newH->left;
			newH->left = this;
			return newH;
		}
		throw "Should never got here.";
	}



	template<typename Elem> bool RB<Elem>::Node::contains(Elem e, Elem** rp) {
		//std::cout << "Encounter:" << this->e << "\n";
		if (this->e == e)
		{
			if (rp != nullptr)
				*rp = &(this->e);
			return true;

		}
		else if (this->e > e)
			return (this->left != nullptr ? this->left->contains(e, rp) : false);
		else
			return (this->right != nullptr ? this->right->contains(e, rp) : false);

	}

	template<typename Elem> std::tuple<typename RB<Elem>::Node*, bool> RB<Elem>::Node::remove(Elem e) {

		int size = this->nodeSize();

		int pos = this->posInNode(e);
		typename RB<Elem>::Node** pToChange; //= this->getP(pos);

		std::tuple<typename RB<Elem>::Node*, bool> delR;// = false;

		if (pos < 0)//In this node;
		{
			auto pSubTree = (pos == FST ? (this->right) : (this->left->right));
			Node* pRightMin = nullptr;
			if (pSubTree != nullptr)
				for (pRightMin = pSubTree; pRightMin->left != nullptr; pRightMin = pRightMin->left)
					;

			if (pRightMin == nullptr)
			{
				if (pos == SND)
				{
					auto p = this->left;
					this->left = this->left->left;
					delete p;
					return { this, false };
				}
				if (this->nodeSize() == 2)
				{
					auto p = this->left;
					this->left->slave = false;
					delete this;
					return { p,false };
				}
				return { this->left,true };

			}
			std::swap(pRightMin->e, *(this->getE(pos)));
			pos = pos == FST ? R : M;
			pToChange = this->getP(pos);
			delR = (*(this->getP(pos)))->remove(e);
		}
		else
		{
			auto p = pToChange = this->getP(pos);
			if (*p == nullptr)
				return { this,false };//Not even exist
			delR = (*p)->remove(e);
		}
			
		//*(this->getP(pos)) = std::get<0>(delR);
		*pToChange = std::get<0>(delR);

		if (!std::get<1>(delR))
			return { this,false };

		std::tuple<typename RB<Elem>::Node*, bool> mergeR;
		if (size == 1)
		{
			if (pos == L)
				mergeR = this->toRight();
			else
				mergeR = this->toLeft();
			return { std::get<0>(mergeR), !std::get<1>(mergeR) };
		}
		else
		{
			switch (pos)
			{
				Node* p;

			case L:
				p = this->left;
				p->slave = false;
				mergeR = p->toRight();
				this->left = std::get<0>(mergeR);
				if (std::get<1>(mergeR))
					this->left->slave = true;
				return { this, false };
			case M:
				p = this->left;
				p->slave = false;
				mergeR = p->toLeft();
				this->left = std::get<0>(mergeR);
				if (std::get<1>(mergeR))
					this->left->slave = true;
				return { this, false };

			case R:
			/*
				this->left->slave = false;
				auto nRoot = this->left;
				this->left = this->left->right;
				nRoot->right = this;
				return { nRoot, false };
			*/
				p = this->left; 
				this->left = p->right;
				mergeR = this->toLeft();
				if (std::get<1>(mergeR))
				{
					auto newH = std::get<0>(mergeR);
					if (newH->nodeSize() > 1)
						throw "Wrong!";
					p->right = newH->left;
					newH->left = p;
					newH->slave = false;
					p->slave = true;
					return { newH,false };
				}
				else
				{
					auto np = std::get<0>(mergeR);
					p->slave = false;
					np->slave = false;
					p->right = np;
					return{ p,false };

				}
			}
		}
		throw "Never!";
	}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The following are the interface exposed to the outside as RedBlack tree.


	template<typename Elem> RB<Elem>::RB() {
		this->t = nullptr;
	}

	template<typename Elem> RB<Elem>& RB<Elem>::operator=(const RB<Elem> &from) {
		if (this->t != nullptr)
		{
			this->t->delAll();
			delete this->t;
		}
		this->t = nullptr;
		if (from.t != nullptr)
			this->t = from.t->copy();
		return *this;
	}

	template<typename Elem> RB<Elem>::RB(const RB<Elem>& from) {
		*this = from;
	}

	template<typename Elem> RB<Elem>::~RB() {
		if (this->t != nullptr)
		{
			this->t->delAll();
			delete this->t;
		}
	}


	template<typename Elem> void RB<Elem>::insert(Elem e) {
		if (this->t == nullptr)
		{
			this->t = new typename RB<Elem>::Node{ e };
			return;
		}

		this->t = this->t->insert(e);
		if (this->t->nodeSize() > 2)
		{
			auto newH = this->t->left;
			this->t->left = newH->right;
			newH->right = this->t;
			this->t = newH;
			newH->slave = false;
			newH->left->slave = false;
		}
		//this->t->insert(e);
	}

	template<typename Elem> void RB<Elem>::remove(Elem e) {
		if (this->t != nullptr)
			this->t = std::get<0>(this->t->remove(e));
	}


	template<typename Elem> bool RB<Elem>::contains(Elem e, Elem **rp) {
		return (this->t != nullptr ? t->contains(e, rp) : false);
	}
}
