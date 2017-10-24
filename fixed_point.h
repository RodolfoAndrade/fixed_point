// fixed_point.h
#ifndef FIXED_POINT_H
#define FIXED_POINT_H

/*Author: Luiz Antonio de Oliveira Junior
  E     : laoj2@cin.ufpe.br
*/
#include <string>
#include <iostream>

using namespace std;

//Implemented based on: http://x86asm.net/articles/fixed-point-arithmetic-and-tricks/


class FixedPoint {
private:
    int SHIFT_AMOUNT;
    int SHIFT_MASK;
    long long value;    

public:    
    FixedPoint(int value=0, int fractionary_bits=8, bool internal_construction=false)
    {
        SHIFT_AMOUNT = fractionary_bits;
        SHIFT_MASK = ((1 << SHIFT_AMOUNT) - 1); // 65535 (all LSB set, all MSB clear)
        if(internal_construction)
            this->value = value;
        else
            this->value = value << SHIFT_AMOUNT;        
    }

    double to_double ()
    {
        return ((double)(value >> SHIFT_AMOUNT)) + ((double)(value & SHIFT_MASK) / (1 << SHIFT_AMOUNT));
    }

    FixedPoint operator + (FixedPoint a)
    {
        try
        {
            if(this->SHIFT_AMOUNT == a.SHIFT_AMOUNT)
            {
                FixedPoint c(this->value + a.value , a.SHIFT_AMOUNT, true);                
                return c;
            }
            else
            {            
                string except = "Exception: Operator '+' is not defined for Fixed Point numbers in different formats:\nQ" + to_string(this->SHIFT_AMOUNT) + "." + to_string(this->SHIFT_AMOUNT) + " and Q" + to_string(a.SHIFT_AMOUNT) + "." + to_string(a.SHIFT_AMOUNT);
                throw except;
            }
            
        }
        catch (string except)
        {
            cout << except << endl;
            exit(1);
        }
    }

    FixedPoint operator - (FixedPoint a)
    {
        try
        {
            if(this->SHIFT_AMOUNT == a.SHIFT_AMOUNT)
            {
                FixedPoint c(this->value - a.value , a.SHIFT_AMOUNT, true);                
                return c;
            }
            else
            {            
                string except = "Exception: Operator '-' is not defined for Fixed Point numbers in different formats:\nQ" + to_string(this->SHIFT_AMOUNT) + "." + to_string(this->SHIFT_AMOUNT) + " and Q" + to_string(a.SHIFT_AMOUNT) + "." + to_string(a.SHIFT_AMOUNT);
                throw except;
            }
            
        }
        catch (string except)
        {
            cout << except << endl;
            exit(1);
        }
    }

    FixedPoint operator / (FixedPoint a)
    {
        try
        {
            if(this->SHIFT_AMOUNT == a.SHIFT_AMOUNT)
            {
                FixedPoint c( (this->value << this->SHIFT_AMOUNT)/a.value ,a.SHIFT_AMOUNT, true);                
                return c;
            }
            else
            {            
                string except = "Exception: Operator '/' is not defined for Fixed Point numbers in different formats:\nQ" + to_string(this->SHIFT_AMOUNT) + "." + to_string(this->SHIFT_AMOUNT) + " and Q" + to_string(a.SHIFT_AMOUNT) + "." + to_string(a.SHIFT_AMOUNT);
                throw except;
            }
            
        }
        catch (string except)
        {
            cout << except << endl;
            exit(1);
        }

    }

    FixedPoint operator * (FixedPoint a)
    {
        /*
        temp = (x * y)
        r = temp + ((temp & 1<<(8-1))<<1)
        r>>=8
        */
        
        try
        {
            if(this->SHIFT_AMOUNT == a.SHIFT_AMOUNT)
            {
                long long temp = this->value * a.value;
                temp = temp + ((temp & 1<<(this->SHIFT_AMOUNT-1))<<1);
                temp >>=this->SHIFT_AMOUNT;

                FixedPoint c( temp, this->SHIFT_AMOUNT, true);                
                return c;
            }
            else
            {            
                string except = "Exception: Operator '*' is not defined for Fixed Point numbers in different formats:\nQ" + to_string(this->SHIFT_AMOUNT) + "." + to_string(this->SHIFT_AMOUNT) + " and Q" + to_string(a.SHIFT_AMOUNT) + "." + to_string(a.SHIFT_AMOUNT);
                throw except;
            }
            
        }
        catch (string except)
        {
            cout << except << endl;
            exit(1);
        }

    }


};

#endif