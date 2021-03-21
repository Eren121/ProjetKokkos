KOKKOS_PATH ?= ${HOME}/kokkos-install
OPENCV_PATH ?= ${HOME}/opencv-install

KOKKOS_DEVICES = "OpenMP"
EXE_NAME = "ProjetKokkos"

SRC = $(wildcard *.cpp serial/*.cpp)
OBJ = $(SRC:.cpp=.o)

# parfois lib parfois lib64, apparemment sur ROMEO lib64
#
LIB_INC = -L${OPENCV_PATH}/lib64 -L${KOKKOS_PATH}/lib64
LIBS = -lkokkoscontainers -lkokkoscore -lopencv_core -lopencv_highgui -lopencv_imgcodecs
INC = -I${KOKKOS_PATH}/include -I${OPENCV_PATH}/include/opencv4 -I. # inclus le répertoire courant pour éviter les "#include ../[...]"

CXX = ${KOKKOS_PATH}/bin/nvcc_wrapper
CXXFLAGS = -O3 -fopenmp -DNOGUI=1

# Avec NOGUI=1, les résultats sont écrits vers out/***.jpeg
#
$(EXE_NAME): $(OBJ)
	${CXX} ${CXXFLAGS} $^ ${LIB_INC} ${LIBS} -o ${EXE_NAME}

# sm_60 doit coincider avec la version de Kokkos compilée pour (PASCAL60 ici)
#
%.o: %.cpp
	${CXX} -arch=sm_60 --expt-extended-lambda -Xcompiler ${CXXFLAGS} -Wfatal-errors ${INC} -std=c++17 -c $< -o $@ -g

.PHONY: clean
clean:
	rm -rf ${OBJ} ${EXE_NAME}
