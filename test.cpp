#include "fixed_point.h"

int main ()
{
    FixedPoint a(5);
    FixedPoint b(1);
    FixedPoint c;

    b = a + ((b/a)*(b/a));

    cout << b.to_double() << endl;

    return 0;
}