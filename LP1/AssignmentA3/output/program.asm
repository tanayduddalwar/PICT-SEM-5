MACRO
INCR &MEM_VAL, &INCR_VAL, &REG
MOVER &REG, &MEM_VAL
ADD &REG, &INCR_VAL
MOVEM &REG, &MEM_VAL
MEND

MACRO
INCR_M &MEM_VAL=, &INCR_VAL=, &REG=
MOVER &REG, &MEM_VAL
ADD &REG, &INCR_VAL
MOVEM &REG, &MEM_VAL
MEND

MACRO
INCR_D &MEM_VAL=, &INCR_VAL=, &REG=AREG
MOVER &REG, &MEM_VAL
ADD &REG, &INCR_VAL
MOVEM &REG, &MEM_VAL
MEND