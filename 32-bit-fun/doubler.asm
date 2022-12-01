; Linux compile with asssembler => nasm -f elf32 doubler.asm -o doubler.o 
; Make executable => ld -m elf_1386 doubler.o -o doubler

global _start ; entrypoint

section .text ; where i write the code
_start:  ; define my entrypoint
  mov ebx, 1 ; start ebx at 1, I am using ebx to store the result, sicnce ebx stores the return status
  mov ecx, 4 ; number of iterations stored
myloop: ; label so I can jump to this by naming
  add ebx, ebx ; ebx += ebx
  dec ecx ; exc -= 1
  cmp ecx, 0 ; compare ecx with 0
  jg myloop ; jump to myloop if ecx is greater than 0
  mov eax, 1 ; sys_exit sysmtem call flag
  int 0x80 ; system call. At this point the value in ebx is returned as status.
