gen-lang:
	bison -d -o src/gen/parser.cpp src/lang/parser.y
	lex -o src/gen/tokens.cpp src/lang/tokens.l

build: gen-lang
	mkdir -p out/release
	g++ -Isrc -std=c++17 \
		-O3 -o out/release/elc \
		src/gen/parser.cpp \
		src/gen/tokens.cpp \
		src/builtin.cpp \
		src/vm.cpp \
		src/main.cpp

debug-build: gen-lang
	mkdir -p out/debug
	g++ -Isrc -std=c++17 \
		-g -o out/debug/elc \
		src/gen/parser.cpp \
		src/gen/tokens.cpp \
		src/builtin.cpp \
		src/vm.cpp \
		src/main.cpp

clean:
	rm -rf out/*
	rm -rf src/gen/*