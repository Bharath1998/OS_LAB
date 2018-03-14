#include <stdio.h>
#include <stdlib.h> // For exit()
 
int main()
{
    FILE *fptr1, *fptr2;
    char filename[100], c;
 
   // printf("Enter the filename to open for reading \n");
    //scanf("%s", filename);
 
    // Open one file for reading
    fptr1 = fopen("a.txt", "r");
    if (fptr1 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }
 
   // printf("Enter the filename to open for writing \n");
    //scanf("%s", filename);
 
    // Open another file for writing
    fptr2 = fopen("b.txt", "w");
    if (fptr2 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }
 
    // Read contents from file
    c = fgetc(fptr1);
    while (c != EOF)
    {
       printf("%c\n",c);
        c = fgetc(fptr1);
    } 
 
    printf("\nContents copied to \n");
 
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}