#include "keys_de.h"
// ************************************
// *    Keymap for German Braille     *
// ************************************
// Keymap for the german "Vollschrift" Braille
// Which corresponds to the "Grade 2" Braille in English
// Contains the 26 letters of the alphabet, the numbers, some contractions
// and punctuation as well as some symbols
// 
// This file is for usage with the de_de layout

// `dot_layer DOT6_LAYER P` will 
// - type the key 'P" when tapped or
// - activate DOT6_LAYER as `sticky layer` when held
// if you want layer behavior on dots without a key, use `&sl` instead
ZMK_BEHAVIOR(dot_layer, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    bindings = <&sl>, <&kp>;
)
&sl {
    release-after-ms = <5000>;
};

// type current layout when pressing D8
ZMK_BEHAVIOR(LAYOUT, macro, bindings = <&kp D &kp E &kp D &kp E>;)
ZMK_COMBO(BR_LAYOUT_KEY,  &LAYOUT, D8,         BASE_LAYER)


// alphabet
ZMK_COMBO(BR_A,  &kp DE_A,        D1,             BASE_LAYER)
ZMK_COMBO(BR_B,  &kp DE_B,        D1 D2,          BASE_LAYER)
ZMK_COMBO(BR_C,  &kp DE_C,        D1 D4,          BASE_LAYER)
ZMK_COMBO(BR_D,  &kp DE_D,        D1 D4 D5,       BASE_LAYER)
ZMK_COMBO(BR_E,  &kp DE_E,        D1 D5,          BASE_LAYER)
ZMK_COMBO(BR_F,  &kp DE_F,        D1 D2 D4,       BASE_LAYER)
ZMK_COMBO(BR_G,  &kp DE_G,        D1 D2 D4 D5,    BASE_LAYER)
ZMK_COMBO(BR_H,  &kp DE_H,        D1 D2 D5,       BASE_LAYER)
ZMK_COMBO(BR_I,  &kp DE_I,        D2 D4,          BASE_LAYER)
ZMK_COMBO(BR_J,  &kp DE_J,        D2 D4 D5,       BASE_LAYER)
ZMK_COMBO(BR_K,  &kp DE_K,        D1 D3 ,         BASE_LAYER)
ZMK_COMBO(BR_L,  &kp DE_L,        D1 D2 D3 ,      BASE_LAYER)
ZMK_COMBO(BR_M,  &kp DE_M,        D1 D3 D4,       BASE_LAYER)
ZMK_COMBO(BR_N,  &kp DE_N,        D1 D3 D4 D5,    BASE_LAYER)
ZMK_COMBO(BR_O,  &kp DE_O,        D1 D3 D5,       BASE_LAYER)
ZMK_COMBO(BR_P,  &kp DE_P,        D1 D2 D3 D4,    BASE_LAYER)
ZMK_COMBO(BR_Q,  &kp DE_Q,        D1 D2 D3 D4 D5, BASE_LAYER)
ZMK_COMBO(BR_R,  &kp DE_R,        D1 D2 D3 D5,    BASE_LAYER)
ZMK_COMBO(BR_S,  &kp DE_S,        D2 D3 D4,       BASE_LAYER)
ZMK_COMBO(BR_T,  &kp DE_T,        D2 D3 D4 D5,    BASE_LAYER)
ZMK_COMBO(BR_U,  &kp DE_U,        D1 D3 D6,       BASE_LAYER)
ZMK_COMBO(BR_V,  &kp DE_V,        D1 D2 D3 D6,    BASE_LAYER)
ZMK_COMBO(BR_W,  &kp DE_W,        D2 D4 D5 D6,    BASE_LAYER)
ZMK_COMBO(BR_X,  &kp DE_X,        D1 D3 D4 D6,    BASE_LAYER)
ZMK_COMBO(BR_Y,  &kp DE_Y,        D1 D3 D4 D5 D6, BASE_LAYER)
ZMK_COMBO(BR_Z,  &kp DE_Z,        D1 D3 D5 D6,    BASE_LAYER)
ZMK_COMBO(BR_AUML, &kp DE_A_UMLAUT,   D3 D4 D5,       BASE_LAYER)
ZMK_COMBO(BR_OUML, &kp DE_O_UMLAUT,   D2 D4 D6,       BASE_LAYER)
ZMK_COMBO(BR_UUML, &kp DE_U_UMLAUT,   D1 D2 D5 D6,    BASE_LAYER)
ZMK_COMBO(BR_SUML, &kp DE_SZ,   D2 D3 D4 D6,    BASE_LAYER)

