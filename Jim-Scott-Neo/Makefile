CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = quadris
OBJECTS = board.o cell.o block.o normal_blocks.o special_blocks.o subject.o textdisplay.o graphicsdisplay.o window.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11
	rm *.o *.d
-include ${DEPENDS}


clean:
	rm ${EXEC}
.PHONY: clean