from ply.lex import lex


class Lexer:
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

    def t_ID(self, t):
        r'[a-zA-Z_][a-zA-Z_0-9]*'
        t.type = self.reserved_words.get(t.value, 'ID')
        return t

    def t_newline(self, t):
        r'\n+'
        t.lexer.lineno += len(t.value)

    t_ignore  = ' \t'

    def t_COMMENT(self, t):
        r'\#.*' # do nothing

    def t_error(self, t):
        print("Illegal character '%s'" % t.value[0])
        t.lexer.skip(1)

    def build(self, **kwargs):
        self.lexer = lex(module=self, **kwargs)

    def tokenize(self, text):
        self.lexer.input(text)

        while True:
            tok = self.lexer.token()
            if not tok: 
                break
            print(tok)
