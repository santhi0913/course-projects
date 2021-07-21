/*
ComputerComp.tst script
computes c=|a-b|( if then else statement )
*/
load Computer.hdl,
output-file ComputerComp.out,
output-list time%S1.4.1 reset%B2.1.2 ARegister[0]%D1.7.1 DRegister[0]%D1.7.1 pc%D1.1.1 RAM64[16]%D1.7.1 RAM64[17]%D1.7.1 RAM64[18]%D1.7.1 ;

// Load Comp.hack into ROM32K chip

ROM32K load Comp.hack,
set RAM64[16] 3,
set RAM64[17] 4,
output;

// Run the clock enough cycles to complete the program's execution (at the beginning pc=0, reset=0)
repeat 12 {
    tick, tock, output;
}

// Reset the computer
set reset 1,
set RAM64[16] 0,
set RAM64[17] 0,
set RAM64[18] 0,
tick, tock,output;
