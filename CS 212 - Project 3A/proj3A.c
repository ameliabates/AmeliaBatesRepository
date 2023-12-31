
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20000

typedef struct
{
    // Add data members here.
    char *keys[MAX_SIZE];
    float values[MAX_SIZE];
    int curID;
} ArrayDictionary;

void Initialize(ArrayDictionary *ad)
{
   // Implement me!
    ad->curID = 0;
    
}

void Store(ArrayDictionary *ad, char *key, float value) //changed pointers here
{
   // Implement me!
    if (ad->curID >= MAX_SIZE)
        exit(EXIT_FAILURE);
    ad->keys[ad->curID] = key;
    ad->values[ad->curID] = value;
    ad->curID++;
}

float Fetch(ArrayDictionary *ad, char *key)
{
   // Implement me!
    for (int i = 0; i < ad->curID; i++)
        if (strcmp(key, ad->keys[i]) == 0)
            return ad->values[i];
    return 0.;

}


int main()
{
    FILE *f = fopen("DJIA", "r");
    if (f == NULL)
    {
         fprintf(stderr, "Unable to open file \"DJIA\" ... did you copy it to the current directory?\n");
         exit(EXIT_FAILURE);
    }

    ArrayDictionary ad;
    Initialize(&ad);

    //
    // Step 1: parse the file and place contents in the Dictionary.
    //  The key should be the date (a char *)
    //  The value should be the closing price.  (look at DJIA for more info)
    //
    
    size_t size = 1024;
    char *buffer = malloc(size*sizeof(char));
    char date_str[10];
    float open, high, low, closePrice;
    
    while (getline(&buffer, &size, f) > 0)
    {

       
        // Hint 1: sscanf is great.  Turn that line into numbers!

        // Hint 2: be very careful about what you send in to Store.
        //         The memory at buffer will be changing, so you can't
        //         use that.  Big hint: strdup
        
        
        sscanf(buffer, "%s %f %f %f %f", date_str, &open, &high, &low, &closePrice);
        
        //printf("%s %f\n", date_str, closePrice);
        
        //printf("The line is \"%s\"\n", buffer);
        
        char *str = strdup(date_str);
        
        Store(&ad, str, closePrice);

    }

    //
    //  For each data, do a fetch.
    //  For each returned closing price, add it to a running sum.
    //  Your goal is ultimately to get the average closing price over
    //  all of the dates in the file.
    //
    float sum = 0.;
    //sum = Fetch(&ad,"12/31/70");
    //printf("%f\n", sum);
    
    char dates[91][10] = {
                 "02/19/21", "02/19/20", "12/19/19", "12/12/19", "12/02/19", "11/22/19", "11/12/19", "10/22/19", "10/02/19", 
                 "09/12/19", "08/22/19", "08/12/19", "08/02/19", "07/22/19", "07/12/19", "07/02/19", "06/12/19", "05/22/19", 
                 "05/02/19", "04/22/19", "04/12/19", "04/02/19", "03/22/19", "03/12/19", "02/22/19", "02/19/19", "02/12/19", 
                 "01/22/19", "01/02/19", "12/19/18", "12/19/17", "12/19/16", "02/19/16", "02/19/15", "12/19/14", "02/19/14", 
                 "12/19/13", "02/19/13", "12/19/12", "12/19/11", "02/19/10", "02/19/09", "12/19/08", "02/19/08", "12/19/07", 
                 "12/19/06", "12/19/05", "02/19/04", "12/19/03", "02/19/03", "12/19/02", "02/19/02", "12/19/01", "12/19/00", 
                 "02/19/99", "02/19/98", "12/19/97", "02/19/97", "12/19/96", "12/19/95", "12/19/94", "02/19/93", "02/19/92", 
                 "12/19/91", "02/19/91", "12/19/90", "12/19/89", "12/19/88", "02/19/88", "02/19/87", "12/19/86", "02/19/86", 
                 "12/19/85", "02/19/85", "12/19/84", "12/19/83", "02/19/82", "02/19/81", "12/19/80", "02/19/80", "12/19/79", 
                 "12/19/78", "12/19/77", "02/19/76", "12/19/75", "02/19/75", "12/19/74", "02/19/74", "12/19/73", "12/19/72", 
                 "02/19/71"
           };
    
    for (int i = 0 ; i < 91 ; i++)
    {
        // You will need to repeat the code from the last while loop to get the data as a "char *"
  
        float val = Fetch(&ad, dates[i]);
        sum += val;
        if (val == 0.)
        {
            printf("Bad fetch!\n");
            exit(EXIT_FAILURE);
        }
    }
    
    // Uncomment this.  Not it assumes you called your sum variable "sum"
     printf("Over the 91 days, the average value was %d\n", (int)(sum/91.0));
    // It should print:
    //    Over the 91 days, the average value was 13209
}
