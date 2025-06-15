section .data
    msg         db  'Please enter a char: ', 10
    msg_len     equ $-msg

section .text
    global _start

_start:
    mov eax, 1
    mov ebx, 1
    mov ecx, msg
    mov edx, msg_len
    int 0x80

    mov eax, 60         ; sys_exit
    xor ebx, edx        ; exit code 0
    int 0x80

    ; mov rax, 1          ; syscall: write
    ; mov rdi, 1          ; file descriptor: stdout
    ; mov rsi, msg        ; pointer to message
    ; mov rdx, 14         ; message length
    ; syscall

    ; mov rax, 60         ; syscall: exit
    ; mov rdi, 0          ; exit code 0
    ; syscall
