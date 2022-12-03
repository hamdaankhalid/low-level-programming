section .text

; Accepts an exit code and terminates current process
exit:
  mov rax, 60 ; exit syscall flag
  syscall ; Since rdi already has the exit call status being passed as the function argument we are chilling

; Accepts a pointer to a string and returns its length
string_length:
    xor rax, rax
.iterate:
  cmp byte [rdi + rax], 0 ; are we at null terminator for input rdi?
  je .end
  inc rax
  jmp .iterate
.end:
    ret

; Accepts a pointer to a null terminated string and prints it stdout.
print_string:
  push rdi ; put input on stack so we can use it later since we dont change anything with rdi it is also used as the argument for the function call below
  call string_length 
  pop rsi ; restore input from stack into rsi
  mov rdx, rax ; the amount of bytes to write is stored in rax from the func call we had made
  mov rax, 1 ; print
  mov rdi, 1  ; file descriptor stdout
  syscall
  ret

; accepts a characcter code directly as its first argument and prints it to stdout
print_char:
  push rdi

  mov rdi, rsp
  call print_string 

  pop rdi
  ret


print_newline:
    mov rdi, 10
    call print_string
    ret

print_uint:
    xor rax, rax
    ret


print_int:
    xor rax, rax
    ret

string_equals:
    xor rax, rax
    ret


read_char:
    xor rax, rax
    ret 

read_word:
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret 

; rdi = source
; rsi = dest
; rdx = dest length 
string_copy:
    push rdi
    push rsi
    push rdx
    
    call string_length
    
    pop rdx
    pop rsi
    pop rdi

    cmp rax, rdx
    jae .length_not_equal
    ; at this point we know they are at equal lengths
.iterate:
  mov dl, byte[rdi] ; use dl register to move bytes
  mov byte[rsi], dl
  inc rdi
  inc rsi
  test dl, dl
  jnz .iterate


.length_not_equal:
    xor rax, rax
    ret
