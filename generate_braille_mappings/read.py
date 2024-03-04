from enum import Enum
import pprint
from braille import BrailleDot, BrailleChar, BrailleChars
import re

LOUIS_TABLES_DIR = "../liblouis/tables"

class Constraint(Enum):
    Nofor = "Nofor"
    Noback = "Noback"
    Nocross = "Nocross"

class LouisParser:
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
    
    def peek(self):
        if self.i < len(self.tokens):
            return self.tokens[self.i]
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
    
        
    def explicit_dots(self, dots_description: str):
        chars = dots_description.split('-')
        chars = BrailleChars.from_string_list(chars)
        return chars
    
    def debug(self, retval):
        if "char" in retval:
            char_or_mod = retval["char"]
        else:
            char_or_mod = retval["modifier"]
            
        if "braille_chars" in retval:
            braille_or_value = retval["braille_chars"].to_unicode()
            braille = retval["braille_chars"]
        else:
            braille_or_value = retval["value"]
            braille = ""
        print(f'{self.path}:{self.linenumber} {char_or_mod} {braille_or_value} {braille} {self.line}')

    def add_regular_braille_definition(self, retval):
        utf8_char = self.to_utf8(self.next())
        braille_chars = self.explicit_dots(self.next())
        retval["char"] = utf8_char
        retval["braille_chars"] = braille_chars


    def rule(self):
        try:
            return self._rule()
        except Exception as e:
            print(f"Error in {self.path}:{self.linenumber} {self.line}")
            raise e

    def _rule(self):
        self.consume_irrelevant_tokens()
        
        retval = {}
        if opcode := self.next():
            retval["opcode"] = opcode
            match opcode:
                case "include": 
                    retval["filename"] = self.next()
                case "undefined": 
                    print(f"undefined {self.path}:{self.linenumber} {self.line}")
                case "display":
                    # no display on a keboard
                    return None
                case "multind":
                    # no fancy backtranslation here
                    return None
                case "space":
                    # ignoring spaces - keyboard has an explicit space key
                    return None
                case "punctuation":
                    self.add_regular_braille_definition(retval)
                case "digit":
                    self.add_regular_braille_definition(retval)
                case "letter":
                    # This is intended for letters which are neither uppercase nor lowercase
                    self.add_regular_braille_definition(retval)
                case "base":
                    # seems like base is just meta information
                    return None
                case "lowercase":
                    self.add_regular_braille_definition(retval)
                case "uppercase":
                    # uppercase is the same as lowercase just shifted
                    return None
                case "litdigit":
                    self.add_regular_braille_definition(retval)
                case "math":
                    self.add_regular_braille_definition(retval)
                # Braille Indicator Opcodes
                case "capsletter":
                    retval["modifier"] = "oneshot-caps"
                    retval["braille_chars"] = self.explicit_dots(self.next())
                case "begcapsword":
                    retval["modifier"] = "capsword"
                    retval["braille_chars"] = self.explicit_dots(self.next())
                case "capsmodechars":
                    retval["modifier"] = "capsmodechars"
                    retval["value"] = self.next()
                case "numsign":
                    retval["modifier"] = "numbers"
                    retval["braille_chars"] = self.explicit_dots(self.next())
                case "numericnocontchars":
                    retval["modifier"] = "numericnocontchars"
                    retval["value"] = self.next()
                case "numericmodechars":
                    retval["modifier"] = "numericmodechars"
                    retval["value"] = self.next()
                case "midendnumericmodechars":
                    retval["modifier"] = "midendnumericmodechars"
                    retval["value"] = self.next()
                case "always":
                    self.add_regular_braille_definition(retval)
                case "sign":
                    self.add_regular_braille_definition(retval)

                case "grouping":
                    # not supported
                    pass
                case "modeletter":
                    # not supported
                    pass
                case "begmodeword":
                    pass
                case "endcapsword":
                    # not supported
                    pass
                case "begcaps":
                    # not supported
                    pass
                case "endcaps":
                    # not supported
                    pass
                case "begcapsphrase":
                    # not supported
                    pass
                case "endcapsphrase":
                    # not supported
                    pass
                case "lencapsphrase":
                    # not supported
                    pass
                case "letsign":
                    # not supported
                    pass
                case "noletsign":
                    # not supported
                    pass
                case "noletsignbefore":
                    # not supported
                    pass
                case "noletsignafter":
                    # not supported
                    pass
                case "nocontractsign":
                    # not supported
                    pass
                case "nonumsign":
                    # not supported
                    pass

                case "begmodephrase":
                    # not supported
                    pass
                case "endmodephrase":
                    # not supported
                    pass
                case "lenmodephrase":
                    # not supported
                    pass

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
                        | "sufword" | "prfword" | "begword" | "begmidword" | "midword" | "midendword" | "endword" | "partword" | "exactdots" \
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
                case _: 
                    return None

        return retval
        
    
def table(text, path):
    rule_lines = [(linenumber, line) for linenumber, line in enumerate(text.splitlines()) 
                  if not line.strip().startswith("#") and line.strip()]
                  
    rules = [LouisParser(path, linenumber, line).rule() for linenumber, line in rule_lines]
    rules = [rule for rule in rules if rule]
    return rules

def read_to_string(path):
    path = LOUIS_TABLES_DIR + "/" + path
    with open(path, "r") as f:
        return f.read()
    
def table_file(path):
    text = read_to_string(path)
    return table(text, path)

def table_expanded(path):
    rules = table_file(path)
    for rule in rules:
        if rule["opcode"] == "include":
            path = rule["filename"]
            rules.extend(table_expanded(path))

    return rules

rules = table_expanded("de-g0.utb")

# remove rules with virtual dots
rules = [rule for rule in rules if "braille_chars" in rule and not rule["braille_chars"].has_virtual_dots()]


# for rules with opcodes 'always', 'lowercase', 'punctuation', 'sign'
# if rules have same braille_chars, keep the first
# not sure if this is the right thing to do
# # seen = dict()
# # _rules = []
# # for rule in rules:
# #     if rule["opcode"] in ["always", "lowercase", "punctuation", "sign"]:
# #         if "braille_chars" in rule and rule["braille_chars"] in seen:
# #             print(f"Duplicate {rule} {seen[rule['braille_chars']]}")
# #         else:
# #             seen[rule["braille_chars"]]= rule
# #             _rules.append(rule)
# #     else:
# #         _rules.append(rule)
# # rules = _rules


# order by opcode then by char
rules = sorted(rules, key=lambda x: (x["opcode"], x.get("char", "")))

for rule in rules:
    print(rule)

