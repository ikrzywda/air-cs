# Igor Krzywda (275480)

## Specyfikacja

* Wejście: plik pgm (wersja ASCII)
* Wyjście: plik pgm (wersjia ASCII)

Program wczytuje obrazy pgm i aplikuje na nie transformacje
(inwersja, przesunięcie poziomu szarości, rozciągnięcie histogramu, progowanie).
Uzytkownik wchodzi w interakcję z programem poprzez interfejs CLI.

## Handlowanie plików

> **Reprezentacja obrazu**

Obraz pgm jest reprezentowany jako struktura trzymająca w sobie dynamiczą
tablicę z samym obrazem oraz pozostałe dane o obrazie w pozostałych polach.

```c
typedef enum {
  P2,
  P3
} PGMType;

typedef struct {
  int width, height, bit_depth, contents_length;
  PGMType file_type;
  int *contents;
} Image;
```

> **Wczytywanie pliku**

Wczytywanie pliku alokuje nowy obiekt `Image` po czym wypełnia jej pola
informacjami o pliku - w przypadku, kiedy obraz jest typy ppm, alokowana 
pamięc na zawartosc obrazu jest trzy razy wieksza

* header pliku:

  * sprawdzenie istnienia pliku i walidacja wersji pliku pgm (`P2` lub `P3` oznacza typ plain)
  * pominięcie komentarza
  * zczytanie wysokości, szerokości i bit depth obrazu

```c
int read_header(FILE *input_stream, Image *output) {
  char buffer[LINE_WIDTH], comment_buffer;
  PGMType file_type;
  int width, height, bit_depth;
  if (fgets(buffer, LINE_WIDTH, input_stream) == NULL) {
    return 1;
  }

  if (!strcmp(buffer, "P2\n")) {
    file_type = P2;
  } else if (!strcmp(buffer, "P3\n")) {
    file_type = P3;
  } else {
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
  output->file_type = file_type;

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

> **Konwersja z ppm do pgm**

Operacje na obrazach są wykonywane na obrazach typu `P2` - konwersja polega
na zaalokowaniu kopii obiektu reprezentującego plik ppm i podmienienie danych 
i zawartosci na pgm (poprzez wyciągnięcie sredniej z wartosci RGB)

```c
Image *ppm_to_pgm(Image *ppm) {
  assert(ppm->file_type == P3);
  
  Image *pgm = malloc(sizeof(Image));
  memcpy(pgm, ppm, sizeof(Image));



  int *pgm_contents = malloc(sizeof(int) * ppm->contents_length);
  int rgb_sum = 0, rgb_mean;

  pgm->contents = pgm_contents;
  pgm->file_type = P2;

  for (int i = 0; i < ppm->contents_length; ++i) {
    for (int j = 0; j < 3; ++j) {
      rgb_sum += ppm->contents[(i * 3) + j];
    }
    pgm_contents[i] = rgb_sum / 3;
    rgb_sum = 0;
  }
  return pgm;
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

Program zczytuje argumenty wywołania i wczytuje je do obiektu sesji.
Sesja trzyma w sobie sciezki inputu i outputu, flagę do wyswietlenia i listę
obiektów operacji - typ i lista argumentów

```c
typedef enum  {
  INVERT,
  EQUALIZE,
  SHIFT,
  THRESHOLD,
} Transformation;

typedef struct {
  Transformation transformation;
  char *args[MAX_ARG_COUNT];
} Operation;

typedef struct {
  char source_path[MAX_PATH_LENGTH];
  char target_path[MAX_PATH_LENGTH];
  int display_flag;
  int operation_count;
  Image *image;
  Operation operations[MAX_OPERATION_COUNT];
} Session;
```

>**Wykonanie sesji**

Sesja wykonuje się następująco:

* wczytaj plik
* wykonaj operacje (iteracja po operacjach)
* zapisz plik
* wyświetl (opcjonalnie)

```c
int run_session(Session *session) {

  FILE *source_image_stream = fopen(session->source_path, "r");
  int arg_1, arg_2;


  if (source_image_stream == NULL) {
    fclose(source_image_stream);
    return 1;
  }

  session->image = new_image(source_image_stream);
  fclose(source_image_stream);
  if (session->image->file_type == P3) {
    session->image = ppm_to_pgm(session->image);
  }

  for (int i = 0; i < session->operation_count; ++i) {
    switch (session->operations[i].transformation) {
      case INVERT: {
        invert_image(session->image);
        break;
      }
      case SHIFT: {
        arg_1 = strtol(session->operations[i].args[0], (char **)NULL, 10);
        arg_2 = strtol(session->operations[i].args[1], (char **)NULL, 10);
        gray_range_shift(session->image, arg_1, arg_2);
        break;
      }
      case EQUALIZE: {
        histogram_equilization(session->image);
        break;
      }
      case THRESHOLD: {
        arg_1 = strtol(session->operations[i].args[0], (char **)NULL, 10);
        thresholding(session->image, arg_1);
        break;
      }
    }
  }

  if (save_to_file(session)) {
    return 1;
  }

  if (session->display_flag) {
    display(session);
  }

  return 0;
}
```

>**Inicjacja i wywołanie (main)**

Sesja jest inicjowana poprzez zczytywanie argumentów uzywając funkcji `getopt`
z `unistd.h`. Mamy dwa przypadki:

* argument bez wartości

    * ustawienie flagi w Session (przypadek display)

    * stworzenie pustego obiektu operacji z typem (przypadek wywołania negatywu)

* argument z wartościami

    * jedna wartośc - skopiowanie `optarg` (extern `getopt`) (np. wczytanie pliku)

    * wiele wartosci - iterowanie po `argv` do momentu spotkania `-` 
    (workaround - `getopt` nie wspiera wielu argumentów (https://stackoverflow.com/questions/3939157/c-getopt-multiple-value)) 
    np. przesunięcie szarości


obiekt sesji jest statycznie zaalokowany, łącznie z tablicą operacji.

```c
int main(int argc, char **argv) {

  Session session;
  Operation *operation;
  int c;

  session.display_flag = 0;
  session.operation_count = 0;

  while ((c = getopt(argc, argv, "i:o:dnt:s:e")) != -1) {
    switch (c) {
    case 'i': {
      strcpy(session.source_path, optarg);
      break;
    }
    case 'o': {
      strcpy(session.target_path, optarg);
      break;
    }
    case 'd': {
      session.display_flag = 1;
      break;
    }
    case 'n': {
      session.operations[session.operation_count].transformation = INVERT;
      session.operation_count++;
      break;
    }
    case 't': {
      init_operation(&session.operations[session.operation_count], 1);
      session.operations[session.operation_count].transformation = THRESHOLD;
      strcpy(session.operations[session.operation_count].args[0], optarg);
      session.operation_count++;
      break;
    }
    case 's': {
      init_operation(&session.operations[session.operation_count], 2);
      session.operations[session.operation_count].transformation = SHIFT;
      optind--;
      for (int i = 0; optind < argc && *argv[optind] != '-' && i <= 2;
           optind++) {
        strcpy(session.operations[session.operation_count].args[i++],
               argv[optind]);
      }
      session.operation_count++;
      break;
    }
    case 'e': {
      init_operation(&session.operations[session.operation_count], 1);
      session.operations[session.operation_count].transformation = EQUALIZE;
      strcpy(session.operations[session.operation_count].args[0], optarg);
      session.operation_count++;
      break;
    }
    }
  }

  run_session(&session);

  return 0;
}
```
