reserved_words = {
    'print': 'PRINT'
}

tokens = [
    'STRING',
    'LPAREN',
    'RPAREN',
    'ID',
 ] + list(reserved_words.values())

 
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_STRING = r'\"(\\.|[^"\\])*\"'

def t_ID(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = reserved_words.get(t.value, 'ID')
    return t


def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

t_ignore  = ' \t'


def t_COMMENT(t):
    r'\#.*' # do nothing


def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)
