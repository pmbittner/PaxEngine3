class PaxProperty:
    def __init__(self, name, ismultiple):
        self.name = name
        self.ismultiple = ismultiple
        self.nameWithoutNamespaces = name.replace("::", "__ns__")


class PaxGenerationData:
    def __init__(self):
        self.includes = []
        self.properties = []
        self.inheritances = []

    def clearPropertyInfo(self):
        self.properties = []
        self.inheritances = []

class PaxPropertyTreeHandle:
    def __init__(self, str_macroname, str_container, includes, attachedEventName, detachedEventName):
        self.macro = str_macroname
        self.container = str_container
        self.includes = includes
        self.attachedEventName = attachedEventName
        self.detachedEventName = detachedEventName

def getCppTypeOf(var):
    return "std::type_index(typeid(" + var + "))"