**IMPLEMENTAREA TEMEI 1 POO-2-CB**

Pentru rezolvarea acestei teme, am definit în directorul tema1 următoarele:
- clasa abstracta ComponentaRetea care este extinsă de:
    - clasa abstracta ProducatorEnergie care este extinsă de:
        - clasa PanouSolar
        - clasa TurbinaEoliana
        - clasa ReactorNuclear
    - clasa abstracta ConsumatorEnergie care este extinsă de:
        - clasa SistemSuportViata
        - clasa LaboratorStiintific
        - clasa SistemIluminat
    - clasa Baterie
- clasa GridController
- în clasa App, metoda main() și metode ajutătoare

*CLASA ComponentaRetea:*
- Sunt definite câmpurile private id și statusOperațional.
- Este definit constructorul cu parametrul id și setează statusul implicit la true
- Sunt definite metodele:
    - getId(): returnează id-ul obiectului curent
    - getStatusOperational(): returnează statusul obiectului curent
    - setStatusOperational(boolean statusOperational): schimba valoarea statusului obiectului curent cu valoarea dată ca parametru

*CLASA ProducatorEnergie:*
- Este definit constructorul care primește parametrul id și apelează constructorul din clasa părinte
- Sunt definite metodele:
    - calculeazaProductie(double factorExtern): este o metodă abstractă ce urmează să fie implementată de clasele concrete pentru a returna energia produsă
    - afisProdTip(): este o metodă abstractă folosită pentru afișarea detaliilor specifice fiecărui tip de producător
    - afisProducatori(List<ProducatorEnergie> producatori): este o metodă statică ce parcurge lista de producători și afișează starea completă a acestora

*CLASA PanouSolar:*
- Este definit câmpul privat putereMaxima.
- Este definit constructorul care inițializează câmpul specific și apelează constructorul din clasa părinte.
- Sunt definite metodele:
    - getPutereMaxima(): returnează puterea maximă a obiectului curent
    - setPutereMaxima(double putereMaxima): schimba valoarea puterii maxime a obiectului curent cu valoarea dată ca parametru
    - calculeazaProductie(double factorExtern): implementează logica de calcul a energiei (putere maximă * factor extern), dar dacă componenta este defectă returnează 0
    - afisProdTip(): suprascrie metoda abstractă din clasa părinte, afișând tipul specific (PanouSolar) și puterea maximă

*CLASA TurbinaEoliana:*
- Este definit câmpul privat putereBaza
- Este definit constructorul care inițializează câmpul specific și apelează constructorul din clasa părinte
- Sunt definite metodele:
    - getPutereBaza(): returnează puterea de bază a obiectului curent.
    - setPutereBaza(double putereBaza): schimbă valoarea puterii de bază a obiectului curent cu valoarea dată ca parametru
    - calculeazaProductie(double factorExtern): implementează logica de calcul a energiei (putere de bază * factor extern), dar dacă componenta este defectă returnează 0
    - afisProdTip(): suprascrie metoda abstractă din clasa părinte, afișând tipul specific (TurbinaEoliana) și puterea de bază

*CLASA ReactorNuclear:*
- Este definit câmpul privat putereConstanta
- Este definit constructorul care inițializează câmpul specific și apelează constructorul din clasa părinte
- Sunt definite metodele:
    - getPutereConstanta(): returnează puterea constantă a obiectului curent
    - setPutereConstanta(double putereConstanta): schimbă valoarea puterii constante a obiectului curent cu valoarea dată ca parametru
    - calculeazaProductie(double factorExtern): implementează logica de calcul a energiei (returnează doar puterea constantă), dar dacă componenta este defectă returnează 0
    - afisProdTip(): suprascrie metoda abstractă din clasa părinte, afișând tipul specific (ReactorNuclear) și puterea de bază

*CLASA ConsumatorEnergie:*
- Implementează interfața Comparable
- Sunt definite câmpurile protected cerereEnergie, prioritate și esteAlimentat
- Este definit constructorul care inițializează aceste câmpuri, setând esteAlimentat implicit la true și apelează constructorul din clasa părinte
- Sunt definite metodele:
    - getPrioritate(): returnează tipul de prioritate al consumatorului curent
    - getCerereEnergie(): returnează cantitatea de energie
    - getEsteAlimentat(): returnează starea de alimentare curentă
    - setPrioritate(int prioritate): schimbă prioritatea consumatorului curent cu valoarea dată ca parametru
    - setEsteAlimentat(boolean esteAlimentat): schimbă valoarea stării de alimentare a consumatorului cu valoarea dată ca parametru
    - setCerereEnergie(double cerereEnergie): schimbă valoarea cererii de energie cu valoarea dată ca parametru
    - getCerereCurenta(): returnează cererea de energie când consumatorul este alimentat și are statusul operațional setat, altfel returnează 0
    - cupleazaLaRetea(): modifică starea câmpului esteAlimentat la true
    - decupleazaDeLaRetea(): modifică starea câmpului esteAlimentat la false
    - compareTo(ConsumatorEnergie consumatorEnergie): implementează regula de sortare descrescătoare în funcție de prioritate, pentru algoritmul de triage
    - afisConTip(): este o metodă abstractă folosită pentru afișarea detaliilor specifice fiecărui tip de consumator
    - afisConsumatori(List<ConsumatorEnergie> consumatori): este o metodă statică ce parcurge lista de consumatori și afișează starea completă a acestora

