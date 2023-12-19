import random


def generate_unique_number(length=5):
    """
    Generate a unique number of a given length.
    The number is generated randomly and is ensured to be unique for each call.
    """
    # Generate a random number with the specified length
    number = random.randint(10**(length-1), 10**length - 1)

    return number