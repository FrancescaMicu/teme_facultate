%include "../include/io.mac"

extern printf
global check_row
global check_column
global check_box
; you can declare any helper variables in .data or .bss

; initilizarea vectorului de frecventa
; pt cifre
section .bss
    frecv resb 10

section .text


; int check_row(char* sudoku, int row);
check_row:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    push ebx
    push ecx
    push edx
    push esi
    push edi

    mov     esi, [ebp + 8]  ; char* sudoku, pointer to 81-long char array
    mov     edx, [ebp + 12]  ; int row 
    ;; DO NOT MODIFY
   
    ;; Freestyle starts here

    ; se considera la inceput eax 1
    mov eax, 1

    ; calcularea contorului de start al
    ; liniei: edx * 9
    imul edx, edx, 9

    ; initializarea lui ebx contor de coloana
    xor ebx, ebx

; parcurgerea vectorului sudoku
verif_lin:
    ; verificare daca am ajuns la finalul vectorului
    cmp ebx, 9
    je prep_reset_lin

    push eax
    ; mutarea in al a elementului
    mov al, [esi + edx]

    ; verificarea daca elementul este cifra valida (1-9)
    cmp al, 1
    jl wrong_lin

    cmp al, 9
    jg wrong_lin

    ; verificare daca cifra apare a mai aparut pe linie
    mov cl, [frecv + eax]
    cmp cl, 1
    je wrong_lin

    ; actualizarea frecventei pentru cifra gasita
    mov byte[frecv + eax], 1
    pop eax
    inc edx
    inc ebx
    jmp verif_lin

; resetarea lui eax pt conditii gresite
wrong_lin:
    pop eax
    mov eax, 2

; pregatirea pt resetarea vectorului de frecventa
prep_reset_lin:
    xor ecx, ecx

reset_frecv_lin:
    ; resetarea la 0 a frecventei
    mov byte[frecv + ecx], 0
    inc ecx

    ; verificare daca am ajuns la finalul vectorului
    cmp ecx, 10
    jl reset_frecv_lin

    ;; MAKE SURE TO LEAVE YOUR RESULT IN EAX BY THE END OF THE FUNCTION
    ;; Remember: OK = 1, NOT_OKAY = 2
    ;; ex. if this row is okay, by this point eax should contain the value 1 

    ;; Freestyle ends here
end_check_row:
    ;; DO NOT MODIFY

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    leave
    ret
    
    ;; DO NOT MODIFY

; int check_column(char* sudoku, int column);
check_column:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    push ebx
    push ecx
    push edx
    push esi
    push edi

    mov     esi, [ebp + 8]  ; char* sudoku, pointer to 81-long char array
    mov     edx, [ebp + 12]  ; int column 
    ;; DO NOT MODIFY
   
    ;; Freestyle starts here

    ; se considera la inceput eax 1
    mov eax, 1

    ; initializarea lui ebx contor pentru linie
    xor ebx, ebx

verif_col:
    ; verificare daca am ajuns la finalul vectorului
    cmp ebx, 9
    je prep_reset_col

    ; calcularea contorului pentru 
    ; linie: ebx * 9
    mov ecx, ebx
    imul ecx, ecx, 9

    ; la contor se adauga contorul de coloana
    add ecx, edx

    push eax
    ; mutarea in al a elementului
    mov al, [esi + ecx]

    ; verificarea daca elementul este cifra valida (1=9)
    cmp al, 1
    jl wrong_col

    cmp al, 9
    jg wrong_col

    ; verificare daca cifra a mai aparut pe coloana
    mov cl, [frecv + eax]
    cmp cl, 1
    je wrong_col

    ; actualizarea frecventei pentru cifra gasita
    mov byte[frecv + eax], 1
    pop eax
    inc ebx
    jmp verif_col

; resetarea lui eax pt conditii gresite
wrong_col:
    pop eax
    mov eax, 2

; pregatirea pt resetarea vectorului de frecventa
prep_reset_col:
    xor ecx, ecx