*CLASA SistemSuportViata:*
- Este definit constructorul cu parametrii specifici componentei, apelează constructorul din clasa părinte și setează prioritatea la 1
- Sunt definite metodele:
    - afisConTip(): suprascrie metoda abstractă din clasa părinte, afișând tipul specifică (SistemSuportViata)

*CLASA LaboratorStiintific:*
- Este definit constructorul cu parametrii specifici componentei, apelează constructorul din clasa părinte și setează prioritatea la 2
- Sunt definite metodele:
    - afisConTip(): suprascrie metoda abstractă din clasa părinte, afișând tipul specific (LaboratorStiintific)

*CLASA SistemIluminat:*
- Este definit constructorul cu parametrii specifici componentei, apelează constructorul din clasa părinte și setează prioritatea la 3
- Sunt definite metodele:
    - afisConTip(): suprascrie metoda abstractă din clasa părinte, afișând tipul specifică (SistemIluminat)

*CLASA Baterie:*
- Sunt definite câmpurile private capacitateMaxima și energieStocata
- Este definit constructorul care inițializează capacitatea maximă și apelează constructorul din clasa părinte
- Sunt definite metodele:
    - getCapacitateMaxima(): returnează capacitatea maximă a bateriei
    - setCapacitateMaxima(double capacitateMaxima): schimbă valoarea capacității maxime a bateriei cu valoarea dată ca parametru
    - getEnergieStocata(): returnează cantitatea curentă de energie stocată în baterie
    - setEnergieStocata(double energieStocata): modifică valoarea energiei stocate manual
    - incarca(double energieDisponibila): dacă bateria nu este defectă, încarcă bateria cu energia posibilă până atinge capacitatea maximă și returnează surplusul, altfel returnează toată energia primită
    - descarca(double energieCeruta): dacă bateria nu este defectă, returnează energia cerută, în funcție de enrgia bateriei, altfel returnează 0
    - afisBaterii(List<Baterie> baterii): este o metodă statică ce parcurge lista de baterii și afișează starea completă a acestora

*CLASA GridController:*
- Sunt definite câmpurile corespunzătoare listelor pentru producători, consumatori și baterii, și variabilele de stare pentru simulare: productieTotala, cerereTotala, esteInBlackout, istoric, cntTick
- Este definit constructorul care inițializează listele, setează starea inițială și resetează contorul de tick-uri la 0
- Sunt definite metodele:
    - addProducatorEnergie(ProducatorEnergie p): primește un obiect producător și îl adaugă în lista prodList
    - addConsumatorEnergie(ConsumatorEnergie c): primește un obiect consumator și îl adaugă în lista consList
    - addBaterie(Baterie b): primește un obiect baterie și îl adaugă în lista baterList
    - getProdList(): returnează lista curentă de producători
    - getConsList(): returnează lista curentă de consumatori
    - getBaterieList(): returnează lista curentă de baterii
    - getEsteInBlackout(): returnează statusul global corespunzător stării de Blackout
    - getIstoric(): returnează lista ce conține istoricul evenimentelor
    - simuleazaTick(double factorSoare, double factorVant): implementează logica de balansare a rețelei, incrementând contorul global cntTick, calculând producția și cererea totală, gestionând valoarea de energie rezultată în următoarele scenarii:
        - delta > 0: distribuie surplusul bateriilor pentru încărcare
        - delta < 0: descarcă bateriile pentru a obține energie, iar daca deficitul persistă, decuplează consumatorii (în funcție de prioritate) și dacă nici decuplarea nu acoperă lipsa de energie, rețeaua intră în blackout
    - afisTick(double energBat, ArrayList<String> consDecupl): afișează mesajul corespunzător la finalul fiecărui pas de simulare
    - idValid(String id): verifică unicitatea unui id în listele de componente, returnând obiectul găsit sau null în caz contrar

