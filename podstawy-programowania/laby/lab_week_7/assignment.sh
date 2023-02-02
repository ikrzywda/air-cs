#!/bin/bash

function find_and_remove() {
	find . -name \*$1.\* -delete
}

function find_phrase_from_recent_files() {
	find . -mtime $1 -type f | xargs grep $2
}

function find_newest() {
	find . -name \*$1.\* | xargs ls -lt | head -n1
}

function find_and_replace() {
	sed -i '' -e 's|Pooh|Winnie|g' **/*.txt
}

function pdf_page_to_jpg() {
	if [ "$#" != 3 ]; then
		echo "Usage: <pdf-filename> <page-number> <output-name>"
		return
	fi
	pdftk $1 cat $2 output /tmp/cut.pdf
	convert /tmp/cut.pdf $3
}

# OP: https://unix.stackexchange.com/questions/19654/how-do-i-change-the-extension-of-multiple-files

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
		copy_rendsafsdafamed_jpg "$file" "$tmpdir"
	done

	for file in *.[pP][nN][gG]; do
		copy_renamed_png "$file" "$tmpdir"
	done

	cd -

	zip -rj $2 $tmpdir
	rm -rf $tmpdir
}
