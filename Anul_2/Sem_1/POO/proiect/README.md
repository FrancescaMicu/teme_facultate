*IMPLEMENTARE PROIECT POO-2-CB*

Pentru rezolvarea acestui proiect, am definit în directorul org.example următoarele:
- clasa Main care conține metoda main()
- clasa Database
- clasa FileProcessing
- clasa Factory
- clasa abstractă Command care este extinsă de:
  - clasa AddServer
  - clasa AddGroup
  - clasa AddMember
  - clasa AddEvent
  - clasa RemoveGroup
  - clasa RemoveMember
  - clasa FindGroup
  - clasa FindMember
- interfața Subject
- interfața Observer
- clasa Server care implementează Subject
- clasa ResourceGroup implementează Observer
- clasa User care este extinsă de:
  - clasa Operator care este extinsă de:
    - clasa Admin
- clasa Alert
- clasa Location
- enum-ul ServerStatus
- enum-ul AlertType
- enum-ul Severity
- enum-ul PathTypes
- clasa MissingIpAddressException
- clasa LocationException
- clasa UserException

**CLASA Main:**
- Este definită metoda:
  - main(String[] args): verifică numărul de argumente primite în linia de comandă, dacă sunt 2 argumente, apelează metoda FileProcessing.readFromFile cu tipul și calea specificată, dar dacă sunt 4 argumente, apelează succesiv citirea pentru servere, grupuri și listener, folosind enum-ul PathTypes
    - afișează un mesaj eroare la consolă dacă nu au fost trimise numărul necesar de argumente

**CLASA FileProcessing:**
- Sunt definite metodele:
  - readFromFile(String typePath, String pathName): construiește calea către fișierul de intrare și parcurge fișierul linie cu linie. Pentru fiecare linie citită:
    - Realizează parsarea parametrilor folosind separatorul "|"
    - Apelează Factory pentru a obține instanța corectă a comenzii, transmițând tipul fișierului, parametrii și numărul liniei curente
    - Execută comanda și adaugă rezultatul într-o listă de mesaje dacă este valid
  - writeInFile(String pathName, List<String> outputMessages): construiește calea către fișierul de ieșire și scrie toate mesajele stocate în listă

**CLASA CommandFactory:**
- Implementează design pattern-ul Factory pentru a gestiona instanțierea obiectelor de tip comanda
- Sunt definite metodele:
  - typeCommand(String typePath, String[] params, int nrCommands): determină categoria comenzii pe baza tipului de fișier primit ca parametru și direcționează execuția:
      - GROUPS: pasează execuția spre metoda groupTypeCommand
      - LISTENER: returnează o nouă instanță AddEvent sau null în caz că e vreo excepție aruncată
      - SERVERS: încearcă să creeze o instanță AddServer, iar în cazul în care sunt aruncate excepții de validare, acestea sunt prinse și se returnează o instanță a comenzii inițializată cu un mesaj de eroare sau null, în funcție de tipul excepției
  - groupTypeCommand(String[] params, int nrCommands): analizează tipul comenzii și instanțiază clasa corespunzătoare, iar în caz de eroare, excepțiile sunt prinse și returnează obiecte de comandă cu mesaj de eroare sau null, în funcție de tipul excepției

**CLASA User:**
- Sunt definite câmpurile pentru nume, rol și email
- Este definit constructorul care inițializează aceste câmpuri cu valorile primite ca parametri
- Sunt definite metodele:
  - getName(): returnează numele utilizatorului.
  - getRole(): returnează rolul utilizatorului.

**CLASA Operator:**
- Este definit câmpul specific departamentului
- Este definit constructorul care primește parametrii specifici, apelând constructorul din clasa părinte și inițializând câmpul nou

**CLASA Admin:**
- Este definit câmpul pentru nivelul de acces
- Este definit constructorul care primește parametrii specifici, apelând constructorul din clasa părinte și inițializând câmpul nou

**ENUM-URILE**
 - AlertType, ServerStatus, Severity
 - Am scris codul pe modelul de la PathTypes pentru a fi mai usor de gestionat cuvintele primite cu litere mici din comenzi

**CLASA Server:**
- Sunt definite câmpurile private care descriu specificațiile serverului, împărțite în câmpuri obligatorii și câmpuri opționale, precum și lista de observatori
- Este definit un constructor privat care primește un obiect de tip Builder pentru inițializarea tuturor câmpurilor și instanțiază lista de observatori
- Sunt definite metodele specifice Observer Pattern:
    - notifyObservers(Alert alert): parcurge lista de observatori și notifică observatorii
    - addObserver(Observer observer): adaugă un nou observator în listă 
    - removeObserver(Observer observer): elimină un observator specific din lista de observatori
    - newAlert(Alert alert): metoda care primește o alertă și apelează notifyObservers pentru a o trimite mai departe
    - getIpAddress(), getStatus() 2 metode getter
- Sunt suprascrise metodele equals() și hashCode():
  - Asigură unicitatea serverului în colecțiile Set din Database în funcție de ip
