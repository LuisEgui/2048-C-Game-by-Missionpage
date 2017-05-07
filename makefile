#######################################################################################
############################### 2048 GAME #############################################

CFLAGS = -Wall -g -ansi -pedantic 

OBJ = 2048.o

#######################################################################################

all: 2048


############################### COMPILE TARGETS #######################################

2048:  2048.c functions.h
	@gcc $(CFLAGS) 2048.c -lm -std=c99 -o 2048
	
	@ echo "2048.c has been compiled...\n"
	
############################### EXEC TARGETS ##########################################

run:

	@ echo "Running the game...\n"
	@./2048
	
runv:
	@valgrind --leak-check=full -v ./2048
	
	@ echo "Running the game with valgrind!\n"


############################### CLEAN TARGETS #########################################

clear:
	@rm -rf *.o
	@ echo "\nRemoving object files...\n"
	
clean:
	@rm 2048
	
	@ echo "\nRemoving the executable of the game...\n"
	
############################### INFO TARGETS ##########################################
	
authors:
	@ echo "--------------------------------------------------------------"
	@ echo "Game developed by Luis! "
	@ echo "I hope you enjoy it!!!"
	@ echo "--------------------------------------------------------------"
	
help:
	@ echo "This is the help for this makefile!\n"
	@ echo "Write \" make all \" to compile all the game.\n"
	@ echo "Write \" make run \" to execute the game COMPILED. If it's not already compiled it will show you an error.\n"
	@ echo "Write \" make authors \" to get the information of the authors.\n"
	@ echo "For more help, OPEN IT!\n"
