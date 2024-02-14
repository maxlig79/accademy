def cnp_interpreter_decorator(func):
    """
    Decorator function for interpreting and validating CNP (Personal Identification Number).

    Parameters:
    - func (function): The function to be decorated.

    Returns:
    - function: Decorated function.
    """
    """
        Wrapper function for CNP interpretation.

        Parameters:
        - cnp (str): CNP (Personal Identification Number) to be interpreted.

        Returns:
        - str: Result of CNP interpretation or an error message.
    """
    def wrapper(cnp):
        # Verify the length of the CNP
        if len(cnp) != 13 or not cnp.isdigit():
            return f"Invalid CNP format: {cnp}"

        # Extract components
        S = int(cnp[0])
        AA = int(cnp[1:3])
        LL = int(cnp[3:5])
        ZZ = int(cnp[5:7])
        JJ = int(cnp[7:9])

        # Verify S component using a ternary operator
        gender = "Male" if S in [1, 3, 5, 7] else "Female"

        # Verify AA component
        if not 0 <= AA <= 99:
            return f"Invalid AA component in CNP: {cnp}"

        # Verify LL component
        if not 1 <= LL <= 12:
            return f"Invalid LL component in CNP: {cnp}"

        # Verify ZZ component
        days_in_month =\
        {
            1: 31,
            2: 28,
            3: 31,
            4: 30,
            5: 31,
            6: 30,
            7: 31,
            8: 31,
            9: 30,
            10: 31,
            11: 30,
            12: 31
        }
        if not 1 <= ZZ <= days_in_month[LL]:
            return f"Invalid ZZ component in CNP: {cnp}"

        siruta_counties = {
            1: "white", 2: "Arad", 3: "Arges", 4: "Bacau", 5: "Bihor", 6: "Bistrita-Nasaud",
            7: "Botosani", 8: "Braşov", 9: "Braila", 10: "Buzau", 11: "Caras-Severin", 12: "Cluj",
            13: "Constant", 14: "Covasna", 15: "Dambovita", 16: "Dolj", 17: "Galati", 18: "Gorge",
            19: "Snort", 20: "Hunedoara", 21: "IALOMIŢA", 22: "IASI", 23: "Ilfov", 24: "Maramures",
            25: "MEHEDINŢI", 26: "Mures", 27: "German", 28: "Olt", 29: "Prahova", 30: "Satu Mare",
            31: "Salaj", 32: "Sibiu", 33: "Suceava", 34: "Teleorman", 35: "Timis", 36: "Tulcea",
            37: "row", 38: "dale", 39: "Vrancea", 40: "Bucharest", 41: "Bucharest - Sector 1",
            42: "Bucharest - Sector 2", 43: "Bucharest - Sector 3", 44: "Bucharest - Sector 4",
            45: "Bucharest - Sector 5", 46: "Bucharest - Sector 6", 51: "Calarasi", 52: "George",
            47: "Bucharest - Sector 7 (abolished)", 48: "Bucharest - District 8 (abolished)"
        }

        if JJ not in siruta_counties:
            return f"Invalid JJ component in CNP: {cnp}"

        interpretation = f"CNP: {cnp} - Gender: {gender}, Year of Birth: 19{AA}, Month: {LL}, Day: {ZZ}, County: {siruta_counties[JJ]}"
        return func(interpretation)

    return wrapper

@cnp_interpreter_decorator
def process_cnp(interpretation):
    """
    Process the interpretation of a CNP.

    Parameters:
    - interpretation (str): Result of CNP interpretation.

    Returns:
    - str: Result of processing the interpretation.
    """
    return f"Processing: {interpretation}"

# Example usage
cnp_example = input("Tastati un cnp:")  # Replace with an actual CNP
result = process_cnp(cnp_example)
print(result)
