#pragma once

#include <tuple>
#include <format>
#include <iostream>
#include "RedBlack.h"


namespace SelfDefined {

	template<typename Elem> void RB<Elem>::print()
	{
		if (this->t == nullptr)
		{
			std::cout << "Empty\n";
			return;
		}
		this->t->print();
		std::cout << std::endl;
	}

	template<typename Elem> int RB<Elem>::Node::print() {
			static int count = 0;
			int croot, cl, cr;
			croot = count;
			count++;
			std::cout << std::format("n{}[label=\"{}\",color={}];\n", croot, this->e, this->slave ? "red" : "black");
			if (this->left)
			{
				cl = this->left->print();
				std::cout << std::format("n{}->n{};\n", croot, cl);

			}
			if (this->right)
			{
				cr = this->right->print();
				std::cout << std::format("n{}->n{};\n", croot, cr);
			}
			return croot;
	}

}
