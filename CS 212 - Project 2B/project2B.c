#include <stdio.h>

int main()
{
    int A[100] = { 252, 657, 268, 402, 950, 66, 391, 285, 133, 577, 649, 166, 987, 314, 954, 214, 920, 230, 904, 801, 40, 552, 369, 682, 202, 712, 395, 517, 755, 603, 134, 385, 428, 941, 443, 477, 95, 647, 687, 737, 673, 19, 325, 697, 577, 181, 45, 964, 267, 600, 858, 145, 780, 760, 949, 507, 673, 717, 446, 634, 635, 679, 466, 474, 916, 855, 216, 899, 804, 159, 237, 625, 963, 388, 437, 682, 821, 325, 805, 876, 968, 414, 190, 434, 902, 794, 752, 729, 77, 243, 705, 953, 765, 637, 765, 158, 166, 599, 70, 927 };

    /* YOUR CODE GOES HERE 
     * HINT: WRITE THE PRINT FUNCTION FIRST */

    /* Step 2: SORT IT */
    
    int  i, j, sorted;
    for (i = 0; i < 99; ++i)
    {
        for (j = 0; j < 99 - i; ++j)
        {
            if (A[j] > A[j+1])
            {
                sorted = A[j+1];
                A[j+1] = A[j];
                A[j] = sorted;
            }
        } 
    }
        
    /* Step 1: PRINT IT */
    
    
    //int n = 0;
    //while(n < 100)
    //{
        //for (i = 0; i <= 9; ++i)
        //{
        //printf("\t%d", A[i]);
        //}
    //n += 10;
    //printf("\n");

    for (int i = 0; i <100; ++i)
    {
        printf ("\t%i", A[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
        
    


}