/**
   @file      evp_decrypt.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 2008 by Mitch Richling.  All rights reserved.
   @Revision  $Revision$ 
   @SCMdate   $Date$
   @brief     How to use OpenSSL's EVP interface to decrypt data.@EOL
   @Keywords  OpenSSL EVP decrypt AES
   @Std       C89

              OpenSSL's EVP interface provides a high level, easy to
              use, interface for some common cryptographic tools.
              evp_encrypt.c illustrates how to do symmetric data
              encryption while evp_decrypt.c illustrates how to do
              symmetric data decryption.

              The STDOUT of this program may be replicated with:

              openssl enc -aes-256-cbc -d \
                -K 000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F \
                -iv 000102030405060708090A0B0C0D0E0F 

*/

#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <stdio.h>

#define INBUFSIZE 512
#define OUTBUFSIZE (1024*1024)

void prtErrAndExit(int eVal, char *msg);
int main(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  int outBytes, inBytes, tmpOutBytes, bytesInBuf, i;
  int cipherBlockSize, cipherKeyLength, cipherIvLength;
  unsigned char key[] = { /* Need all 32 bytes... */
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
  };
  unsigned char iv[] = { /* Only need 16 bytes... */
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
  };
  unsigned char buf2crypt[INBUFSIZE];
  unsigned char outBuf[OUTBUFSIZE];
  EVP_CIPHER_CTX ctx;

  EVP_CIPHER_CTX_init(&ctx);
  EVP_DecryptInit_ex(&ctx, EVP_aes_256_cbc(), NULL, key, iv);

  cipherBlockSize = EVP_CIPHER_CTX_block_size(&ctx); 
  cipherKeyLength = EVP_CIPHER_CTX_key_length(&ctx);
  cipherIvLength  = EVP_CIPHER_CTX_iv_length(&ctx);

  fprintf(stderr, "INFO(evp_decrypt): Enc Algo:   %s\n", OBJ_nid2ln(EVP_CIPHER_CTX_nid(&ctx)));
  fprintf(stderr, "INFO(evp_decrypt): Key:        ");
  for(i=0; i<cipherKeyLength; i++)
    fprintf(stderr, "%02X", (int)(key[i]));
  fprintf(stderr, "\n");
  fprintf(stderr, "INFO(evp_decrypt): IV:         ");
  for(i=0; i<cipherIvLength; i++)
    fprintf(stderr, "%02X", (int)(iv[i]));
  fprintf(stderr, "\n");
  fprintf(stderr, "INFO(evp_decrypt): block size: %d\n", cipherBlockSize);
  fprintf(stderr, "INFO(evp_decrypt): key length: %d\n", cipherKeyLength);
  fprintf(stderr, "INFO(evp_decrypt): IV length:  %d\n", cipherIvLength);

  if((cipherKeyLength > 32) || (cipherIvLength  > 16))
    prtErrAndExit(1, "ERROR: Hardwired key or iv was too short!!\n"); 

  fprintf(stderr, "INFO(evp_decrypt): READING DATA");
  inBytes = outBytes = 0;
  while( (bytesInBuf = fread(buf2crypt, sizeof(char), INBUFSIZE, stdin)) > 0) {
    fprintf(stderr, ".");
    if((OUTBUFSIZE - ((bytesInBuf + cipherBlockSize - 1) + outBytes)) <= 0)
      prtErrAndExit(1, "ERROR: Buffer was not big enough to hold decrypted data!!\n");
    if(!EVP_DecryptUpdate(&ctx, outBuf + outBytes, &tmpOutBytes, buf2crypt, bytesInBuf))
      prtErrAndExit(1, "ERROR: EVP_DecryptUpdate didn't work...\n");
    outBytes += tmpOutBytes;
    inBytes += bytesInBuf;
  } /* end while */
  fprintf(stderr, "DONE\n");

  if((OUTBUFSIZE - (cipherBlockSize + outBytes)) <= 0)
    prtErrAndExit(1, "ERROR: Buffer was not big enough to hold decrypted data!!\n");
  if(!EVP_DecryptFinal_ex(&ctx, outBuf+outBytes, &tmpOutBytes))
    prtErrAndExit(1, "ERROR: EVP_DecryptFinal_ex didn't work...\n");
  outBytes += tmpOutBytes;

  fprintf(stderr, "INFO(evp_decrypt): Bytes in:   %d\n", inBytes);
  fprintf(stderr, "INFO(evp_decrypt): Bytes out:  %d\n", outBytes);

  EVP_CIPHER_CTX_cleanup(&ctx);

  fwrite(outBuf, 1, outBytes, stdout);
  return 1;
} /* end func main */

/* Save some vertical space with this simple error handling function.. */
void prtErrAndExit(int eVal, char *msg) {
  if(msg != NULL)
    fprintf(stderr, "INFO(evp_decrypt): %s\n\n", msg);
  exit(eVal);
} /* end func prtErrAndExit */
