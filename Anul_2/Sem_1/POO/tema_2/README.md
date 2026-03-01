**IMPLEMENTAREA TEMEI 2 POO-2-CB**

Pentru rezolvarea acestei teme, am definit în directorul org.example următoarele:
- clasa Main care conține metoda main()
- clasa Platform care gestionează entitățile principale
- clasa Exam
- clasa Student
- clasa abstractă generică Question<T> (implementează interfețele Gradable și Comparable) care este extinsă de:
 - clasa OpenEndedQuestion
 - clasa FillInTheBlankQuestion 
 - clasa MultipleChoiceQuestion
- clasa de excepție SubmissionOutsideTimeIntervalException
- interfața Gradable
- enum-ul Correctness
- enum-ul ResponseOption

*CLASA Main:*
- Are definită metoda:
 - main(String[] args): gestionează deschiderea fișierului de input primit ca argument, instanțiază obiectul de tip Platform, citește fișierul linie cu linie și apelează metoda interpretCommands din platformă pentru fiecare linie/comandă citită

*CLASA Platform:*
- Sunt definite câmpurile private exams și students de tip HashMap
- Am folosit HashMap-uri pentru examene și studenți deoarece operațiunile critice implică accesarea frecventă a acestora după nume (cheie unică). HashMap oferă o complexitate de O(1) la operațiile de inserare și căutare, fiind mult mai eficient decât parcurgerea unei liste
- Este definit constructorul care inițializează cele două HashMap-uri
- Sunt definite metodele:
  - createExam(): instanțiază un nou examen și îl adaugă în map-ul de examene
  - addQuestion(): determină tipul întrebării (open_ended, fill_in_the_blank, multiple_choice), instanțiază obiectul corespunzător și îl adaugă în examenul specificat.
  - listHistoryQuestion(): apelează metoda de afișare după dată (timestamp) din clasa Exam
  - printExam(): apelează metoda de afișare după dificultate din clasa Exam
  - registerStudent(): instanțiază un nou student și îl adaugă în map-ul de studenți
  - submitExam(): preia răspunsurile, apelează metoda de corectare din Exam și tratează excepția SubmissionOutsideTimeIntervalException
  - showStudentScore(): afișează nota unui student la un anumit examen
  - generateReport(): generează raportul cu toți studenții și notele lor
  - interpretCommands(): parsează linia de comandă, convertește parametrii la tipurile corecte (LocalDateTime, int, double) și se asigură că este apelată metoda corespunzătoare comenzii primite

*CLASA Exam:*
- Sunt definite câmpurile pentru detalii examen (timestamp, nume, data de început, data de final) și colecțiile pentru întrebări și studenți
- Este definit constructorul care inițializează TreeSet-urile (unul cu comparator default, celălalt cu comparator explicit) și HashMap-ul
- Colecții:
  - questionsSortByDate: un TreeSet care menține întrebările sortate cronologic (folosind compareTo din Question)
  - questionsSortByDiff: un TreeSet care menține întrebările sortate după dificultate (folosind QuestionComparator)
    - Am folosit TreeSet-uri deoarece operațiunile de adăugare și afișare pot fi intercalate, și așa se pot ține întrebările sortate automat la inserare (O(log N)). Astfel, se elimină necesitatea sortării integrale a listei la fiecare comandă de afișare, optimizând timpul de execuție 
  - students: un HashMap ce mapează obiectul Student la nota obținută
    - Am folosit HashMap pentru rapiditatea accesului (O(1)) necesară la validarea și înregistrarea notelor în momentul submisiei examenului
- Sunt definite metodele:
  - addQuestion(): adaugă întrebarea în ambele TreeSet-uri pentru a menține sortările active
  - printQuestionsAfterTimestamp(): iterează prin questionsSortByDate și scrie întrebările (ordonate cronologic) în fișierul de istoric
  - printQuestionsAfterDifficulty(): iterează prin questionsSortByDiff și scrie întrebările (ordonate după dificultate) în fișierul de printare a examenului
  - printResultsAnytime(): creează o listă de studenți din cheile map-ului, o sortează alfabetic și scrie raportul
  - studAnswersChecked(): verifică încadrarea în timp a submisiei studentului (aruncând excepție dacă e cazul), iterează prin întrebările sortate după dificultate, compară răspunsurile studentului cu cele corecte și calculează punctajul total

*CLASA QuestionComparator:*
- Are rolul de a sorta întrebările după dificultate, iar în caz de egalitate, după text
- Este folosită în constructorul TreeSet-ului questionsSortByDiff.

*CLASA Question<T>:*
- Implementează interfața Comparable
- Sunt definite câmpurile: text, autor, dificultate, punctaj, răspuns corect de tip T
- Este definit constructorul care inițializează aceste câmpuri
- Sunt definite metodele:
  - checkAnswer(): metodă abstractă implementată de subclase
  - transfAnswer(): metodă abstractă pentru convertirea inputului String în tipul generic T
  - compareTo(): definește regula de sortare cronologică

*CLASELE OpenEndedQuestion, FillInTheBlankQuestion, MultipleChoiceQuestion:*
- Extind clasa Question specificând tipul generic (String sau ResponseOption)
- Implementează metodele:
  - transfAnswer: convertește tipul răspunsului (pentru OpenEndedQuestion și FillInTheBlankQuestion rămâne String, iar pentru MultipleChoiceQuestion se convertește în ResponseOption)
  - checkAnswer: implementează logica specifică de punctare (potrivire exactă sau parțială în funcție de cerință și marja de eroare calculată)
  - procentQuestion: returnează procentul din punctaj (1.0, 0.0, 0.7 sau 0.5) conform interfeței Gradable

*CLASA Student:*
- Implementează interfața Comparable
- Sunt definite câmpurile name, group și un HashMap pentru notele examenelor
- Sunt definite metodele:
  - equals() și hashCode(): Suprascrierea metodelor este esențială pentru ca obiectele Student să fie unice după nume atunci când sunt folosite pe post de chei în HashMap-ul din clasa Exam
  - compareTo(): definește sortarea alfabetică după nume
  - calcScoreCurrExam() și setScore(): gestionează notele studentului