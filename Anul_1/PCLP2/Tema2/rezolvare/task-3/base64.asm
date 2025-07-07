%include "../include/io.mac"

extern printf
global base64

section .data
	alphabet db 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
	fmt db "%d", 10, 0

section .text

base64:
	;; DO NOT MODIFY

    push ebp
    mov ebp, esp
	pusha

	mov esi, [ebp + 8] ; source array
	mov ebx, [ebp + 12] ; n
	mov edi, [ebp + 16] ; dest array
	mov edx, [ebp + 20] ; pointer to dest length

	;; DO NOT MODIFY


	; -- Your code starts here --

	; initializarea contorului
	xor ecx, ecx
	mov dword[edx], 0

; parcurgerea vectorului
iter_arr:
	; verificare daca am ajuns la finalul vectorului
	cmp ecx, ebx
	je end

	; mutarea primului byte in eax
	mov al, byte[esi + ecx]
	inc ecx
	shl eax, 8

	push ebx

	; mutarea celui de al doilea byte in eax
	mov bl, byte[esi + ecx]
	inc ecx
	or eax, ebx
	shl eax, 8

	; mutarea celui de al treilea byte in eax
	mov bl, byte[esi + ecx]
	or eax, ebx

	; initializarea contorului pentru transformare
	mov ebx, 0
	inc ecx

	; salvare pe stiva
	push ecx
	push esi

; efectuarea trasnformarii in base64
transf_base64:

	; calcularea offsetului pentru extragere grupului
	; respectiv de 6 biti cu formula: 18 - ebx * 6
	mov esi, ebx
	imul esi, esi, 6
	mov ecx, 18
	sub ecx, esi

	; pastrarea in esi a exact 6 biti
	mov esi, eax
	shr esi, cl
	and esi, 63
	
	push eax
	push ebx

	; identificarea literei din vectorul alfabet
	; si mutarea in vectorul final
	mov al, byte[alphabet + esi]
	mov ebx, [edx]
	mov byte[edi + ebx], al

	pop ebx
	pop eax

	; incrementarea lungimii vectorului final
	mov ecx, [edx]
	inc ecx
	mov [edx], ecx

	; verificare daca am transformat cele 4 grupuri
	inc ebx
	cmp ebx, 4
	jl transf_base64

	; restaurarea stivei
	pop esi
	pop ecx
	pop ebx

	jmp iter_arr

; sfarsitul codului
end:
	
	; -- Your code ends here --


	;; DO NOT MODIFY

	popa
	leave
	ret

	;; DO NOT MODIFY