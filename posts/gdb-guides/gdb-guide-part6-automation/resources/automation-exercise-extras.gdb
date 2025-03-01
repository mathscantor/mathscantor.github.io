et pag off
set output-radix 16
set confirm off
set disassembly-flavor intel

b write
condition 1 $rdi != 1
commands 1
  info registers rdi rsi rdx
  printf "IPC Message: %s\n", $rsi
  continue
end

# After setting the breakpoint and  commands, resume the process.
continue