- clasa statică internă Builder: Implementează Builder Pattern pentru construirea obiectelor Server
  - Este definit constructorul Builder(String ipAddress, Location location, User owner) care inițializează câmpurile obligatorii
  - Sunt definite metodele de tip setter pentru setarea câmpurilor opționale și returnează instanța curentă
  - Este definită și metoda build() care creează și returnează noua instanță a clasei Server

**CLASA Location:**
- Sunt definite câmpurile private ce descriu locația geografică, având un câmp obligatoriu și câmpuri opționale
- Este definit un constructor privat care primește un obiect de tip Builder pentru inițializarea tuturor câmpurilor
- clasa statică internă Builder: Implementează Builder Pattern pentru construirea obiectelor Location
  - Este definit constructorul Builder(String country) care inițializează câmpul obligatoriu
  - Sunt definite metodele de tip setter (setCity, setAddress, setLatitude, setLongitude) pentru setarea câmpurilor opționale și returnează instanța curentă
  - Este definită metoda build() care creează și returnează noua instanță a clasei Location

**CLASA ResourceGroup:**
- Sunt definite câmpurile private pentru lista de membri și adresa IP a grupului
- Este definit constructorul care inițializează adresa IP și instanțiază lista de membri
- Este definită metoda specifică Observer Pattern:
  - update(Alert alert): metodă utilizată pentru primirea notificărilor despre alerte de la server
- Sunt definite metodele pentru gestionarea membrilor grupului:
    - addMember(User user): adaugă un utilizator în listă
    - removeMember(User user): elimină un utilizator din listă
    - getMembers(): returnează lista completă de membri
    - getUser(String name, String role): caută și returnează un utilizator specific pe baza numelui și rolului acestuia
    - getIpAddress(): metodă getter pentru adresa IP
- Sunt suprascrise metodele equals() și hashCode():
  - Asigură unicitatea grupului în colecțiile Set din Database în funcție de ip

**CLASA Database:**
- Implementează Design Pattern-ul Singleton
- Sunt definite câmpurile private de tip Set pentru stocarea unică a entităților
- Este definit constructorul privat care inițializează colecțiile
- Este definită metoda statică getInstance() care returnează instanța unică a clasei
- Sunt definite metodele:
    - addServer(Server server): adaugă un server în set și verifică automat dacă există un grup asociat pentru a adăugarea unui observator nou (Observer pattern)
    - addResourceGroup(ResourceGroup group): adaugă un grup în set și îl abonează automat la serverul corespunzător
    - addAlert(Alert alert): adaugă o alertă nouă
    - findServer(String ipAddress), findGroup(String ipAddress): metode de căutare a entităților pe baza adresei IP
    - removeGroup(ResourceGroup group): șterge grupul din bază și îl scoate ca observator de la toate serverele monitorizate

**EXCEPȚIILE:**
- UserException, MissingIpAddressException, LocationException
- Aceste clase extind Exception și sunt folosite pentru transmiterea mesajelor specifice prin constructorul super atunci când câmpurile obligatorii lipsesc

**INTERFAȚA Subject:**
- Sunt definite metodele abstracte necesare gestionării listei de observatori și anunțării evenimentelor:
    - notifyObservers(Alert alert): parcurge lista de observatori și le trimite notificarea
    - addObserver(Observer observer): adaugă un nou observator pentru a primi actualizări
    - removeObserver(Observer observer): elimină un observator din lista de notificare
    - newAlert(Alert alert): metoda care primește o alertă și inițiază procesul de notificare către toți observatorii

**INTERFAȚA Observer:**
- Este definită metoda abstractă:
  - update(Alert alert): metoda apelată automat de Subject atunci când apare o nouă alertă, permițând observatorului să reacționeze

**CLASA abstractă Command:**
- Este baza Design Pattern-ului Command
- Este definită metoda abstractă:
  - execute(): realizează acțiunea specifică și a returna rezultatul sub formă de String (mesajul de output)

**CLASA AddServer:**
- Sunt definite câmpurile private server și error (pentru gestionarea cazurilor de validare eșuată)
- Sunt definiți constructorii:
    - AddServer(String[] params): validează parametrii obligatorii aruncând excepții specifice, construiește obiectele Location și Server folosind Builder Pattern și datele din array
    - AddServer(String error): inițializează comanda cu un mesaj de eroare atunci când validarea eșuează
- Este suprascrisă metoda execute():
  - Verifică existența erorilor, returnând mesajul de eroare în caz afirmativ
  - Altfel, adaugă serverul creat și returnează mesajul de succes

**CLASA AddGroup:**
- Sunt definite câmpurile private group și error (pentru gestionarea erorilor)
- Sunt definiți constructorii:
  - AddGroup(String[] params): validează existența parametrului obligatoriu aruncând MissingIpAddressException și instanțiază noul ResourceGroup
  - AddGroup(String error): inițializează comanda cu un mesaj de eroare atunci când validarea eșuează
- Este suprascrisă metoda execute():
    - Verifică existența erorilor, returnând mesajul de eroare în caz afirmativ
    - Altfel, adaugă grupul în Database și returnează mesajul de succes

