>## Autor: Igor Krzywda (275480)
>### Data Wykonania: 29.11.22

## Kod źródłowy


## Core

## Dane wejściowe

Dane wejściowe są zczytywane ze strumienia `stdin` w następującym formacie:

```txt
val
val
val
val
val
99
```

gdzie `val` jest zdefiniowana następująco w mbnf:

```txt
val = digit {digit}["." digit{digit}]
digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | 9
```

a `99` jest kodem terminacji wejścia.

## Implementacja

>### Zczytywanie bloku danych

Blok danych jest zczytywany za pomocą funkcji `scan_normalized_data`, która zwraca
`0` po zczytaniu bloku zakończonym sukcesem lub 1 w przeciwnym przypadku (natrafienie
na wartość terminującą wejście lub brak danych wejściowych).

Dane wejściowe są zczytywane w grupach zawierających maksymalnie liczbę elementów, która jest
zdefiniowana w stałej `BATCH_LENGTH`. Wartości są zczytywane w głównej pętli funkcji
dopóki bufor wyjściowy `readings` nie jest wypełniony oraz wartość została poprawnie 
zczytana z `stdin`. W przypadu natrafienia na kod wyjścia `exit_flag` jest ustawiona na `1` i
zachodzi wyjście z pętli. Jeśli wartości jest spoza zakresu wartości, to jest pomijana.

Zwracana jest alternatywa `exit_flag` i `!i`, która jest prawdą w przypadku nie zczytania
żadnych warości lub natrafiono na `EXIT_CODE`. Do tablicy wyjściowej są poprawne wartości z 
`EXIT_CODE` na ostatnim miejscu.

```c
int scan_normalized_data_chunk(float readings[BATCH_LENGTH]) { 
  float pressure;
  int i = 0, exit_flag = 1;

  while (i < BATCH_LENGTH && (scanf("%f", &pressure) == 1)) {
    if (pressure == EXIT_CODE) {
      exit_flag = 0;
      break;
    }
    if (pressure > UPPER_VALUE_THRESHOLD || pressure < LOWER_VALUE_THRESHOLD) continue;
    readings[i] = pressure;
    ++i;
  }
  readings[i] = EXIT_CODE;
  return (exit_flag || !i);
}
```

>### Wyliczanie przecięć z zerem

Liczba przecięć z zerem jest wyliczana funkcją `compute_frequency_normalized_input`.
Do funkcji przekazywany jest wstaźnik do tablicy z danymi wejściowymi.

Główna pętla przechodzi po danych wejściowych. Jeśli jedna z wartości jest
kodem wyjścia, pętla się kończy. Przecięcie jest stwierdzane w przypadku, kiedy
warość logiczna różności od zera dwóch sąsiadujących wartości jest inna - warunek
`!(data_batch[i] < 0) != !(data_batch[i + 1] < 0)` jest równoważny
`data_batch[i] < 0 XOR data_batch[i + 1] < 0`.

```c
int compute_frequency_normalized_input(float data_batch[BATCH_LENGTH]) {
  int change_count = 0;
  for (int i = 0; i < BATCH_LENGTH; ++i) {
    if (data_batch[i] == EXIT_CODE || data_batch[i+1] ==  EXIT_CODE) {
      break;
    }
    if (!(data_batch[i] < 0) != !(data_batch[i + 1] < 0)) {
      ++change_count;
    }
  }
  return change_count;
}
```

>### Driver code

Program zczytuje dane używając pozyżej opisanej funkcji `scan_normalized_data_chunk` i warunkiem
stopu jest zwrócenie `1` przez tę funkcję.

W każdym obrocie pętli jest wyliczana liczba przecięć zer i w przypadku kiedy wartości
są spoza predefiniowanego przedziału (zdefiniowanych w stałych `LOWER_FREQUENCY_THRESHOLD` oraz
`UPPER_FREQUENCY_THRESHOLD`) do strumienia wyjścia jest przekazywany wiadomość.

```c
void read_normalized_data() {
  float pressures[BATCH_LENGTH], frequency;
  while (!scan_normalized_data_chunk(pressures))
    frequency = compute_frequency_normalized_input(pressures);
    print_frequency(frequency);
  }
```

>### Definicja stałych

