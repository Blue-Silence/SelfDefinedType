#pragma once

template<typename Elem> void swap(Elem& a, Elem& b) {
	Elem tmp = a;
	a = b;
	b = tmp;
}
