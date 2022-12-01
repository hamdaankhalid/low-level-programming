; print newline prints the newline char
; print_hex will accept a number and print it in hexadecimal format.

section .data
  newline_char: db 10
  codes: db '0123456789ABCDEF'

global _start

section .text

print_newline:
  mov rax, 1 ; 'write' syscall identifier
  mov rdi, 1 ; stdout file descriptor
  mov rsi, newline_char ; what to write
  mov rdx, 1 ; the amount of bytes to write
  syscall
  ret

print_hex:
  mov rax, rdi ; 
  mov rdi, 1 
  mov rdx, 1
  mov rcx, 64
  ; each 4 bits should be out[ut as one hexadecimal digit
  ; use shift and bitwise AND to isolate them
  ; the result is the offset in 'codes' array
iterate:
  push rax ; save the initial value
  sub rcx, 4 ; shift to 60, 56, 52, ... 0
  ; cl is a register, smallest part of rcx
  sar rax, cl
  and rax, 0xf ; clear all the buts but the lowest 4
  lea rsi, [codes + rax] ; take hexadecimal character code
  mov rax, 1

  ; syscall leaves rcx and r11 changed so we save it to the stack
  push rcx
  syscall
  pop rcx
  
  pop rax
  ; test can be used for the fastes 'is it a zero?' check
  test rcx, rcx
  jnz iterate ; transfers control to the specified address if the value in the accumulator is not 0.
  ret

_start:
  mov rdi, 0x1122334455667788
  call print_hex
  call print_newline

  mov rax, 60 ; exit system call
  xor rdi, rdi
  syscall
