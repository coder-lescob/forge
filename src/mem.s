global isheap,@function
global isstack,@function

section .text

isstack:
    mov rcx, rax    ; rcx = rax
    xor rax, rax    ; rax = 0
    cmp rcx, rsp    ; if rcx > rsp
    jb ret_false    ; it's a stack var
    mov rax, 1      ; rax = 1
ret_false:
    ret

isheap:
    call isstack
    xor rax, 1
    ret

section .data

section .note.GNU-stack