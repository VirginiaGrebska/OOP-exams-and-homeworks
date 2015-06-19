#ifndef HEX_H
#define HEX_H


class Hex
{
private:
    bool* number;
    bool sign;
    int length;
    Hex addZero(int)const;
    void removeZero();
    Hex division (Hex other, bool flag) const;
public:
    Hex();
    Hex(const char* , int);
    Hex(const Hex&);
    ~Hex();
    Hex& operator= (const Hex&);

    Hex operator+ (const Hex&) const;
    Hex& operator+= (const Hex&);

    Hex operator- (const Hex&) const;
    Hex& operator-= (const Hex&);

    Hex operator* (const Hex&) const;
    Hex& operator*= (const Hex&);

    Hex operator/ (const Hex&) const;
    Hex& operator/= (const Hex&);

    Hex operator% (const Hex&) const;
    Hex& operator%= (const Hex&);


    bool operator< (const Hex&);
    bool operator<= (const Hex&);
    bool operator> (const Hex&);
    bool operator>= (const Hex&);
    bool operator== (const Hex&);
    bool operator!= (const Hex&);

    void print() const;

};

#endif // HEX_H
