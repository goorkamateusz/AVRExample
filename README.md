<style>
    img {
        max-width: 50%;
        border-radius: 5px;
    }
</style>

# AVR Basics

Część z materiału realizowanego w ramach kursu "Podstawy Techniki Mikroprocesorowej II".

## Specyfikacja
- Język: `C`,
- Kompilator: `avr-gcc` (Dla Windowsa: [WinAVR](https://sourceforge.net/projects/winavr/)),
- Program symulacyjny: [SimulIDE](https://www.simulide.com/p/home.html),
- Mikrokontroler: `Atmega 32` / `Atmega 328`;

## Uruchomienie

Do kompilacji wymagany jest kompilator `avr-gcc`.
Aby skompilować konkretny z wymienionych programów przygotowano skrypt `prepare.sh`, który na podstawie szablonu tworzy odpowiedni `Makefile`.

- `make build` - polecenie kompilujące program,
- `make burn` - polecenie wysyłające program do kontrolera,
- `make clean` - usuwa wygenerowane pliki binarne;

## Opis przykładów

### Przykład 1. - Sterowanie jasnością didoty przy pomocy przycisków
![Schemat](docs/ex1.png)

### Przykład 2. - Generator sygnału PWM
![Schemat](docs/ex2.png)

### Przykład 3. - Regulator dwustanowy wraz z wyświetlaczem
![Schemat](docs/ex3.png)

### Przykład 4. - Regulator PI
![Schemat](docs/ex4.png)

## Tips:
- https://forbot.pl/blog/szybki-start-z-winavr-id1055
- https://izzudinhafizprojects.wordpress.com/2021/04/05/setting-up-visual-studio-code-vscode-for-avr-programming-not-arduino/
- W pliku `/.vscode/c_cpp_properties.json` ścieżkę `D:\\WinAVR` można zamienic na lokalizację instalaci WinAVR, tak aby Visual Studio Code poprawnie działał.

## Autor
Górka Mateusz, [@goorkamateusz](https://goorkamateusz.github.io)
