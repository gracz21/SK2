SK2
===

Gra "Żużel" dla 4-os. jako projekt na zaliczenie przedmiotu Sieci Komputerowe 2.

Jak odpalać?
===
Kompilowanie za pomocą polecenia make w głównym folderze repo.
Opdalać z głównego folderu repo poleceniem ./bin/zuzel

Protokół (komunikacja za pomocą TCP)
===
1. Po połaczeniu się klienta z serwerem, serwer wysyła mu id gracza, którym jest (gracz stawiający grę (będący serwerem) ma zawsze id 0, gracze dołączający do gry (klienci) mają id 1-3) oraz wartość zmiennej last (0 jeżeli serwer nie zgromadził 3 klientów, 1 jeżeli doąłczający klient jest 3. graczem (czyli serwer zgromadził potrzebną listę graczy). Jeżeli klient otrzyma last = 0, to czeka na kolejny komunikat od serwera informujący o tym, że zgromadzona zostałą odpowiednia liczba graczy. Serwer po zebraniu 3 klientów wysyła do 1. i 2. informację o tym, że została zgromadzona odpowiednia liczba graczy (last = 1). W tym momencie wszyscy klienci i serwer rozpoczynają odliczanie do gry.
2. Podczas gry serwer zbiera od każdego z graczy po kolei wartości kątów ich wychyleń. W tym czasie każdy z klientów wysyła swój kąt.
3. Po zgromadzeniu wszystkich kątów serwer zbiera te wartości (wraz ze swoim kątem) do tablicy, która jest nastepnie wysyłana do każdego z klientów. Klienci w tym czasie odbierają tablicę kątów od serwera.
