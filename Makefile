CC=g++ -g

#all: vr el2fi cfp mr spikedata merge CAT FRH

all:
	$(CC)  -o bubble.solver  main.cpp

