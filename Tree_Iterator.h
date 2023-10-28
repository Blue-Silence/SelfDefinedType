#pragma once

#include "SelfStack.h"

#include <iostream>


using SelfDefined::stack;

namespace SelfDefined {

	template<typename Node> class BSTIterator {
		static const char L = -1, R = 1;
		stack<Node*> ps;
		stack<char> dir;
	public:
		Node* now;
	private:
		bool aheadOfBegin;
		bool outOfTail;
		BSTIterator() {};
	public:
		BSTIterator(Node* root);
		BSTIterator& operator++();
		BSTIterator& operator--();
		Node& operator*() const;
		static BSTIterator end(Node* root);

		bool operator==(const BSTIterator& b) const ; // can only used to compare the end
		bool operator!=(const BSTIterator& b) const { return !(*this == b); } // can only used to compare the end

	};
	
	template<typename Node> BSTIterator<Node>::BSTIterator(Node* root) {
		this->aheadOfBegin = this->outOfTail = (root==nullptr);
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

	template<typename Node> BSTIterator<Node>& BSTIterator<Node>::operator++() {
		if (this->outOfTail)
			throw "Already out of tail!";
		//	return;
		this->aheadOfBegin = false;
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
			if (this->dir.top() == L)
			{
				this->dir.pop();
				this->now = this->ps.top();
				this->ps.pop();
				return *this;
			}
			this->dir.pop();
			this->ps.pop();
		}
		this->outOfTail = true;
		return *this;
	}

	template<typename Node> BSTIterator<Node>& BSTIterator<Node>::operator--() {
		if (this->aheadOfBegin)
			throw "Already ahead of begin!";

		this->outOfTail = false;
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
			return &this;
		}
		for (;;)
		{
			if (this->dir.size == 0)
				break;
			if (this->dir.top() == R)
			{
				this->dir.pop();
				this->now = this->ps.top();
				this->ps.pop();
				return *this;
			}
			this->dir.pop();
			this->ps.pop();
		}
		this->aheadofBegin = true;
		return *this;
	}

	template<typename Node> BSTIterator<Node> BSTIterator<Node>::end(Node* root) {
		BSTIterator<Node> ei;
		ei.aheadOfBegin = (root == nullptr);
		ei.outOfTail = true;
		for (auto p = root; p != nullptr; p = p->right)
		{
			ei.dir.push(L);
			ei.ps.push(p);
		}
		if (ei.dir.size())
		{
			ei.dir.pop();
			ei.now = ei.ps.top();
			ei.ps.pop();
		}

		return ei;
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
