gen-lang:
	bison -d -o src/gen/parser.cpp src/lang/parser.y
	lex -o src/gen/tokens.cpp src/lang/tokens.l

build: gen-lang
	mkdir -p out/release
	g++ -Isrc -std=c++17 \
		-Ofast -o out/release/elc \
		src/gen/parser.cpp \
		src/gen/tokens.cpp \
		src/builtin.cpp \
		src/vm.cpp \
		src/main.cpp

debug-build: gen-lang
	meson out/debug
	ninja -C out/debug

clean:
	rm -rf out/*
	rm -rf src/gen/*