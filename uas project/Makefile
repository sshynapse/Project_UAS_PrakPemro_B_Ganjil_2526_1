CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = perpustakaan
SRCS = main.c buku.c anggota.c peminjaman.c utils.c
HDRS = perpustakaan.h

$(TARGET): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)