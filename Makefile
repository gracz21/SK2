CC=g++
LD=g++

CFLAGS=
LDFLAGS= -L/usr/local/lib/ -lallegro -lallegro_dialog -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf

SRCS=play.cpp player.cpp main.cpp client.cpp server.cpp
TARGET=bin/zuzel

OBJS=$(addprefix obj/, $(addsuffix .o, $(SRCS)))

$(TARGET): $(OBJS) 
	$(LD) -Wall $(OBJS) -o $(TARGET) $(LDFLAGS)

obj/%.cpp.o: src/%.cpp
	$(CC) -Wall -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJS) $(TARGET)
