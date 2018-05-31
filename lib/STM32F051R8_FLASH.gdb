target remote :4242
load
displ /i $pc
displ /x $pc
displ /x $sp
displ /x $r0
displ /x $r1
displ /x $r2
displ /x $r3
displ
b main
monitor reset
