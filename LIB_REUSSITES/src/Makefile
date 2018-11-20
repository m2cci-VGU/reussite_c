DIR=..
LIB=${DIR}/lib
INCL=${DIR}/include

.%.o: %.c
	gcc -I${INCL} -fPIC -c -g $<
#	chgrp dsu-ens *.o
#	chmod g+w *.o

%.o: %.c ${INCL}/%.h
	gcc -I${INCL} -fPIC -c -g $<
#	chgrp dsu-ens *.o
#	chmod g+w *.o

libmachine_trace.a: machine_trace.o graphlib_w.o
	ar rc libmachine_trace.a machine_trace.o graphlib_w.o
#	chgrp dsu-ens libmachine_trace.a
#	chmod g+w libmachine_trace.a

clean:
	/bin/rm -f *.a *.o *~

install:
	mv *.o *.a ${LIB}/
