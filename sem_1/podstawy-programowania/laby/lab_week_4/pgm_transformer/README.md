# Igor Krzywda (275480)

## Specyfikacja

* Wejście: plik pgm (wersja ASCII)
* Wyjście: plik pgm (wersjia ASCII)

Program wczytuje obrazy pgm i aplikuje na nie transformacje
(inwersja, przesunięcie poziomu szarości, rozciągnięcie histogramu, progowanie).
Uzytkownik wchodzi w interakcję z programem poprzez interfejs CLI.

## Handlowanie plików PGM

> **Reprezentacja obrazu**

Obraz pgm jest reprezentowany jako struktura trzymająca w sobie dynamiczą
tablicę z samym obrazem oraz pozostałe dane o obrazie w pozostałych polach

```c
typedef struct {
  int width, height, bit_depth, contents_length;
  int *contents;
} PGMImage;
```

Biorąc pod uwagę, że obrazy mogą przyjmować rózne rozmiary, a informacja
o wymiarach obrazu jest explicite potrzebna jedynie przy zapisywaniu pliku,
dynamiczna tablica jest bardziej adekwatną reprezentacją danych
(dwuwymiarowa tablica dynamiczna wnosi niepotrzebną złozoność).

> **Wczytywanie pliku**

Wczytywanie pliku alokuje nowy obiekt `PGMImage` po czym wypełnia jej pola 
pliku pgm

* header pliku:

  * sprawdzenie istnienia pliku i walidacja wersji pliku pgm (`P2` oznacza typ plain)
  * pominięcie komentarza
  * zczytanie wysokości, szerokości i bit depth obrazu

```c
int read_header(FILE *input_stream, PGMImage *output) {
  char buffer[LINE_WIDTH], comment_buffer;
  int width, height, bit_depth;
  if (fgets(buffer, LINE_WIDTH, input_stream) == NULL || strcmp(buffer, "P2")) {
    return 1;
  }

  while ((comment_buffer = fgetc(input_stream)) == '#' &&
         fgets(buffer, LINE_WIDTH, input_stream))
    ;

  ungetc(comment_buffer, input_stream);

  if (fscanf(input_stream, "%d %d %d", &height, &width, &bit_depth) != 3) {
    return 1;
  }

  output->height = height;
  output->width = width;
  output->bit_depth = bit_depth;

  return 0;
}
```

* wczytanie obrazu

  * zaalokowanie tablicy o rozmiarze obrazy (znana z headera)
  * zapisanie zawartości walidując wszystkie punkty jako liczby całkowite

```c
int *load_contents(FILE *input_stream, int length) {
  int *contents = malloc(sizeof(int) * length), point;

  if (contents == NULL) {
    return NULL;
  }

  for (int i = 0; i < length; ++i) {
    if (!fscanf(input_stream, "%d ", &point)) {
      free(contents);
      return NULL;
    }
    contents[i] = point;
  }
  return contents;
}
```

> **Zapisywanie do pliku**

* zapisanie headera
* zapisanie wartości - ze względu na specyfikację pgm (max. 70 znaków na linię),
break-line jest zapisywany co 11 wartości, kazda z których ma co najmniej
3 znaki

## Operacje na obrazach

Wszystkie zaimplementowane operacje mają wspólny komponent iterowania przez
ponkty w obrazie i aplikowanie transformacji dla kazdego punktu.

```c
#define VALUES_PER_LINE 11

int write_to_file(FILE *write_stream, PGMImage *source) {
  fprintf(write_stream, "P2\n%d %d\n%d\n", source->height, source->width,
          source->bit_depth);
  int length = source->width * source->height;
  for (int i = 0; i < length; ++i) {
    if (!(i % VALUES_PER_LINE)) {
      fputc('\n', write_stream);
    }
    fprintf(write_stream, " %-3d ", source->contents[i]);
  }
  return 0;
```

> **Inwersja**

Zamienienie wartosci na wartosc odwrotną

```c
int invert_image(PGMImage *source) {
  int length = source->height * source->width;
  int new_val;

  for (int i = 0; i < length; ++i) {
    new_val = source->bit_depth - source->contents[i];
    source->contents[i] = new_val;
  }
  return 0;
}
```

