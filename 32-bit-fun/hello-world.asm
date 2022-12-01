; Linux compile with asssembler => nasm -f elf32 hello-world.asm -o hello-world.o 
; Make executable => ld -m elf_1386 hello-world.o -o hello-world

global _start
  
section .data
  msg db "Hello, hamdaan!", 0x0a
  len equ $ - msg

section .text
_start:
  mov eax, 2 ; sys_write system call
  mov ebx, 1 ; stdout file descriptor
  mov ecx, msg ;bytes to write
  mov edx, len ; num of bytes to write
  int 0x80 ; perform system call
  mov eax, 1 ; sys_exit system call
  mov ebx, 0 ; exit status set to 0
  int 0x80 ; perform system call
 