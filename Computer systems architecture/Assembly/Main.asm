.386
.model flat, stdcall
.stack 4096

ExitProcess PROTO, dwExitCode:DWORD

.data

.code
main PROC ; for(i=5; i!=0; i-- ) y -= i
    
    mov ax, 0
    mov cx, 5

_loop:
    mov dx, 0
    cmp dx, cx
    jz _end

    mov dx, cx
    xor dx, x0ffff
    add dx, 1
    add ax, dx

    add cx, 0xffff
    jmp _loop

_end:    
    
    INVOKE ExitProcess, ax
main ENDP

END main