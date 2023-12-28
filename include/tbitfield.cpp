// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 1) {
		throw "incorrect_bitlen_throw";
	}

	BitLen = len;
	MemLen = (len - 1) / 32 + 1;
	pMem = new TELEM[MemLen];
	
	for (int i = 0; i < MemLen; ++i) 
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (32 - n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen) {
		throw "incorrect_bit_throw";
	}

	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen) {
		throw "incorrect_bit_throw";
	}

	pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen) {
		throw "incorrect_bit_throw";
	}

	return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> (32 - n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (MemLen != bf.MemLen) {
		delete[] pMem;
		pMem = new TELEM[bf.MemLen];
	}
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for (int i = 0; i < MemLen; ++i) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < BitLen; ++i) {
			if (GetBit(i) != bf.GetBit(i)) {
				return 0;
			}
		}
		return 1;
    }
	else {
		return 0;
	}

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return (!(*this == bf));
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = max(GetLength(), bf.GetLength());
	int cycle = min(GetLength(), bf.GetLength());
	TBitField ans(len);
	if (len == bf.GetLength()) {
		ans = bf;
		for (int i = 0; i < cycle; ++i) {
			if (GetBit(i)) {
				ans.SetBit(i);
			}
		}
	}
	else {
		ans = *this;
		for (int i = 0; i < cycle; ++i) {
			if (bf.GetBit(i)) {
				ans.SetBit(i);
			}
		}
	}
	return ans;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = max(GetLength(), bf.GetLength());
	int cycle = min(GetLength(), bf.GetLength());
	TBitField ans(len);
	for (int i = 0; i < cycle; ++i) {
		if (GetBit(i) && bf.GetBit(i)) {
			ans.SetBit(i);
		}
	}
	return ans;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField ans(GetLength());
	for (int i = 0; i < BitLen; ++i) {
		if (!(GetBit(i))) {
			ans.SetBit(i);
		}
	}
	return ans;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); ++i) {
		ostr << bf.GetBit(i);
	}
	ostr << "\n";
	return ostr;
}
