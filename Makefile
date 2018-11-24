
.SUFFIXES:
.SUFFIXES: .c .o

DIR = LIB_REUSSITES
INCL = ${DIR}/include
LIB = ${DIR}/lib

.c.o :
	gcc -Wall -g -ansi -c -I${INCL} $<

.PHONY : all
all : Reussites.e testR7.e testMD.e

Reussites.e: ${LIB}/libmachine_trace.a Alea.o Tas.o AfficherTas.o R7.o MD.o InteractionReussite.o Reussite.c
	gcc  -g -I${INCL} -o Reussites.e Reussite.c ${LIB}/graphlib_w.o InteractionReussite.o MD.o R7.o Tas.o AfficherTas.o Alea.o -L${LIB} -lmachine_trace -L/usr/X11R6/lib -lX11 -lm

testR7.e: ${LIB}/libmachine_trace.a Alea.o Tas.o AfficherTas.o R7.o testR7.c
	gcc  -g -I${INCL} -o testR7.e testR7.c ${LIB}/graphlib_w.o R7.o Tas.o AfficherTas.o Alea.o -L${LIB} -lmachine_trace -L/usr/X11R6/lib -lX11 -lm

testMD.e: ${LIB}/libmachine_trace.a Alea.o Tas.o AfficherTas.o MD.o testMD.c
	gcc  -g -I${INCL} -o testMD.e testMD.c ${LIB}/graphlib_w.o MD.o Tas.o AfficherTas.o Alea.o -L${LIB} -lmachine_trace -L/usr/X11R6/lib -lX11 -lm



test.e : ${LIB}/libmachine_trace.a testTasACompleter.o TasACompleter.o testTasACompleter.c
	@echo creation de test :
	gcc -g -I${INCL} -o test.e testTasACompleter.c TasACompleter.o testTasACompleter.o Alea.o -L${LIB} -lmachine_trace -L/usr/X11R6/lib -lX11 -lm
	@echo -------------------------------
#
# testTasACompleter.o : testTasACompleter.c TasACompleter.h
# 	@echo creation de testTasACompleter.o :
# 	gcc -g -Wall -c testTasACompleter.c
# 	@echo -------------------------------
#
# TasACompleter.o: TasACompleter.c TypesConst.h TasACompleter.h
# 	@echo creation de TasACompleter.o :
# 	gcc -g -Wall -c  TasACompleter.c
# 	@echo -------------------------------
#
# Tas.o : Tas.c Tas.h
# 	@echo creation de tas.o :
# 	gcc -g -Wall -c Tas.c
# 	@echo -------------------------------

# Alea.o: Alea.c Alea.h
# 	@echo creation de Alea.o :
# 	gcc -g -Wall -c Alea.c
# 	@echo -------------------------------

clean:
	rm -f *.o *.e *~
