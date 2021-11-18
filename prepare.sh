#!/bash/sh

test -z "$1" && echo "Brak argumentu" && return 1
test -f "MakefileTemplate" || echo "Brak szablonu" || return 2

sed "s/{NAME OF SOURCE FILE}/$1/g" "MakefileTemplate" > "Makefile"

make build
