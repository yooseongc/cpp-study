CXXFLAGS+= -std=c++20
MFLAGS+= -fmodules
CXXFLAGS+= ${MFLAGS}
CXXFLAGS+= ${OPTFLAGS}
CXXFLAGS+= -pedantic
CXXFLAGS+= -Wall

CXX= g++

all: math_app

clean:
	rm -f ${MAIN_TARGETS} *.o *.pcm

%.pcm: %.cppm
	${CXX} -std=c++20 ${MFLAGS} -E -o $@ $?

math.pcm: math.cppm math_extra.pcm
	${CXX} -std=c++20 ${MFLAGS} -fmodule-file=math_extra.pcm -E -o $@ $<

math.o: math.cpp math.pcm
	${CXX} -std=c++20 ${MFLAGS} -fmodule-file=math.pcm -c -o $@ $<

vector_from_generated_module: vector_from_generated_module.cpp
	${CXX} ${CXXFLAGS} -o $@ $? -fmodule-map-file=dmc_modules.map -fimplicit-modules

vector_from_module: vector_from_module.cpp vector.pcm
	${CXX} --std=c++20 ${MFLAGS} ${OPTFLAGS} -fmodule-file=vector.pcm -o $@ $<

math_app: math.o math_app.cpp
	${CXX} --std=c++20 ${MFLAGS} -fprebuilt-module-path=. -o $@ $+