*CLASA App:*
- A conținut câmpul scanner și metodele App(InputStream input), run() implementate de la început
- A fost completată metoda main() și adăugate metode ajutătoare prelucrării comenzilor:
    - Metodele definite pentru implementarea celor 7 comenzi:
        - comanda0(String[] cuv, GridController grid): verifică dacă puterea specificată este un număr pozitiv și unicitatea id-ului folosind metoda grid.idValid(), determină tipul de producător (solar, eolian, nuclear) și creează obiectul corespunzător acestuia și adaugă noul producător în sistem prin grid.addProducatorEnergie(), afișând mesajul de succes
        - comanda1(String[] cuv, GridController grid): verifică dacă cererea de putere este un număr pozitiv și unicitatea id-ul, determină tipul de consumator (SistemSuportViata, LaboratorStiintific, SistemIluminat), creează obiectul și adaugă consumatorul în lista din GridController, afișând mesajul de succes
        - comanda2(String[] cuv, GridController grid): verificarea cazului în care capacitatea bateriei este un număr pozitiv unicitatea id-ului creează obiectul și adaugă bateria în lista din GridController, afișând mesajul de succes
        - comanda3(String[] cuv, GridController grid): verifică dacă factorii externi sunt numere pozitive, testează dacă rețeaua este deja în Blackout, afișând mesajul corespunzătoar, altfel apelează metoda grid.simuleazaTick() pentru execuția balansării
        - comanda4(String[] cuv, GridController grid): obține obiectul corespunzător id-ului din listele de componente și dacă există, îi actualizează starea operațională, afișând mesajul corespunzător
        - comanda5(GridController grid): afișează starea globală, dacă nu este goală, apelând metodele de afișare din clasele componentelor pentru afișarea tuturor detaliilor
        - comanda6(GridController grid): verifică dacă istoricul este gol și dacă se găsesc evenimente, le afișează
        - comanda7(): închie bucla din main(), afișând mesajul corespunzător
    - main(String[] args): citește comenzile de la tastatură, împarte linia citită în cuvinte și, în funcție de numărul comenzii verifică daca parametrii primiți sunt de tipul specificat și apelând metoda ajutătoare corespunzătoare comenzii, returnând eroare in caz contrar

*BONUS:*
- Ce alte cazuri limită ați mai trata în această aplicație?
    - spațieri diferite de formatul obișnuit (mai multe spații sau tab în loc de un singur spațiu)
        - rezolvare: comenzile sunt tratate indiferent de spatieri
    - tipurile de componente scrise cu majuscule în loc de litere mici
        - rezolvare: tipurile de componente sunt recunoscute indiferent de modul în care sunt scrise (de exemplu, folosind metoda String.equalsIgnoreCase())
    - scrierea în altă ordine a cuvintelor din comandă
        - rezolvare: se afișează eroare de tip Format Invalid
- Cum ați refactoriza comenzile și răspunsurile din aplicație?
    - primele 3 comenzi (0 - 2) trebuie transformate în una singură, unde se verifică tipul de componentă adăugată și numărul de cuvinte din comandă și în funcție de acestea, se verifică în ce listă se adaugă componenta
        - adăugarea unei verificări suplimentare, dacă rețeaua este în blackout, să nu mai poată fi adăgată nici o componentă nouă, afișându-se un  mesaj de eroare corespunzător (REȚEA ÎN BLACKOUT: componenta nu a putut fi adăugată)
    - comanda 3: mesajele de eroare ar trebui îmbunătățite, făcându-se o distincție mai clară între o rețea care era dinainte în blackout și una care intră în blackout după noul tick
        - mesaj de eroare dacă rețeaua era deja în blackout: "EROARE: Reteaua este DEJA in BLACKOUT. Simulare se oprește acum."
        - mesaj de eroare dacă rețeaua intră în timpul simulării actuale în blackout: "BLACKOUT ÎN TIMPUL TICK-ULUI CURENT! SIMULARE SE OPREȘTE ACUM."
    - comanda 4: adăugarea unei verificări suplimentare, dacă sistemul este in blackout, o componentă nu mai poate fi reparată, poate fi doar setată drept defectă
    - comanda 5: afișarea componentelor ar trebui făcută în funcție de status, prima dată componentele funcționale și, la final, cele defecte
    - comanda 6: istoricul trebuie restructurat pentru ca mesajele să fie mai sugestive, starea finală (SUCCES și EROARE) trebuie însoțită de coduri specifice și de codul comenzii (0 - 7)
    - comanda 7: rămâne la fel
    - pentru mesajele din urma comenzilor, trebuie adăugate coduri specifice, în funcție de reușita, eroare și de tipul fiecăreia dintre acestea (de exemplu eroarea cu codul 0 să fie specifică erorii de adăugării unei noi componente)