> **progowanie**

dla wartosci ponizej progu mapowanie na 0, w.p.p na maksymalną wartośc

```c
int thresholding(PGMImage *source, int threshold) {
  int length = source->height * source->width;
  int new_val;

  for (int i = 0; i < length; ++i) {
    new_val = source->contents[i] < threshold ? 0 : source->bit_depth;
    source->contents[i] = new_val;
  }
  return 0;
}
```

> **wyrównanie histogramu**

wyrównanie kontrastu - zakres wartosci wynosi od 0 do maksymalnej wartosci

```c
int histogram_equilization(PGMImage *source) {
  int length = source->height * source->width;
  int min_val = source->bit_depth, max_val = 0;
  int current_val;
  float coefficient, new_val;

  for (int i = 0; i < length; ++i) {
    current_val = source->contents[i];
    if (current_val < min_val) {
      min_val = current_val;
    }
    if (current_val > max_val) {
      max_val = current_val;
    }
  }

  coefficient = source->bit_depth / (max_val - min_val);

  for (int i = 0; i < length; ++i) {
    current_val = source->contents[i];
    new_val = (current_val - min_val) * coefficient;

    source->contents[i] = (int)new_val;
  }
  return 0;
}
```

> **przesunięcie zakresu szarości**

dla wartosci ponizej progu czerni mapowanie do 0, powyzej progu bieli - 
poziom bieli, w.p.p. mapowanie na przedzial

```c
int gray_range_shift(PGMImage *source, int black_lvl, int white_lvl) {
  float mid_coeff = source->bit_depth / (black_lvl * white_lvl);
  int current_val, new_val;

  for (int i = 0; i < source->contents_length; ++i) {
    current_val = source->contents[i];

    if (current_val < black_lvl) {
      new_val = 0;
    } else if (current_val > white_lvl) {
      new_val = white_lvl;
    } else {
      new_val = (int)((current_val - black_lvl) * mid_coeff);
    }
    source->contents[i] = new_val;
  }
  return 0;
}
```

## CLI

>**Sesja i komendy**

CLI ma 8 komend: `"load", "save",  "exit", "display","invert", "equalize", "shift", "threshold"`,
które mogą brac argumenty, przykładowo: `load foo.pgm` załaduje plik do sesji. Sesja
trzyma obraz, ściezki do source i targertowego pliku, argumenty, flagi i bufor na błędy

```c
typedef struct {
  char source_path[MAX_PATH_LENGTH];
  char target_path[MAX_PATH_LENGTH];
  PGMImage *pgm_image;
  char error_buffer[ERROR_BUFFER_LENGTH];
  char *args[MAX_ARG_COUNT];
  int _argc;
  int is_source, is_target, is_error;
} Session;
```

Komendy są tablicą stringów, która jest mapowana przez enuma, np. aby wyciągnąc
`load` z `COMMANDS` wystarczy uzyc `COMMANDS[LOAD]`

```c
typedef enum Commands {
  LOAD_SOURCE_FILE,
  SAVE_TO_FILE,
  EXIT,
  DISPLAY,
  INVERT,
  EQUALIZE,
  SHIFT,
  THRESHOLD,
} Commands;


const char *COMMANDS[COMMAND_COUNT] = {
    "load", "save",  "exit", "display","invert", "equalize", "shift", "threshold"
};
```

> **główna pętla**

CLI działa w pętli, w której dzieją się następujące rzeczy:

* zczytywanie komendy i wyświetlanie status line'a

```c

  int display_status_line(Session *session) {
    if (session->is_source) {
        printf("(%s) ", session->source_path);
    }
    if (session->is_target) {
        printf("-> (%s) ", session->target_path);
    }
    printf(">>> ");
    return 0;
}
  
  while (!display_status_line(&session) && fgets(buffer, LINE_BUFFER_LENGTH, stdin)) { ... }
```

* ztokenizowanie i wczytanie komendy
  * tokenizacja jest wykonywana z uzyciem `strtok` z delimiterem spacji i new-line
  * argumenty są kopiowane do sesji

