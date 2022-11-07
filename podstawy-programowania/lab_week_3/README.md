# Sprawozdanie z laboratorium 

>## Autor: Igor Krzywda (275480)
>### Data Wykonania: 16.10.22


## Specyfikacja

### Wejście

Dane do programu przekazywane są przez `stdin` w dwóch wersjach - dane "surowe"
oraz "znormalizowane"

#### Raw input

* `raw_input_1` ([przeciecia_zera_1.txt](https://kcir.pwr.edu.pl/~mucha/PProg/Pomoce/przeciecia_zera1.txt)) 
    w postaci`HH:MM:SS.SSS PP.PP` gdzie:
    - `H` == godziny
    - `M` == minuty
    - `S` == sekundy
    - `P` == ciśnienie tętnicze

* `raw_input_2` ([przeciecia_zera_2.txt](https://kcir.pwr.edu.pl/~mucha/PProg/Pomoce/przeciecia_zera2.txt))
    w postaci `S.SS PP.PP` dla czasu pomiaru mniejszego jak minuta oraz `M'S.SS P.PP` dla
    czasu pomiaru większego jak minuta

#### Normalized input

* `normalized_input` wejście znormalizowane gdzie danymi wejściowymi są liczby
    całkowite z przedziału `[-10,10]` i kodem wyjściowym `99`

### Wyjście

Uderzenia na minutę (przy wejściu raw) wraz z ostrzeżeniami jeśli BPM wychodzi poza
dolny lun górny limit - analogicznie dla danych znormalizowanych operując na liczbie
przecięć zera.



## Implementacja

### Znormalizowane wejście

#### Stałe 

```c
#define BATCH_LENGTH 99
#define LOWER_THRESHOLD_INTERSECTIONS 8
#define UPPER_THRESHOLD_INTERSECTIONS 14

#define NORMALIZED_INPUT_DURATION 10
#define NORMALIZED_INPUT_BATCH_EXIT_CODE 99
#define INPUT_LOWER_BOUND -10
#define INPUT_UPPER_BOUND 10
```

#### Czytanie danych wejściowych z stdin

Dane wejściowe czytane są za pomocą `scanf` do tablicy z 99 

```c
int scan_normalized_data_chunk(int pressures[BATCH_LENGTH]) {
  int pressure, i = 0;
  while (i < BATCH_LENGTH && (scanf("%d", &pressure) == 1) &&
         pressure != NORMALIZED_INPUT_BATCH_EXIT_CODE) {
    if (pressure < INPUT_LOWER_BOUND ||
        pressure > INPUT_UPPER_BOUND) {
      continue;
    }
    pressures[i++] = pressure;
  }
  return i;
}
```

