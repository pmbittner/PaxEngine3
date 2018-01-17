import os
import re

EntityComponentRegex = ".*(PAX_ENTITYCOMPONENT|PAX_ENTITYCOMPONENT_DERIVED)\((\s*[a-zA-Z]+\s*)(,\s*[a-zA-Z]+\s*)*\)\s+(class|struct)\s+(?P<Type>[a-zA-Z]+)\s*:\s*(?P<Parents>([a-zA-Z\s]+)(\s*,\s*([a-zA-Z\s]+))*).*"


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


class GenerationData:
    def __init__(self):
        self.includes = []


def getCppTypeOf(var):
    return "std::type_index(typeid(" + var + "))"


def scanFilesForEntityComponentInheritance(generationData, dir):
    entityComponents = ["EntityComponent"]
    entityComponentInheritances = []
    includes = ["core/entity/Entity.h"]

    for root, subdirs, files in os.walk(dir):
        for filename in files:
            if filename.endswith(".h"):
                file_path = os.path.join(root, filename)
                headerFile = open(file_path, "r")
                code = headerFile.read()

                if "PAX_ENTITYCOMPONENT" in code:
                    m = entityComponentRegexPattern.search(code)
                    if m is not None:
                        ecType = m.group("Type")
                        ecParents = m.group("Parents")
                        print("Inheritance found:", ecType, "inherits", ecParents)
                        entityComponents.append(ecType)
                        entityComponentInheritances.append((ecType.strip(), ecParents.strip()))

                        includes.append(file_path.replace(precompilationDirectory, ""))

                headerFile.close()

    generationData.entityComponents = entityComponents
    generationData.entityComponentInheritances = entityComponentInheritances
    generationData.includes.extend(includes)


def generateEventHandlers(file, etype):
    file.writeLine("static void " + etype + "Attached(Entity* e, EntityComponent *c) {")
    file.incrementIndent()
    file.writeLine("EntityComponentAddedEvent<" + etype + "> event(static_cast<" + etype + "*>(c), e);")
    file.writeLine("e->_localEventService(event);")
    file.decrementIndent()
    file.writeLine("}")
    file.writeLine("static void " + etype + "Detached(Entity* e, EntityComponent *c) {")
    file.incrementIndent()
    file.writeLine("EntityComponentRemovedEvent<" + etype + "> event(static_cast<" + etype + "*>(c), e);")
    file.writeLine("e->_localEventService(event);")
    file.decrementIndent()
    file.writeLine("}")


if __name__ == "__main__":
    print("PRECOMPILER Start")
    entityComponentRegexPattern = re.compile(EntityComponentRegex, re.MULTILINE)
    myPath = os.path.realpath(__file__)

    precompilationDirectory = os.path.dirname(myPath) + "/../include/"
    targetFile = os.path.dirname(myPath) + "/../src/generated/EntityComponentTypeHierarchy.cpp"
    genData = GenerationData()
    genData.includes.append("generated/EntityComponentTypeHierarchy.h")
    genData.includes.append("core/entity/event/EntityComponentAddedEvent.h")
    genData.includes.append("core/entity/event/EntityComponentRemovedEvent.h")

    scanFilesForEntityComponentInheritance(genData, precompilationDirectory)

    print()
    print("Generating source file", targetFile)
    print()

    outFile = FileWriter(open(targetFile, "w"))

    for include in genData.includes:
        outFile.writeLine("#include <" + include.replace("\\", "/") + ">")

    knownTypes = ["EntityComponent"]
    inheritancePairs = []
    sortedInheritancePairs = []

    for str_entitycomponent, str_parents in genData.entityComponentInheritances:
        supertypes = str_parents.split(",")
        for supertype in supertypes:
            supertypeCut = supertype.replace("public", "").replace("private", "").replace("protected", "").strip()
            if supertypeCut in genData.entityComponents:
                inheritancePairs.append((str_entitycomponent, supertypeCut))

    while len(inheritancePairs) > 0:
        for etype, eparent in inheritancePairs:
            if eparent in knownTypes:
                sortedInheritancePairs.append((etype, eparent))
                inheritancePairs.remove((etype, eparent))
                knownTypes.append(etype)

    outFile.writeLine("")
    outFile.writeLine("namespace PAX {")
    outFile.incrementIndent()
    outFile.writeLine("namespace Generated {")
    outFile.incrementIndent()

    outFile.writeLine("TypeMap<void (*)(Entity*, EntityComponent*)> EntityComponentTypeHierarchy::OnEntityComponentAttached;")
    outFile.writeLine("TypeMap<void (*)(Entity*, EntityComponent*)> EntityComponentTypeHierarchy::OnEntityComponentDetached;")
    outFile.writeLine("")

    addEventHandlersToMapCalls = []

    # generate event handlers for attached & detached
    eventBrokerName = "EntityComponentTypeHierarchyEventBroker";
    outFile.writeLine("class " + eventBrokerName + " {")
    outFile.writeLine("public:")
    outFile.incrementIndent()
    for etype in genData.entityComponents:
        generateEventHandlers(outFile, etype)
        addEventHandlersToMapCalls.append("OnEntityComponentAttached.put(" + getCppTypeOf(etype) + ", &" + eventBrokerName + "::" + etype + "Attached);")
        addEventHandlersToMapCalls.append("OnEntityComponentDetached.put(" + getCppTypeOf(etype) + ", &" + eventBrokerName + "::" + etype + "Detached);")
    outFile.decrementIndent()
    outFile.writeLine("};")
    outFile.writeLine("")

    # generate type hierarchy method calls
    outFile.writeLine("void EntityComponentTypeHierarchy::initialize() {")
    outFile.incrementIndent()

    for call in addEventHandlersToMapCalls:
        outFile.writeLine(call)

    outFile.writeLine("")
    outFile.writeLine("Reflection::TypeHierarchy &h = Entity::EntityComponentTypes;")

    for etype, eparent in sortedInheritancePairs:
        outFile.writeLine("h.add(" + getCppTypeOf(etype) + ", " + getCppTypeOf(eparent) + ");")
        print("Wrote inheritance", etype, "->", eparent)

    outFile.decrementIndent()
    outFile.writeLine("}")  # void createEntityComponentTypeHierarchy()
    outFile.decrementIndent()

    outFile.writeLine("}")  # namespace Generated
    outFile.decrementIndent()
    outFile.writeLine("}")  # namespace PAX

    outFile.close()
