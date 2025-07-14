
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

SRCS = main.cpp corretor.cpp imovel.cpp cliente.cpp

imobiliaria: $(SRCS)
	$(CXX) $(CXXFLAGS) -o imobiliaria $(SRCS)

clean:
	rm -f imobiliaria