Stała `BATCH_LENGTH` jest owrapowana aby umożliwić przekazywanie `BATCH_LENGTH`
podczas kompilacji - w przypadku, gdy nie jest podana `BATCH_LEGTH` wynosi 99.

```c
#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef BATCH_LENGTH
  #define BATCH_LENGTH 99
#endif

#define LOWER_FREQUENCY_THRESHOLD 8
#define UPPER_FREQUENCY_THRESHOLD 14
#define NORMALIZED_INPUT_DURATION 10

#define LOWER_VALUE_THRESHOLD -10
#define UPPER_VALUE_THRESHOLD 10

#define EXIT_CODE 99

#endif
```

## Testy


Gdzie `input` to ścieżka do pliku z danymi wejściowymi

>## Testy

Do testowania (poza ostatnim) używana jest funkcja `print_frequency_debug` 
działająca jak poniżej w miejsce drukowania zgodnego ze specyfikacją zadania w
sekcji *Driver Code*

```c
void print_frequency_debug(float frequency) {
  printf("frequency: %f\t", frequency);
  if (frequency < LOWER_FREQUENCY_THRESHOLD) {
    printf("[ERROR] frequency too low");
  }
  if (frequency > UPPER_FREQUENCY_THRESHOLD) {
    printf("[ERROR] frequency too high");
  }
  putchar('\n');
}
```

### Zczytywanie jednego bloku danych i wyliczenie wartości

* Dane wejściowe:

```txt
5
-5
-3
1
-1
```

Przewidywana wartość częstotliwości to `3` przecięcia zera oraz komunikat o wartości
spoza przedziału.

* Wynik testu:

```bash
frequency: 3.000000	[ERROR] frequency too low
```

Program poprawnie odczytał jedną grupę wartości i wyliczył jej wartość


### Terminowanie wejścia

* Dane wejściowe:

```txt
5
-5
-3
1
-1
99
1
23
-2
23
```

Przewidywana wartość dla testu to wyjście jak w teście pierwszym

* Wynik testu (wielkość grupy: 5):

```bash
frequency: 3.000000	[ERROR] frequency too low
```

Program poprawnie zakończył zczytywanie wartości po odczytaniu terminującej
kodu terminującego wejście.


### Brak przecięć

* Dane wejściowe

```txt
-5
-5
-3
-1
-1
```

Przewidywana wartość dla testu to `0`

* Wynik testu (wielkość grupy: 5):

```bash
frequency: 0.000000	[ERROR] frequency too low
```

Program poprawnie wyliczył przypadek bez przecięć.

### Zczytywanie wielu bloków danych

* Dane wejściowe

```txt
1
-1
-1
-1
-1

1
-1
-1
-1
-1

1
-1
1
1
-1

1
-1
1
-1
1
```

Przewidywany wynik dla testu to `1,2,3,4` dla odpowiednich grup danych

* Wynik testu (wielkość grupy: 5):

```bash
frequency: 1.000000	[ERROR] frequency too low
frequency: 1.000000	[ERROR] frequency too low
frequency: 3.000000	[ERROR] frequency too low
frequency: 4.000000	[ERROR] frequency too low
```

Test przeszedł pomyślnie - program poprawnie wyliczył liczby przecięć zer dla 
każdej grupy.

### Pomijanie wartośći spoza przedziału

* Dane wejściowe

```txt
1
100
-1
-100
1500
101
11
-1
-1
-1
```

Przewidywany wynik dla testu to jeden komunikat z wartoścą `1`

* Wynik testu (wielkość grupy: 5):

```bash
frequency: 1.000000	[ERROR] frequency too low
```

Test przeszedł pomyślnie - program poprawnie odfiltrował wartości spoza 
przediału.

### Test wersji bez printowania informacji debugowej

* Dane wejściowe

```txt
-3.98
7.12
-9.12
9.57
-8.60
7.63
-4.35
2.01
-1.65
4.38

-7.23
8.54
-8.27
7.29
-4.35
-1.47
1.41
4.88
7.59
9.00
```
Przewidywany wynik dla testu to jeden komunikat z błędem


* Wynik testu (wielkość grupy: 10):

```bash
[ERROR] frequency too low
```

Test przeszedł pomyślnie - pierwsza grupa miała `9` przecięć, a druga
`5` - zatem był przewidywany jeden komunikat

