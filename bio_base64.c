/**
   @file      bio_base64.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2008 by Mitch Richling.  All rights reserved.
   @Revision  $Revision$ 
   @SCMdate   $Date$
   @brief     OpenSSL, BIO base64 encode example.@EOL
   @Keywords  none
   @Std       C89

              This program illustrates how to chain a BIO filter
              object to an output BIO object to seamlessly base64
              encode data passing through.  See bio_unbase64.c for an
              example of how to decode base64.
              
*/
 
#include <openssl/ssl.h>
#include <openssl/bio.h>

int main(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  BIO *bio_stdin, *bio_base64, *bio_stdout;
  char inBuffer[512];
  int numBytesIn;

  /* Create two BIO objects */
  bio_stdin  = BIO_new_fp(stdin,  BIO_NOCLOSE);
  bio_stdout = BIO_new_fp(stdout, BIO_NOCLOSE);

  /* Create a base64 filter and connect it to the stdout bio */
  bio_base64 = BIO_new(BIO_f_base64());
  bio_stdout = BIO_push(bio_base64, bio_stdout);

  /* Now read from our in bio and write to out out bio. */
  while((numBytesIn = BIO_read(bio_stdin, inBuffer, 512)) > 0) {
    BIO_write(bio_stdout, inBuffer, numBytesIn);
  } /* end while */

  /* Tell the base64 bio that we are done, and to flush the rest */
  BIO_flush(bio_stdout);

  /* Use BIO_free_all to free whole chain (the stdout and bio_base64 too. */
  BIO_free_all(bio_stdout);  
  /* BIO_free is good enough here, but free_all would work too. */
  BIO_free(bio_stdin);

  return 0;
} /* end func main */
