global _start
section .data
  message db "yellow"
section .start
_start:
  mov [message], byte 'H' ; move byte H into start of the memory of message
  mov [message+5], byte '!' ; move byte ! into 5 offset from start of memory of message  
  mov eax, 4  ; sys_write system call set
  mov ebx, 1 ; stdout file descriptor
  mov ecx, message ; bytes to write
  mov edx, 6 ; num of bytes to write
  int 0x80 ; perfrom system call
  mov eax, 1 ; sys exit system call
  mov ebx, 0 ; exit status is 0
  int 0x80
