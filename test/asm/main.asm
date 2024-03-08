section .text
        global  main
        extern printf
    main:
;         mov     edx,end_len
;         mov     ecx,end_msg
;         ; mov     ebx,0               ;first argument: file handle (stdout)
;         mov     eax,4               ;system call number (sys_write)
;         int     0x80                ;call kernel
;         mov     edx, start_msg
;         mov     ecx, start_len
;         mov     ebx,0               ;first argument: file handle (stdout)
;         mov     eax,4               ;system call number (sys_write)
;         int     0x80                ;call kernel
;
;         mov     eax,1               ;system call number (sys_exit)
;         int     0x80                ;call kernel
        mov rax, 1 ; sys_write
        mov rdi, 0 ; std
        mov rsi, start_msg
        mov rdx, start_len
        syscall
        mov rax, 1
        mov rdi, 0
        mov rsi, end_msg
        mov rdx, end_len
        syscall

        mov rax, 1
        mov rbx, 2
        add rax, rbx
        mov [sum], rax
        mov rax, sum
        mov rdi, rax
        ; mov rsi, sum
        mov eax, 0

        call printf
        ; mov DWORD PTR, 1
        ; mov DWORD PTR, 2
        ; mov edx, DWORD PTR
        ; mov eax, edx

        mov rax,60
        mov rdi, 0
        syscall

section .data                   ;section declaration
    start_msg db      "Hello, world!",10 ;our dear string
    start_len equ     $ - start_msg

    end_msg db      "Bye World!", 10
    end_len equ     $ - end_msg

    sum resb 1
