# gdb --batch -x solution.gdb ./bin

set pag off 
set output-radix 16
set disassembly-flavor intel

b *(main + 0x5d2)
commands
	set $flag = {unsigned long long}$rdi
	continue
end

b *(main + 0x5d7)
commands
	x/s $flag
	continue
end

run