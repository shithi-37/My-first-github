#include<stdio.h>
int main()
{
    int Age,Emergency;
    scanf("%d %d",&Age,&Emergency);
    if(Age >= 60 && Emergency >= 4)
    {
        printf("Immediate ICU");
    }
   else if(Age >= 60 && Emergency >= 2 )
    {
        printf("Priority Doctor");
    }
    else if(Age >= 60 && Emergency < 2 &&  Emergency < 4 )
    {
        printf("General Checkup");
    }

    else if(Age>=18 && Age<=59 && Emergency >= 4 )
    {
        printf("Emergency Ward");
    }
    else if(Age>=18 && Age<=59 && Emergency >= 2)
    {
        printf("Doctor Consultation");
    }
    else if(Age>=18 && Age<=59 && Emergency < 4 && Emergency < 2 )
    {
        printf("Waiting Room");
    }
    else if(Age < 18 && Emergency >= 3 )
    {
        printf("Pediatric Emergency");
    }
    else {
         printf("Pediatric Checkup");
    }

    return 0;
}
