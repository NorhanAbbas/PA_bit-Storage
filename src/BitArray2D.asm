 ;Credits go to Arnold Smith & Maria Gallivan
 ;they have helped me with this part ¯\_(ツ)_/¯
        global  set_bit_elem
        global  get_bit_elem
        section .text

set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here

        ;index = row*row_width + column
        ;byte_offset = index / 8
        ;bit_offset = index - (byte_offset * 8)
        ;mask = 1 << (8 - bit_offset - 1)
        ;byte := byte or mask

        ;index = row*row_width + column
        mov rax,rdx         ; move row to rax
        imul rax,rsi        ; multiply row by row width, store it in rax
        add rax,rcx         ; add it to column

        ;bit_offset = index - (byte_offset * 8)
        cmp rax, 8          ; if < 8, go to another step, >= (jge)
        jl .LanotherStep
        jge .Loffset

        ;mask = 1 << (8 - bit_offset - 1)

.Loffset:   ; to get the byte offset
        ;mov r2, rax
        sar rax, 3
        cmp rax, 8          ; if rax >= 8, (jge) repeat, (jl)
        jge .Loffset
        ;cmovae Loffset     ;unsigned

.LanotherStep:
        ;cmp rax, 1
        cmp rax, 0          ; if equal to
        je .finish
.finish:

       ;byte := byte or mask
       mov rdx, 1          ; set that bit to 1
       mov rax, rdx        ; place the row into rax

       mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
       pop rbp             ; remove rbp from the stack to restore rsp to initial value
       ret                 ; return value in rax




get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col
        mov rax,rdx         ; move row to rax
        imul rax,rsi        ; multiply row by row width, store it in rax
        add rax,rcx         ; add it to column


        ; should i compare it to 1 or 8 bits??? for the offset?
        ;cmp rax, 1          ; compare the target bit to 1
        ;je .done              ; if rax = 1, go to L1



        ;bit_offset = index - (byte_offset * 8)
        cmp rax, 8          ; if < 8, go to another step, >= (jge)
        jl .LanotherStep
        jge .Loffset


.Loffset:   ; to get the byte offset
        ;mov r2, rax
        ;div rax, 8
        sar rax, 3
        cmp rax, 8          ; if rax >= 8, (jge) repeat, (jl)
        jge .Loffset
        ;cmovae Loffset     ;unsigned

.LanotherStep:
        ;cmp rax, 1
        cmp rax, 0          ; if equal to
        je .finish
.finish:

       ;byte := byte or mask
       mov rdx, 1          ; set that bit to 1
       mov rax, rdx        ; place the row into rax

       mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
       pop rbp             ; remove rbp from the stack to restore rsp to initial value
       ret                 ; return value in rax



.done:
        mov rax, 0
        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax

;mask = 1 << (8 - bit_offset - 1)
.mask:                      ; not sure if this is being used!
       shl rax, 1           ; shift left
       sub rax, 1           ; subtract 1
       cmp rax, 0           ; check if it is not equal to zero, (jne) Repeat
       jne .mask