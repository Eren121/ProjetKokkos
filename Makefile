KOKKOS_PATH = ${HOME}/kokkos-install
KOKKOS_DEVICES = "OpenMP"
EXE_NAME = "01_Exercise"

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

LIBS = -lkokkoscontainers -lkokkoscore -lopencv_core -lopencv_highgui -lopencv_imgcodecs
INC = -I${KOKKOS_PATH}/include -I/usr/include/opencv4 -I. # inclus le répertoire courant pour éviter les "#include ../[...]"

CXX = ${KOKKOS_PATH}/bin/nvcc_wrapper
CXXFLAGS = -O3

$(EXE_NAME): $(OBJ)
	${CXX} ${CXXFLAGS} $^ -L${KOKKOS_PATH}/lib ${LIBS}

%.o: %.cpp
	${CXX} ${CXXFLAGS}  -arch=sm_70 --expt-extended-lambda -Xcompiler -fopenmp -Wfatal-errors ${INC} -std=c++17 -c $<
