QT       -= gui

TARGET = cuda_one
TEMPLATE = lib

#CONFIG += staticlib

DEFINES += LIB_ONE

INCLUDEPATH += $$PWD/include

SOURCES += \
     wrap_cuda_one.cpp

HEADERS += \
    wrap_cuda_one.h

#CUDA_LIBS = libcuda libcudart
CUDA_OBJECTS_DIR = ./
CUDA_SOURCES += \
        cuda.cu \

CUDA_SDK = "/usr/local/cuda"   # Path to cuda SDK install
CUDA_DIR = $$CUDA_SDK          # Path to cuda toolkit install
SYSTEM_NAME = unix             # Depending on your system either 'Win32', 'x64', or 'Win64'
SYSTEM_TYPE = 64               # '32' or '64', depending on your system
#CUDA_ARCH = compute_52           # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'
#CUDA_GENCODE =  -gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_37,code=sm_37 -gencode arch=compute_50,code=sm_50 -gencode arch=compute_52,code=sm_52 -gencode arch=compute_52,code=compute_52 #SMS ?= 20 30 35 37 50 52
CUDA_GENCODE =  -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_37,code=sm_37 -gencode arch=compute_50,code=sm_50 -gencode arch=compute_52,code=sm_52 -gencode arch=compute_52,code=compute_52 #SMS ?= 20 30 35 37 50 52
NVCC_OPTIONS = --use_fast_math
NVCCFLAGS    = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v
INCLUDEPATH  += $$CUDA_DIR/include
CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')
#NVCC_LIBS = $$join($$CUDA_DIR/lib64,' -l','-l', '')
#LIBS += $$join(CUDA_LIBS,'.so ', '', '.so')
LIBS += -L$$CUDA_DIR/lib64 -lcudart -lcuda


# Configuration of the Cuda compiler
CONFIG(debug, debug|release) {
    # Debug mode
    cuda_d.input = CUDA_SOURCES
    cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}.o
    #cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE $$CUDA_GENCODE -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC --machine $$SYSTEM_TYPE $$CUDA_GENCODE -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME} $$NVCCFLAGS
    cuda_d.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda_d
} else {
    # Release mode
    cuda.input = CUDA_SOURCES
    cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}.o
    #cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE $$CUDA_GENCODE -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.commands = $$CUDA_DIR/bin/nvcc -D_RELEASE $$NVCC_OPTIONS $$CUDA_INC --machine $$SYSTEM_TYPE $$CUDA_GENCODE -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda
}


## войдёт в makefile в неихменном виде следовательно пути будут отсчитываться от makefile
DESTDIR += ../lib

#unix{
#    CONFIG  += link_pkgconfig
#    LIBS += -L$$CUDA_DIR/lib64 -lcudart -lcuda
#}


#QMAKE_CXXFLAGS += $$(CXXFLAGS)
#QMAKE_CFLAGS += $$(CFLAGS)
#QMAKE_LFLAGS += $$(LDFLAGS)
