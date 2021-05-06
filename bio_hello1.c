/**
   @file      bio_hello1.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2008 by Mitch Richling.  All rights reserved.
   @brief     Simple first BIO program.@EOL
   @Keywords  none
   @Std       C99
*/

#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>

int main(int argc, char *argv[]);

int main(int argc, char *argv[]) {

  BIO *bio_stdout;

  bio_stdout = BIO_new_fp(stdout, BIO_NOCLOSE);

  BIO_write(bio_stdout, "hello, World!\n", 14);

  BIO_free_all(bio_stdout);  

  return 0;
} /* end func main */
