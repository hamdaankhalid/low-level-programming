
global _start

section .data
  given_str: db 'hamdaan khalid', 0 ; null terminated with the 0
  newline_char: db 10

section .text

strlen:
  xor rax, rax ;rax holds length, we zero it out first
.loop:
  cmp byte [rdi + rax], 0 ; check if we are at null
  je .end ; if we are at null exit the loop and the func
  inc rax ; if we not at null we reach here and increment our accumulator
  jmp .loop ; keep looping
.end:
  ret
_start:
  mov rdi, given_str ; pass in argument for fucn call below
  call strlen
  
  mov rdi, rax ; set exit status as result
  mov rax, 60 ; exit syscall flag
  syscall