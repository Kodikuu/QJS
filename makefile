OBJS = \
	src/main.o \
	src/lib.o

INCLUDES = \
	-Iincludes \
	-Isrc

LIBS = \
	deps/libmatoya.a \
	deps/libquickjs.a

FXCFLAGS = \
	/O3 \
	/Ges \
	/nologo

FLAGS = \
	-O2

LIB_FLAGS = \
	/nologo


CFLAGS = $(INCLUDES) $(FLAGS)

all: clean $(OBJS)
	@gcc $(OBJS) $(LIBS) $(INCLUDES) -lpthread -lm -ldl -o main
	@chmod +x main
	@rm src/*.o
	@echo running main
	@echo
	@./main

clean: 
	@rm -f src/*.o
	@rm main
