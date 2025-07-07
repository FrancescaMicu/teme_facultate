Micu Francesca-Maria 313CB
Tema 3 - PCLP2
Punctaj local: 100

Descrierea implemetarii temei:

Task 1:
parcurgere_lista:
Reprezinta bucla principala care parcurge lista. Verifica daca s-a ajuns la finalul array-ului si cauta nodul cap de lista (cel cu valoarea 1).

inceput_lista:
Se executa cand este gasit nodul de inceput de lista. Salveaza adresa acestui nod in registrul eax, care va fi valoarea returnata de functie.

determin_next:
Initializeaza registrul edx pentru cautare si determina valoarea nodului care ar trebui sa urmeze dupa cel curent (valoarea curenta + 1).

caut_next:
Bucla care cauta in lista nodul cu valoarea urmatoare determinata anterior. Compara valoarea cautata cu valorile celorlalte noduri pana cand gaseste nodul cautat.

gasit_next:
Actualizeaza campul "next" al nodului curent pentru a indica adresa nodului gasit, stabilind astfel legatura in lista inlantuita.

final:
Restaureaza cadrul de stiva si returneaza adresa nodului cap de lista.


Task 2:
Functia cmp_sort:
cmp_sort:
Este folosita ca parametru in apelul qsort. Primeste doua cuvinte, calculeaza lungimea fiecaruia si le compara mai intai dupa lungime, iar apoi lexicografic daca lungimile sunt egale.

ret_1: 
Se executa cand primul cuvant este mai lung decat al doilea. Seteaza valoarea lui eax la 1, indicand ca primul element trebuie sa fie inaintea celui de al doilea in vectorul sortat.

verif_lexic:
Se executa cand cele doua cuvinte au aceeasi lungime. Apeleaza functia strcmp pentru a compara cuvintele lexicografic, rezultatul fiind returnat direct in eax.

final:
Restaureaza valorile registrelor salvate initial si pregateste returnarea din functie.


Functia sort:
sort:
Extrage parametrii primit din stiva, pregateste parametrii pentru qsort si apoi face apelul efectiv pentru compararea vectorului de cuvinte, folosund functia definita mai sus cmp_sort.


Functia get_words:
get_words:
Extrage primul cuvant din textul primit ca parametru, folosindu-se de variabila delimitatori (definita in data si care contine caracterele care separa cuvintele) si il salveaza in vectorul de cuvinte.

obtinere_cuv:
Se cauta cele number_of_words cuvinte printr-o bucla si pentru fiecare iteratie, apeleaza strtok cu NULL pentru a obtine urmatorul cuvant, il salveaza in vectorul de cuvinte.


Task 3:
kfib: 
Se compara valorile parametrilor n si K pentru a determina cazul de calcul necesar.

caz_mai_mic:
Se executa cand n este mai mic decat K si seteaza rezultatul la 0, conform sectiunii teoretice din cerinta.

caz_egal:
Se executa cand n este egal cu K si seteaza rezultatul la 1, conform definitiei.

caz_mai_mare:
Trateaza ultimul caz si initializeaza suma si indexul pentru calculul recursiv al celor n - index termeni din kfib care alcatuiesc rezultatul final.

det_kfib:
Pentru fiecare iteratie a buclei se calculeaza termenul (n - index) din secventa prin apeluri recursive, apoi urmand a fi adaugat la suma totala.

final:
Restaureaza valorile registrelor salvate initial si returneaza rezultatul calculat, care reprezinta al n-lea termen din secventa KFib.


Task 4:

Subtask 1:
check_palindrome: Initializeaza indexul pentru parcurgerea sirului si calculeaza jumatatea lungimii sirului pentru a sti cand sa opreasca verificarea.

parcurgere_caract: Pentru fiecare iteratie, compara un caracter de la inceputul sirului cu caracterul corespunzator de la sfarsitul sirului, al carei pozitie in sir este obtinuta prin forumla (len - 1 - index).

nu_palind: Se executa cand se gasesc doua caractere complementare care nu sunt identice, indicand ca sirul nu este palindrom si seteaza registrul de retur (eax) la 0.

final_palind: Restaureaza registrele salvate si returneaza rezultatul obtinut.


Subtask 2:
Functia composite_palindrom
composite_palindrome:
Se aloca un buffer temporar pe stiva pentru construirea sirurilor concatenate (cu dimensiunea n * 11=10 caractere + 1 terminator). Se initializeaza variabilele declarate in section .data, respectiv sir_max (care va retine cel mai bun palindrom gasit) si max_len (lungimea acestuia). Apoi apeleaza functia de backtracking care va explora toate combinatiile posibile de cuvinte (reprezentand toate submultimile care se formeaza cu n cuvinte), incepand cu indexul 0 si sirul gol. La final, se aloca memorie pe heap pentru rezultat (cu max_len + 1), copiaza palindromul maxim gasit si il returneaza.


Functia caut_palind_max:
Implementeaza algoritmul de backtracking care genereaza toate combinatiile posibile de cuvinte din vectorul de cuvinte. Functia primeste sase parametri: vectorul de cuvinte, sirul curent format, lungimea sirului curent, indexul curent in vector, sirul maxim gasit pana acum si lungimea acestui sir. Pentru fiecare pozitie din vector, functia face doua apeluri recursive: una in care include cuvantul curent in combinatie si alta in care il exclude.

caut_palind_max: La inceput, se verifica daca sirul curent e gol in caz afirmativ sarind la labelul de verificare finala. Altfel, se verifica daca sirul curent este palindrom, caz in care il compara cu cel mai bun palindrom gasit anterior. Daca sirurile au aceeasi lungime sare la labelul de verificare lexicografica a celor doua siruri, daca e mai mare sirul curent se actualizeaza maximul in nou_max, altfel sare la verif_final.

verif_lexic: Functia strcmp este folosita pentru a compara lexicografic cele doua siruri. Daca noul palindrom este lexicografic mai mic, se actualizeaza sir_max sarind la nou_max.

nou_max: Actualizeaza sirul maxim si lungimea sa atunci cand se gaseste un palindrom mai bun. Foloseste functia strcpy pentru a copia noul palindrom in variabila sir_max.

verif_final: Se verifica daca algoritmul a ajuns la finalul vectorului de cuvinte, caz in care se iese din acel apel de recursie.

adaug_cuv_sir: Concateneaza un nou cuvant la sirul curent folosind functia strcat si apoi determina noua lungime a sirului rezultat cu strlen.

apel_fct: Se fac cele doua apeluri recursive specifice backtrackingului. Intre cele doua apeluri, functia sterge cuvantul adaugat. punand un terminator NULL la pozitia corespunzatoare (salvata intr un push anterior al lui ebx), pentru a reveni la starea anterioara si a concatena urmatorul cuvant.

final_fct: Restaureaza registrele salvate


