# Igor Krzywda (275480)

## Instrukcja uzytkowania

```sh
source assignment.sh  # wszystkie definicje są dostępne w obecnym shellu
```

## Struktura sprawozdania

* skrypt
* output (testy są robione na plikach udostępnionych na stronie zadania)

## Operacje z `find`

`find` pozwala na znajdowanie plików po regexie z dodatkową funkcjonalnością
tj. usuwanie

```sh
function find_and_remove() {
	find . -name \*$1.\* -delete
}
```

```sh
$ find_and_remove test
```

Brak outputu - pliki z frazą `test` zostały usunięte

```sh
function find_phrase_from_recent_files() {
	find . -mtime $1 -type f | xargs grep $2
}

```sh
❯ find_phrase_from_recent_files -1d Instrukcja
./README.md:## Instrukcja uzytkowania
```

Fraza znaleziona w pliku, który został edytowany w przeciągu dnia

```sh
function find_newest() {
	find . -name \*$1.\* | xargs ls -lt | head -n1
}
```

```sh
❯ find_newest kubus
-rwxr--r--  1 igor  staff  10025  1 Feb 19:53 ./Pliki_do_pracy/kubus.text

❯ find . -name "*kubus*" | xargs ls -lt
-rwxr--r--  1 igor  staff  10025  1 Feb 19:53 ./Pliki_do_pracy/kubus.text
-rwxr--r--  1 igor  staff  10025  1 Feb 19:53 ./Pliki_do_pracy/Teksty/kubus.txt
-rwxr--r--  1 igor  staff  10025  1 Feb 19:53 ./Pliki_do_pracy/Foto_album/Backups/kubus.txt
```

Wyłuskany najnowszy plik z frazą


## Sed

Poniewaz wrappowanie samego `sed`a nie ma większego uzytku, ponizsza funkcja
zamienia frazę `Pooh` na `Winnie` - uzywam `|` jako delimiter z przyzwyczajenia -
wygodniej jest zamieniac  w ten sposób ściezki, jako nie trzeba escapowac `/`

```sh
function find_and_replace() {
	sed -i '' -e 's|Pooh|Winnie|g' **/*.txt
}
```

Grepowanie po uzyciu tej komendy pokazało wiele `Willie` - tyle, ile było 
`Pooh`

## Konwersja strony z pdfa do jpg

```sh
function pdf_page_to_jpg() {
	if [ "$#" != 3 ]; then
		echo "Usage: <pdf-filename> <page-number> <output-name>"
		return
	fi
	pdftk $1 cat $2 output /tmp/cut.pdf
	convert /tmp/cut.pdf $3
}
```

```sh
❯ pdf_page_to_jpg Pliki_do_pracy/relacja.pdf 1 out.jpg

❯ ls out.jpg
 out.jpg
```

Konwersja działa

## Zmiana wielkości liter w extensions na małe

```sh
function extension_to_lower_case_png() {
	for file in *.[pP][nN][gG]; do
		nname="${file%.*}.png"
		if [ "$nname" != "$file" ]; then
			mv "$file" "$nname"
		fi
	done

}

function extension_to_lower_case_jpg() {
	for file in *.[jJ][pP][gG]; do
		nname="${file%.*}.jpg"
		if [ "$nname" != "$file" ]; then
			cp "$file" "$nname"
		fi
	done
}
```

Uzywane w helperach w sekcji ponizej (`mv` zamienione na `cp`)

## Zipowanie obrazów ze normalizacją nazw

Jako nazwy tymczasowego foldeu uzywam losowo wygenerowanego klucza `uuid` w
directory `/tmp`. Tam przekopiowuję pliki `jpg/png` ze znormalizowaną nazwą.
Aby ułatwic zamianę nazw plików, tymczasowo przechodzę do docelowego folderu,
po czym wracam do poprzedniej ściezki `cd -`. Do archiwizacji uzywam `zip` 
(flaga `-j` ignoruje strukturę plików)

```sh
function copy_renamed_jpg() {
	file=$1
	tmpdir=$2

	nname="${file// /-}"
	nname="${nname%.*}.jpg"
	cp $file $tmpdir/$nname
}

function copy_renamed_png() {
	file=$1
	tmpdir=$2

	nname="${file// /-}"
	nname="${nname%.*}.png"
	cp $file $tmpdir/$nname
}

function rename_and_archive() {
	tmpdir=/tmp/$(uuidgen)
	cd $1
	mkdir $tmpdir
	for file in *.[jJ][pP][gG]; do
		copy_renamed_jpg "$file" "$tmpdir"
	done

	for file in *.[pP][nN][gG]; do
		copy_renamed_png "$file" "$tmpdir"
	done

	cd -

	zip -rj $2 $tmpdir
	rm -rf $tmpdir
}
```

```sh
❯ ls -l Pliki_do_pracy/Foto_album
drwxr-xr-x    - igor  1 Feb 19:53  Backups
drwxr-xr-x    - igor  1 Feb 20:25  Do_obrobki
.rw-r--r--  23k igor 10 Nov  2021  photo 2021-02-04_14-43-10.jpg
.rw-r--r-- 141k igor 10 Nov  2021  photo_2021-02-04_18-56-02.png
.rw-r--r--  86k igor 10 Nov  2021  photo_2021-03-11_23-24-27.jpg
.rw-r--r--  86k igor 10 Nov  2021  photo_2021-05-14_17-47-10.jpg
.rw-r--r--  57k igor 10 Nov  2021  photo_2021-07-26_16-03-07.jpg
.rw-r--r--  67k igor 10 Nov  2021  photo_2021-08-12_23-30-09.jpg
.rw-r--r--  88k igor 10 Nov  2021  photo_2021-08-17_06-54-40.jpg
.rw-r--r--  34k igor 10 Nov  2021  photo_2021-11-04_07-52-38.jpg
.rw-r--r--  54k igor 10 Nov  2021  test.png
drwxr-xr-x    - igor  1 Feb 20:54  Zbior_1

❯ rename_and_archive Pliki_do_pracy/Foto_album/ test.zip
~/workspace/pwr/air-cs/podstawy-programowania/laby/lab_week_7
  adding: photo_2021-05-14_17-47-10.jpg (deflated 1%)
  adding: photo_2021-08-12_23-30-09.jpg (deflated 2%)
  adding: photo_2021-03-11_23-24-27.jpg (deflated 1%)
  adding: photo-2021-02-04_14-43-10.jpg (deflated 0%)
  adding: photo_2021-11-04_07-52-38.jpg (deflated 1%)
  adding: test.png (deflated 9%)
  adding: photo_2021-08-17_06-54-40.jpg (deflated 3%)
  adding: photo_2021-02-04_18-56-02.png (deflated 1%)
  adding: photo_2021-07-26_16-03-07.jpg (deflated 6%)

❯ mkdir test
❯ cd test && unzip ../test.zip
❯ cd -
❯ ls -l test
.rw-r--r--  23k igor  2 Feb 09:52  photo-2021-02-04_14-43-10.jpg
.rw-r--r-- 141k igor  2 Feb 09:52  photo_2021-02-04_18-56-02.png
.rw-r--r--  86k igor  2 Feb 09:52  photo_2021-03-11_23-24-27.jpg
.rw-r--r--  86k igor  2 Feb 09:52  photo_2021-05-14_17-47-10.jpg
.rw-r--r--  57k igor  2 Feb 09:52  photo_2021-07-26_16-03-07.jpg
.rw-r--r--  67k igor  2 Feb 09:52  photo_2021-08-12_23-30-09.jpg
.rw-r--r--  88k igor  2 Feb 09:52  photo_2021-08-17_06-54-40.jpg
.rw-r--r--  34k igor  2 Feb 09:52  photo_2021-11-04_07-52-38.jpg
.rw-r--r--  54k igor  2 Feb 09:52  test.png

```
