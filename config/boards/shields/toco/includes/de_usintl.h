// ************************************
// *    Keymap for German Braille     *
// ************************************
// Keymap for the german "Vollschrift" Braille
// Which corresponds to the "Grade 2" Braille in English
// Contains the 26 letters of the alphabet, the numbers, some contractions
// and punctuation as well as some symbols
// This file is for usage with the US International layout

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

// Using the us_international keymap as a base
ZMK_BEHAVIOR(DE_AUML,   macro,  bindings = <&macro_tap &kp RA(Q)>;)
ZMK_BEHAVIOR(DE_OUML,   macro,  bindings = <&macro_tap &kp RA(P)>;)
ZMK_BEHAVIOR(DE_UUML,   macro,  bindings = <&macro_tap &kp RA(Y)>;)
ZMK_BEHAVIOR(DE_SUML,   macro,  bindings = <&macro_tap &kp RA(S)>;)
ZMK_BEHAVIOR(DE_Y,      macro,  bindings = <&macro_tap &kp Y>;)
ZMK_BEHAVIOR(DE_Z,      macro,  bindings = <&macro_tap &kp Z>;)


// alphabet
ZMK_COMBO(BR_A,  &kp A,        D1,             BASE_LAYER)
ZMK_COMBO(BR_B,  &kp B,        D1 D2,          BASE_LAYER)
ZMK_COMBO(BR_C,  &kp C,        D1 D4,          BASE_LAYER)
ZMK_COMBO(BR_D,  &kp D,        D1 D4 D5,       BASE_LAYER)
ZMK_COMBO(BR_E,  &kp E,        D1 D5,          BASE_LAYER)
ZMK_COMBO(BR_F,  &kp F,        D1 D2 D4,       BASE_LAYER)
ZMK_COMBO(BR_G,  &kp G,        D1 D2 D4 D5,    BASE_LAYER)
ZMK_COMBO(BR_H,  &kp H,        D1 D2 D5,       BASE_LAYER)
ZMK_COMBO(BR_I,  &kp I,        D2 D4,          BASE_LAYER)
ZMK_COMBO(BR_J,  &kp J,        D2 D4 D5,       BASE_LAYER)
ZMK_COMBO(BR_K,  &kp K,        D1 D3 ,         BASE_LAYER)
ZMK_COMBO(BR_L,  &kp L,        D1 D2 D3 ,      BASE_LAYER)
ZMK_COMBO(BR_M,  &kp M,        D1 D3 D4,       BASE_LAYER)
ZMK_COMBO(BR_N,  &kp N,        D1 D3 D4 D5,    BASE_LAYER)
ZMK_COMBO(BR_O,  &kp O,        D1 D3 D5,       BASE_LAYER)
ZMK_COMBO(BR_P,  &kp P,        D1 D2 D3 D4,    BASE_LAYER)
ZMK_COMBO(BR_Q,  &kp Q,        D1 D2 D3 D4 D5, BASE_LAYER)
ZMK_COMBO(BR_R,  &kp R,        D1 D2 D3 D5,    BASE_LAYER)
ZMK_COMBO(BR_S,  &kp S,        D2 D3 D4,       BASE_LAYER)
ZMK_COMBO(BR_T,  &kp T,        D2 D3 D4 D5,    BASE_LAYER)
ZMK_COMBO(BR_U,  &kp U,        D1 D3 D6,       BASE_LAYER)
ZMK_COMBO(BR_V,  &kp V,        D1 D2 D3 D6,    BASE_LAYER)
ZMK_COMBO(BR_W,  &kp W,        D2 D4 D5 D6,    BASE_LAYER)
ZMK_COMBO(BR_X,  &kp X,        D1 D3 D4 D6,    BASE_LAYER)
ZMK_COMBO(BR_Y,  &DE_Y,        D1 D3 D4 D5 D6, BASE_LAYER)
ZMK_COMBO(BR_Z,  &DE_Z,        D1 D3 D5 D6,    BASE_LAYER)
ZMK_COMBO(BR_AUML, &DE_AUML,   D3 D4 D5,       BASE_LAYER)
ZMK_COMBO(BR_OUML, &DE_OUML,   D2 D4 D6,       BASE_LAYER)
ZMK_COMBO(BR_UUML, &DE_UUML,   D1 D2 D5 D6,    BASE_LAYER)
ZMK_COMBO(BR_SUML, &DE_SUML,   D2 D3 D4 D6,    BASE_LAYER)

