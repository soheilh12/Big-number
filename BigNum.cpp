#include <iostream>
#include <string>
//#include <iomanip>
//#include <stdexcept>

using namespace std;

#include "BigNum.h"

    BigNum::BigNum()
    {
        length = 1;
        number[0] = 0;
        isNegative = false;
    }
    BigNum::BigNum(long long int n)
    {
        if(n < 0)
        {
            isNegative = true;
            n *= -1;
        }
        else
            isNegative = false;
        int i;
        if(n == 0)
            number[0] = '0';
        for(i = 0; n != 0 ;i++)
        {
            number[i] = (n % 10) + '0';
            n /= 10;
        }
        length = (i==0?1:i);
    }

    BigNum::BigNum(int n)
    {
        if(n < 0)
        {
            isNegative = true;
            n *= -1;
        }
        else
            isNegative = false;
        int i;
        if(n == 0)
            number[0] = '0';
        for(i = 0; n != 0 ;i++)
        {
            number[i] = (n % 10) + '0';
            n /= 10;
        }
        length = (i==0?1:i);
    }

    BigNum::BigNum(string stringNum)
    {
        int i = 0, j, k;
        if(stringNum[0] == '-')
        {
            i++;
            isNegative = true;
        }
        else
            isNegative = false;
        if(stringNum[0] == '+')
            i++;

        for(k = i; stringNum[k] >= '0' && stringNum[k] <= '9' && k < stringNum.length(); k++);
        length = k - i;

        if(length == 0)
            throw invalid_argument("The string should start with a number.");

        for(j = length - 1; j >= 0 ;j--)
        {
            if(j == length - 1)
                number = stringNum[i + j];
            else
                number += stringNum[i + j];
        }
    }

    BigNum::BigNum(const char *ptr)
    {
        string stringNum = static_cast<string>(ptr);
        int i = 0, j, k;
        if(stringNum[0] == '-')
        {
            i++;
            isNegative = true;
        }
        else
            isNegative = false;
        if(stringNum[0] == '+')
            i++;

        for(k = i; stringNum[k] >= '0' && stringNum[k] <= '9' && k < stringNum.length(); k++);
        length = k - i;


        for(j = length - 1; j >= 0 ;j--)
        {
            if(j == length - 1)
                number = stringNum[i + j];
            else
                number += stringNum[i + j];
        }
    }

    BigNum::BigNum(const BigNum &A)
    {
        setLength(A.getLength());
        number = A.getNumber();
        if(A.signOf() == 1)
            isNegative = false;
        else
            isNegative = true;
    }

    int BigNum::signOf() const
    {
        if(isNegative == true)
            return -1;
        return 1;
    }

    void BigNum::setNegative(bool b)
    {
        isNegative = b;
    }

    void BigNum::setLength(size_t l)
    {
        if(l > 0 )
        {
            for(int i=length;i<l;i++)
                this->number+='\0';
            length = l;
        }

    }

    size_t BigNum::getLength() const
    {
        return length;
    }

    void BigNum::setNumber(string str)
    {
        int flag = 0;
        for(int i = 0; i < str.length(); i++)
            if(str[i] < '0' || str[i] > '9')
            {
                flag = 1;
                break;
            }
        if (flag == 0)
            number = str;
    }

    string BigNum::getNumber() const
    {
        string s;
        s = number[0];
        for (int i = 1; i < length; i++)
            s = s + number[i];
        return s;
    }


    BigNum &BigNum::operator=(const BigNum& rhs)
    {
        length = rhs.getLength();
        number = rhs.getNumber();
        if(rhs.signOf() == 1)
            isNegative = false;
        else
            isNegative = true;
        return *this;
    }

    BigNum &BigNum::operator=(const char* ptr)
    {
        BigNum A(ptr);
        *this = A;
        return *this;
    }

    BigNum BigNum::dummySum(BigNum a) const
    {
        BigNum c;
        c = *this;
        int l = a.getLength();
        a.setLength(c.getLength());
        int k = 0;
        for (int i = 0; i < l; i++)
            {
                int m = c[c.getLength() - i] - '0' + a[c.getLength() - i] - '0' + k;
                c[c.getLength() - i] = (m % 10) + '0';
                k = m / 10;
            }
        for (int i = l; i < c.getLength(); i++)
        {
            int m = c[c.getLength() - i] - '0' + k;
            c[c.getLength() - i] = (m % 10) + '0';
            k = m / 10;
        }
        if(k > 0)
        {
            c.setLength(c.getLength() + 1);
            c[1] = k + '0';
        }
        return c;
    }

    BigNum BigNum::dummyDif(BigNum a) const
    {
        BigNum c;
        c = *this;
        int l = a.getLength();
        a.setLength(c.getLength());
        int k = 0;
        for (int i = 0; i < l; i++)
            {
                int m = c[c.getLength() - i] - '0' -( a[c.getLength() - i] - '0') + k;
                if (m < 0)
                {
                    k = -1;
                    m = 10 + m;
                }
                else
                    k = 0;
                c[c.getLength() - i] = (m % 10) + '0';
            }
        for (int i = l; i < c.getLength(); i++)
        {
            int m = c[c.getLength() - i] - '0' + k;
            if (m < 0)
                {
                    k = -1;
                    m = 10 + m;
                }
            else
                k = 0;
            c[c.getLength() - i] = (m % 10) + '0';

        }
        int i;
        for(i = 1; c[i] == '0'; i++)
        {
        }
        c.setLength(c.getLength() - i + 1);
        return c;
    }

    BigNum BigNum::operator+(const BigNum &a) const
    {
        if(this->signOf() == 1 && a.signOf() == 1)
        {
            if (*this > a)
                return this->dummySum(a);
            else
                return a.dummySum(*this);
        }

        if(this->signOf() == -1 && a.signOf() == 1)
        {
            BigNum b;
            b = *this;
            b.setNegative(false);

            if (b > a)
            {
                b = b.dummyDif(a);
                b.setNegative(-1);
                return b;
            }
            else
                return a.dummyDif(*this);
        }

        if(this->signOf() == 1 && a.signOf() == -1)
        {
            BigNum b;
            b = a;
            b.setNegative(1);
            if (*this >= b)
                return this->dummyDif(a);
            else
            {
                b = a.dummyDif(*this);
                b.setNegative(-1);
                return b;
            }
        }
        BigNum b;
        b = this->dummySum(a);
        b.setNegative(-1);
        return b;
    }

    BigNum BigNum::operator-(const BigNum &a) const
    {
        BigNum A;
        A = a;
        if(A.signOf() == 1)
            A.setNegative(true);
        else
            A.setNegative(false);

        return (*this + A);
    }

    BigNum BigNum::digitMultBN(int a, int b) const
    {
        BigNum A;
        A = *this;
        int m, k = 0;
        for(int i = 0; i < A.getLength(); i++)
        {
            m = ((number[i] - '0') * a) + k;
            A[A.getLength() - i] = (m % 10) + '0';
            k = m / 10;
        }
        if(k > 0)
        {
            A.setLength(A.getLength() + 1);
            A[1] = k + '0';
        }
        A.setLength(A.getLength() + b);
        b;
        for(int i = 1; i <= A.getLength() - b; i++)
        {
            A[i] = A[i + b];
        }
        for(int i = A.getLength() - b + 1; i <= A.getLength(); i++)
        {
            A[i] = '0';
        }
        return A;
    }

    BigNum BigNum::operator*(const BigNum &a) const
    {
        BigNum A[a.getLength()];
        for(int i = 0; i < a.getLength(); i++)
            A[i] = this->digitMultBN(a[i + 1] - '0', (a.getLength() - i) - 1);
        BigNum mult(0);
        for(int i = 0; i < a.getLength(); i++)
        {
            mult = mult + A[i];
        }
        return mult;
    }

    BigNum &BigNum::operator+=(const BigNum &a)
    {
        *this = *this + a;
        return *this;
    }

    BigNum &BigNum::operator-=(const BigNum &a)
    {
        *this = *this - a;
        return *this;
    }

    BigNum &BigNum::operator*=(const BigNum &a)
    {
        *this = *this * a;
        return *this;
    }


    bool BigNum::operator>(const BigNum &a) const
    {
        if(this->isNegative == true && a.signOf() == 1)
            return false;
        if(this->isNegative == false && a.signOf() == -1)
            return true;
        if(this->length > a.getLength())
            return (this->isNegative ? false : true);
        if(this->length == a.getLength())
        {
            for (int i = 1; i <= length; i++)
            {
                if(number[length - i] > a.number[length - i])
                    return (this->isNegative ? false : true);
                if(number[length - i] < a.number[length - i])
                    return (this->isNegative ? true : false);
            }
            return (this->isNegative ? true : false);
        }
        return (this->isNegative ? true : false);
    }

    bool BigNum::operator<(const BigNum &a) const
    {
        if(a > *this)
            return true;
        return false;
    }

    bool BigNum::operator>=(const BigNum &a) const
    {
        if(a < *this)
            return false;
        return true;
    }

    bool BigNum::operator<=(const BigNum &a) const
    {
        if(a > *this)
            return false;
        return true;
    }



    bool BigNum::operator==(const BigNum &a) const
    {
        if(this->signOf() * a.signOf() == -1)
            return false;
        if(this->length != a.getLength())
            return false;
        for (int i = 1; i <= length; i++)
            if(number[length - i] != a.number[length - i])
                return false;
        return true;
    }

    bool BigNum::operator!=(const BigNum &a) const
    {
        if(a == *this)
            return false;
        return true;
    }

    char BigNum::operator[](size_t s) const
    {
        if(s < 1 || s > length)
            throw out_of_range("Subscript out of range");
        return (number[length - s]);
    }
    char &BigNum::operator[](size_t s)
    {
        if(s < 1)
            throw out_of_range("Subscript out of range");
        return number[length - s];
    }

    void BigNum::printDelimiter()
    {
        if(isNegative == true)
            cout << "-";
        for(int i = length - 1; i >= 0; i--)
        {
            cout << number[i];
            if((i % 3 == 0) && (i != 0))
                cout << ",";
        }
        cout << endl;
    }

    BigNum::~BigNum()
    {
    }




    istream &operator>>(istream &input, BigNum &A)
    {
        string stringNum;
        input >> stringNum;
        A = stringNum;
        return input;
    }
    ostream &operator<<(ostream &output, const BigNum &A)
    {
        if(A.signOf() == -1)
            output << "-";
        for(int i = 1; i <= A.getLength(); i++)
            output << A[i];
        return output;
    }

