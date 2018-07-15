include ../Makefile.inc

GEN_EXERCISE = copy tee

exegen: ${GEN_EXERCISE}

showall :
	@ echo ${EXE}

clean :
	${RM} *.o

${GEN_EXERCISE} : ${TLPI_LIB}		# True as a rough approximation