// simple contractions
ZMK_BEHAVIOR(AU,    macro,  bindings = <&macro_tap &kp A &kp U>;)
ZMK_COMBO(BR_AU, &AU,  D1 D6,             BASE_LAYER)

ZMK_BEHAVIOR(EU,    macro,  bindings = <&macro_tap &kp E &kp U>;)
ZMK_COMBO(BR_EU, &EU,  D1 D2 D6,          BASE_LAYER)

ZMK_BEHAVIOR(EI,    macro,  bindings = <&macro_tap &kp E &kp I>;)
ZMK_COMBO(BR_EI, &EI,  D1 D4 D6,          BASE_LAYER)

ZMK_BEHAVIOR(CH,    macro,  bindings = <&macro_tap &kp C &kp H>;)
ZMK_COMBO(BR_CH, &CH,  D1 D4 D5 D6,       BASE_LAYER)

ZMK_BEHAVIOR(ST,    macro,  bindings = <&macro_tap &kp S &kp T>;)
ZMK_COMBO(BR_ST, &ST,  D2 D3 D4 D5 D6,    BASE_LAYER)

ZMK_BEHAVIOR(IE,    macro,  bindings = <&macro_tap &kp I &kp E>;)
ZMK_COMBO(BR_IE, &IE,  D3 D4 D6,          BASE_LAYER)

ZMK_BEHAVIOR(SCH,   macro,  bindings = <&macro_tap &kp S &kp C &kp H>;)
ZMK_COMBO(BR_SCH, &SCH, D1 D5 D6,         BASE_LAYER)

ZMK_BEHAVIOR(AUML_U, macro, bindings = <&macro_tap &DE_AUML &kp U>;)
ZMK_COMBO(BR_AUML_U, &AUML_U,  D3 D4,     BASE_LAYER)

// Numbers and number layer
ZMK_COMBO(BR_TO_NUM, &to NUM_LAYER,    D3 D4 D5 D6,  BASE_LAYER)
ZMK_COMBO(BR_1, &kp N1,        D1,             NUM_LAYER)
ZMK_COMBO(BR_2, &kp N2,        D1 D2,          NUM_LAYER)
ZMK_COMBO(BR_3, &kp N3,        D1 D4,          NUM_LAYER)
ZMK_COMBO(BR_4, &kp N4,        D1 D4 D5,       NUM_LAYER)
ZMK_COMBO(BR_5, &kp N5,        D1 D5,          NUM_LAYER)
ZMK_COMBO(BR_6, &kp N6,        D1 D2 D4,       NUM_LAYER)
ZMK_COMBO(BR_7, &kp N7,        D1 D2 D4 D5,    NUM_LAYER)
ZMK_COMBO(BR_8, &kp N8,        D1 D2 D5,       NUM_LAYER)
ZMK_COMBO(BR_9, &kp N9,        D2 D4,          NUM_LAYER)
// zero has double meaning when typing percent
ZMK_COMBO(BR_0, &dot_layer ADDITIONAL_LAYER N0,   D2 D4 D5,       NUM_LAYER)

