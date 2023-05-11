#ifndef BIGNUM_H_INCLUDED
#define BIGNUM_H_INCLUDED

class BigNum
{
    friend std::istream &operator>>(std::istream&, BigNum&);
    friend std::ostream &operator<<(std::ostream&, const BigNum&);

public:
    BigNum();
    BigNum(long long int);
    BigNum(int);
    BigNum(std::string);
    BigNum(const char *);
    BigNum(const BigNum&);


    int signOf() const;
    void setNegative(bool);

    void setLength(size_t);
    size_t getLength() const;

    void setNumber(std::string);
    std::string getNumber() const;


    BigNum dummySum(BigNum) const;

    BigNum dummyDif(BigNum) const;

    BigNum operator+(const BigNum&) const;


    BigNum operator-(const BigNum&) const;

    BigNum digitMultBN(int, int) const;

    BigNum operator*(const BigNum&) const;

//    BigNum operator/(const BigNum&) const;

    BigNum &operator+=(const BigNum&);

    BigNum &operator-=(const BigNum&);

    BigNum &operator*=(const BigNum&);

    bool operator>(const BigNum&) const;

    bool operator<(const BigNum&) const;

    bool operator>=(const BigNum&) const;

    bool operator<=(const BigNum&) const;

    bool operator==(const BigNum&) const;

    bool operator!=(const BigNum&) const;

    char operator[](size_t) const;
    char &operator[](size_t);

    void printDelimiter ();
    BigNum &operator=(const BigNum&);
    BigNum &operator=(const char*);


    ~BigNum();

private:
    size_t length;
    bool isNegative;
    std::string number;
};

#endif // BIGNUM_H_INCLUDED
