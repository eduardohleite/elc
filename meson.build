project('elc', 'cpp',
        default_options : ['c_std=c17', 'cpp_std=c++17'])

inc = include_directories('src')

src = [
    'src/gen/parser.cpp',
	'src/gen/tokens.cpp',
	'src/builtin.cpp',
	'src/vm.cpp',
	'src/main.cpp'
]

executable('elc', sources: src, include_directories: inc, cpp_args: '-g')