// "simple" symbols (no layer needed)
ZMK_COMBO(BR_COMMA,         &kp COMMA,          D2,         BASE_LAYER)
ZMK_COMBO(BR_SEMI,          &kp SEMI,           D2 D3,      BASE_LAYER)
ZMK_COMBO(BR_COLON,         &kp COLON,          D2 D5,      BASE_LAYER)
ZMK_COMBO(BR_QUESTION,      &kp QUESTION,       D2 D6,      BASE_LAYER)
ZMK_COMBO(BR_EXCLAMATION,   &kp EXCLAMATION,    D2 D3 D5,   BASE_LAYER)
ZMK_COMBO(BR_LPAR,          &kp LPAR,           D2 D3 D5 D6,BASE_LAYER)
ZMK_COMBO(BR_DOUBLE_QUOTE1, &kp DOUBLE_QUOTES,  D2 D3 D6,   BASE_LAYER)
ZMK_COMBO(BR_DOUBLE_QUOTE2, &kp DOUBLE_QUOTES,  D3 D5 D6,   BASE_LAYER)
// ZMK_COMBO(BR_PARAGRAPH,     &kp RA(LS(S)),      D3 D4 D6,   BASE_LAYER) // Collides with BR_IE - preferring that to this symbol
ZMK_COMBO(BR_DOT,           &kp DOT,            D3,         BASE_LAYER)
ZMK_COMBO(BR_MINUS,         &kp MINUS,          D3 D6,      BASE_LAYER)
ZMK_COMBO(BR_APOSTROPHE,    &dot_layer DOT6_LAYER APOSTROPHE, D6, BASE_LAYER)

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
ZMK_COMBO(BR_DASH,      &kp MINUS,          D3 D6,       DOT6_LAYER) // Gedankenstrich
ZMK_COMBO(BR_PIPE,      &kp PIPE,           D3 D6,       DOT5_LAYER) // Abtrennungszeichen (senkrechter Strich)
ZMK_COMBO(BR_BRACKET,   &kp LEFT_BRACKET,   D2 D3 D5 D6, DOT6_LAYER) // Eckige Klammer auf
ZMK_COMBO(BR_LT,        &kp LESS_THAN,      D2 D3 D5 D6, DOT5_LAYER) // Spitze Klammer auf
ZMK_COMBO(BR_LCURLY,    &kp LEFT_BRACE,     D1 D2 D3 D5 D6, DOT5_LAYER) // Geschweifte Klammer auf
ZMK_COMBO(BR_LBRACKET,  &kp LEFT_BRACKET,   D1 D2 D3 D5 D6, DOT45_LAYER) // Phonetische Klammer auf
ZMK_COMBO(BR_RBRACKET,  &kp RIGHT_BRACKET,  D2 D3 D4 D5 D6, DOT45_LAYER) // Phonetische Klammer zu
ZMK_COMBO(BR_SLASH,     &kp SLASH,          D3 D4,      DOT45_LAYER) // Phonemische Klammer auf und zu
ZMK_COMBO(BR_SQUOTE,    &kp SINGLE_QUOTE,   D2 D3 D6,   DOT6_LAYER) // "einfaches" Anführungszeichen am Anfang
ZMK_COMBO(BR_BACKTICK,  &kp GRAVE,          D3 D5 D6,   DOT6_LAYER) // "einfaches" Anführungszeichen am Ende
ZMK_COMBO(BR_SLASH2,    &kp SLASH,          D2,         DOT5_LAYER) // Schrägstrich
ZMK_COMBO(BR_AMPERSAND, &kp AMPERSAND,      D1 D3 D6,   DOT5_LAYER) // Et-Zeichen ("kaufmännisches Und")
ZMK_COMBO(BR_STAR,      &kp STAR,           D3 D5,      DOT6_LAYER) // Stern
ZMK_COMBO(BR_PERCENT,   &kp LS(N5),         D3 D5 D6,   ADDITIONAL_LAYER) // Prozentzeichen
ZMK_COMBO(BR_DEGREE,    &kp RA(LS(SEMI)),   D3 D5 D6,   DOT4_LAYER) // Gradzeichen
ZMK_COMBO(BR_BACKSLASH, &kp BACKSLASH,      D3 D4,      DOT4_LAYER) // Backslash
ZMK_COMBO(BR_AT,        &kp AT_SIGN,        D3 D4 D5,   DOT4_LAYER) // AT
ZMK_COMBO(BR_UNDERSCORE,&kp UNDERSCORE,     D4 D5 D6,   DOT4_LAYER) // Unterstrich
ZMK_COMBO(BR_HASH,      &kp HASH,           D3 D4 D5 D6,DOT4_LAYER) // Hash #
ZMK_COMBO(BR_EURO,      &kp RA(N5),         D1 D5,      DOT4_LAYER)   // euro
ZMK_COMBO(BR_DOLLAR,    &kp DOLLAR,         D2 D3 D4,   DOT4_LAYER)   // dollar
ZMK_COMBO(BR_CENT,      &kp RA(LS(C)),      D1 D4,      DOT4_LAYER)   // dollar cent (Dollar-)Centzeichen
ZMK_COMBO(BR_POUND,     &kp RA(LS(N4)),     D1 D2 D3,   DOT4_LAYER)   // £ Pfund- oder Lirazeichen (Währungsangaben)

