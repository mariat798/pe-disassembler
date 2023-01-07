/// rva.hpp

#pragma once

template<typename T>
class rva
{
protected:

	unsigned long base;
	unsigned long offset;

public:

	rva(unsigned long const base, unsigned long const offset);
	rva(void * const base, unsigned long const offset);

	T* operator->() const;
	T& operator*() const;
	rva<T> operator[](unsigned const i) const;
	T* operator&() const;

	rva<T>& operator++();
	rva<T> operator+(unsigned const rhs) const;

	bool operator==(const rva<T> rhs);
	bool operator!=(const rva<T> rhs);
	bool operator!();

	void advance(unsigned long const by);
};

#include "rva.ipp"
