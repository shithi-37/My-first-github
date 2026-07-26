#include<stdio.h>
int main()
{
    int unit, freedom;
    float bill, vat, final;

    printf("Enter units: ");
    scanf("%d", &unit);

    printf("Freedom fighter? (1=Yes, 0=No): ");
    scanf("%d", &freedom);

    if(unit < 0)
    {
        printf("Invalid Input");
    }
    else
    {

        if(unit <= 100)
        {
            bill = unit * 5;
        }
        else if(unit <= 200)
        {
            bill = 100 * 5 + (unit - 100) * 7;
        }
        else if(unit <= 400)
        {
            bill = 100 * 5 + 100 * 7 + (unit - 200) * 10;
        }
        else
        {
            bill = 100 * 5 + 100 * 7 + 200 * 10 + (unit - 400) * 15;
        }


        if(bill > 12000)
        {
            bill = bill - (bill * 0.10);
        }
        else if(bill > 6000)
        {
            bill = bill - (bill * 0.05);
        }


        if(freedom == 1)
        {
            final = bill;
        }
        else
        {
            vat = bill * 0.15;
            final = bill + vat;
        }

        printf("Bill = %.2f\n", bill);

        if(freedom == 0)
            printf("VAT = %.2f\n", vat);
        else
            printf("VAT = 0.00 ");

        printf("Final Bill = %.2f\n", final);
    }

    return 0;
}






















