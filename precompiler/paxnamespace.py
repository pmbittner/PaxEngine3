import re
import math


class CppScope:
    def __init__(self, name):
        self.name = name

    def getName(self):
        return self.name


def getNamespace(str_code, str_className):
    scopestack = []
    classPos = str_code.find(str_className)

    classDeclarationRegex = re.compile("(class|struct)\s" + str_className, re.MULTILINE)
    namespaceDeclarationRegex = re.compile("namespace\s(?P<Name>[a-zA-Z0-9]+)\s{", re.MULTILINE)

    match = classDeclarationRegex.search(str_code)
    classDeclarationPosition = match.start()

    while True: #code is not empty
        nextbracketopenedpos = str_code.find("{")
        nextbracketclosedpos = str_code.find("}")

        if nextbracketopenedpos == -1:
            nextbracketopenedpos = math.inf
        if nextbracketclosedpos == -1:
            nextbracketclosedpos = math.inf

        nearestbracketpos = min(nextbracketopenedpos, nextbracketclosedpos)
        if nearestbracketpos > classDeclarationPosition:
            break

        if (nextbracketopenedpos < nextbracketclosedpos): # scope opened
            scopename = ""

            namespacematch = namespaceDeclarationRegex.search(str_code)
            if namespacematch is not None:
                if namespacematch.end() == nextbracketopenedpos + 1:
                    # namespace found
                    scopename = namespacematch.group("Name").strip()

            scopestack.append(CppScope(scopename))
        else: # scrope closed
            scopestack.pop()

        step = nearestbracketpos + 1
        str_code = str_code[step:]
        classDeclarationPosition = classDeclarationPosition - step

    namespace = ""
    while scopestack:
        foundNs = scopestack.pop().name
        if len(namespace) > 0 and len(foundNs) > 0:
            foundNs = foundNs + "::"
        namespace = foundNs + namespace

    return namespace