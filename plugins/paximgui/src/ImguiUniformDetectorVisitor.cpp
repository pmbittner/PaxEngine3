//
// Created by Paul on 04.09.2022.
//

#include "paximgui/ImguiUniformDetectorVisitor.h"

namespace PAX {
    namespace Imgui {
        template<typename T>
        static Variable* parseVariable(Antlr::ImguiPPParser::Imgui_uniformContext *context) {
            const std::string name = context->name->getText();

            bool isRanged = false;
            std::string from_str, to_str;
            Antlr::ImguiPPParser::Imgui_ranged_annotationContext * rangedContext = context->imgui_ranged_annotation();
            if (rangedContext) {
                isRanged = true;
                from_str = rangedContext->from->getText();
                to_str = rangedContext->to->getText();
            }

            bool hasInitialValue = false;
            std::string initialValue_str;
            if (context->initialValue) {
                hasInitialValue = true;
                initialValue_str = context->initialValue->getText();
            }

            T val = T();
            if (hasInitialValue) {
                val = String::convertTo<T>(initialValue_str);
            }

            if (isRanged) {
                const auto from = String::convertTo<T>(from_str);
                const auto to = String::convertTo<T>(to_str);
                return new VariableT<T>(name, val, from, to);
            } else {
                return new VariableT<T>(name, val);
            }
        }

        antlrcpp::Any
        ImguiUniformDetectorVisitor::visitProgram(Antlr::ImguiPPParser::ProgramContext *context) {
            variables = Variables();
            for (auto * child : context->imgui_uniform()) {
                visitImgui_uniform(child);
            }

            return {};
        }

        antlrcpp::Any
        ImguiUniformDetectorVisitor::visitImgui_uniform(Antlr::ImguiPPParser::Imgui_uniformContext *context) {
            const std::string type = context->type->getText();

            Variable * variable = nullptr;

            if (std::string("float") == type) {
                variable = parseVariable<float>(context);
            } else if (std::string("int") == type) {
                variable = parseVariable<int>(context);
            } else if (std::string("IMGUI_COLOR") == type) {
                variable = parseVariable<Color>(context);
            } else {
                PAX_LOG(Log::Level::Warn, "Type \"" << type << "\" of variable " << context->name << " is not supported!");
            }

            if (variable) {
                variables.variables.emplace_back(variable);
            }

            return {};
        }

        antlrcpp::Any
        ImguiUniformDetectorVisitor::visitImgui_annotation(Antlr::ImguiPPParser::Imgui_annotationContext *context) {
            return {};
        }

        antlrcpp::Any
        ImguiUniformDetectorVisitor::visitImgui_ranged_annotation(
                Antlr::ImguiPPParser::Imgui_ranged_annotationContext *context) {
            return {};
        }
    }
}