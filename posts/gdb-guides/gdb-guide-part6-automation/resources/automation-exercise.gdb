set pag off
set output-radix 16
set confirm off
set disassembly-flavor intel

b write
commands
  info registers rdi rsi rdx
  continue
end

# After setting the breakpoint and  commands, resume the process.
continue
