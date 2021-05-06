##
# @file      makefile
# @author    Mitch Richling <https://www.mitchr.me/>
# @Copyright Copyright 2008 by Mitch Richling.  All rights reserved.
# @Revision  $Revision$
# @SCMdate   $Date$
# @brief     @EOL
# @Keywords  
# @Std       GNUmake BSDmake SYSVmake GenericMake
#
#            Notes here
#            

# Fix for local needs
CC       = gcc
CXX      = g++
CFLAGS   = -Wall
CXXFLAGS = -Wall

# Uncomment to build all when make file changes
#SPECDEP=makefile

# Put targets here
TARGETS = bio_hello0 bio_hello1 bio_base64 bio_unbase64 bio_cp bio_dgst evp_dgst  evp_encrypt evp_decrypt bio_hello2

all : $(TARGETS)
	@echo Make Complete

clean :
	rm -rf a.out *~ *.bak $(TARGETS)
	@echo Make Complete

bio_base64 : bio_base64.c $(SPECDEP)
	 cc -Wall bio_base64.c -o bio_base64 -lcrypto

bio_cp : bio_cp.c $(SPECDEP)
	 cc -Wall bio_cp.c -o bio_cp -lcrypto

bio_hello2 : bio_hello2.c $(SPECDEP)
	 cc -Wall bio_hello2.c -o bio_hello2 -lcrypto

bio_dgst : bio_dgst.c $(SPECDEP)
	 cc -Wall bio_dgst.c -o bio_dgst -lcrypto

bio_hello0 : bio_hello0.c $(SPECDEP)
	 cc -Wall bio_hello0.c -o bio_hello0 -lcrypto

bio_hello1 : bio_hello1.c $(SPECDEP)
	 cc -Wall bio_hello1.c -o bio_hello1 -lcrypto

bio_unbase64 : bio_unbase64.c $(SPECDEP)
	 cc -Wall bio_unbase64.c -o bio_unbase64 -lcrypto

evp_dgst : evp_dgst.c $(SPECDEP)
	cc -Wall evp_dgst.c -o evp_dgst -lcrypto

enc : enc.c $(SPECDEP)
	 cc -Wall enc.c -o enc -lcrypto

evp_encrypt : evp_encrypt.c $(SPECDEP)
	 cc -Wall evp_encrypt.c -o evp_encrypt -lcrypto

evp_decrypt : evp_decrypt.c $(SPECDEP)
	 cc -Wall evp_decrypt.c -o evp_decrypt -lcrypto
