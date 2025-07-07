section .text
global kfib

kfib:
    ; create a new stack frame
    push ebp
    mov ebp, esp

    ; 8 -> offsetul unde e salvat parametrul n
    mov ebx, [ebp + 8]
    ; 12 -> offsetul unde e salvat parametrul K
    mov edx, [ebp + 12]

    ; compararea lui n si K
    cmp ebx, edx
    jl caz_mai_mic
    je caz_egal
    jmp caz_mai_mare

caz_mai_mic:
    ; returneaza 0 pentru cazul in care n e mai mic decat K
    xor eax, eax
    jmp final

caz_egal:
    ; returneaza 1 pentru cazul de egalitate
    ; 1 -> valoarea de retur pentru cazul de egalitate
    mov eax, 1
    jmp final

caz_mai_mare:
    ; initializarea sumei pentru kfib
    xor edi, edi
    ; 1 -> indexul de start in parcurgerea termenilor kfib
    mov ecx, 1

det_kfib:
    ; calcularea n - index
    mov esi, ebx
    sub esi, ecx

    ; salvarea registrelor pe stiva
    push ebx
    push ecx
    push edi

    ; apelul recursiv pentru kfib anterior
    push edx
    push esi
    call kfib
    ; 8 -> offsetul pentru curatarea stivei dupa apel
    add esp, 8

    ; restaurarea registrelor
    pop edi
    pop ecx
    pop ebx

    ; adaugarea noului element kfib determinat la suma
    add edi, eax

    ; verificarea daca s-au adunat cei n - index termeni
    inc ecx
    cmp ecx, edx
    jle det_kfib

    ; mutarea sumei in registrul de retur
    mov eax, edi

final:
    mov esp, ebp
    pop ebp
    ret