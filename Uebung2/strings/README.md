# Strings

Klassen StringView und String

## Vorgehensweise
- Klasse StringView: alle Methoden inline, d.h. direkt innerhalb StringView.h, implementieren
- Klasse String: alle Methoden in MyString.cpp implementieren (MyString.h darf nicht verändert werden)
- nirgends den Operator new verwenden
- Unit-Tests ausführen

### Verwendung von Visual Studio

- Alle Projekteinstellungen sind schon vorgenommen. Einfach Strings.sln öffnen.
- Führen Sie wiederholt ```Rebuild All``` aus, um sicherzustellen, dass alles fehlerfrei kompiliert und keine Warnungen mehr erscheinen.
- Konsolen-Applikation starten: Mit der rechten Maustaste auf Console klicken und "Set as Startup Project" auswählen. Anschliessend ausführen.
- Unit-Tests ausführen: Öffnen Sie den Test-Explorer und führen Sie die Unit-Tests aus UnitTest und UnitTest2 aus.

### Verwendung von CMake

CMakeLists.txt ist so aufgebaut, dass das Google-Test-Framework heruntergeladen und installiert wird und dass zwei Applikationen (Console und UnitTest2) erstellt werden.
Führen Sie im Projektverzeichnis folgende Befehle aus:
```
cmake .
cmake --build .
./Console/Console
./UnitTest2/UnitTest2
```
