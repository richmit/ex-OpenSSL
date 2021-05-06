/**
   @file      bio_cp.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2008 by Mitch Richling.  All rights reserved.
   @brief     Demo basic BIO I/O with files.@EOL
   @Keywords  openssl bio
   @Std       C99

              The error checking in this program is not completely
              ideal, but it is typical of what one sees in the real
              world.  In particular, one should be more careful about
              interpreting values of 0, -1, and -2 from BIO_read and
              BIO_write.
*/

#include <openssl/ssl.h>
#include <openssl/bio.h>

#define BUFSIZE 512

int main(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  BIO *bio_stdin, *bio_stdout;
  char buf[BUFSIZE];
  int numBytesIn, numBytesOut;

  bio_stdin  = BIO_new_fp(stdin,  BIO_NOCLOSE);
  bio_stdout = BIO_new_fp(stdout, BIO_NOCLOSE);

  if(bio_stdin == NULL) {
    fprintf(stderr, "ERROR: stdin could not be attached to BIO!\n");
    return 1;
  }
  if(bio_stdout == NULL) {
    fprintf(stderr, "ERROR: stdout could not be attached to BIO!\n");
    return 2;
  }

  while((numBytesIn = BIO_read(bio_stdin, buf, BUFSIZE)) > 0) {
    numBytesOut = BIO_write(bio_stdout, buf, numBytesIn);
    if(numBytesIn != numBytesOut)
      fprintf(stderr, "ERROR: Didn't write as many bytes (%d) as we got (%d)!\n", numBytesIn, numBytesOut);
  } /* end while */
  if(numBytesIn < 0) 
    fprintf(stderr, "ERROR: Some sorta read error (BIO_read).  Return value: %d\n", numBytesIn);

  if(BIO_free(bio_stdout) == 0)
    fprintf(stderr, "ERROR: Could not free bio_stdout!\n");    
  if(BIO_free(bio_stdin) == 0)
    fprintf(stderr, "ERROR: Could not free bio_stdin!\n");    

  return 0;
} /* end func main */
