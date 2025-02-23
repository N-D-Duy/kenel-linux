CC = gcc
CFLAGS = -Wall -lm

TARGET = program

OBJS = tinh.o tamgiac.o hinhvuong.o hinhtron.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

tinh.o: tinh.c tamgiac.h hinhvuong.h hinhtron.h
	$(CC) -c tinh.c

tamgiac.o: tamgiac.c tamgiac.h
	$(CC) -c tamgiac.c

hinhvuong.o: hinhvuong.c hinhvuong.h
	$(CC) -c hinhvuong.c

hinhtron.o: hinhtron.c hinhtron.h
	$(CC) -c hinhtron.c

clean:
	rm -f $(OBJS) $(TARGET)
