.PHONY = server client all clean
CC=gcc
SRC_DIR = src
INC_DIR = /inc
DEPFLAGS = -MP -MD
C_FLAGS = -Wall $(foreach D, $(H_LIBS), -I$(D)) $(DEPFLAGS)

SERVER_SRC = $(SRC_DIR)/server.c
CLIENT_SRC = $(SRC_DIR)/client.c
COMMON_SRC = $(wildcard $(SRC_DIR)/*.c)
COMMON_SRC := $(filter-out $(SERVER_SRC) $(CLIENT_SRC), $(COMMON_SRC))

SERVER_OBJ = $(SERVER_SRC:.c=.o) $(COMMON_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o) $(COMMON_SRC:.c=.o)

SERVER_DEP = $(SERVER_OBJ:.o=.d)
CLIENT_DEP = $(CLIENT_OBJ:.o=.d)

all: server client showip
	$(info "Built server and client")

server: $(SERVER_OBJ)
	$(CC) -o $@ $^

showip: src/showip.o
	$(CC) -o $@ $^

client: $(CLIENT_OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(SRC_DIR)/*.d server client

-include $(SERVER_DEP) $(CLIENT_DEP)

