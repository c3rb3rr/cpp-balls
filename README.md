Projekt zaliczeniowy wykonany na zajęcia z C++ używając jak najwięcej z podanych zagadnień.

Gra "kulki" polega na zbieraniu przez gracza, tj. zielony kwadrat jak najwięcej punktów. Punktami są różnokolorowe kółka, które losowo pojawiają się na mapie. Trzeba jednak uważać na kulki koloru czerwonego, które dodatkowo mają biały zarys. Te kulki zabierają każdorazowo po 1HP z puli 10HP, którymi dysponuje gracz na początku gry. Na szczęście istnieją również kulki leczące, które występują pod postacią zielonych kułek z białym zarysem. Taka kulka przywraca za każdym razem 1HP, uzdrawiając gracza aż do osiągnięcia przez niego początkowej ilości HP.

Gra została stworzona w języku c++, oparta jest o bibliotekę SFML używając środowiska Visual Studio.
W grze zawarte zostały zawarte następujące zagadnienia:
  - destruktor wirualny (kulki.h 22 linijka, Player.h 23 linijka)
  - konstruktory i dekonstruktory (Game.h 39 linijka, Game.cpp 43 linijka)
  - klasy (Game.h 11 linijka, Kulki.h 12 linijka, Player.h 9 linijka)
  - STL (iterator) (Game.cpp 146 linijka)
  - zakresowa pętla for (Game.cpp 203 linijka)
  - szablon funkcji (kulki.cpp 3 linijka)
  - wyjątki (Game.cpp 120 linijka)
  - pliki .h z deklaracjami i .cpp z definicjami metod
  - Linkery (przy kompilacji pod linuxem w makefile).
