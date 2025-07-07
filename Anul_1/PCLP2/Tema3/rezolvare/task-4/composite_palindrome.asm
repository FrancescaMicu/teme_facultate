section .data
    ; 0 -> initializarea cu 0 a numarului
    nr_cuv dd 0
    ; 0 -> initializarea cu 0 a sirului
    sir_max times 165 db 0
    ; 0 -> initializarea cu 0 a numarului
    max_len dd 0
    ; 0 -> initializarea cu 0 a numarului
    rez_palindrom dd 0
    ; 0 -> initializarea cu 0 a numarului
    rez_strcmp dd 0
section .text
global check_palindrome
global composite_palindrome
global caut_palind_max
extern malloc
extern strcat
extern strcmp
extern strlen
extern strcpy

check_palindrome:
    ; create a new stack frame
    push ebp
    mov ebp, esp

    ; salvarea registrelor pe stiva
    push ebx
    push ecx
    push edx
    push esi

    ; 8 -> offsetul unde e salvat parametrul str
    mov edi, [ebp + 8]
    ; 8 -> offsetul unde e salvat parametrul len
    mov ebx, [ebp + 12] 

    ; initializarea indexului de parcurgere a sirului de caractere
    xor ecx, ecx
    ; calcularea jumatatii lungimii
    mov esi, ebx
    ; 1 -> valoare folosita pentru impartirea la 2
    ; impartirea la 2 se realizeaza prin shiftarea la dreapta cu 1
    shr esi, 1
    dec ebx

parcurgere_caract:
    ; verificarea caracterelor de la pozitii complementare in sir
    mov dl, byte[edi + ecx]
    ; determinarea pozitiei caracterului complementar
    mov eax, ebx
    sub eax, ecx
    cmp dl, byte[edi + eax]
    jne nu_palind

    ; verificare daca s-a parcurs sirul
    inc ecx
    cmp ecx, esi
    jl parcurgere_caract

    ; actualizarea lui eax cu 1 daca e palindrom
    ; 1 -> valoare de retur daca sirul e palindrom
    mov eax, 1
    jmp final_palind

nu_palind:
    ; actualizarea lui eax cu 0 daca nu e palindrom
    xor eax, eax

final_palind:
    ;restaurarea registrelor folosite
    pop esi
    pop edx
    pop ecx
    pop ebx

    mov esp, ebp
    pop ebp
    ret

caut_palind_max:
    push ebp
    mov ebp, esp

    ; 8 -> offsetul unde e salvat parametrul lungimii sirului palindrom maxim lexicografic
    mov eax, [ebp + 8]
    ; 12 -> offsetul unde e salvat parametrul pentru sirul palindrom maxim lexicografic
    mov esi, [ebp + 12]
    ; 16 -> offsetul unde e salvat parametrul indexul vectorului
    mov ecx, [ebp + 16]
    ; 20 -> offsetul unde e salvat parametrul lungimea sirului curent concatenat
    mov ebx, [ebp + 20]
    ; 24 -> offsetul unde e salvat parametrul sirul curent concatenat
    mov edx, [ebp + 24]
    ; 28 -> offsetul unde e salvat parametrul vectorul de cuvinte strs
    mov edi, [ebp + 28]

    ; verificare daca sirul curent concatenat este gol
    ; 0 -> valoare care verifica daca sirul nu contine cuvinte
    cmp ebx, 0
    je verif_final

    ; apelarea functiei de verificare palindrom pentru sirul curent concatenat
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi

    push ebx
    push edx
    call check_palindrome
    ; 8 -> offsetul pentru curatarea stivei dupa apel
    add esp, 8

    ; retinerea rezultatului intr-o variabila
    mov dword[rez_palindrom], eax

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ; daca nu e palindrom se duce la verificarea finala
    ; 0 -> valoare intoarsa din functie pentru un sir care nu e palindrom
    cmp dword[rez_palindrom], 0
    je verif_final

    ; verificarea daca s-a gasit un palindrom mai bun fata de sir max
    cmp ebx, dword[max_len]
    jg nou_max
    je verif_lexic

    ; sare la verificarea finala daca sirul curent nu e un nou sir_max
    jmp verif_final

verif_lexic:
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi

    ; apelarea functiei strcmp pentru sirul curent si sir_max
    push sir_max
    push edx
    call strcmp
    ; 8 -> offsetul pentru curatarea stivei dupa apel
    add esp, 8

    ; retinerea rezultatului intr-o variabila
    mov dword[rez_strcmp], eax

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ; verificare daca sirul nou e mai bun lexicografic fata de sir_max
    ; 0 -> valoarea returnata de strcmp daca cele doua siruri sunt egale
    cmp dword[rez_strcmp], 0
    jl nou_max

    jmp verif_final

