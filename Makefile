CC := g++
CFLAGS := -std=c++17 -Wall
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

all: main run clean

main: main.o src/grass/grass.o src/route/route.o src/car/car.o src/car_manager/manager.o
	$(CC) $(CFLAGS) -o main $^ $(SFML_LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c $<

src/grass/grass.o: src/grass/grass.cpp
	$(CC) $(CFLAGS) -c $< -o $@

src/route/route.o: src/route/route.cpp
	$(CC) $(CFLAGS) -c $< -o $@

src/car/car.o: src/car/car.cpp
	$(CC) $(CFLAGS) -c $< -o $@

src/car_manager/manager.o: src/car_manager/manager.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./main

clean:
	rm -f main main.o src/grass/grass.o src/route/route.o src/car/car.o src/car_manager/manager.o