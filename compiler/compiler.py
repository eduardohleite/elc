class Compiler:
    def __init__(self, lexer):
        self.lexer = lexer
    
    def compile(self, fname):
        with open(fname) as f:
            raw = f.read()
        
        self.lexer.input(raw)

        while True:
            tok = self.lexer.token()
            if not tok: 
                break
            print(tok)