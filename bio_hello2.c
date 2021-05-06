/**
   @file      bio_hello2.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2008 by Mitch Richling.  All rights reserved.
   @brief     Demo basic BIO I/O file open.@EOL
   @Keywords  openssl bio
   @Std       C99

*/

#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <stdio.h>

int main(int argc, char *argv[]);

int main(int argc, char *argv[]) {

  BIO *bio_out;

  bio_out = BIO_new_file("helloFile.txt", "w");
  if(bio_out == NULL) {
    fprintf(stderr, "ERROR: File output BIO could not be created!\n");
    return 1;
  }

  BIO_printf(bio_out, "Hello World\n");

  BIO_free(bio_out);

  fprintf(stderr, "INFO(bio_hello2): Wrote file helloFile.txt!\n");

  return 0;
} /* end func main */