```c
    command_token = strtok(buffer, " \n");

    if (command_token == NULL) {
      continue;
    }

    for (arg_i = 0; arg_i < MAX_ARG_COUNT &&
           (current_token = strtok(NULL, " \n")) != NULL;
         ++arg_i) {
        strcpy(session.args[arg_i], current_token);
    }
    session._argc = arg_i;
```

* parsowanie komendy
  * znalezienie indeksu w tablicy komend odpowiadający wartości enuma komend

```c
Commands parse_command(char *token) {
  for (int i = 0; i < COMMAND_COUNT; ++i) {
    if (!strcmp(token, COMMANDS[i])) {
      return i;
    }
  }
  return -1;
}

switch (parse_command(command_token)) { ... }
```

* wywołanie odpowiedniej funkcji z argumentami

>przykład funkcji unarnej ze stringiem jako argument

```c
case LOAD_SOURCE_FILE: {
  if (session._argc < 1) {
      strcpy(session.error_buffer, "load file command takes one argument");
      session.is_error = 1;
      break;
  }
  if (load_file(&session, session.args[0])) {
      sprintf(session.error_buffer, "failed to load file: %s", session.args[0]);
      session.is_error = 1;
      break;
  }
  break;
}
```
  
>przykład funkcji z wieloma argumentami z castowaniem typów

`strtol` zamienia string'a na liczbę całkowitą o zadanej bazie

```c
int _gray_range_shift(Session *session) {
    int black_lvl = strtol(session->args[0], (char **)NULL, 10);
    int white_lvl = strtol(session->args[1], (char **)NULL, 10);

    return gray_range_shift(session->pgm_image, black_lvl, white_lvl);
}

...

case SHIFT: {
  if (session._argc < 2) {
      strcpy(session.error_buffer, "load file command takes two arguments");
      session.is_error = 1;
      break;
  }
  if (_gray_range_shift(&session)) {
      sprintf(session.error_buffer, "failed to load file: %s", session.args[0]);
      session.is_error = 1;
      break;
  }
  break;
}
```


* handlowanie erorr'ów

jeśli pojawi się error, zostanie wyprintowany

```c
if (session.is_error) {
    printf("ERROR: %s\n", session.error_buffer);
    session.is_error = 0;
}
```

## Testy transformacji

Testy są zawarte w pliku `tests/tests.c`. Testy są zautowamyzowane i wykorzystują
fixture'y obiektu `PGMImage` ze stałą zawartością, aby wydajnie przeprowadzac 
testy jednostkowe.

```c
PGMImage *ranged_image_fixture(int range_start, int range_end) {
  int size = range_end - range_start + 1;
  PGMImage *image_fixture = malloc(sizeof(PGMImage));
  image_fixture->contents = malloc(sizeof(int) * size);

  image_fixture->contents_length = size;
  image_fixture->width = IMAGE_FIXTURE_WIDTH;
  image_fixture->height = size / IMAGE_FIXTURE_WIDTH;
  image_fixture->bit_depth = IMAGE_FIXTURE_BIT_DEPTH;

  for (int i = 0; i < size; ++i) {
    image_fixture->contents[i] = i + range_start;
  }

  return image_fixture;
}

PGMImage *full_range_image_fixture() {
  PGMImage *image_fixture = malloc(sizeof(PGMImage));
  image_fixture->contents = malloc(sizeof(int) * IMAGE_FIXTURE_CONTENT_LENGTH);

  image_fixture->contents_length = IMAGE_FIXTURE_CONTENT_LENGTH;
  image_fixture->width = IMAGE_FIXTURE_WIDTH;
  image_fixture->height = IMAGE_FIXTURE_HEIGHT;
  image_fixture->bit_depth = IMAGE_FIXTURE_BIT_DEPTH;

  for (int i = 0; i < IMAGE_FIXTURE_CONTENT_LENGTH; ++i) {
    image_fixture->contents[i] = i;
  }

  return image_fixture;
}

PGMImage *single_value_image_fixture(int value) {
  PGMImage *image_fixture = malloc(sizeof(PGMImage));
  image_fixture->contents = malloc(sizeof(int));

  image_fixture->contents[0] = value;
  image_fixture->contents_length = 1;
  image_fixture->bit_depth = IMAGE_FIXTURE_BIT_DEPTH;
  image_fixture->width = 1;
  image_fixture->height = 1;

  return image_fixture;
}
```

