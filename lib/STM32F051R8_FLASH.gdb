target remote :4242
load
displ /i $pc
displ /x $sp
displ
b ResetHandler
b SystemInit
b main