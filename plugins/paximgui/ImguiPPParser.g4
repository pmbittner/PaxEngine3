parser grammar ImguiPPParser;

options { tokenVocab=ImguiPPLexer; }

program: imgui_uniform* EOF;

imgui_annotation : IMGUI;
imgui_ranged_annotation: IMGUI_RANGED BRACKET_L from=IDENTIFIER COMMA to=IDENTIFIER BRACKET_R;

imgui_uniform: (imgui_annotation | imgui_ranged_annotation) type=IDENTIFIER name=IDENTIFIER (EQUALS initialValue=UNIFORM_INITIAL_VALUE UNIFORM_INITIALIZATION_END | SEMICOLON);
