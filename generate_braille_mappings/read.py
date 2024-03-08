from enum import Enum
import itertools
import pprint
from braille import BrailleDot, BrailleChar, BrailleChars
import re
from dataclasses import dataclass
import collections
from TableParser import TableParser
from SingleRuleParser import *

def group_by_dot_pattern(rules):
    the_dots = dict()
    # group by dot pattern
    for rule in rules:
        l = the_dots.get(rule.braille_chars , [])
        l.append(rule)
        the_dots[rule.braille_chars] = l

    return the_dots

def print_dot_groups(rules):
    the_dots = group_by_dot_pattern(rules)

    for dots, some_rules in the_dots.items():
        if len(some_rules) > 1:
            print("DUPLICATE: ", end='')
        matching_chars = "".join([a_rule.char for a_rule in some_rules])
        print(matching_chars, some_rules)

def remove_already_existing(all_rules, final_rules):
    # ignore rules when the utf8 char is already in the final rules
    existing_chars = [rule.char for rule in final_rules]
    return [rule for rule in all_rules if rule.char not in existing_chars]

def do_the_thing():
    rules = TableParser("de-g1.ctb").rules
    # remove rules with virtual dots
    # rules = [rule for rule in rules if 
    #          hasattr(rule, "braille_chars") and not rule.braille_chars.has_virtual_dots() or 
    #          not hasattr(rule, "braille_chars")]
    # for rule in rules:
    #     print(rule)
    
    search = [
        BrailleChar.from_chars("16"),
        BrailleChar.from_chars("126"),
        BrailleChar.from_chars("136"),
    ]


    grouped = dict()
    for rule in rules:
        l = grouped.get(type(rule), [])
        l.append(rule)
        grouped[type(rule)] = l
    
    # for r in [rule for rule in grouped.get(IncludeRule, [])]:
    #     print(r)

    # print_dot_groups( [rule for rule in grouped.get(CharOrSignRule, []) if rule.opcode == "math"])

    always_rules = [rule for rule in grouped.get(CharOrSignRule, []) if rule.opcode == "always"]
    # take the first of duplicate always rules  

    # print("always_rules")
    # print_dot_groups(always_rules)
    # print("DONE")

    # print_dot_groups(grouped[DigitRule])
    # print_dot_groups(grouped[CharOrSignRule])




    # order by opcode then by char
    # rules = sorted(rules, key=lambda x: (x["opcode"], x.get("char", "")))

    # for rule in rules:
    #     print(rule)

# do_the_thing()
stuff = ["1", "2", "3", "4", "5", "6"]
for L in range(len(stuff) + 1):
    for subset in itertools.combinations(stuff, L):
        str_subset = ''.join(subset)
        br = BrailleChar.from_chars(str_subset)
        out = "{:<6} {:<5}".format(br.short_str(), br.to_unicode())
        print(out)


