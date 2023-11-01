#pragma once

#include "SelfStack.h"

#include <iostream>


using SelfDefined::stack;

namespace SelfDefined {

	template<typename Node> class BSTIterator {
		//static const char L = -1, R = 1;
		stack<Node*> ps;
		stack<char> dir;
	public:
		Node* now;
		enum Dir {
			L = -1, M = 0, R = 1
		};
	private:
		bool aheadOfBegin;
		bool outOfTail;
		BSTIterator() {};
		void toLeftMost();
		void toRightMost();
	public:
		BSTIterator(Node* root, char d = L);
		BSTIterator& operator++();
		BSTIterator& operator--();
		Node& operator*() const;

		bool operator==(const BSTIterator& b) const ; // can only used to compare the end
		bool operator!=(const BSTIterator& b) const { return !(*this == b); } // can only used to compare the end

	};
	
	template<typename Node> BSTIterator<Node>::BSTIterator(Node* root, char d) {
		this->aheadOfBegin = this->outOfTail = (root==nullptr);
		this->now = root;
		switch (d)
		{
		case L:
			this->toLeftMost();
			break;
		case R:
			this->toRightMost();
			this->outOfTail = true;
			break;
		}
	}

	template<typename Node> BSTIterator<Node>& BSTIterator<Node>::operator++() {
		if (this->outOfTail)
			throw "Already out of tail!";
		//	return;
		if (this->aheadOfBegin)
		{
			this->aheadOfBegin = false;
			return *this;
		}

		if (this->now->right != nullptr)
		{
			this->dir.push(R);
			this->ps.push(this->now);
			for (auto p = this->now->right; p!= nullptr; p = p->left)
			{
				this->dir.push(L);
				this->ps.push(p);
			}
			this->dir.pop();
			this->now = this->ps.top();
			this->ps.pop();
			return *this;
		}
		for (;;)
		{
			if (this->dir.size() == 0)
				break;
			this->now = this->ps.top();
			if (this->dir.top() == L)
			{
				this->dir.pop();
				this->ps.pop();
				return *this;
			}
			this->dir.pop();
			this->ps.pop();
		}
		this->outOfTail = true;
		this->toRightMost();
		return *this;
	}

	template<typename Node> BSTIterator<Node>& BSTIterator<Node>::operator--() {
		if (this->aheadOfBegin)
			throw "Already ahead of begin!";

		if (this->outOfTail)
		{
			this->outOfTail = false;
			return *this;
		}

		if (this->now->left != nullptr)
		{
			this->dir.push(L);
			this->ps.push(this->now);
			for (auto p = this->now->left; p!= nullptr; p = p->right)
			{
				this->dir.push(R);
				this->ps.push(p);
			}
			this->dir.pop();
			this->now = this->ps.top();
			this->ps.pop();
			return *this;
		}
		for (;;)
		{
			if (this->dir.size() == 0)
				break;
			this->now = this->ps.top();
			if (this->dir.top() == R)
			{
				this->dir.pop();
				this->ps.pop();
				return *this;
			}
			this->dir.pop();
			this->ps.pop();
		}

		this->aheadOfBegin = true;
		this->toLeftMost();
		return *this;
	}

	template<typename Node> void BSTIterator<Node>::toLeftMost() {
		Node* root = this->now;
		for (; this->ps.size() > 0; this->ps.pop(), this->dir.pop())
			root = this->ps.top();
		for (auto p = root; p != nullptr; p = p->left)
		{
			this->dir.push(L);
			this->ps.push(p);
		}
		if (this->dir.size())
		{
			this->dir.pop();
			this->now = this->ps.top();
			this->ps.pop();
		}
	}

	template<typename Node> void BSTIterator<Node>::toRightMost() {
		Node* root = this->now;
		for (; this->ps.size() > 0; this->ps.pop(), this->dir.pop())
			root = this->ps.top();
		for (auto p = root; p != nullptr; p = p->right)
		{
			this->dir.push(R);
			this->ps.push(p);
		}
		if (this->dir.size())
		{
			this->dir.pop();
			this->now = this->ps.top();
			this->ps.pop();
		}
	}


	template<typename Node> Node& BSTIterator<Node>::operator*() const{
		if (this->outOfTail || this->aheadOfBegin)
			throw "Accessing invalid location";
		return *(this->now);
	}

	template<typename Node> bool BSTIterator<Node>::operator==(const BSTIterator<Node> & b) const {
		return (this->outOfTail || this->aheadOfBegin) && (this->aheadOfBegin == b.aheadOfBegin) && (this->outOfTail == b.outOfTail);
	}

}
