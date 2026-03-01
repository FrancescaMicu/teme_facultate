**Bonus - Funcționalitate pentru semnalarea întrebărilor greșite în timpul examenului**

Am propus implementarea unei funcționalități inspirate din platformele educaționale precum Moodle, care permite studenților să semnaleze ("flag") în timp real întrebările considerate de ei greșite.
De asemenea, aplicația permite autorului să corecteze întrebarea și să actualizeze punctajele studenților care au avut în examen întrebarea greșită.

*În CLASA Question<T>:*
- Se adaugă câmpul private String isFlagged
  - Dacă isFlagged este null, întrebarea nu a fost marcată drept greșită de către studenți
  - Altfel, cel puțin un student a considerat ceva greșit la întrebare și poate scrie un mesaj în care să descrie ce crede că este greșit
- Se adaugă următoarea metodă:
  - flagQuestion(String message): Setează câmpul isFlagged cu mesajul de flag dat de student
   - Dacă isFlagged nu este null (un alt student a mai trimis deja un mesaj referitor la întrebarea respectivă și autorul nu a modificat întrebarea), se concatenează la câmp noul mesaj, separat printr-un caracter de linie nouă (\n)

*În CLASA Platform:*
- Se adaugă următoarea colecție pentru a putea fi anunțați autorii când una dintre întrebările lor a fost semnalată drept greșită:
  - HashSet<String> questAuthors: am ales să folosesc HashSet deoarece am presupus că autorii sunt unici după nume și prioritatea este ca autorii să fie găsiți și anunțați cât mai rapid, operațiile de adăugare și verificare a existenței la HashSet fiind cele mai eficiente în acest caz
- Este adăugată comanda flag_question (care va fi prelucrată în interpretCommands) împreună cu metoda flagQuestion() în care se întâmplă următoarele:
  - Comanda va respecta formatul flag_question | <timestamp> | <nume_examen> | <text_intrebare> | <mesaj_cu_motivul> 
  - Este identificată întrebarea (din colecțiile de întrebări din clasa Exam) după textul întrebării primite în comandă
  - Se apelează metoda flagQuestion(mesaj_cu_motivul) pe obiectul întrebării găsite
  - Se caută autorul în colecția de autori și îl "alertează", scriind într-un fișier (console.out) un mesaj corespunzător semnalării (flagging-ului) unei întrebări care o să conțină toate mesajele date de studenți la întrebarea respectivă
- Este adăugată comanda solve_flagged_question (care va fi prelucrată în interpretCommands) împreună cu metoda solveFlaggedQuestion() în care se întâmplă următoarele:
  - Comanda va respecta formatul solve_flagged_question | <timestamp> | <nume_examen> | <text_intrebare_veche> | <text_intrebare_noua> | <raspuns_corect>
  - Este căutată întrebarea după textul întrebării vechi și se actualizează textul acesteia cu noul text împreună cu varianta de răspuns (se modifică acestea indiferent dacă sunt diferite de cele inițiale sau nu, cu valorile din comandă) în ambele colecții de întrebări din Exam
  - Pentru că întrebările din questionsSortByDiff sunt sortate secundar după textul întrebării, pentru a păstra ordinea impusă de comparatorul colecției, prima dată trebuie ștearsă vechea întrebare și instanțiată o nouă întrebare cu noile valori și readăugată în colecție
  - Este resetat flag-ul întrebării (setat înapoi la null) și punctajul studenților care au avut întrebarea respectivă la examen este setat la maxim
  - Se scrie într-un fișier (console.out) un mesaj corespunzător rezolvării întrebării greșite și actualizării notelor