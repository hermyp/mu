all:
	g++ src/*.c++ \
	-lopenal -lalut \
	-I lib \
	-Wno-deprecated-declarations \
	-o mu
