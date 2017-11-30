CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = my_quadris

${EXEC}: *.cc
	${CXX} ${CXXFLAGS} *.cc -o ${EXEC}

clean:
	rm *.d
.PHONY: clean