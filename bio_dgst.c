/**
   @file      bio_dgst.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2008 by Mitch Richling.  All rights reserved.
   @Revision  $Revision$ 
   @SCMdate   $Date$
   @brief     Demonstrate the BIO digest filter object.@EOL
   @Keywords  none
   @Std       C89
*/
 
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <stdio.h>

int main(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  BIO *bio_stdin, *bio_md5;
  unsigned char buf[512], mdBuf[EVP_MAX_MD_SIZE];
  int i, mdLength;

  /* Create a BIO objects */
  bio_stdin  = BIO_new_fp(stdin,  BIO_NOCLOSE);

  /* Create a base64 filter and connect it to the bio_stdin */
  bio_md5 = BIO_new(BIO_f_md());
  BIO_set_md(bio_md5, EVP_md5());
  bio_stdin = BIO_push(bio_md5, bio_stdin);

  /* Read from bio_stdin, and compute the hash as a side effect. */
  while(BIO_read(bio_stdin, buf, 512) > 0) {
  } /* end while */

  /* Now extract the hash via BIO_gets (which is kinda odd really). */
  mdLength = BIO_gets(bio_md5, (char *)mdBuf, EVP_MAX_MD_SIZE);
  for(i=0; i<mdLength; i++) 
    printf("%02x", (unsigned int)(mdBuf[i]));
  printf("\n");

  BIO_free_all(bio_stdin);    

  return 0;
} /* end func main */
