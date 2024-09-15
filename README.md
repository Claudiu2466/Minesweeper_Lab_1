1. Proiect: Minesweeper101

2. Proiectul dat reprezinta o miniversiune a jocului "MINESWEEPER".

3. Regulile de joc: Minesweeper este un gen de jocuri video cu puzzle logic, jucat în general pe computere personale. Jocul are o grilă de plăci pe care se poate face clic, cu „mine” ascunse (descrise ca mine navale în jocul original) împrăștiate pe toată tabla. Obiectivul este de a curăța tabla fără a detona nicio mină, cu ajutorul unor indicii despre numărul de mine învecinate din fiecare câmp. Un joc de Minesweeper începe atunci când jucătorul selectează pentru prima dată o celulă de pe o tablă. În unele variante, primul clic este garantat a fi sigur, iar unele garantează în continuare că toate celulele adiacente sunt, de asemenea, sigure. În timpul jocului, jucătorul folosește informațiile date din celulele deschise pentru a deduce alte celule care pot fi deschise în siguranță, obținând în mod iterativ mai multe informații pentru a rezolva tabla. Jucătorul primește, de asemenea, numărul de mine rămase pe tablă, cunoscut sub numele de număr de mine, care este calculat ca numărul total de mine scăzut din numărul de celule marcate (astfel, numărul de mine poate fi negativ dacă au fost plasate prea multe steaguri) .
Pentru a câștiga un joc de Minesweeper, toate celulele care nu sunt mine trebuie să fie deschise fără a deschide o mină. Nu există niciun scor, dar există un cronometru care înregistrează timpul necesar pentru a termina jocul. Dificultatea poate fi crescută prin adăugarea de mine sau începând cu o grilă mai mare. Majoritatea variantelor de Minesweeper care nu sunt jucate pe o tablă fixă ​​oferă trei configurații implicite de placă, de obicei cunoscute sub numele de Începător, Intermediar și Expert, în ordinea creșterii dificultății. Începătorul este de obicei pe o placă de 8x8 sau 9x9 care conține 10 mine, Intermediar este de obicei pe o placă de 16x16 cu 40 de mine și expert este de obicei pe o placă de 30x16 cu 99 de mine; cu toate acestea, există de obicei o opțiune pentru a personaliza dimensiunea plăcii și numărul de mine.

In proiectul dat versiunea de joc este simplificata dar are la baza aceasi logica de joc. Jucatorul incepe prin a alege cu ce dificultate doreste sa inceapa jocul dupa care incepe jocul. Jocul permite amplasarea random a minelor pe grila ceea ce asigura ca jocul sa fie mereu diferit.

4. Tipuri de date:

-------
| Int |
-------
Sunt numere intregi, care sunt ulterior folosite pentru a face operatii necesare ca jocul sa functioneze.
In cadrul jocului Minesweeper sunt folosite pentru a stoca (dimensiuni a campului de joc, coordonatele mouse-ului pentru a deschide sau marca o celula, numarul de mine din campul de joc, variabile de iterare, variabile de input de la utilizator.


--------
| Char |
--------
Este un tip de date care stocheaza cate un singur caracter.
In joc acesta se foloseste pentru a reprezenta celulele din campul de joc. Spre exemplu starea unei celule(este libera, marcata sau contine o mina).


----------
| Char** |
----------
Reprezinta tablouri de siruri de caractere.
In cazul jocului Minesweeper sunt utilizate pentru a reprezenta 2 tipuri de matrici. O matrice care stocheaza date despre locul de amplasare a minelor pe camp si a celulelor libere si o matrice care stocheaza ce vede jucatorul in consola de joc (celule inchise, celule deschise sau celule marcate cu flag).


--------
| Bool |
--------
Este un tip de date care ia o valoare de tip true sau false.
In joc e utilizat pentru a indica mai ulte stari binare cum ar fi (daca campul de joc a fost generau sau nu, daca jocul este jucat de utilizator sau automatizat, daca jocul s-a terminat sau daca jucatorul a castigat sau a pierdut).


----------
| HANDLE |
----------
Tip de date specific pentru Windows API care este utilizat pentru a identifica obiecte din sistemul de operare, cum ar fi ferestrele consolei sau dispozitivele de intrare sau iesire.
In cazul nostru acestea sunt utilizate pentru a primi input de la mouse si de a controla outputul textului pe ecran.


----------------
| INPUT_RECORD |
----------------
Structura specifica Windows API-ului care stocheaza datele de intrare a utilizatorului, inclusiv evenimentele de tastatura si mouse.
Pentru jocul Minesweeper acesta inregistreaza evenimentele de intrare de la mouse si tastatura pentru a controla interactiunea jucatorului cu campul de joc.


------------------------
| DWORD (unsigned long)|
------------------------
In Windows API reprezinta un alias pentru tipul de date unsigned long.
In cazul nostru este folosit pentru a citi starea butoanelor mouse-ului (daca a fost un buton apasat sau nu), pentru cititrea caracterului apasat de la tastatura sau pentru a verifica numarul evenimentelor de intrare in cadrul consolei Windows.


------------------------
| WORD (unsigned short)|
------------------------
In Windows API reprezinta un alias pentru tipul de date unsigned short.
In cazul nostru acesta este utilizat pentru a seta culorile de fundal si text atunci cand se afiseaza celulele pe ecran(celule deschise, celule cu flag sau mine explodate).
În acest sistem, valorile pentru culorile de fundal si text sunt:

0 = Negru
1 = Albastru
2 = Verde
3 = Cyan
4 = Roșu
5 = Magenta
6 = Galben
7 = Alb
8 = Gri închis
9 = Albastru deschis
A = Verde deschis
B = Cyan deschis
C = Roșu deschis
D = Magenta deschisă
E = Galben deschis
F = Alb strălucitor

---------
| COORD |
---------

Tip de date specific Windows API-ului care este responsabil pentru stocarea coordonatelor pe axa X si Y a cursorului in consola.
In joc acesta este responsabil de pozitia de inceput, in fereastra consolei, unde sunt afisate elementele jocului.


-----------------------
| CONSOLE_CURSOR_INFO |
-----------------------
Este o structura specifica Windows API-ului folosita pentru a controla aspectul cursorului din consola.
In cazul nostru acesta este responsabil de vizibilitatea cursorului in timpul jocului si cand acesta este sau nu vizibil.


------------------------------
| CONSOLE_SCREEN_BUFFER_INFO |
------------------------------
Este o structura specifica Windows API-ului care contine informatii despre buffer-ul de ecran al consolei. Aceasta structura are informatii despre dimensiunea si starea buferului de ecran, inclusiv pozitia cursorului si alte date despre buffer.
In contextul nostru acesta se foloseste pentru a stoca informatii despre pozitia cursorului si dimensiunea ecranului. 


---------------
| std::string |
---------------
Tip de date standart pentru c++ care ajuta la manipularea sirurilor de caractere.
In cazul nostru este folosit pentru a crea o linie de deespartire din caracterul "-". 

Aceste tipuri de date sunt esentiale pentru ca jocul nostru sa lucreze corect. 
