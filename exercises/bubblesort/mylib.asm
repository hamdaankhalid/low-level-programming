
; Some NOTES to remember when coding :)
; %rdi	1st argument
; %rsi	2nd argument,
; %rdx	3rd argument

global bubblesort
global sumarr
global swaptwo


; ############### bubblesort function #############
; int array as first arg -> rdi
; size of array as second arg -> rsi
;**
bubblesort:
  push r14 ; Save non-volatile registers we overwrite
  push r15

  mov rax, 0 ; outer loop counter
.outer_loop_for:
  cmp rax, rsi ; if we have done n^2 iterations we need to exit
  je .exit
  mov rcx, 1; inner loop counter that goes form 1 - n comparing i with i -1
  .inner_loop_for:
    cmp rcx, rsi ; if inner loop counter has reached end then end this iteration of inner loop
    je .end_outer_loop_for
    
    mov r14d, [rdi + (rcx * 4)] ; load 4 byte int from c array at rcx into r14d
    mov r15d, [rdi + (rcx-1)*4] ; load 4 byte int from c array at 1 before rcx into r15d
    cmp r14d, r15d ; if the number at our current index is less than the its neighbor then we skip swapping othewise we swap
    jg .skip_swap

    mov [rdi+ rcx*4], r15d ; SWAP the neighbors
    mov [rdi+ (rcx-1)*4], r14d

    .skip_swap:
      inc rcx
      jmp .inner_loop_for
.end_outer_loop_for:
  inc rax
  jmp .outer_loop_for
.exit:
  pop r15 ; Restore non-volatile registers
  pop r14
  ret


swaptwo:
  push r14           ; Save non-volatile registers we overwrite
  push r15

  mov r14,[rdi+ rsi*4] ; Move 4 byte from [rdi+rsi] to r14.
  mov r15,[rdi+ rdx*4] ; Move 4 byte from [rdi+rdx] to R15. R15B is lower 8 bits of R15
  mov [rdi+ rsi*4],r15 ; Move the byte in R15B to [rdi+rsi]
  mov [rdi+ rdx*4],r14 ; Move the byte in R14B to [rdi+rdx]
  mov rax,rdi

  pop r15            ; Restore non-volatile registers
  pop r14
  ret


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