reset_frecv_col:
    ; resetarea la 0 a frecventei
    mov byte[frecv + ecx], 0
    inc ecx

    ; verificare daca am ajuns la finalul vectorului
    cmp ecx, 10
    jl reset_frecv_col

    ;; MAKE SURE TO LEAVE YOUR RESULT IN EAX BY THE END OF THE FUNCTION
    ;; Remember: OK = 1, NOT_OKAY = 2
    ;; ex. if this column is okay, by this point eax should contain the value 1 

    ;; Freestyle ends here
end_check_column:
    ;; DO NOT MODIFY

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    leave
    ret
    
    ;; DO NOT MODIFY


; int check_box(char* sudoku, int box);
check_box:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    push ebx
    push ecx
    push edx
    push esi
    push edi

    mov     esi, [ebp + 8]  ; char* sudoku, pointer to 81-long char array
    mov     edx, [ebp + 12]  ; int box 
    ;; DO NOT MODIFY
   
    ;; Freestyle starts here

    ; se calculeaza contoarele de linie
    ; si coloana dupa formulele
    ; linie = edx / 3 * 3
    ; col = edx % 3 * 3

    mov eax, edx
    mov ecx, 3
    xor edx, edx
    div ecx

    mov ebx, eax
    mov ecx, edx

    ; ebx contor de linie de unde incepe boxul
    ; ecx contor de coloana de unde incepe boxul
    imul ebx, ebx, 3
    imul ecx, ecx, 3

    mov eax, 1; se considera eax 1

    ; contor care verifica parcurgerea a 9 elemente
    xor edx, edx

    ; edi va retine coloana de la care
    ; incepe boxul
    mov edi, ecx

verif_box:
    ; verificare daca am ajuns la finalul vectorului
    cmp edx, 9
    je prep_reset_box

    ; calcularea indexului dupa formula
    ; ebx * 9 + ecx
    push edi
    mov edi, ebx
    imul edi, edi, 9
    add edi, ecx

    push eax
    ; mutarea in al a elementului
    push edx
    mov al, [esi + edi]

    ; verificare daca al este cifra valida (1-9)
    cmp al, 1
    jl wrong_box

    cmp al, 9
    jg wrong_box

    ; verificare daca cifra a mai aparut in box
    mov dl, [frecv + eax]
    cmp dl, 1
    je wrong_box

    ; actualizares frecventei pentru cifra gasita
    mov byte[frecv + eax], 1

    ; recalcularea contorului de coloana
    inc ecx

    xor edx, edx
    mov eax, ecx

    push ebx
    mov ebx, 3
    div ebx

    ; verificare daca coloana iese din box
    test edx, edx
    jz increm_lin

    ; restaurarea stivei
    pop ebx
    pop edx
    pop eax
    pop edi

    inc edx
    jmp verif_box

; trecerea la urmatoare linie din box
increm_lin:
    ; restaurarea stivei
    pop ebx
    pop edx
    pop eax
    pop edi

    ; incrementarea si resetarea contorilor
    inc ebx
    inc edx
    mov ecx, edi
    
    jmp verif_box

; resetarea lui eax pt conditii gresite
wrong_box:
    pop edx
    pop eax
    pop edi
    
    mov eax, 2

; pregatirea pt resetarea vectorului de frecventa
prep_reset_box:
    xor ecx, ecx

reset_frecv_box:
    ; resetarea la 0 a frecventei
    mov byte[frecv + ecx], 0
    inc ecx

    ; verificare daca am ajuns la finalul vectorului
    cmp ecx, 10
    jl reset_frecv_box

    ;; MAKE SURE TO LEAVE YOUR RESULT IN EAX BY THE END OF THE FUNCTION
    ;; Remember: OK = 1, NOT_OKAY = 2
    ;; ex. if this box is okay, by this point eax should contain the value 1 

    ;; Freestyle ends here
end_check_box:
    ;; DO NOT MODIFY

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    leave
    ret
    
    ;; DO NOT MODIFY
