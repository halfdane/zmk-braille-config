from braille import BrailleChars
import re
from dataclasses import dataclass

LOUIS_TABLES_DIR = "../liblouis/tables"

@dataclass(frozen=True, eq=True, order=True)
class Rule:
    opcode: str
    rule_file: str
    linenumber: int

@dataclass(frozen=True, eq=True, order=True)
class IncludeRule(Rule):
    filename: str

@dataclass(frozen=True, eq=True, order=True)
class BrailleRule(Rule):
    char: str
    braille_chars: BrailleChars

    def __str__(self) -> str:
        return "{:<5} {: <20} {: <20}".format(self.char, self.braille_chars.short_str(), f"{self.rule_file}:{self.linenumber}")

@dataclass(frozen=True, eq=True, order=True)
class DigitRule(BrailleRule):
    pass

@dataclass(frozen=True, eq=True, order=True)
class CharOrSignRule(BrailleRule):
    pass


@dataclass(frozen=True, eq=True, order=True)
class LayerRule(Rule):
    modifier: str
    braille_chars: BrailleChars

@dataclass(frozen=True, eq=True, order=True)
class MetaRule(Rule):
    value: str

class SingleRuleParser:
    def __init__(self, path, linenumber, line):
        self.path = path
        self.linenumber = linenumber
        self.line = line
        self.tokens = line.split()
        self.i = 0

    def next(self):
        if self.i < len(self.tokens):
            self.i += 1
            return self.tokens[self.i - 1]
        return None
    
    def next_if_eq(self, token):
        if self.i < len(self.tokens):
            if self.tokens[self.i] == token:
                self.i += 1
                return True
        return False

    def consume_irrelevant_tokens(self):
        self.next_if_eq("nofor")
        self.next_if_eq("noback")
        self.next_if_eq("nocross")

        while self.next_if_eq("before") or self.next_if_eq("after"):
            self.next()

        while self.next_if_eq("empmatchbefore") or self.next_if_eq("empmatchafter"):
            pass
    
    # catch four digit hex numbers
    hex_re = re.compile(r"\\x([0-9a-fA-F]{4})")
    
    def to_utf8(self, codepoint):
        # extract the hex number
        hex = self.hex_re.search(codepoint)
        if hex:
            nr = hex.group(1)
            return chr(int(nr, 16))
        else:
            return codepoint

    def rule(self) -> Rule:
        try:
            return self._rule()
        except Exception as e:
            print(f"Error in {self.path}:{self.linenumber} {self.line}")
            raise e

    def _rule(self) -> Rule:
        self.consume_irrelevant_tokens()
        
        retval = {}
        if opcode := self.next():
            retval["opcode"] = opcode
            match opcode:
                case "include":
                    return IncludeRule(opcode=opcode, filename=self.next(), rule_file=self.path, linenumber=self.linenumber)
                case "punctuation" | "letter" | "lowercase" | "math" | "always" | "sign" | "partword":
                    utf8_char = self.to_utf8(self.next())
                    braille_chars = BrailleChars.from_string_list(self.next().split('-'))
                    return CharOrSignRule(opcode=opcode, char=utf8_char, braille_chars=braille_chars, rule_file=self.path, linenumber=self.linenumber)
                case "digit" | "litdigit":
                    utf8_char = self.to_utf8(self.next())
                    braille_chars = BrailleChars.from_string_list(self.next().split('-'))
                    return DigitRule(opcode=opcode, char=utf8_char, braille_chars=braille_chars, rule_file=self.path, linenumber=self.linenumber)
                case "capsletter" | "begcapsword" | "numsign":
                    braille_chars = BrailleChars.from_string_list(self.next().split('-'))
                    return LayerRule(opcode=opcode, modifier="numbers", braille_chars=braille_chars, rule_file=self.path, linenumber=self.linenumber)
                # configuration for Opcodes
                case "capsmodechars" | "numericnocontchars" | "numericmodechars" | "midendnumericmodechars":
                    return MetaRule(opcode=opcode, value=self.next(), rule_file=self.path, linenumber=self.linenumber)

                case "base":
                    # seems like base is just meta information
                    return None
                case "uppercase":
                    # uppercase is the same as lowercase just shifted
                    return None
            
                case "display":
                    # no display on a keboard
                    return None
                case "multind":
                    # no fancy backtranslation here
                    return None
                case "space":
                    # ignoring spaces - keyboard has an explicit space key
                    return None

                case "grouping" | "modeletter" | "begmodeword" | "begcaps" | "endcaps" | "begcapsphrase" | "endcapsphrase" | "lencapsphrase" \
                        | "letsign" | "noletsign" | "noletsignbefore" | "noletsignafter" | "nocontractsign" | "nonumsign" \
                        | "begmodephrase" | "endmodephrase" | "lenmodephrase" | "endcapsword":
                    # not supported
                    return None

                # Opcodes for Standing Alone Sequences
                # stand alone sequences are not supported
                case "seqdelimiter" | "seqbeforechars" | "seqafterchars" | "seqafterpattern" | "seqafterexpression":
                    return None

                # Emphasis Opcodes
                # none of the emphasis opcodes are supported
                case "class" | "emphclass" | "begemph" | "endemph" | "noemphchars" | "emphletter" | "begemphword" | "endemphword" \
                        | "emphmodechars" | "begemphphrase" | "endemphphrase" | "lenemphphrase" : 
                    return None

                # Special Symbol Opcodes
                case "decpoint" | "hyphen":
                    # not supported
                    return None

                # Special Processing Opcodes
                # Translation Opcodes
                case "capsnocont" | "compbrl" | "comp6" | "nocont" | "replace":
                    # not supported
                    return None
                case "repeated" | "repword" | "rependword" | "largesign" | "word" | "syllable" | "joinword" | "lowword" | "contraction" \
                        | "sufword" | "prfword" | "begword" | "begmidword" | "midword" | "midendword" | "endword" | "exactdots" \
                        | "prepunc" | "postpunc" | "begnum" | "midnum" | "endnum" | "joinnum":
                    # not supported
                    return None

                # Computer braille and Character-Class Opcodes
                # no computer braille support
                case "begcomp" | "endcomp" | "attribute":
                    return None

                # Swap Opcodes
                # no swap support
                case "swapcd" | "swapdd" | "swapcc":
                    return None

                # Context and Multipass Opcodes
                # no multipass support
                case "context" | "pass2" | "pass3" | "pass4":
                    return None

                # The correct Opcode
                # The match Opcode
                case "correct" | "match" | "literal":
                    # not supported
                    return None
                case "undefined": 
                    raise BaseException(f"undefined {self.path}:{self.linenumber} {self.line}")
                case _: 
                    return None

        return retval
        
