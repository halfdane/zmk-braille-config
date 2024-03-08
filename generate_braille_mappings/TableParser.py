from SingleRuleParser import SingleRuleParser, IncludeRule

LOUIS_TABLES_DIR = "../liblouis/tables"

        
class TableParser:
    def __init__(self, path) -> None:
        self.path = path
        self.rules = self.table_expanded(path)

    def read_file(self, path):
        path = LOUIS_TABLES_DIR + "/" + path
        linenumber = 0
        with open(path, "r") as f:
            while line := f.readline():
                linenumber += 1
                if line.strip() and not line.strip().startswith("#"):
                    yield linenumber, line.strip()

    def table_expanded(self, path):
        rules = []
        rules_by_ruletype = {}
        for linenumber, line in self.read_file(path):
            rule = SingleRuleParser(path, linenumber, line).rule()

            already_seen_dot_patterns, rule_by_type = rules_by_ruletype.get(type(rule), (set(), []))

            if type(rule) == IncludeRule:
                more_rules = self.table_expanded(rule.filename)
                for a_type, (dot_patterns, some_rules) in more_rules.items():
                    for a_rule in some_rules:
                        if a_rule.braille_chars not in already_seen_dot_patterns:
                            already_seen_dot_patterns.add(a_rule.braille_chars)
                            rule_by_type.append(a_rule)
                            rules_by_ruletype[a_type] = (already_seen_dot_patterns, rule_by_type)

            elif rule:
                # add current rule only if it is not an include rule
                # and it is not empty
                already_seen_dot_patterns.add(rule.braille_chars)
                rule_by_type.append(rule)
                rules_by_ruletype[type(rule)] = (already_seen_dot_patterns, rule_by_type)
                # rules.append(rule)
        print(rules_by_ruletype)
        return rules_by_ruletype