// simple contractions
ZMK_BEHAVIOR(AU,    macro,  bindings = <&macro_tap &kp DE_A &kp DE_U>;)
ZMK_COMBO(BR_AU, &AU,  D1 D6,             BASE_LAYER)

ZMK_BEHAVIOR(EU,    macro,  bindings = <&macro_tap &kp DE_E &kp DE_U>;)
ZMK_COMBO(BR_EU, &EU,  D1 D2 D6,          BASE_LAYER)

ZMK_BEHAVIOR(EI,    macro,  bindings = <&macro_tap &kp DE_E &kp DE_I>;)
ZMK_COMBO(BR_EI, &EI,  D1 D4 D6,          BASE_LAYER)

ZMK_BEHAVIOR(CH,    macro,  bindings = <&macro_tap &kp DE_C &kp DE_H>;)
ZMK_COMBO(BR_CH, &CH,  D1 D4 D5 D6,       BASE_LAYER)

ZMK_BEHAVIOR(ST,    macro,  bindings = <&macro_tap &kp DE_S &kp DE_T>;)
ZMK_COMBO(BR_ST, &ST,  D2 D3 D4 D5 D6,    BASE_LAYER)

ZMK_BEHAVIOR(IE,    macro,  bindings = <&macro_tap &kp DE_I &kp DE_E>;)
ZMK_COMBO(BR_IE, &IE,  D3 D4 D6,          BASE_LAYER)

ZMK_BEHAVIOR(SCH,   macro,  bindings = <&macro_tap &kp DE_S &kp DE_C &kp DE_H>;)
ZMK_COMBO(BR_SCH, &SCH, D1 D5 D6,         BASE_LAYER)

ZMK_BEHAVIOR(AUML_U, macro, bindings = <&macro_tap &kp DE_A_UMLAUT &kp DE_U>;)
ZMK_COMBO(BR_AUML_U, &AUML_U,  D3 D4,     BASE_LAYER)

// Numbers and number layer
ZMK_COMBO(BR_TO_NUM, &to NUM_LAYER,    D3 D4 D5 D6,  BASE_LAYER)
ZMK_COMBO(BR_1, &kp DE_N1,        D1,             NUM_LAYER)
ZMK_COMBO(BR_2, &kp DE_N2,        D1 D2,          NUM_LAYER)
ZMK_COMBO(BR_3, &kp DE_N3,        D1 D4,          NUM_LAYER)
ZMK_COMBO(BR_4, &kp DE_N4,        D1 D4 D5,       NUM_LAYER)
ZMK_COMBO(BR_5, &kp DE_N5,        D1 D5,          NUM_LAYER)
ZMK_COMBO(BR_6, &kp DE_N6,        D1 D2 D4,       NUM_LAYER)
ZMK_COMBO(BR_7, &kp DE_N7,        D1 D2 D4 D5,    NUM_LAYER)
ZMK_COMBO(BR_8, &kp DE_N8,        D1 D2 D5,       NUM_LAYER)
ZMK_COMBO(BR_9, &kp DE_N9,        D2 D4,          NUM_LAYER)
// zero has double meaning when typing percent
ZMK_COMBO(BR_0, &dot_layer ADDITIONAL_LAYER N0,   D2 D4 D5,       NUM_LAYER)

// "simple" symbols (no layer needed)
ZMK_COMBO(BR_COMMA,         &kp DE_COMMA,       D2,         BASE_LAYER)
ZMK_COMBO(BR_SEMI,          &kp DE_SEMI,        D2 D3,      BASE_LAYER)
ZMK_COMBO(BR_COLON,         &kp DE_COLON,       D2 D5,      BASE_LAYER)
ZMK_COMBO(BR_QUESTION,      &kp DE_QUESTION,    D2 D6,      BASE_LAYER)
ZMK_COMBO(BR_EXCLAMATION,   &kp DE_EXCLAMATION, D2 D3 D5,   BASE_LAYER)
ZMK_COMBO(BR_LPAR,          &kp DE_LPAR,        D2 D3 D5 D6,BASE_LAYER)
ZMK_COMBO(BR_DQT1,          &kp DE_DQT,         D2 D3 D6,   BASE_LAYER)
ZMK_COMBO(BR_DQT2,          &kp DE_DQT,         D3 D5 D6,   BASE_LAYER)
// ZMK_COMBO(BR_PARAGRAPH,     ,      D3 D4 D6,   BASE_LAYER) // Collides with BR_IE - preferring that to this symbol
ZMK_COMBO(BR_DOT,           &kp DE_DOT,            D3,         BASE_LAYER)
ZMK_COMBO(BR_MINUS,         &kp DE_MINUS,          D3 D6,      BASE_LAYER)
ZMK_COMBO(BR_APOSTROPHE,    &dot_layer DOT6_LAYER DE_APOSTROPHE, D6, BASE_LAYER)

