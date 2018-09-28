import os
import re
import sys

import util.paxfilewriter as paxfilewriter
import util.definitions as definitions
import precompilers.fileScan as FileScan

if __name__ == "__main__":
    myPath = os.path.realpath(__file__)
    projectName = "PAX"
    precompilationDirectory = os.path.dirname(myPath) + "/../include/"
    targetFile = ""
    className = "Plugin"
    pluginHeaderIncludePath = className + ".h"

    if len(sys.argv) > 3:
        projectName = sys.argv[1]
        precompilationDirectory = sys.argv[2]
        targetFile = sys.argv[3]

        if len(sys.argv) > 4:
            className = sys.argv[4]
            pluginHeaderIncludePath = className + ".h"

            if len(sys.argv) > 5:
                pluginHeaderIncludePath = sys.argv[5]
    else:
        print("Error: The following arguments are required in this order; <project name> <precompilation directory> <file path to generate>")

    print("PRECOMPILER Start")

    print("Reading from directory", precompilationDirectory)
    print("Generating source file", targetFile)

    genData = definitions.PaxGenerationData()

    ### Claim necessary information
    # Check if projectName contains multiple namespaces like PAX::Many::Namespaces::lol
    projectNamespaces = projectName.split("::")

    outFile = paxfilewriter.FileWriter(open(targetFile, "w"))

    genData.includes.append(pluginHeaderIncludePath)
    genData.includes.append("memory")

    entityPropertyTreeHandle = definitions.PaxPropertyTreeHandle("PAX_ENTITYCOMPONENT_BODY", "PAX::Entity",
        [
            "paxcore/entity/Entity.h",
            "paxcore/entity/EntityComponent.h",
            "paxcore/entity/event/EntityComponentAddedEvent.h",
            "paxcore/entity/event/EntityComponentRemovedEvent.h"
        ],
        "PAX::EntityComponentAddedEvent", "PAX::EntityComponentRemovedEvent")

    worldLayerPropertyTreeHandle = definitions.PaxPropertyTreeHandle("PAX_WORLDLAYERPROPERTY_BODY", "PAX::WorldLayer",
        [
            "paxcore/world/WorldLayer.h",
            "paxcore/world/WorldLayerProperty.h",
            "paxcore/world/event/WorldLayerPropertyAddedEvent.h",
            "paxcore/world/event/WorldLayerPropertyRemovedEvent.h"
        ],
        "PAX::WorldLayerPropertyAddedEvent", "PAX::WorldLayerPropertyRemovedEvent")

    TREEHANDLES = [entityPropertyTreeHandle, worldLayerPropertyTreeHandle]

    for treeHandle in TREEHANDLES:
        genData.includes.extend(treeHandle.includes)
        genData.clearPropertyInfo()

        FileScan.scanFilesForProperties(genData, precompilationDirectory, treeHandle)

        # TODO Sort inheritances, when root is known (eg PAX::EntityComponent)

        treeHandle.sortedInheritancePairs = genData.inheritances
        treeHandle.properties = genData.properties

    genData.clearPropertyInfo()

    ### Write Include directives
    for include in genData.includes:
        outFile.writeLine("#include <" + include.replace("\\", "/") + ">")
    outFile.writeLine("")

    for namespace in projectNamespaces:
        outFile.writeLine("namespace " + namespace + " {")
        outFile.incrementIndent()

    addEventHandlersToMapCalls = {}

    # generate event handlers for attached & detached
    eventBrokerName = "PropertyAttachmentEventBroker"
    outFile.writeLine("namespace Generated {")
    outFile.incrementIndent()
    outFile.writeLine("class " + eventBrokerName + " {")
    outFile.writeLine("public:")
    outFile.incrementIndent()

    for treeHandle in TREEHANDLES:
        addEventHandlersToMapCalls[treeHandle] = []
        for prop in treeHandle.properties:
            FileScan.generateEventHandlers(outFile, prop, treeHandle.container, treeHandle.attachedEventName, treeHandle.detachedEventName)
            addEventHandlersToMapCalls[treeHandle].append("reflectionData.propertyAttachedHandlers.put(" + definitions.getCppTypeOf(prop.name) + ", &Generated::" + eventBrokerName + "::" + prop.nameWithoutNamespaces + "Attached);")
            addEventHandlersToMapCalls[treeHandle].append("reflectionData.propertyDetachedHandlers.put(" + definitions.getCppTypeOf(prop.name) + ", &Generated::" + eventBrokerName + "::" + prop.nameWithoutNamespaces + "Detached);")

    outFile.decrementIndent()
    outFile.writeLine("};")  # class <eventBrokerName>
    outFile.decrementIndent()  # namespace Generated
    outFile.writeLine("}")
    outFile.writeLine("")

    # generate type hierarchy method calls
    outFile.writeLine("void " + className + "::internal_initializeReflectionData() {")
    outFile.incrementIndent()


    for treeHandle in TREEHANDLES:
        # open new scope to avoid namespace conflicts
        outFile.writeLine("{")
        outFile.incrementIndent()

        outFile.writeLine("PAX::PropertyReflectionData<" + treeHandle.container + ">& reflectionData = " + treeHandle.container + "::ReflectionData;\n")

        for call in addEventHandlersToMapCalls[treeHandle]:
            outFile.writeLine(call)

        outFile.writeLine("")

        for child, parent in treeHandle.sortedInheritancePairs:
            outFile.writeLine("reflectionData.propertyTypeHierarchy.add(" + definitions.getCppTypeOf(child) + ", " + definitions.getCppTypeOf(parent) + ");")
            print("\t", child, "->", parent)

        outFile.writeLine("")
        for prop in treeHandle.properties:
            outFile.writeLine("reflectionData.isMultiple.put(" + definitions.getCppTypeOf(prop.name) + ", " + prop.name + "::IsMultiple());")

        outFile.decrementIndent()
        outFile.writeLine("}")  # scope

    outFile.decrementIndent()
    outFile.writeLine("}")  # void createEntityComponentTypeHierarchy()
    outFile.decrementIndent()

    for namespace in projectNamespaces:
        outFile.writeLine("}")  # namespace <projectName>
        outFile.decrementIndent()

    outFile.close()

    print("PRECOMPILER Done")
