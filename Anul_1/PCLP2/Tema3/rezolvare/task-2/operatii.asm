section .data
    ; 10 -> codul ASCII pentru newline
    delimitator db " ,.", 10, 0

section .text
global sort
global get_words
global cmp_sort
extern strtok
extern strlen
extern strcmp
extern qsort

; functie pentru compararea lexicografica a doua cuvinte
cmp_sort:
    ; create a new stack frame
    push ebp
    mov ebp, esp

    ; salvarea pe stiva a registrelor folosite
    push ebx
    push ecx
    push edx
    push esi
    push edi

    ; 8 -> offsetul unde e salvat primul cuvant
    mov esi, [ebp + 8]
    ; 12 -> offsetul unde e salvat al doilea cuvant
    mov edi, [ebp + 12]

    ; salvarea pe stiva a registrelor folosite
    push esi
    push edi

    ; determinarea lungimii primului cuvant
    push dword[esi]
    call strlen
    ; 4 -> offsetul pentru curatarea stivei dupa apel
    add esp, 4
    mov ebx, eax

    ; recuperarea registrelor
    pop edi
    pop esi

    ; salvarea pe stiva a registrelor folosite
    push ebx
    push esi
    push edi

    ; determinarea lungimii celui de al doilea cuvant
    push dword[edi]
    call strlen
    ; 4 -> offsetul pentru curatarea stivei dupa apel
    add esp, 4
    mov edx, eax

    ; recuperarea registrelor
    pop edi
    pop esi
    pop ebx

    ; compararea lungimii cuvintelor
    cmp ebx, edx
    je verif_lexic
    jg ret_1

    ; actualizarea lui eax pentru -1
    ; -1 -> caz de returnare daca primul cuvant e mai mic decat al doilea
    mov eax, -1
    jmp final

ret_1:
    ; actualizarea lui eax cu 1
    ; 1 -> caz de returnare daca primul cuvant e mai mare decat al doilea
    mov eax, 1
    jmp final

verif_lexic:
    ; compararea cuvintelor 
    push dword[edi]
    push dword[esi]
    call strcmp
    ; 8 -> offsetul pentru curatarea stivei dupa apel
    add esp, 8

final:
    ; restaurarea registrlor
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx

    mov esp, ebp
    pop ebp
    ret

;; sort(char **words, int number_of_words, int size)
;  functia va trebui sa apeleze qsort pentru soratrea cuvintelor 
;  dupa lungime si apoi lexicografix
sort:
    ; create a new stack frame
    push ebp
    mov ebp, esp

    ; 8 -> offsetul unde e salvat parametrul words
    mov edi, [ebp + 8]
    ; 12 -> offsetul unde e salvat parametrul number_of_words
    mov ebx, [ebp + 12]
    ; 16 -> offsetul unde e salvat parametrul size
    mov edx, [ebp + 16]

    ; apelarea functiei qsort
    push cmp_sort
    push edx
    push ebx
    push edi
    call qsort
    ; 16 -> offsetul pentru curatarea stivei dupa apel
    add esp, 16

    mov esp, ebp
    pop ebp 
    ret

;; get_words(char *s, char **words, int number_of_words)
;  separa stringul s in cuvinte si salveaza cuvintele in words
;  number_of_words reprezinta numarul de cuvinte
get_words:
    ; create a new stack frame
    push ebp
    mov ebp, esp

    ; 8 -> offsetul unde e salvat parametrul s
    mov edi, [ebp + 8]
    ; 12 -> offsetul unde e salvat parametrul words
    mov esi, [ebp + 12]
    ; 16 -> offsetul unde e salvat parametrul number_of_words
    mov ebx, [ebp + 16]

    ; obtinerea primului cuvant din text
    push delimitator
    push edi
    call strtok
    ; 8 -> offsetul pentru curatarea stivei dupa apel
    add esp, 8

    ; initializarea indexului pentru parcurgerea vectorului
    xor ecx, ecx

    ; salvarea primului cuvant in vector
    ; 4 -> dimensiunea unui pointer pentru a vectorul de cuvinte
    mov [esi + 4 * ecx], eax
    inc ecx

obtinere_cuv:
    ; salvarea pe stiva a registrelor folosite
    push ebx
    push ecx
    push esi
    push edi

    ; obtinerea urmatorului cuvant din text
    push delimitator
    ; 0 -> echivalent cu parametrul NULL pentru strtok
    push 0
    call strtok
    ; 8 -> offsetul pentru cei 2 parametrii ai functiei apelate
    add esp, 8

    ; recuperarea registrelor
    pop edi
    pop esi
    pop ecx
    pop ebx

    ; salvarea cuvantului obtinut in vector
    ; 4 -> dimensiunea unui pointer pentru a vectorul de cuvinte
    mov [esi + 4 * ecx], eax

    ; verificare daca s-au obtinut toate cuvintele
    inc ecx
    cmp ecx, ebx
    jl obtinere_cuv

    mov esp, ebp
    pop ebp
    ret

