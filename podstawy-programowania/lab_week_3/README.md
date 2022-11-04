# Sprawozdanie z laboratorium 

>## Autor: Igor Krzywda (275480)
>### Data Wykonania: 16.10.22


## Specyfikacja

### Wejście

Dane do programu przekazywane są przez `stdin` w trzech możliwych postaciach:

* `raw_input_1` ([przeciecia_zera_1.txt](https://kcir.pwr.edu.pl/~mucha/PProg/Pomoce/przeciecia_zera1.txt)) 
    w postaci`HH:MM:SS.SSS PP.PP` gdzie:
    - `H` == godziny
    - `M` == minuty
    - `S` == sekundy
    - `P` == ciśnienie tętnicze

* `raw_input_2` ([przeciecia_zera_2.txt](https://kcir.pwr.edu.pl/~mucha/PProg/Pomoce/przeciecia_zera2.txt))
    w postaci `S.SS PP.PP` dla czasu pomiaru mniejszego jak minuta oraz `M'S.SS P.PP` dla
    czasu pomiaru większego jak minuta

* `normalized_input` wejście znormalizowane gdzie danymi wejściowymi są liczby
    całkowite z przedziału `[-10,10]`

### Wyjście

Danymi wyjściowymi są jest częstotliwość uderzeń na minutę....


## Kod

