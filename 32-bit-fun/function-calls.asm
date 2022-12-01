global  _start

_start:
  call myfunc
  mov eax, 1 ; sys exit call
  mov ebx, 0 ; exit code
  int 0x80 ; perform system exit

; Preserving stack and allocating space on the stack is known as prologue
; Restoring of stack and returning is known as epoilogue
myfunc:
  push ebp ; preserve old value of ebp this allows nested function calls
  mov ebp, esp ; store esp stack pointer in ebp so we can change it back ater we are done messing aroud with stack pointer
  sub esp, 2 ; make 2 byte spaces in our stack
  mov[esp], byte 'H'
  mov[esp+1], byte 'i'
  mov eax, 4 ; sys_write system call
  mov ebx, 1 ; stdout file descriptor
  mov ecx, esp ; bytes to write
  mov edx, 2 ; num of bytes to write to stdout
  int 0x80 ; make system call
  mov esp, ebp ; reset our stack to what it was before our manipulations
  pop ebp
  ret
