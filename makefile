INCLUDES = \
	-Iincludes \
	-Isrc \
	-Ideps/imgui

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
	src/libmtymap.c \
	src/libimgui.c \

CPPFiles = \
	deps/imgui/im.cpp


OBJS = \
	main.bc \
	utils.bc \
	libmatoya.bc \
	libparsec.bc \
	libmtymap.bc \
	libimgui.bc \
	im.bc

INCLUDES = \
	-Iincludes \
	-Isrc

FLAGS = \
	-Os

CFLAGS = $(INCLUDES) $(FLAGS)

all:
	@binary_to_compressed_c -nocompress main.js mainjs > includes/defaultjs.h
	@binary_to_compressed_c -nocompress deps/parsec32.dll p32 > includes/parsec_embed.h

	@clang $(CFILES) $(CPPFiles) $(CFLAGS) -c -emit-llvm
	@rc /nologo resources/.rc

	@del debug.exe
	@lld-link $(OBJS) $(LIBS) /NOLOGO resources/.res  /SUBSYSTEM:Console /OUT:debug.exe /debug

	@del release.exe
	@lld-link $(OBJS) $(LIBS) /NOLOGO resources/.res  /SUBSYSTEM:WINDOWS /OUT:release.exe

	@del $(OBJS)

run:
	debug.exe
