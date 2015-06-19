#include "Hex.h"

Hex::Hex()
{
    sign = 1;
    length = 1;
    number = new bool [1];
    number[0] = 0;
}

Hex::Hex(const char* num, int size)
{
    if(num != NULL)
    {
        sign = (num[size-1] != '-');
        length = 4*(size - 1 + sign);
        number = new bool [length];
        for(int i = size - 1 - (!sign), j = -1; i >= 0; i--)
        {
            switch(num[i])
            {
            case '0' : {number[++j] = 0;
                        number[++j] = 0;
                        number[++j] = 0;
                        number[++j] = 0;
                        }break;
            case '1' : {number[++j] = 0;
                        number[++j] = 0;
                        number[++j] = 0;
                        number[++j] = 1;
                        }break;
            case '2' : {number[++j] = 0;
                        number[++j] = 0;
                        number[++j] = 1;
                        number[++j] = 0;
                        }break;
            case '3' : {number[++j] = 0;
                        number[++j] = 0;
                        number[++j] = 1;
                        number[++j] = 1;
                        }break;
            case '4' : {number[++j] = 0;
                        number[++j] = 1;
                        number[++j] = 0;
                        number[++j] = 0;
                        }break;
            case '5' : {number[++j] = 0;
                        number[++j] = 1;
                        number[++j] = 0;
                        number[++j] = 1;
                        }break;
            case '6' : {number[++j] = 0;
                        number[++j] = 1;
                        number[++j] = 1;
                        number[++j] = 0;
                        }break;
            case '7' : {number[++j] = 0;
                        number[++j] = 1;
                        number[++j] = 1;
                        number[++j] = 1;
                        }break;
            case '8' : {number[++j] = 1;
                        number[++j] = 0;
                        number[++j] = 0;
                        number[++j] = 0;
                        }break;
            case '9' : {number[++j] = 1;
                        number[++j] = 0;
                        number[++j] = 0;
                        number[++j] = 1;
                        }break;
            case 'A' :
            case 'a' : {number[++j] = 1;
                        number[++j] = 0;
                        number[++j] = 1;
                        number[++j] = 0;
                        }break;
            case 'B' :
            case 'b' : {number[++j] = 1;
                        number[++j] = 0;
                        number[++j] = 1;
                        number[++j] = 1;
                        }break;
            case 'C' :
            case 'c' : {number[++j] = 1;
                        number[++j] = 1;
                        number[++j] = 0;
                        number[++j] = 0;
                        }break;
            case 'D' :
            case 'd' : {number[++j] = 1;
                        number[++j] = 1;
                        number[++j] = 0;
                        number[++j] = 1;
                        }break;
            case 'E' :
            case 'e' : {number[++j] = 1;
                        number[++j] = 1;
                        number[++j] = 1;
                        number[++j] = 0;
                        }break;
            case 'F' :
            case 'f' : {number[++j] = 1;
                        number[++j] = 1;
                        number[++j] = 1;
                        number[++j] = 1;
                        }break;
        }
        }
        removeZero();
    }
    else
    {
        sign = 1;
        length = 1;
        number = new bool [1];
        number[0] = 0;
    }
}

Hex::Hex(const Hex& other)
{
    length = other.length;
    sign = other.sign;
    if(other.number != NULL)
    {
        number = new bool [length];
        for(int i = 0; i < length; i++)
            number[i] = other.number[i];
    }
    else
        number = NULL;
}

Hex& Hex::operator=(const Hex& other)
{
    if(this == &other)
        return *this;
    if(number != NULL)
        delete [] number;
    length = other.length;
    sign = other.sign;
    if(other.number != NULL)
    {
        number = new bool [length];
        for(int i = 0; i < length; i++)
            number[i] = other.number[i];
    }
    else
        number = NULL;
    return *this;
}

Hex::~Hex ()
{
    delete [] number;
}

