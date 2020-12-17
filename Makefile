CFILES := $(wildcard *.c src/*.c)
INCLUDES := -I "src/"

PROG := main
CFLAGS := $(INCLUDES) $(FOO)
MAP_FILE :=$(PROG).map
LDFLAGS :=  -Xlinker -Map=$(MAP_FILE)

CC := gcc
LD := ld

OBJECTS := $(CFILES:.c=.o)
.DEFAULT_GOAL := all

%.o : %.c
	@echo 'Building file: $<'
	@$(CC) -c $(CFLAGS) -o $@ $< 

$(PROG) : $(OBJECTS)
	@echo 'Linking: $@'
	@$(CC) $(LDFLAGS) -o $@ $^ 

all: $(PROG)

OBJ := $(patsubst src/%,src\\%,$(OBJECTS))
clean:
	del /f $(PROG).exe
	del /f $(PROG).map
	del /f $(OBJ)