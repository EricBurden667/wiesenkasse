# Wiesenkasse
Dies ist ein Projekt, um ein sehr einfaches System zu erstellen, um bei den Flohmärkten unseres Vereins wie bei einer Kasse durch beliebige Endgeräte Daten eingeben zu können.

# Code
Aktuell gibt es nur einen Layer, der in C++, genauer mit Hilfe von [Crow](https://crowcpp.org/master/) geschrieben wurde.

Um diesen lokal nutzen zu können, muss die Datei "api.cpp" zB mit Hilfe von [clang](https://man.openbsd.org/clang.1) oder g++ kompiliert werden.

Der Start erstellt einen Service auf 18080/tcp, der auf versch. Endpoints reagiert.

Es handelt sich her um mein erstes Projekt in C++!
