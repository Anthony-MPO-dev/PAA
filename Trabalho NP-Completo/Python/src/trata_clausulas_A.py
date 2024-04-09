def parse_3CNF_instance(instance_str):
        """
        Analisa uma instância do problema 3CNF-SAT fornecida como uma string.

        Argumentos:
        instance_str -- A instância do problema 3CNF-SAT como uma string.

        Retorna:
        Uma lista de cláusulas na forma de listas de literais.
        """
        clauses = []
        clause_strs = instance_str.split("∧")
        
        for clause_str in clause_strs:
            clause = []
            literals = clause_str.strip().replace("(", "").replace(")", "").split("v")
            for literal in literals:
                clause.append(literal.strip())
            clauses.append(clause)
        
        return clauses