**CLASA AddMember:**
- Sunt definite câmpurile private user, group și error
- Sunt definiți constructorii:
    - AddMember(String[] params): validează parametrii, identifică tipul utilizatorului (Admin sau Operator) și caută grupul țintă în Database
    - AddMember(String error): inițializează comanda cu un mesaj de eroare
- Este suprascrisă metoda execute():
    - Verifică existența erorilor
    - Dacă grupul și utilizatorul sunt valide, adaugă utilizatorul în lista Resource Group și returnează mesajul de succes

**CLASA AddEvent:**
- Sunt definite câmpurile private alert (evenimentul creat), server (sursa evenimentului) și database
- Este definit constructorul:
  - AddEvent(String[] params): convertește parametrii în Enum-uri (AlertType, Severity), creează obiectul Alert și identifică serverul corespunzător din Database
- Este suprascrisă metoda execute():
    - Adaugă alerta în Database
    - Dacă serverul există, apelează metoda server.newAlert(alert) pentru a declanșa notificarea observatorilor
    - Returnează mesajul de succes cu detaliile complete ale evenimentului

**CLASA RemoveGroup:**
- Sunt definite câmpurile private group, error (mesajul de eroare) și database
- Sunt definiți constructorii:
    - RemoveGroup(String[] params): validează parametrul obligatoriu  aruncând MissingIpAddressException, caută grupul în Database și setează un mesaj de eroare dacă acesta nu este găsit
    - RemoveGroup(String error): inițializează comanda cu un mesaj de eroare
- Este suprascrisă metoda execute():
  - Verifică dacă există erori de validare sau căutare, returnând mesajul corespunzător
  - Altfel, apelează metoda database.removeGroup(group) pentru a șterge grupul și a-l dezabona de la servere, returnând mesajul de succes

**CLASA RemoveMember:**
- Sunt definite câmpurile private user, group și error
- Sunt definiți constructorii:
    - RemoveMember(String[] params): validează parametrii obligatorii aruncând excepțiile corespunzătoare, caută grupul și utilizatorul specificat; dacă nu sunt găsite, setează mesajul de eroare în câmpul error
    - RemoveMember(String error): inițializează comanda cu un mesaj de eroare
- Este suprascrisă metoda execute():
  - Verifică existența erorilor setate în constructor
  - Dacă validarea a reușit, elimină utilizatorul din lista de Resource Group și returnează mesajul de succes

**CLASA FindGroup:**
- Sunt definite câmpurile private group și error
- Sunt definiți constructorii:
    - FindGroup(String[] params): validează prezența IP-ului, interoghează baza de date pentru a găsi grupul și setează eroarea dacă nu găsește grupul
    - FindGroup(String error): inițializează comanda cu un mesaj de eroare
- Este suprascrisă metoda execute():
    - Dacă nu există erori, returnează un mesaj ce confirmă găsirea grupului
    - În caz contrar, returnează mesajul de eroare stocat

**CLASA FindMember:**
- Sunt definite câmpurile private user, group și error
- Sunt definiți constructorii:
    - FindMember(String[] params): realizează validarea parametrilor, caută grupul în Database și apoi utilizatorul în Resource Group; în cazul în care oricare dintre parametrii lipsește, construiește mesajul de eroare specific
    - FindMember(String error): inițializează comanda cu un mesaj de eroare
- Este suprascrisă metoda execute():
  - Verifică existența erorilor setate în constructor
  - Dacă validarea a reușit, returnează detaliile utilizatorului găsit confirmând existența acestuia în sistem

**MOTIVARE DESIGN PATTERNS FOLOSITE**
- ***Singleton Pattern***
  - A fost folosit în clasa Database
  - Am folosit Singleton deoarece garantează existența unei singure instanțe a bazei de date pe durata rulării aplicației

- ***Factory Pattern***
  - A fost folosit în clasa CommandFactory.
  - Am folosit Factory Pattern pentru a permite în CommandFactory să decidă ce tip de obiect Command trebuie instanțiat în funcție de tipul fișierului și de parametrii primiți, simplificând codul de procesare a fișierelor

- ***Command Pattern***
  - A fost folosit în clasa abstractă Command și implementările sale
  - Am folosit Command pentru a separa fiecare comandă la o clasă specifică. Permite apelarea comenzii doar prin apelul execute() fără să ne intereseze tipul comenzii

- ***Observer Pattern***
  - A fost folosit între clasa Server (care implementează Subject) și clasa ResourceGroup (care implementează Observer)
  - Am folosit Observer pentru a putea implementa sistemul de notificare al evenimentelor. Atunci când un server primește o alertă, acesta notifică automat toate grupurile de resurse care sunt observator la serverul respectiv

- ***Builder Pattern***
  - A fost folosit în clasele Server și Location
  - Am folosit Builder deoarece obiectele instanțiate au atât câmpuri obligatorii, cât și numeroase câmpuri opționale, iar acest Pattern permite construcția pas cu pas a obiectelor