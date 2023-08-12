CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

LIB = lib/mysys.c lib/user.c lib/tell.c lib/cJSON.c lib/mycjson.c lib/init.c
serALL = server/*.c $(LIB)
clnALL = client/*.c $(LIB)
123ALL = 123/*.c $(LIB)

all: ser cln 

ser: $(serALL)
	$(CC) $(CFLAGS) $^ -o $@

cln: $(clnALL)
	$(CC) $(CFLAGS) $^ -o $@

ceshi: $(123ALL)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f server client ceshi
