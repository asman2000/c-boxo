#
# boxo - step 00
#

CC = vc
CFLAGS =-c -O2 -c99 -sd -sc -IC:/vbcc/targets/m68k-amigaos/include/ -IC:/vbcc/include_h/

SRCDIR = src
OBJDIR = obj

BIN = exe\boxo-00

LIBS =-LC:/vbcc/targets/m68k-amigaos/lib -lvc -lamiga

LINK = vlink -bamigahunk -Bstatic -Cvbcc -nostdlib -s -x C:/vbcc/targets/m68k-amigaos/lib/startup.o
 
OBJ =	$(OBJDIR)\boxo.o 

LINKOBJ =	$(OBJDIR)\boxo.o 

RM = rm

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(LINK) $(LINKOBJ) -o $(BIN) $(LIBS)

$(OBJDIR)\boxo.o: $(SRCDIR)/boxo.c
	$(CC) $(CFLAGS) $(SRCDIR)/boxo.c -o $(OBJDIR)/boxo.o
