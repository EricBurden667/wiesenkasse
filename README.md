# Wiesenkasse
Dies ist ein Projekt, um ein sehr einfaches System zu erstellen, um bei den Flohmärkten unseres Vereins wie bei einer Kasse durch beliebige Endgeräte Daten eingeben zu können.

# Code
Aktuell gibt es nur einen Layer, der in C++, genauer mit Hilfe von [Crow](https://crowcpp.org/master/) geschrieben wurde.

Als Abhängigkeiten sollten also folgende Pakete, bzw Dev-files vorliegen:
  * crow
  * sqlite3 (zB als libsqlite3-dev)
  * sqliteCpp (zB [direkt](https://github.com/SRombauts/SQLiteCpp) oder libsqlitecpp-dev)

Um das Projekt lokal nutzen zu können, muss die Datei "api.cpp" zB mit Hilfe von [clang](https://man.openbsd.org/clang.1) oder g++ kompiliert werden.

Dies kann zB mit Hilfe von
$ make rebuild geschehen.

Der Start erstellt einen Service auf 18080/tcp, der auf versch. Endpoints reagiert.
Die Datenbank wird mit den benötigten Tabellen automatisch erzeugt (zur Zeit noch mit kleinem Fehler).

Es handelt sich her um mein erstes Projekt in C++!

# Details
## Architektur
Sieht seltsam aus, aber dieser Service ist so aufgebaut, dass Crow die APIs bereitstellt und eigentlich nur Funktionen aufruft. Das sollte eine Modularität bereitstellen, die bei solchen Versuchen sinnvoll scheint.

## Tabellen
Es gibt derzeit zwei Tabellen: 'verk' und 'kasse'

Die Tabelle 'verk' enthält die Verkäufernummer, die sich auch auf den zu verkaufenden Artikeln befindet, den dazu gehörenden Namen, eine optionale Beschreibung und die Angabe, wieviel Prozent der Förderverein vom Umsatz erhält (zur Zeit sind 10% der normale Satz).

```sql
    ID INT PRIMARY KEY NOT NULL,
    name TEXT NOT NULL,
    description CHAR(255),
    fees INT DEFAULT 10
```

Die Tabelle 'kasse' wird dann von allen durch das HTML-Formular (<host>/form) gefüllt, zur Zeit leider noch nicht via Transaktion:

```sql
    ID INT PRIMARY KEY NOT NULL,
    verkID INT NOT NULL,
    price DOUBLE NOT NULL
```

# TODO
  * Anpassen von storeData() -> Transaktionen!
  * Anzeige des Warenkorbes im Client als Tabelle
  * Löschen von einzelnen Artikeln im Client
  * Absenden des Warenkorbes im Client
  * Löschen des Warenkorbes im Client
  * Anpassen von printData() -> verkID, name, description, fees
  * Darstellung von printAllData() -> .mode?, JavaScript

# Fixed
  * Datenbank wird jetzt korrekt beim Start geprüft und ggfs erstellt (Danke für den Patch!)
