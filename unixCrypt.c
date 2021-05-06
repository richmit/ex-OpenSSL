/**
   @file      unixCrypt.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2008 by Mitch Richling.  All rights reserved.
   @Revision  $Revision$ 
   @SCMdate   $Date$
   @brief     Demonstrate OpenSSL DES_crypt (crypt replacement).@EOL
   @Keywords  none
   @Std       C89

              OpenSSL comes with a fast version crypt (DES_crypt).  It
              also comes with one that is thread safe (DES_fcrypt)
              that takes as a final argument a pointer to a space
              where the encrypted password string will be written:

                 char *DES_fcrypt(const char *buf, const char *salt, char *ret)
*/

#include <stdio.h>
#include <openssl/des.h>

int main() {
  char *pw;
  int i;
  printf("START\n");
  for(i=0;i<1000000;i++) {
    pw = DES_crypt("abcdef", "ab");
  }
  printf("DONE\n");
}
