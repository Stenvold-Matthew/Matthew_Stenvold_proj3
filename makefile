proj3: driver.o
	g++ driver.o -o proj3

driver.o: driver.cpp
	g++ -c driver.cpp

clean:
	rm *.o proj3