#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
  int lines_allocated = 128;
  int max_line_length = 100;
  int result = 0;

  /*Allocate memory to the array with the length of number of lines expected*/
  char** lines = (char **)malloc(sizeof(char*)*lines_allocated);
  if (lines == NULL)
  {
    /*If there isn't enough free RAM, catch it and fail. Unfortunately, this won't work on modern Linux systems, which just allocate virtual memory and OOM-kill you, if they end up not being able to deliver.*/
    fprintf(stderr, "Out of memory (1). \n");
    exit(1);
  } /* type name = initialisation. Syntax to create pointer to file and initialise it*/
  FILE* fp = fopen("numbers", "r");
  if (fp == NULL)
    {
      fprintf(stderr, "Error opening file. \n");
      exit(2);
    }

  /* Doing some actual work: */
  int i;
  for (i=0; 1; i++) /*this creates an infinite loop*/
  {
    int j;
    /*managing the memory allocated for our array by doubling as needed. Doubling memory is a standard approach for handling array memory, as it is a good balance between memory blocked and copy operations. */ 
    if (i >= lines_allocated)
    {
      int new_size;
      new_size = lines_allocated*2;
      lines = (char **)realloc(lines,sizeof(char*)*new_size);
        if (lines == NULL)
        {
          fprintf(stderr, "Out of memory. \n");
          exit(3);
        }
      lines_allocated = new_size;
    }
  
    /*This allocates a chunk of memory the size of the max line length and writes the pointer to this area in memory at place 'i' in our array of pointers (lines)*/
    lines[i] = malloc(max_line_length);
    if (lines[i] == NULL)
    {
      /*again, as all the times before we try to catch that we are out of memory. As mentioned already, this won't work in kernels that just OOM-kill us*/
      fprintf(stderr, "Out of memory (3). \n");
      exit(4);
    }
  
    /*this is where we bail out of our infinite loop, after having iterated over all the lines in our file*/
    if (fgets(lines[i], max_line_length-1, fp) == NULL)
    {
      break;
    }
    /*working from the end of the string, we loop through the lines of the string and check whether we encounter a new line or carriage return and if so substitute it with a null character*/
    for (j=strlen(lines[i])-1; j>=0 && (lines[i][j]=='\n' || lines[i][j]=='\r');j--);
    lines[i][j+1]='\0';
   
    /* convert string (character array) to integer and write into numbers array*/
    sscanf(lines[i], "%d", &numbers[i]);

  }
  /*Don't forget to close the file*/
  fclose(fp);
 
  int j;
  /*loop through all the lines of the file and print what is there (i at this point is the value of what it was at the end of the big loop above, ergo the number of acutal line in the file*/
  for(j=0;j<=i;j++)
  {
    result = result + numbers[j];
    printf("%d \n", numbers[j]);
  }

  printf("the result is %d \n", result);

  /* first we free all the memory at all the places in the array, then the memory of the array itself*/
  for (;i>=0;i--)
    free(lines[i]);
  free(lines);

  return 0;
}