// one shot shift
ZMK_COMBO(BR_UPPER,  &sk LSHIFT,    D4 D6,  BASE_LAYER)
// additional layers for complex symbols
ZMK_COMBO(BR_DOT4,  &sl DOT4_LAYER,  D4,      BASE_LAYER)
ZMK_COMBO(BR_DOT5,  &sl DOT5_LAYER,  D5,      BASE_LAYER)
// D4 D5 short press is caps word, long press is layer
ZMK_BEHAVIOR(dot45_capsword, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    bindings = <&sl>, <&caps_word>;
)
ZMK_COMBO(BR_DOT45, &dot45_capsword DOT45_LAYER 0, D4 D5,   BASE_LAYER)

// "complex" symbols (need one or several layers)
ZMK_COMBO(BR_DASH,      &kp DE_MINUS,                  D3 D6,       DOT6_LAYER) // Gedankenstrich
ZMK_COMBO(BR_PIPE,      &kp DE_PIPE,   D3 D6,   DOT5_LAYER) // Abtrennungszeichen (senkrechter Strich)
ZMK_COMBO(BR_BRACKET,   &kp DE_LEFT_BRACKET,                 D2 D3 D5 D6,    DOT6_LAYER) // Eckige Klammer auf
ZMK_COMBO(BR_LT,        &kp DE_LT,       D2 D3 D5 D6,  DOT5_LAYER) // Spitze Klammer auf
ZMK_COMBO(BR_LCURLY,    &kp DE_LEFT_BRACE,                 D1 D2 D3 D5 D6, DOT5_LAYER) // Geschweifte Klammer auf
ZMK_COMBO(BR_LBRACKET,  &kp DE_LEFT_BRACKET,                 D1 D2 D3 D5 D6, DOT45_LAYER) // Phonetische Klammer auf
ZMK_COMBO(BR_RBRACKET,  &kp DE_RIGHT_BRACKET,                 D2 D3 D4 D5 D6, DOT45_LAYER) // Phonetische Klammer zu
ZMK_COMBO(BR_SLASH,     &kp DE_SLASH,                 D3 D4,      DOT45_LAYER) // Phonemische Klammer auf und zu
ZMK_COMBO(BR_SQUOTE,    &kp DE_SINGLE_QUOTE,          D2 D3 D6,   DOT6_LAYER) // "einfaches" Anführungszeichen am Anfang
ZMK_COMBO(BR_BACKTICK,  &kp DE_GRAVE,                  D3 D5 D6,   DOT6_LAYER) // "einfaches" Anführungszeichen am Ende
ZMK_COMBO(BR_SLASH2,    &kp DE_SLASH,                 D2,         DOT5_LAYER) // Schrägstrich
ZMK_COMBO(BR_AMPERSAND, &kp DE_AMPERSAND,                 D1 D3 D6,   DOT5_LAYER) // Et-Zeichen ("kaufmännisches Und")
ZMK_COMBO(BR_STAR,      &kp DE_STAR,      D3 D5,   DOT6_LAYER) // Stern
ZMK_COMBO(BR_PERCENT,   &kp DE_PERCENT,                 D3 D5 D6,   ADDITIONAL_LAYER) // Prozentzeichen
ZMK_COMBO(BR_DEGREE,    &kp DE_DEGREE,                  D3 D5 D6,   DOT4_LAYER) // Gradzeichen
ZMK_COMBO(BR_BACKSLASH, &kp DE_BACKSLASH,              D3 D4,      DOT4_LAYER) // Backslash
ZMK_COMBO(BR_AT,        &kp DE_AT,                  D3 D4 D5,   DOT4_LAYER) // AT
ZMK_COMBO(BR_UNDERSCORE,&kp DE_UNDERSCORE,               D4 D5 D6,   DOT4_LAYER) // Unterstrich
ZMK_COMBO(BR_HASH,      &kp DE_HASH,              D3 D4 D5 D6,DOT4_LAYER) // Hash #
ZMK_COMBO(BR_EURO,      &kp DE_EURO,                  D1 D5,      DOT4_LAYER)   // euro
ZMK_COMBO(BR_DOLLAR,    &kp DE_DOLLAR,                 D2 D3 D4,   DOT4_LAYER)   // dollar
ZMK_COMBO(BR_CENT,      &kp RA(C),                  D1 D4,      DOT4_LAYER)   // dollar cent (Dollar-)Centzeichen
ZMK_COMBO(BR_POUND,     &kp DE_POUND,             D1 D2 D3,   DOT4_LAYER)   // £ Pfund- oder Lirazeichen (Währungsangaben)


