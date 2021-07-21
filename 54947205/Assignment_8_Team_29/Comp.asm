// if a>b then c=a-b else c=b-a
 
   @a
   D=M    // D = a
   @b
   D=D-M  // D = a - b
   @ENDIF
   D;JGT  // if(a-b)>0 goto ENDIF
   @b
   D=M    // D = b
   @a
   D=D-M  // D = b - a
(ENDIF)
   @c
   M=D    // M = c