Dodatkowo zdefiniowałem makro drukujące nazwę funkcji po przejściu testu, 
zatem komunikat `<nazwa testu>...PASSED` oznacza przejście testu. Wszytkie
testy przeszły, testy nalezy czytac nastepujaco:
* `<prefix>_fixture` - setup
* wywołanie transformaci
* wyrazenie w asersji - sprawdzany warunek

```c
#define PRINT_SUCCESS() printf("%s...PASSED\n", __func__)
```

* test inwersji - jeden case - sprawdzenie czy cały zakres został odwrócony

```c
void test_invert() {
  PGMImage *image = full_range_image_fixture();

  invert_image(image);

  for (int i = 0; i < IMAGE_FIXTURE_CONTENT_LENGTH; ++i) {
    assert(image->contents[i] == IMAGE_FIXTURE_BIT_DEPTH - i);
  }
  PRINT_SUCCESS();
}
```

* test przeusnięcia szarości - w tych testach uzywam obrazu z jednym pikselem jako
fiksturę jako transformacja nie polega na innych wartościach w obrazie




>* ponizej poziomu czerni 
>```c 
> void test_gray_range_shift_black_range() {
>   PGMImage *image = single_value_image_fixture(10);
>   gray_range_shift(image, 20, 200);
>   assert(image->contents[0] == 0);
> 
>   PRINT_SUCCESS();
> }
> ```
> 
> * powyzej poziomu bieli
> 
> ```c
> void test_gray_range_shift_white_range() {
>   PGMImage *image = single_value_image_fixture(100);
>   gray_range_shift(image, 20, 90);
>   assert(image->contents[0] == 90);
> 
>   PRINT_SUCCESS();
> }
> ```
> 
> * wartośc pośrednia - jako wartośc docelową wybieram wartosc wyliczoną z manualnie
>   podstawionymi parametrami
> 
> ```c
> void test_gray_range_shift_mid_value() {
>   PGMImage *image = single_value_image_fixture(100);
>   int target_value = (int)((50 - 10) * (float)(IMAGE_FIXTURE_BIT_DEPTH / (10 * 100)));
>   gray_range_shift(image, 10, 100);
>   assert(image->contents[0] == target_value);
> 
>   PRINT_SUCCESS();
> }
> ```

* testy wyrównania histogramu

> * test końców przedziału - uzyta fixture'y z zakresem warosci
> ```c
> void test_histogram_equalization_range_ends() {
>   PGMImage *image = ranged_image_fixture(100, 150);
>   
>   histogram_equilization(image);
>   assert(image->contents[0] == 0);
>   assert(image->contents[image->contents_length - 1] == IMAGE_FIXTURE_BIT_DEPTH);
> 
>   PRINT_SUCCESS();
> }
> ```
>
> * test srodku przedzialu - srodkowa wartosci wejsciowego przedzialu powinna mapowac
> się do srodka przedzialu wyjsciowego `(0, BIT_DEPTH)`
>```c
>void test_histogram_equalization_mid_range() {
>  PGMImage *image = ranged_image_fixture(0, 2);
>  histogram_equilization(image);
>
>  assert(image->contents[1] == IMAGE_FIXTURE_BIT_DEPTH / 2);
>  PRINT_SUCCESS();
>}
>```


* testy progowania

> * test dla wartosci ponizej progu - mapowanie na 0
>
>```c
>void test_thresholding_below() {
>  PGMImage *image = single_value_image_fixture(100);
>  thresholding(image, 105);
>
>  assert(image->contents[0] == 0);
>  PRINT_SUCCESS();
>}
>```
>
>* test dla wartosci powyzej progu - mapowanie na BIT_DEPTH
>
>```c
>void test_thresholding_above() {
>  PGMImage *image = single_value_image_fixture(110);
>
>  thresholding(image, 105);
>  assert(image->contents[0] == IMAGE_FIXTURE_BIT_DEPTH);
>  PRINT_SUCCESS();
>}
>```
