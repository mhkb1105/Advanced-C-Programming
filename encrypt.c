#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  FILE *fp_in, *fp_out;
  char *filename, filename_enc[FILENAME_MAX];
  int i, shift;

  if (argc != 3)
  {
    printf("Invalid input\n");
    exit(1);
  }

  if (atoi(argv[2]) < 1 || atoi(argv[2]) > 25)
  {
    printf("Invalid shift amount.\n");
    exit(1);
  }
  
  filename = argv[1]; 
  shift = atoi(argv[2]);

  if ((fp_in = fopen(filename, "r")) == NULL)
  {
    printf("Cannot open file\n");
    exit(1);
  }

  strcpy(filename_enc, filename);
  strcat(filename_enc, ".enc");
 
 if ((fp_out = fopen(filename_enc, "w")) == NULL) 
  {
    printf("Cannot open file\n");
    fclose(fp_in);
    exit(1);
  }


  while ((i = getc(fp_in)) != EOF) 
  {
    if ('A' <= i && i <= 'Z') 
    {
      i = ((i - 'A') + shift) % 26 + 'A';
    }
    else if ('a' <= i && i <= 'z') 
    {
      i = ((i - 'a') + shift) % 26 + 'a';
    }
    putc(i, fp_out);  
  }

  fclose(fp_in); 
  fclose(fp_out); 

  return 0;
}