Hex Hex::operator+(const Hex& other) const
{
    Hex tmp, result;
    if(sign && !other.sign)
    {
        tmp = other;
        tmp.sign = 1;
        result = (*this) - tmp;
        return result;
    }
    if(!sign && other.sign)
    {
        tmp = *this;
        tmp.sign = 1;
        result = other - tmp;
        return result;
    }
    if(length < other.length)
    {
        tmp = *this;
        result = other;
    }
    else
    {
        tmp = other;
        result = *this;
    }
    for(int i = result.length - 1, j = tmp.length - 1; j >=0; i--, j--)
    {
        if((tmp.number[j] && !result.number[i]) ||
           (!tmp.number[j] && result.number[i]))
            result.number[i] = 1;
        else if(tmp.number[j])
        {
            int l = i;
            while(result.number[l] && l >= 0)
            {
                result.number[l] = 0;
                l--;
            }
            if(l >= 0)
                result.number[l] = 1;
            else
            {
                Hex tmp2;
                tmp2.sign = result.sign;
                tmp2.length = result.length + 1;
                tmp2.number = new bool[tmp2.length];
                for(int k = 0; k < result.length; k++)
                    tmp2.number[k+1] = result.number[k];
                tmp2.number[0] = 1;
                result = tmp2;
                i++;
            }
        }
    }
    if(!sign)
        result.sign = 0;
    return result;
}

Hex& Hex::operator+=(const Hex& other)
{
    *this = *this + other;
    return *this;
}

Hex Hex::operator-(const Hex& other) const
{
    Hex tmp, result;
    if(!sign && other.sign)
    {
        tmp = other;
        tmp.sign = 0;
        result = *this + tmp;
        return result;
    }
    if(sign && !other.sign)
    {
        tmp = other;
        tmp.sign = 1;
        result = (*this) + tmp;
        return result;
    }
    if(!sign && !other.sign)
    {
        result = other;
        result.sign = 1;
        tmp = *this;
        tmp.sign = 1;
    }
    else
    {
        result = *this;
        tmp = other;
    }
    if(result < tmp)
    {
        Hex tmp2 = result;
        result = tmp;
        tmp = tmp2;
        result.sign = 0;
    }
    for(int i = result.length - 1, j = tmp.length - 1; j >=0; i--, j--)
        if(tmp.number[j])
        {
            if(result.number[i])
                result.number[i] = 0;
            else
            {
                int l = i;
                while(!result.number[l])
                {
                    result.number[l] = 1;
                    l--;
                }
                result.number[l] = 0;
            }
        }
    result.removeZero();
    return result;
}

Hex& Hex::operator-=(const Hex& other)
{
    *this = *this - other;
    return *this;
}

void Hex::removeZero()
{
    int counter = 0;
    while(number[counter] == 0 && counter < length)
    {
        counter++;
    }

    Hex tmp;
    tmp.sign = sign;

    if(length == counter)
    {
        tmp.length = 1;
        tmp.number = new bool[1];
        tmp.number[0] = 0;
    }
    else
    {
        tmp.length = length - counter;
        tmp.number = new bool[tmp.length];
        for(int i = 0; counter < length; counter++, i++)
            tmp.number[i] = number[counter];
    }
    *this = tmp;
}

Hex Hex::addZero(int num)const
{
    Hex tmp;
    tmp.sign = sign;
    tmp.length = length + num;
    tmp.number = new bool[tmp.length];
    for(int i = 0; i < length; i++)
        tmp.number[i] = number[i];
    for(int i = length; i < tmp.length; i++)
        tmp.number[i] = 0;
    return tmp;
}

Hex Hex::operator*(const Hex& other) const
{
    Hex multiplier1, multiplier2, result;
    if(length > other.length)
    {
        multiplier1 = *this;
        multiplier2 = other;
        multiplier1.sign = 1;
        multiplier2.sign = 1;
    }
    else
    {
        multiplier1 = other;
        multiplier2 = *this;
        multiplier1.sign = 1;
        multiplier2.sign = 1;
    }
    result.length = 1;
    result.number = new bool [1];
    result.number[0] = 0;

    for(int i = multiplier2.length - 1, counter = 0; i >= 0; i--, counter++)
        if(multiplier2.number[i])
            result += multiplier1.addZero(counter);

    if(sign == other.sign)
        result.sign = 1;
    else
        result.sign = 0;
    return result;
}

