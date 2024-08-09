all:
	g++ src/*.c++ \
	-lopenal -lalut \
	-I lib -I src/header \
	-Wno-deprecated-declarations \
	-o mu
