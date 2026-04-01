CC = gcc
SRC = Exo3.c
TARGET = exo3

TARGETDIR = ../bin
OUT = $(TARGETDIR)/$(TARGET)

#all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p $(TARGETDIR)
	$(CC) -o $@ $<

clean:
	rm -f $(OUT)

fclean: clean
	rm -rf $(TARGETDIR)

