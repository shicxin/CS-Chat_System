CC = gcc
# CFLAGS = -Wall -Wextra -pedantic -std=c99
CFLAGS = -std=c11
LIB = lib/cJSON.c lib/tell.c lib/user.c lib/init.c
serALL = server/*.c $(LIB)
clnALL = client/*.c $(LIB)

all: ser cln

ser: $(serALL)
	$(CC) $(CFLAGS) $^ -o $@

cln: $(clnALL)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f server client
