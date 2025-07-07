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

section .text
    global sort_events
    extern printf

sort_events:
    ;; DO NOT MODIFY
    enter 0, 0
    pusha

    mov ebx, [ebp + 8]      ; events
    mov ecx, [ebp + 12]     ; length
    ;; DO NOT MODIFY

    ;; Your code starts here
    
    ; initializarea contoarelor pt cele doua bucle
    ; ale algoritmului de sortare
    xor esi, esi
    xor edi, edi

; parcurgerea primei bucle
iter_arr_1:
    ; verificare daca am ajuns la finalul vectorului
    cmp esi, ecx
    je end
    
    ; sare la a 2 a iteratie
    jmp iter_arr_2

; pregatirea pentru o noua iteratie
; a primei bucle
prep_back_to_arr_1:
    xor edi, edi
    inc esi
    jmp iter_arr_1

; parcurgerea celei de a doua bucle
iter_arr_2:
    ; verificare daca am ajuns la finalul vectorului
    cmp edi, ecx
    je prep_back_to_arr_1

    push ecx

    ; calcularea offseturilor elementelor
    mov eax, 36
    imul eax, esi

    mov edx, 36
    imul edx, edi

    ; retinerea validului elementelor
    mov cl, [ebx + eax + events.valid]
    mov ch, [ebx + edx + events.valid]

    ; pregatirea contorului pentru interschimbare
    push esi
    mov esi, 36

    ; verificare daca trebuie interschimbate
    cmp cl, ch
    ; primul e valid, al doilea nu
    jg swap_elem
    je verif_date

    ; restaurarea stivei
    pop esi
    pop ecx
    inc edi
    jmp iter_arr_2

; verificarea datei
verif_date:
    ; verificarea relatiei de ordine pt an
    push edi
    mov cx, [ebx + eax + events.date + date.year]
    mov di, [ebx + edx + events.date + date.year]
    cmp cx, di
    jl prep_swap_from_year
    jg prep_back_to_arr_2_from_year
    pop edi


    ; verificarea relatiei de ordine pt lunia
    mov cl, [ebx + eax + events.date + date.month]
    mov ch, [ebx + edx + events.date + date.month]
    cmp cl, ch
    jl swap_elem
    jg prep_back_to_arr_2

    ; verificarea relatiei de ordine pt zi
    mov cl, [ebx + eax + events.date + date.day]
    mov ch, [ebx + edx + events.date + date.day]
    cmp cl, ch
    jl swap_elem
    jg prep_back_to_arr_2

    ; pregatirea pentru verificarea numelui
    xor esi, esi
    jmp strcmp

; verificarea numelui
strcmp:
    push eax

    ; calcularea offsetului caracterului respectiv
    add eax, events.name
    add eax, esi

    push edx
    add edx, events.name 
    add edx, esi

    ; retinerea caracterului respectiv
    mov cl, byte[ebx + eax]
    mov ch, byte[ebx + edx]

    pop edx
    pop eax

    ; verificare daca s-a ajuns la finalul numelui
    cmp cl, 0
    je prep_back_to_arr_2
    cmp ch, 0
    je prep_back_to_arr_2
    
    ; verificarea relatiei de ordine intre nume
    cmp cl, ch
    jl prep_swap_from_strcmp
    jg prep_back_to_arr_2

    inc esi
    jmp strcmp

; intoarcerea la a 2 a bucla dupa verificarea anului
prep_back_to_arr_2_from_year:
    pop edi
    jmp prep_back_to_arr_2

; pregatirea pentru interschimbare dupa verificarea anului
prep_swap_from_year:
    pop edi
    jmp swap_elem

; pregatirea pentru interschimbare dupa compararea numelor
prep_swap_from_strcmp:
    mov esi, 36
    jmp swap_elem

; pregatirea pentru intoarcerea la a 2 a bucla
; dupa restul verificarilor
prep_back_to_arr_2:
    pop esi
    pop ecx
    inc edi
    jmp iter_arr_2

; interschimbarea elementelor din vector
swap_elem:
    ; interschimbarea elementelor
    mov cl, [ebx + eax]
    mov ch, [ebx + edx]

    mov [ebx + eax], ch
    mov [ebx + edx], cl

    ; incrementarea/decrementarea contoarelor pentru bytes
    inc eax
    inc edx
    dec esi

    ; verificare daca s-a ajuns la finalul bytes-urilor
    cmp esi, 0
    jne swap_elem

    jmp prep_back_to_arr_2

; sfarsitul codului
end:

    ;; Your code ends here

    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY