IMPLEMENTARE TEMA AA - TEXT EDITOR

In implementarea temei am folosit un Piece Table cu urmatoarele doua structuri:
- typedef struct TPiece: 
	- buffType: indica sursa textului: 0 pentru bufferul original si 1 pentru bufferul de adaugare
	- startIdx: indexul de la care incepe textul in buffer-ul respectiv
	- length: lungimea sirului de caractere specificata de piesa respectiva
- typedef struct TTextEditor:
	- firstBuff: buffer care stocheaza textul initial al fisierului
	- newBuff: buffer in care se scriu toate sirurile de caractere noi adaugate
	- capNewBuff: retine capacitatea de scriere in newBuff
	- idxWrite: retine pozitia curenta de scriere in newBuff
	- allPieces: vectorul (de tip ArrayList) de structuri Piece care retine textul final in ordinea corecta
	- nrPieces: numarul curent de piese din allPieces
	- capNrPieces: capacitatea alocata pentru vectorul de piese
	- cursor: pozitia globala a cursorului in text
	- totalLen: lungimea totala a textului

Pentru gestionarea memoriei, am aplicat conceptul de ArrayList prezentat la curs. Astfel, atunci cand spatiul alocat nu mai este suficient, capacitatea vectorului este dublata.
Aceasta abordare asigura o complexitate amortizata constanta O(1) pentru operatiile de adaugare la final si minimizeaza apelurile costisitoare de realloc (fiind mai dese la inceput si mai rare proportional cu numarul de piese adaugate).

Am implementat urmatoarele functii:
- create_table: Este alocata o variabila de tip TextEditor* si ii sunt initializate campurile. Daca nu sunt furnizate fisiere sau text, se initializeaza buffere goale. Textul initial este pus in firstBuff, iar newBuff este initializat cu o capacitate mica (100). Se creeaza prima piesa care acopera intreg continutul initial
- advance_cursor: Actualizeaza pozitia cursorului cu valoarea primita ca parametru, asigurandu-se ca acesta ramane in limitele valide ale textului (intre 0 si lungimea totala)
- show_global_cursor: Returneaza pozitia curenta a cursorului din text
- add_text: Adauga textul nou in bufferul newBuff, redimensionandu-l daca este cazul. Identifica piesa de la pozitia cursorului si realizeaza inserarea in ArrayListul de piese. Sunt tratate trei cazuri (inserare la inceput, la final sau in interior), folosind memmove pentru shiftarea pieselor pentru eficienta. In cazul inserarii in interior, este folosita logica de split-uire a pieselor: piesa curenta este taiata in doua (partea stanga si partea dreapta), iar noua piesa este inserata intre ele, crescand numarul total de piese
- delete_text: Reconstruieste vectorul de piese intr-un nou array, alegand doar piesele care trebuie pastrate, pastrand capacitatea curenta. Piesele care nu sunt afectate sunt copiate direct, iar cele care se intersecteaza cu zona stearsa sunt split-uite (la stanga sau dreapta) si adaugate in noul vector. Se verifica capacitatea la inceputul operatiei de split, evitand realocarile multiple
- extract_current_text: Construieste textul final intr-un singur sir de caractere. Se parcurge vectorul de piese si se copiaza textele corespunzatoare din bufferul original sau din buffType, concatenandu-le in ordinea corecta
- save_current_text: Salveaza starea curenta a editorului. Este actualizat pointerul cursorului, se scrie textul reconstruit (cu ajutorul functiei anterioare) in fisierul specificat si este salvat in variabila text primita ca parametru

Complexitatea operatiilor:
- create_table: Presupune citirea din fisier a textului avand astfel complexitate O(n), unde n este lungimea totala a textului (numarul total de caractere)
- advance_cursor: Are complexitate O(1), folosindu-se de campul cursor din structura
- show_global_cursor: Are complexitate O(1), returnand campul cursor definit in structura
- add_text: Gasirea piesei curente si operatiile de shiftare au toate cost O(numarul de piese)
- delete_text: Presupune o singura parcurgere a pieselor, avand astfel complexitate O(numarul de piese)
- extract_current_text: Are complexitate O(n), presupunand reconstruirea caracter cu caracter a textului
- save_current_text: Apeleaza functia extract_current_text(), avand astfel complexitate O(n)

Probleme intampinate:
- delete_text: A trebuit sa regandesc strategia de realocare a memoriei pentru a creste eficienta. Initial, implementarea folosea realloc in mod repetat, insa varianta finala se bazeaza pe o singura verificare a capacitatii la inceputul cazului de split, reducand astfel numarul de apeluri costisitoare
- add_text: Calcularea corecta a indecsilor startIdx si length pentru cazurile de split a pieselor a necesitat o atentie sporita. De asemenea, utilizarea functiei memmove a fost esentiala pentru a asigura shiftarea corecta si rapida a pieselor