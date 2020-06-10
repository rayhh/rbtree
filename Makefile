all:rbtreemain

CFLAGS=-g -O0 -Wall

rbtreemain:rbtreemain.o over_speed_rbtree.o rbtree.o

rbtree.o:rbtree.h rbtree.c

over_speed_rbtree:over_speed_rbtree.h over_speed_rbtree.c

rbtreemain.o:rbtreemain.c

.PHONY:clean

clean:
        rm *.o rbtreemain
