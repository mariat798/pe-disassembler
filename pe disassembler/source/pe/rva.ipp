/// rva.ipp

#pragma once

#include "rva.hpp"

template<typename T>
inline rva<T>::rva(unsigned long const base, unsigned long const offset) :
	base(base), offset(offset)
{ }

template<typename T>
rva<T>::rva(void* const base, unsigned long const offset) :
	base(reinterpret_cast<unsigned long const>(base)), offset(offset)
{ }

template<typename T>
T* rva<T>::operator->() const
{
	return reinterpret_cast<T*>(base + offset);
}

template<typename T>
inline T& rva<T>::operator*() const
{
	return *reinterpret_cast<T*>(base + offset);
}

template<typename T>
inline rva<T> rva<T>::operator[](unsigned const i) const
{
	return rva<T>(base, offset + i * sizeof(T));
}

template<typename T>
inline T* rva<T>::operator&() const
{
	return reinterpret_cast<T*>(base + offset);
}

template<typename T>
inline bool rva<T>::operator==(const rva<T> rhs)
{
	return base == rhs.base && offset == rhs.offset;
}

template<typename T>
inline bool rva<T>::operator!=(const rva<T> rhs)
{
	return !(*this == rhs);
}

template<typename T>
inline void rva<T>::advance(unsigned long const by)
{
	offset += by;
}
