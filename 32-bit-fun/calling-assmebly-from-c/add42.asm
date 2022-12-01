global add42

add42:
  push ebp ; prologue next 2 lines
  mov ebp, esp
  mov eax, [ebp + 8] ; move arg into eax;
  add eax, 42 ; add 42 to eax
  mov esp, ebp ; epilogue next 2 lines
  pop ebp
  ret
