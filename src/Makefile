XX = g++
CPPFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lstdc++

app: main.o thread_pool.o
	$(CXX) $(CPPFLAGS) -o app main.o thread_pool.o $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CPPFLAGS) -c main.cpp

thread_pool.o: thread_pool.h thread_pool.cpp
	$(CXX) $(CPPFLAGS) -c thread_pool.cpp

clean:
	rm -f app *.o