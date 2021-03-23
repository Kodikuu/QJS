OBJS = \
	src/main.o \
	src/lib.o \
	src/libmatoya.o

INCLUDES = \
	-Iincludes \
	-Isrc

LIBS = \
	deps/libmatoya.a \
	deps/libquickjs.a

FLAGS = \
	-Os


CFLAGS = $(INCLUDES) $(FLAGS)

all: clean $(OBJS)
	@gcc $(OBJS) $(LIBS) $(INCLUDES) -lpthread -lm -ldl -o main -flto
	@strip --strip-unneeded main
	@chmod +x main
	@rm src/*.o
	@echo running main
	@echo

clean: 
	@rm -f src/*.o
	@rm -f main
