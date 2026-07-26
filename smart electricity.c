#include<stdio.h>
int main()
{
   int unit;
   float bill;
   scanf("%d",&unit);
   if(unit<0)
    {
        printf("Invalid Input");
    }

    if(unit < 0)
    {
        printf("Invalid Input");
    }
    else if(unit <= 100)
    {
        bill = unit * 5;
    }
    else if(unit <= 200)
    {
        bill = 100 * 5 + (unit - 100) * 7;
    }
    else if(unit <= 300)
    {
        bill = 100 * 5 + 100 * 7 + (unit - 200) * 10;
    }
    else
    {
        bill = 100 * 5 + 100 * 7 + 100 * 10 + (unit - 300) * 15;
    }

    if(unit >= 0)
    {
        if(bill > 5000)
        {
            bill = bill - (bill * 0.05);
        }
        else
        {
            bill = bill + (bill * 0.15);
        }

        printf("Final Bill = %.2f", bill);
    }

    return 0;
}

















