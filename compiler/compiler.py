class Compiler:
    def __init__(self, lexer):
        self.lexer = lexer
        self.lexer.build()
    
    def compile(self, fname):
        with open(fname) as f:
            raw = f.read()
       
        self.lexer.tokenize(raw)