Hex& Hex::operator*=(const Hex& other)
{
    *this = *this * other;
    return *this;
}

Hex Hex::division(Hex other, bool flag) const
{
    if(other.length > length)
    {
        if(flag)
        {
            Hex result;
            result.sign = 1;
            result.length = 4;
            result.number = new bool[4];
            result.number[0] = 0;
            result.number[1] = 0;
            result.number[2] = 0;
            result.number[3] = 0;
            return result;
        }
        else
            return *this;
    }
    Hex divident = *this, divider = other, quotient;
    divident.sign = 1;
    divider.sign = 1;
    quotient.length = divident.length - divider.length + 1;
    quotient.number = new bool[quotient.length];
    divider = divider.addZero(quotient.length - 1);

    for(int i = 0; divident >= other; i++)
    {
        if(divident >= divider)
        {
            divident -= divider;
            quotient.number[i] = 1;
        }
        else
            quotient.number[i] = 0;
        divider.length--;
    }
    if(sign == other.sign)
    {
        quotient.sign = 1;
        divident.sign = 1;
    }
    else
    {
        quotient.sign = 0;
        divident.sign = 0;
    }
    if(flag)
    {
        quotient.removeZero();
        return quotient;
    }
    return divident;
}

Hex Hex::operator/(const Hex& other) const
{
    return division(other, 1);
}

Hex& Hex::operator/=(const Hex& other)
{
    *this = division(other, 1);
    return *this;
}

Hex Hex::operator%(const Hex& other) const
{
    return division(other, 0);
}

Hex& Hex::operator%=(const Hex& other)
{
    *this = division(other, 0);
    return *this;
}

bool Hex::operator<(const Hex& other)
{
    return !(*this >= other);
}

bool Hex::operator<=(const Hex& other)
{
    return !(*this > other);
}

bool Hex::operator>(const Hex& other)
{
    if(sign && !other.sign)
        return 1;
    if(!sign && other.sign)
        return 0;
    if(length > other.length)
    {
        if(sign)
            return 1;
        return 0;
    }
    if(length < other.length)
    {
        if(!sign)
            return 1;
        return 0;
    }
    for(int i = 0; i < length; i++)
        {
            if(number[i] && !other.number[i])
            {
                if(sign)
                    return 1;
                return 0;
            }
            if(!number[i] && other.number[i])
            {
                if(!sign)
                    return 1;
                return 0;
            }
        }
    return 0;
}

bool Hex::operator>=(const Hex& other)
{
    return (*this > other) || (*this == other);
}

bool Hex::operator==(const Hex& other)
{
    if (length != other.length || sign != other.sign)
        return 0;
    for(int i = 0; i < length; i++)
        if(number[i] != other.number[i])
            return 0;
    return 1;
}

bool Hex::operator!=(const Hex& other)
{
    return !(*this == other);
}


void Hex::print() const
{
    for(int i = length - 1; i >= 0;)
    {
        int num = 0;
        if(i >= 0 && number[i])
            num += 1;
        i--;
        if(i >= 0 && number[i])
            num += 10;
        i--;
        if(i >= 0 && number[i])
            num += 100;
        i--;
        if(i >= 0 && number[i])
            num += 1000;
        i--;

        switch (num)
        {
        case 0: cout << '0'; break;
        case 1: cout << '1'; break;
        case 10: cout << '2'; break;
        case 11: cout << '3'; break;
        case 100: cout << '4'; break;
        case 101: cout << '5'; break;
        case 110: cout << '6'; break;
        case 111: cout << '7'; break;
        case 1000: cout << '8'; break;
        case 1001: cout << '9'; break;
        case 1010: cout << 'A'; break;
        case 1011: cout << 'B'; break;
        case 1100: cout << 'C'; break;
        case 1101: cout << 'D'; break;
        case 1110: cout << 'E'; break;
        case 1111: cout << 'F'; break;
        }
    }
    if(!sign)
        cout << '-';
}
