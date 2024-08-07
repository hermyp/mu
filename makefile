all:
	g++ src/*.c++ \
	-lopenal -lalut \
	-I lib \
	-o mu
