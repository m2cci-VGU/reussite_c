
.SUFFIXES:
.SUFFIXES: .c .o

DIR = LIB_REUSSITES
INCL = ${DIR}/include
LIB = ${DIR}/lib

.c.o :
	gcc -Wall -g -ansi -c -I${INCL} $<

Reussites.e: ${LIB}/libmachine_trace.a Alea.o Tas.o AfficherTas.o R7.o MD.o InteractionReussite.o Reussite.c
	gcc  -g -I${INCL} -o Reussites.e Reussite.c ${LIB}/graphlib_w.o InteractionReussite.o MD.o R7.o Tas.o AfficherTas.o Alea.o -L${LIB} -lmachine_trace -L/usr/X11R6/lib -lX11 -lm

clean:
	rm -f AfficherTas.o Alea.o InteractionReussite.o R7.o MD.o Reussite.o *.e
