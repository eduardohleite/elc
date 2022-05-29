gen-lang:
	bison -d -o src/gen/parser.cpp src/lang/parser.y
	lex -o src/gen/tokens.cpp src/lang/tokens.l

build: gen-lang
	mkdir -p out
	g++ -Isrc -o out/elc src/gen/parser.cpp src/gen/tokens.cpp src/main.cpp

clean:
	rm -f out/*
	rm -f src/gen/*