nou_max:
    push eax
    push ebx
    push ecx
    push edx
    push edi
    push esi

    ; actualizarea lui sir_max cu noul sir gasit
    push edx
    push sir_max
    call strcpy
    ; 8 -> offsetul pentru curatarea stivei dupa apel
    add esp, 8

    pop esi
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ;actualizare lungimii maxime a sirului
    mov eax, ebx
    mov dword[max_len], eax

verif_final:
    ; verificare daca s-au parcurs toate cuvintele din vector
    cmp ecx, dword[nr_cuv]
    jge final_fct

adaug_cuv_sir:
    ; pastrarea pozitiei ultimului cuvint adaugat
    push ebx

    ; adaugarea unui nou cuvant in sirul curent concatenat
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi

    ; apelarea functiei strcat
    ; 4 -> dimensiunea unui pointer pentru a vectorul de cuvinte
    push dword[edi + 4 * ecx]
    push edx
    call strcat
    ; 8 -> offsetul pentru curatarea stivei dupa apel
    add esp, 8

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ; determinarea lungimii noului sir
    push eax
    push ecx
    push edx
    push esi
    push edi

    ; apelarea functiei strlen
    push edx
    call strlen
    ; 4 -> offsetul pentru curatarea stivei dupa apel
    add esp, 4

    ; actualizarea lungimii
    mov ebx, eax

    pop edi
    pop esi
    pop edx
    pop ecx
    pop eax

apel_fct:
    ; salvarea pe stiva a registrelor
    push eax
    push ebx
    push ecx
    push edx
    push edi
    push esi

    ; incrementarea indexului de vector
    inc ecx

    ; apelarea functiei cu noul cuvant adaugat
    push edi
    push edx
    push ebx
    push ecx
    push sir_max
    push dword[max_len]
    call caut_palind_max
    ; 24 -> offsetul pentru curatarea stivei dupa apel
    add esp, 24

    ; restaurarea stivei
    pop esi
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ; stergerea cuvantul nou adaugat
    pop ebx
    ; 0 -> are rol de terminator NULL
    mov byte[edx + ebx], 0

    ; salvarea pe stiva a registrelor
    push eax
    push ebx
    push ecx
    push edx
    push edi
    push esi

    ; incrementarea indexului
    inc ecx

    ; apelarea functiei fara noul cuvant adaugat
    push edi
    push edx
    push ebx
    push ecx
    push sir_max
    push dword[max_len]
    call caut_palind_max
    ; 24 -> offsetul pentru curatarea stivei dupa apel
    add esp, 24

    ; restaurarea stivei
    pop esi
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax

final_fct:
    mov esp, ebp
    pop ebp
    ret

composite_palindrome:
    push ebp
    mov ebp, esp

    ; 8 -> offsetul unde e salvat parametrul strs
    mov edi, [ebp + 8]
    ; 12 -> offsetul unde e salvat parametrul n
    mov ebx, [ebp + 12]

    ; salvarea numarului de cuvinte n intr-o variabila
    mov dword[nr_cuv], ebx

    ; alocare pe stiva a registrului care va contine sirul curent
    ; 11 -> numarul maxim de litere dintr-un cuvant (10) + 1 (null)
    imul ebx, ebx, 11
    sub esp, ebx
    mov edx, esp
    ; 0 -> are rol de terminator NULL
    mov byte [edx], 0
    push ebx

    ; initializarea lungimii maxime a palindromului
    ; 0 -> valoare initiala pt lungime maxima
    mov dword[max_len], 0


    push edi
    push edx
    ; 0 -> lungimea curenta a sirului
    push 0
    ; 0 -> indexul initial de parcurgere a vectorului
    push 0
    push sir_max
    push dword[max_len]
    call caut_palind_max
    ; 24 -> offsetul pentru curatarea stivei dupa apel
    add esp, 24

    ; resetarea stivei dupa alocare
    pop ebx
    add esp, ebx

    ; incrementarea lungimii pentru null terminator
    inc dword[max_len]
    ; alocarea in heap a sirului rezultat
    push dword[max_len]
    call malloc
    ; 4 -> offsetul pentru curatarea stivei dupa apel
    add esp, 4

    ; copierea in eax a sirului maxim rezultat
    push sir_max
    push eax
    call strcpy
    ; 8 -> offsetul pentru curatarea stivei dupa apel
    add esp, 8

    mov esp, ebp
    pop ebp
    ret