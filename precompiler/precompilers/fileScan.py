import os
import re

import util.paxnamespace as paxnamespace
import util.definitions as definitions



def scanFilesForProperties(generationData, dir, treehandle):
    properties = []
    regex = "(struct|class)\s(?P<Type>[:a-zA-Z0-9]+)\s:[<>a-zA-Z0-9\s,:]*\s{([a-zA-Z0-9\s,;\(\):=&\*])*" + treehandle.macro + "\(\s*(?P<Parent>[<>:a-zA-Z0-9]+)\s*,\s*(?P<IsMultiple>[a-zA-Z]+)\s*\)"
    regexPattern = re.compile(regex, re.MULTILINE)
    includes = []

    for root, subdirs, files in os.walk(dir):
        for filename in files:
            if filename.endswith(".h"):
                file_path = os.path.join(root, filename)
                headerFile = open(file_path, "r")
                code = headerFile.read()

                if treehandle.macro in code:
                    m = regexPattern.search(code)
                    if m is not None:
                        propType = m.group("Type").strip()
                        propParent = m.group("Parent").strip()
                        propIsMultiple = m.group("IsMultiple").strip()

                        # Search for namespaces
                        propnamespace = paxnamespace.getNamespace(code, propType)

                        propFullQualifiedName = propType
                        if propnamespace:
                            propFullQualifiedName = propnamespace + "::" + propFullQualifiedName

                        prop = definitions.PaxProperty(propFullQualifiedName, propIsMultiple)
                        prop.namespace = propnamespace
                        prop.fullQualifiedName = propFullQualifiedName
                        properties.append(prop)
                        generationData.inheritances.append((propFullQualifiedName, propParent))

                        includes.append(file_path.replace(dir, ""))

                headerFile.close()

    generationData.properties = properties
    generationData.includes.extend(includes)


def generateEventHandlers(file, entityComponent, containerName, attachedEventName, detachedEventName):
    propertyBaseName = "Property<" + containerName + ">"

    file.writeLine("static void " + entityComponent.nameWithoutNamespaces + "Attached(" + containerName + "* e, const std::shared_ptr<" + propertyBaseName + "> & c) {")
    file.incrementIndent()
    file.writeLine(attachedEventName + "<" + entityComponent.name + "> event(std::dynamic_pointer_cast<" + entityComponent.name + ">(c), e);")
    file.writeLine("e->getEventService()(event);")
    file.decrementIndent()
    file.writeLine("}")
    file.writeLine("static void " + entityComponent.nameWithoutNamespaces + "Detached(" + containerName + "* e, const std::shared_ptr<" + propertyBaseName + "> & c) {")
    file.incrementIndent()
    file.writeLine(detachedEventName + "<" + entityComponent.name + "> event(std::dynamic_pointer_cast<" + entityComponent.name + ">(c), e);")
    file.writeLine("e->getEventService()(event);")
    file.decrementIndent()
    file.writeLine("}")
