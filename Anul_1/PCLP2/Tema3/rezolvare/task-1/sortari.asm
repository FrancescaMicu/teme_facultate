section .text
global sort

;   struct node {
;    int val;
;    struct node* next;
;   };

;; struct node* sort(int n, struct node* node);
;   The function will link the nodes in the array
;   in ascending order and will return the address
;   of the new found head of the list
; @params:
;   n -> the number of nodes in the array
;   node -> a pointer to the beginning in the array
;   @returns:
;   the address of the head of the sorted list
sort:
    ; create a new stack frame
    push ebp
    mov ebp, esp

    ; 8 -> offsetul unde e salvat parametrul n
    mov ebx, [ebp + 8]
    ; 12 -> offsetul unde e salvat parametrul node
    mov edi, [ebp + 12]

    ;initializarea indexului de parcurgere
    xor ecx, ecx

parcurgere_lista:
    ; verificare daca s-a ajuns la finalul listei
    cmp ecx, ebx
    jge final

    ; verificare daca s-a gasit capatul de lista
    ; 8 -> dimensiunea totala al unui nod
    ; 1 -> valoarea din primul nod
    cmp dword[edi + 8 * ecx], 1
    je inceput_lista

    jmp determin_next

inceput_lista:
    ; 8 -> dimensiunea totala al unui nod
    lea eax, [edi + 8 * ecx]

determin_next:
    ; initializarea indexului pentru cautarea valorii urmatoare
    xor edx, edx

    ; determinarea elementului care ar trebui sa urmeze dupa cel curent
    ; 8 -> dimensiunea totala al unui nod
    mov esi, [edi + 8 * ecx]
    inc esi

caut_next:
    ; verificare daca s-a gasit elementul cautat
    ; 8 -> dimensiunea totala al unui nod
    cmp esi, [edi + 8 * edx]
    je gasit_next

    ; cautare in continuarea listei
    inc edx
    cmp edx, ebx
    jl caut_next

    ; intoarcerea in parcurgerea initiala
    inc ecx
    jmp parcurgere_lista

gasit_next:
    ; actualizarea campului next cu adresa elementului gasit
    push ebx
    ; 8 -> dimensiunea totala al unui nod
    lea ebx, [edi + 8 * edx] 
    ; 8 -> dimensiunea totala al unui nod
    ; 4 -> offsetul unde se afla campul node
    mov [edi + 8 * ecx + 4], ebx 
    pop ebx

    ; intoarcerea in parcurgerea initiala
    inc ecx
    cmp ecx, ebx
    jl parcurgere_lista

final:
    mov esp, ebp
    pop ebp
    ret