// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    MaxPower = max(MaxPower, Elem);
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.GetMaxPower();
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower) {
        return 0;
    }
    else {
        for (int i = 0; i < MaxPower; ++i) {
            if (BitField.GetBit(i) != s.BitField.GetBit(i)) {
                return 0;
            }
        }
        return 1;
    }
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{

    MaxPower = max(MaxPower, s.MaxPower);
    BitField = BitField | s.BitField;
    return *this;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet temp(GetMaxPower());
    temp.BitField.SetBit(Elem);
    BitField = BitField | temp.BitField;
    return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    return 0;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    MaxPower = max(MaxPower, s.MaxPower);
    BitField = BitField & s.BitField;
    return *this;
}

TSet TSet::operator~(void) // дополнение
{
    BitField = ~BitField;
    return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    TBitField temp = s.BitField;
    ostr << temp;
    return ostr;
}
