
#include <commands.h>
#include <shell.h>
#include <stdioAPI.h>
#include <tron.h>


void help(args argsVec){
    printf("\n");
    printf("Command List:\n");
    printf("inforeg - Prints the registers\n");
    printf("divzero - Tests div zero exception\n");
    printf("invopcode - TEsts invalid opcode exception\n");
    printf("time - Prints the current time\n");
    printf("clear - Clears the screen\n");
    printf("tron - Lets you play tron\n");
    printf("biggie - Lets you zoom in\n");
    printf("smalls - Lets you zoom out\n");
    printf("getContent - Print the next 32 bytes to the memory address you pass as an argument \n");
    printf("help - Prints this menu\n");
}

void inforeg(args argsVec){
    //Poner para imprimir los registros
    printf("\n");
    printf("Registers:\n");
    printf("RAX: 0x%x\n", getRAX());
    printf("RBX: 0x%x\n", getRBX());
    printf("RCX: 0x%x\n", getRCX());
    printf("RDX: 0x%x\n", getRDX());
    printf("RBP: 0x%x\n", getRBP());
    printf("RSP: 0x%x\n", getRSP());
    printf("RDI: 0x%x\n", getRDI());
    printf("RSI: 0x%x\n", getRSI());
    printf("R8: 0x%x\n", getR8());
    printf("R9: 0x%x\n", getR9());
    printf("R10: 0x%x\n", getR10());
    printf("R11: 0x%x\n", getR11());
    printf("R12: 0x%x\n", getR12());
    printf("R13: 0x%x\n", getR13());
    printf("R14: 0x%x\n", getR14());
    printf("R15: 0x%x\n", getR15());
}

void div_zero_exception_tester(args argsVec){
    int j=1,i=0;
    j=j/i;
}

void invalid_opcode_exception_tester(args argsVec){
    invalidOpcodeTester();
}

void tron_command(args argsVec){
    tron();
}

void clear(args argsVec){
    clearScreen();
}

void getContent(args argsVec){
    char * address = (char *) argsVec[0];
    unsigned char  * realAddress = (unsigned char *)hex2int(address);
    printf("\n");
    for(int i = 0; i < 32; i++){
        printf("The contents of the memory address %x is %x \n", realAddress +i, realAddress[i]);
    }
    
}

void time(args argsVec){
    printf("\n");
    while(1){
        if(getStatusRegA()!=0x80){
            printf("The time is: %d:%x:%x\n",calculateHours() ,getMinutes(),getSeconds());
            return;
        }
    }
}


int calculateHours(){

	int dec = getHours() & 240;
	dec = dec >> 4;
	int units = getHours() & 15;
	return ((dec * 10 + units)-3)%24;

}

