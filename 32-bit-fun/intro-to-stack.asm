; Linux compile with asssembler => nasm -f elf32 intro-to-stack.asm -o intro-to-stack.o 
; Make executable => ld -m elf_1386 intro-to-stack.o -o intro-to-stack

global _start

_start:
  sub esp, 4 ;make space for 4 bytes on the stack esp
  mov [esp], byte 'H'
  mov [esp+1], byte 'e'
  mov [esp+2], byte 'y'
  mov [esp+3], byte '!'
  mov eax, 4 ; sys_write system call
  mov ebx, 1 ; stdout file description
  mov ecx, esp ; pointer to bytes to write
  mov edx, 4 ; num of bytes to write
  int 0x80 ; perform system call
  mov eax, 1 ; sys_exit system call
  mov ebx, 0 ; exit status is 0
  int 0x80
