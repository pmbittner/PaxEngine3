lexer grammar ImguiPPLexer;

WS: [ \t]+ -> skip;
SINGLELINE_COMMENT: [ \t\n\r]* '//' (~('\r' | '\n'))* -> skip;
MULTILINE_COMMENT: [ \t\n\r]* '/*' ([ \t\n\r]|.)*? '*/' -> skip;
LINEBREAK: [\n\r] -> skip;

IMGUI: 'IMGUI' WS* -> pushMode(IMGUI_ANNOTATION_MODE);
IMGUI_RANGED: 'IMGUI_RANGED' -> pushMode(IMGUI_ANNOTATION_MODE);
ANYTHING_ELSE: .+? -> skip;

mode IMGUI_ANNOTATION_MODE;
//WS2: [ \t]+ -> skip;
//MACRO_DEFINITION2: [ \t\n\r]* '#' (~('\r' | '\n'))* -> skip;
//SINGLELINE_COMMENT2: [ \t\n\r]* '//' (~('\r' | '\n'))* -> skip;
//MULTILINE_COMMENT2: [ \t\n\r]* '/*' ([ \t\n\r]|.)*? '*/' -> skip;
//LINEBREAK2: [\n\r] -> skip;

//WS2: [ \t]+ -> skip;
//IDENTIFIER: [a-zA-Z_0-9.(),]+;
//EQUALS: '=' -> pushMode;
BRACKET_L: '(';
BRACKET_R: ')';
IDENTIFIER: ~('=' | ',' | ';' | ' ' | '\t' | '(' | ')')+;
COMMA: ',';
EQUALS: '=' -> pushMode(UNIFORM_INITIALIZATION);
SEMICOLON: ';' -> popMode;

mode UNIFORM_INITIALIZATION;
UNIFORM_INITIAL_VALUE: ~(';')+;
UNIFORM_INITIALIZATION_END: ';' -> popMode, popMode;