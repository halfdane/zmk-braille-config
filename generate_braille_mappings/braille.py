from typing import List

DOTS = {
    '0': 'DOT0',
    '1': 'DOT1',
    '2': 'DOT2',
    '3': 'DOT3',
    '4': 'DOT4',
    '5': 'DOT5',
    '6': 'DOT6',
    '7': 'DOT7',
    '8': 'DOT8',
    '9': 'DOT9',
    'a': 'DOTA',
    'b': 'DOTB',
    'c': 'DOTC',
    'd': 'DOTD',
    'e': 'DOTE',
    'f': 'DOTF',
}

VIRTUAL_DOTS = {
    'DOT0',
    'DOT9',
    'DOTA',
    'DOTB',
    'DOTC',
    'DOTD',
    'DOTE',
    'DOTF',
}

DOT_TO_HEX = {
    'DOT0': 0x0000,
    'DOT1': 0x0001,
    'DOT2': 0x0002,
    'DOT3': 0x0004,
    'DOT4': 0x0008,
    'DOT5': 0x0010,
    'DOT6': 0x0020,
    'DOT7': 0x0040,
    'DOT8': 0x0080,
    'DOT9': 0x0100,
    'DOTA': 0x0200,
    'DOTB': 0x0400,
    'DOTC': 0x0800,
    'DOTD': 0x1000,
    'DOTE': 0x2000,
    'DOTF': 0x4000,
}


class BrailleDot:
    def __init__(self, dot):
        self.dot = DOTS[dot]

    def is_virtual(self):
        return self.dot in VIRTUAL_DOTS
    
    def to_hex(self):
        return DOT_TO_HEX[self.dot]
    
    def from_char(char):
        try:
            return BrailleDot(char)
        except KeyError:
            raise ValueError(f"Invalid character {char}")

    def __str__(self):
        return self.dot
    
    def __repr__(self):
        return self.__str__()
    
    def __eq__(self, __value: object) -> bool:
        if isinstance(__value, BrailleDot):
            return self.dot == __value.dot
        else:
            return False
    
    def __hash__(self) -> int:
        return hash(self.dot)

class BrailleChar:
    def __init__(self, dots: List[BrailleDot]):
        self.dots = list(dots)

    def from_chars(chars):
        try:
            the_char = BrailleChar(BrailleDot.from_char(c) for c in chars)
            return the_char
        except KeyError:
            raise ValueError(f"Invalid character {chars}")

    def to_unicode(self):
        if any(dot.is_virtual() for dot in self.dots):
            unicode_plane = 0xF0000 # Unicode Supplementary Private Use Area-A
        else:
            unicode_plane = 0x2800 # braille patterns

        hexcodes = [dot.to_hex() for dot in self.dots]
        unicode = unicode_plane | sum(hexcodes)
        return chr(unicode)
    
    def has_virtual_dots(self):
        return any(dot.is_virtual() for dot in self.dots)

    def __str__(self):
        return f"[{', '.join(str(dot) for dot in self.dots)}]"
    
    def __repr__(self):
        return self.__str__()
    
    def __eq__(self, __value: object) -> bool:
        if isinstance(__value, BrailleChar):
            return self.dots == __value.dots
        else:
            return False
    
    def __hash__(self) -> int:
        return hash(tuple(self.dots))
    

class BrailleChars:
    def __init__(self, chars: List[BrailleChar]):
        self.chars = list(chars)

    def from_string_list(strings):
        the_chars = BrailleChars([BrailleChar.from_chars(c) for c in strings])
        return the_chars

    def has_virtual_dots(self):
        return any(char.has_virtual_dots() for char in self.chars)

    def to_unicode(self):
        return ''.join(char.to_unicode() for char in self.chars)
    
    def __str__(self):
        return f"[{', '.join(str(char) for char in self.chars)}]"
    
    def __repr__(self):
        return self.__str__()
    
    def __eq__(self, __value: object) -> bool:
        if isinstance(__value, BrailleChars):
            return self.chars == __value.chars
        else:
            return False

    def __hash__(self) -> int:
        return hash(tuple(self.chars))

