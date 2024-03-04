// position of dots on keyboard
//  ╭─────────────────╮
//  │  TL  4   1  TR  │
//  │      5   2      │
//  │      6   3      │
//  │  BL  8   7  BR  │
//  ╰─────────────────╯

#if USB_PORT_POSITION == USB_ON_TOP

#define TL 0
#define TR 3
#define BL 8
#define BR 11

#if PREFER_DOTS == DOT1_ON_LEFT
#define D1 1
#define D2 4
#define D3 6
#define D4 2
#define D5 5
#define D6 7
#define D7 9
#define D8 10
#elif PREFER_DOTS == DOT1_ON_RIGHT
#define D1 2
#define D2 5
#define D3 7
#define D4 1
#define D5 4
#define D6 6
#define D7 10
#define D8 9
#endif // PREFER_DOTS

#elif USB_PORT_POSITION == USB_ON_BOTTOM

#define TL 11
#define TR 8
#define BL 3
#define BR 0

#if PREFER_DOTS == DOT1_ON_LEFT
#define D1 10
#define D2 7
#define D3 5
#define D4 9
#define D5 6
#define D6 4
#define D7 2
#define D8 1
#elif PREFER_DOTS == DOT1_ON_RIGHT
#define D1 9
#define D2 6
#define D3 4
#define D4 10
#define D5 7
#define D6 5
#define D7 1
#define D8 2
#endif // PREFER_DOTS

#endif // USB_PORT_POSITION
