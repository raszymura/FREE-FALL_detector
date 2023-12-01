## Detektor spadku swobodnego

Mając do dyspozycji napisany **IMU simulator** należy przygotować prosty moduł aplikacyjny (w języku C lub C++), który będzie przetwarzał dane pomiarowe z symulatora celem wykrycia swobodnego spadku urządzenia. Moduł powinien zostać zintegrowany w głównej aplikacji i podlega stawianym jej wymaganiom. Należy podkreślić, że celem tego etapu nie jest przygotowanie zaawansowanego algorytmu przetwarzania. Swobodny spadek jest definiowany jako stan układu, w którym przyspieszenia ze wszystkich 3 osi mieszczą się jednocześnie w pewnym zakresie wartości wokół 0 g. Stan ten musi być podtrzymany przez jakiś czas, tj. nie może być stwierdzony po jednej pasującej próbce. Wykrycie stanu swobodnego spadku powinno zostać zaprezentowane użytkownikowi aplikacji (forma notyfikacji). Konfiguracja algorytmu (czułość, stała czasowa) powinna być możliwa bez konieczności rekompilacji oprogramowania. Walidację poprawności stworzonego kodu w tym etapie można przeprowadzić korzystając z wcześniej przygotowanego symulatora oraz przekazanego pliku CSV. Plik z danymi zawiera logi obrazujące ruch fizycznego urządzenia z układem IMU, w tym w szczególności jego podrzucanie. 

Kryteria oceny etapu zadania:
• Separacja warstw oprogramowania
• Zgodność implementacji algorytmu detekcji swobodnego spadku z założeniami 
• Integracja istniejącego kodu do działającej aplikacji