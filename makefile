INCLUDES = \
	-Iincludes \
	-Isrc

LIBS = \
	deps/matoya.lib \
	deps/quickjs.lib \
	deps/parsec32.lib \
	bcrypt.lib \
	d3d11.lib \
	d3d9.lib \
	hid.lib \
	uuid.lib \
	dxguid.lib \
	opengl32.lib \
	ws2_32.lib \
	user32.lib \
	gdi32.lib \
	xinput9_1_0.lib \
	ole32.lib \
	shell32.lib \
	windowscodecs.lib \
	shlwapi.lib \
	imm32.lib \
	winmm.lib \
	Advapi32.lib \
	Userenv.lib \
	Winhttp.lib \
	Crypt32.lib \
	Secur32.lib

CFILES =  \
	src/main.c \
	src/utils.c \
	src/libmatoya.c \
	src/libparsec.c \
	src/libmtymap.c

OBJS = \
	main.o \
	utils.o \
	libmatoya.o \
	libparsec.o \
	libmtymap.o

INCLUDES = \
	-Iincludes \
	-Isrc

FLAGS = \
	-Os \
	-march=native


CFLAGS = $(INCLUDES) $(FLAGS)

all:
   clang $(CFILES) $(CFLAGS) -c
   link $(OBJS) $(LIBS)
