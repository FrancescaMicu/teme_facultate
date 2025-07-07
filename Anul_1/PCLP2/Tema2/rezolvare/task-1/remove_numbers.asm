%include "../include/io.mac"

extern printf
global remove_numbers

section .data
	fmt db "%d", 10, 0

section .text

; function signature: 
; void remove_numbers(int *a, int n, int *target, int *ptr_len);

remove_numbers:
	;; DO NOT MODIFY
	push    ebp
	mov     ebp, esp
	pusha

	mov     esi, [ebp + 8] ; source array
	mov     ebx, [ebp + 12] ; n
	mov     edi, [ebp + 16] ; dest array
	mov     edx, [ebp + 20] ; pointer to dest length

	;; DO NOT MODIFY
   

	;; Your code starts here

	; golire/initializare registre
	xor ecx, ecx
	mov dword [edx], 0

; parcurgerea vectorului initial
iter_arr:
	; verificare daca am ajuns la finalul vectorului
	cmp ecx, ebx
	je end
	mov eax, [esi + 4 * ecx]

	; verificare numar impar
	test eax, 1
	jz add_arr
	
	inc ecx
	jmp iter_arr

; adaugarea in vectorul nou
add_arr:
	push ebx
	mov ebx, eax
	dec ebx

	; verificare daca elementul e putere de 2
	test eax, ebx
	jz is_2_pow
	mov ebx, [edx]

	; adaugarea in noul vector
	mov [edi + ebx * 4], eax
	inc ebx
	mov [edx], ebx
	pop ebx

	inc ecx
	jmp iter_arr
	
; intoarcerea la vectorul initial
is_2_pow:
	pop ebx
	inc ecx
	jmp iter_arr

; sfarsitul codului
end:
	
	;; Your code ends here
	

	;; DO NOT MODIFY

	popa
	leave
	ret
	
	;; DO NOT MODIFY
