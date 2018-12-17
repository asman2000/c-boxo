#
# boxo - step 02
#

CC = vc
CFLAGS =-c -O2 -c99 -sd -sc -IC:/vbcc/targets/m68k-amigaos/include/ -IC:/vbcc/include_h/

SRCDIR = src
OBJDIR = obj

BIN = exe\boxo-02

LIBS =-LC:/vbcc/targets/m68k-amigaos/lib -lvc -lamiga

LINK = vlink -bamigahunk -Bstatic -Cvbcc -nostdlib -s -x C:/vbcc/targets/m68k-amigaos/lib/startup.o
 
OBJ =	$(OBJDIR)\boxo.o \
	$(OBJDIR)\window.o \
	$(OBJDIR)\input.o \
	$(OBJDIR)\gfx.o 

LINKOBJ =	$(OBJDIR)\boxo.o \
	$(OBJDIR)\window.o \
	$(OBJDIR)\input.o \
	$(OBJDIR)\gfx.o 
	

RM = rm

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(LINK) $(LINKOBJ) -o $(BIN) $(LIBS)

$(OBJDIR)\boxo.o: $(SRCDIR)/boxo.c
	$(CC) $(CFLAGS) $(SRCDIR)/boxo.c -o $(OBJDIR)/boxo.o
$(OBJDIR)\window.o: $(SRCDIR)/window.c
	$(CC) $(CFLAGS) $(SRCDIR)/window.c -o $(OBJDIR)/window.o
$(OBJDIR)\input.o: $(SRCDIR)/input.c
	$(CC) $(CFLAGS) $(SRCDIR)/input.c -o $(OBJDIR)/input.o
$(OBJDIR)\gfx.o: $(SRCDIR)/gfx.c
	$(CC) $(CFLAGS) $(SRCDIR)/gfx.c -o $(OBJDIR)/gfx.o
