/*
ComputerSum.tst script
computes the sum of integers from 1 to 10 (loop statement)
*/
load Computer.hdl,
output-file ComputerSum.out,
output-list time%S1.4.1 reset%B2.1.2 ARegister[0]%D1.7.1 DRegister[0]%D1.7.1  pc%D1.1.1 RAM64[16]%D1.7.1 RAM64[17]%D1.7.1;

// Load Sum.Hack into ROM32K chip

ROM32K load Sum.hack,

// Run the clock enough cycles to complete the program's execution (at the beginning pc=0, reset=0)
repeat 151 {
    tick, tock, output;
}

// Reset the computer
set reset 1,
set RAM64[16] 0,
set RAM64[17] 0,
tick, tock, output;