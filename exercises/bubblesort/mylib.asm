
; Some NOTES to remember when coding :)
; %rdi	1st argument
; %rsi	2nd argument,
; %rdx	3rd argument

global bubblesort
global sumarr


; ############### bubblesort function #############
; int array as first arg
; size of array as second arg
bubblesort:
  ; PROLOGUE
  push rbp ; preserve old value of ebp this allows nested function calls
  mov rbp, rsp ; store esp stack pointer in ebp so we can change it back ater we are done messing aroud with stack pointer
  ; ########
  mov rax, 1 ; iterator starts from first item in arr
.outer_loop:
  cmp rax, rsi
  je .end
  ; now rax holds the index of the candidate
  ; rdi already has first value, our array pointer
  ; rsi already holds the size of the array
  push rdi
  push rsi
  push rax
  mov rdx, rax
  call move_idx_to_spot
  pop rax
  pop rsi
  pop rdi
  inc rax
  jmp .outer_loop
.end:
  ; EPILOGUE
  mov rsp, rbp ; reset our stack to what it was before our manipulations
  pop rbp
  ; #########
  ret

; Bubble each candidate till sorted
; first argument is the pointer to the first element of the int array %rdi
; second argument is the size of the int array %rsi
; third argument is currIdx %rdx
move_idx_to_spot:
  ; PROLOGUE
  push rbp ; preserve old value of ebp this allows nested function calls
  mov rbp, rsp ; store esp stack pointer in ebp so we can change it back ater we are done messing aroud with stack pointer
  ; ########
  xor rcx, rcx ;  0 out our offset iterator
.loop:
  mov r10, rcx
  add r10, rdx  ; r10 = rcx+rdx
  cmp r10, rsi ; if our offset+iterator has reached end of array terminate
  je .end
  mov r11, [rdi + rcx*4] ; put curr in temp
  cmp [rdi + (rcx*4) - 4], r11 ; if curr is less than the one before swap
  jg .if_greater_then_swap
.continue:
  inc rcx
  jmp .loop
.end:
  ; EPILOGUE
  mov rsp, rbp ; reset our stack to what it was before our manipulations
  pop rbp
  ; #########
  ret
.if_greater_then_swap:
  ; SWAP
  mov r14, [rdi + rcx*4]
  mov r13, [rdi + (rcx*4) - 4]
  mov [rdi + rcx*4], r13
  mov [rdi + (rcx*4) - 4], r14
  jmp .continue


; ############### sumarr function #############
; Pass array pointer as 1st argument, and return sum
sumarr:
  ; PROLOGUE
  push rbp ; preserve old value of ebp this allows nested function calls
  mov rbp, rsp ; store esp stack pointer in ebp so we can change it back ater we are done messing aroud with stack pointer
  ; ########
  ;first argument is the pointer to the first element of the int array %rdi
  ; second argument is the size of the int array %rsi
  xor rcx, rcx ; 0 out our iterator
  xor rdx, rdx ; 0 out accumulator
.iterate:
  cmp rcx, rsi
  je .end
  add rdx, [rdi + rcx*4]
  inc rcx
  jmp .iterate
.end:
  mov rax, rdx
  ; EPILOGUE
  mov rsp, rbp ; reset our stack to what it was before our manipulations
  pop rbp
  ; #########
  ret
