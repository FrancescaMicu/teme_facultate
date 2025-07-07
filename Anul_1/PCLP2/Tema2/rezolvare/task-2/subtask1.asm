%include "../include/io.mac"

; declare your structs here

struc date
    .day:       resb 1
    .month:     resb 1
    .year:      resw 1
endstruc

struc events
    .name:      resb 31
    .valid:     resb 1
    .date:      resb date_size
endstruc 

section .data

section .text
    global check_events
    extern printf

check_events:
    ;; DO NOT MODIFY
    enter 0,0
    pusha

    mov ebx, [ebp + 8]      ; events
    mov ecx, [ebp + 12]     ; length
    ;; DO NOT MODIFY

    ;; Your code starts here

; initializarea contorului pentru parcurgere
xor esi, esi

; parcurgerea vectorului de evenimente
iter_arr:
    ; verificare daca am ajuns la finalul vectorului
    cmp esi, ecx
    je end

    ; obtinerea adresei elementului
    mov eax, events_size
    imul eax, esi

    ; setare ca fiind valid la inceput
    mov byte[ebx + eax + events.valid], 1

    ; verificare daca anul e valid
    cmp word[ebx + eax + events.date + date.year], 1990
    jl not_valid

    cmp word[ebx + eax + events.date + date.year], 2030
    jg not_valid

    ; verificare daca luna e valida
    cmp byte[ebx + eax + events.date + date.month], 1
    jl not_valid

    cmp byte[ebx + eax + events.date + date.month], 12
    jg not_valid

    ; obtinerea numarului de zile din luna respectiva
    push ecx
    mov cl, [ebx + eax + events.date + date.month]
    jmp days_of_month

; determinarea nr de zile din luna
days_of_month:
    ; verifica daca luna are 28 de zile
    cmp cl, 2
    je days_28

    ; verifica daca luna are 30 de zile
    cmp cl, 4
    je days_30
    cmp cl, 6
    je days_30
    cmp cl, 9
    je days_30
    cmp cl, 11
    je days_30

    ; altfel luna are 31 de zile
    mov dl, 31

    jmp valid_day

; verificare daca data este valida
valid_day:
    pop ecx

    ; verificare daca ziua e valida
    cmp byte[ebx + eax + events.date + date.day], 1
    jl not_valid

    cmp byte[ebx + eax + events.date + date.day], dl
    jg not_valid

    ; incrementare si salt
    inc esi
    jmp iter_arr

days_30:
    mov dl, 30
    jmp valid_day

days_28:
    mov dl, 28
    jmp valid_day

; resetarea daca nu e valid 
not_valid:
    mov byte[ebx + eax + events.valid], 0
    inc esi
    jmp iter_arr

; sfarsitul codului
end:

    ;; Your code ends here

    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY