/**
   @file      dgst.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1995,1998,2005 by Mitch Richling.  All rights reserved.
   @Revision  $Revision$ 
   @SCMdate   $Date$
   @brief     Compute both the MD5 and SHA1 checksums of STDIN.@EOL
   @Keywords  none
   @Std       C89

              OpenSSL's EVP interface provides a high level, easy to
              use, interface for some common cryptographic tools.
              This program illustrates how to compute the md5 and sha1
              hash using this interface.


*/

#include <stdio.h>              /* I/O lib         ISOC  */
#include <stdlib.h>             /* Standard Lib    ISOC  */
#include <openssl/ssl.h>
#include <openssl/evp.h>

#define INBUFSIZE 1024

int main(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  EVP_MD_CTX *md5ctx=EVP_MD_CTX_new(), *sha1ctx=EVP_MD_CTX_new();
  unsigned char md5val[EVP_MAX_MD_SIZE], sha1val[EVP_MAX_MD_SIZE];
  unsigned int md5len, i, sha1len;
  char buf[INBUFSIZE];
  int numIn;

  if((md5ctx  == NULL) || (sha1ctx == NULL)) {
    fprintf(stderr, "Could not allocate EVP_MAX_MD obj");
    return 1;
  }
      
  /* Initialize the hash objects. */
  EVP_DigestInit(&md5ctx, EVP_md5());
  EVP_DigestInit(&sha1ctx, EVP_sha1());

  /* Note: Must not call these AFTER we use EVP_DigestFinal */
  fprintf(stderr, "INFO(evp_dgst): H1: Dgst Algo:  %s\n", OBJ_nid2ln(EVP_MD_CTX_type(&md5ctx)));
  fprintf(stderr, "INFO(evp_dgst): H1: Block Size: %d\n", (int)(EVP_MD_CTX_block_size(&md5ctx)));
  fprintf(stderr, "INFO(evp_dgst): H1: Hash Size:  %d\n", (int)(EVP_MD_CTX_size(&md5ctx)));
  fprintf(stderr, "INFO(evp_dgst): H2: Dgst Algo:  %s\n", OBJ_nid2ln(EVP_MD_CTX_type(&sha1ctx)));
  fprintf(stderr, "INFO(evp_dgst): H2: Block Size: %d\n", (int)(EVP_MD_CTX_block_size(&sha1ctx)));
  fprintf(stderr, "INFO(evp_dgst): H2: Hash Size:  %d\n", (int)(EVP_MD_CTX_size(&sha1ctx)));

  /* Add the data to the checksum */
  fprintf(stderr, "INFO(evp_dgst): READING DATA");
  while( (numIn = fread(buf, sizeof(char), INBUFSIZE, stdin)) > 0) {
    fprintf(stderr, ".");
    EVP_DigestUpdate(&md5ctx,  buf, numIn);
    EVP_DigestUpdate(&sha1ctx, buf, numIn);
  } /* end while */
  fprintf(stderr, "DONE\n");

  /* Finish up the hash function computation. */
  EVP_DigestFinal(&md5ctx,  md5val,  &md5len);
  EVP_DigestFinal(&sha1ctx, sha1val, &sha1len);

  printf(" MD5: ");
  for(i=0; i<md5len; i++)
    printf("%02x", md5val[i]);
  printf("\n");
  printf("SHA1: ");
  for(i=0; i<sha1len; i++)
    printf("%02x", sha1val[i]);
  printf("\n");

  /* Free up EVP_MD_CTX objects */
  EVP_MD_CTX_free(md5ctx);
  EVP_MD_CTX_free(sha1ctx);

  return 0;  

} /* end func main */

