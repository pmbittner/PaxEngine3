
def createindent(level):
    return "    " * level


class FileWriter:
    def __init__(self, file, linebreak="\n"):
        self.file = file
        self.lb = linebreak
        self.indentCount = 0
        self.indent = createindent(self.indentCount)

    def incrementIndent(self):
        self.indentCount += 1
        self.indent = createindent(self.indentCount)

    def decrementIndent(self):
        self.indentCount -= 1
        self.indent = createindent(self.indentCount)

    def writeLine(self, text):
        self.file.write(self.indent + text + self.lb)

    def close(self):
        self.file.close()