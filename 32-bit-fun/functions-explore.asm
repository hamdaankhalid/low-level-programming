; use stack to pass parameters to function in x86 right before calls and return values are put in using eax register

global _start

_start:
  push 21 ; 21 is pushed on the stack this will be used as an argument by the call below
  call times2
  mov ebx, eax ; result from above func is stored in eax, move it into ebx
  mov eax, 1 ; sys exit call
  int 0x80 ; perform system exit

_times2:
  push ebp ; next 2 lines are prologues
  mov ebp, esp
  mov eax, [ebp+8] ; move the argument passed to the function into eax
  add eax, eax ; eax += eax
  mov esp, ebp ; epilogue
  pop ebp
  ret
