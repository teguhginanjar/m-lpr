CC		= gcc
SRC		= main.c mlpr.c 
OBJS	= ${SRC:.o=.c}
TARGET	= ./TARGET
LIBS	= 
CFLAGS	= -g -Wall 
${TARGET} : ${OBJS}
	@${CC} -o ${TARGET} ${LIBS} ${OBJS}
.c.o :
	@${CC} ${CFLAGS} $<
clean:
	@rm -rf *.o *.c~ *.h~ Makefile~ ${TARGET}
