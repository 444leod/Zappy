
def add_tuples(t1: tuple, t2: tuple):
    return tuple(a + b for a, b in zip(t1, t2))

def turn_left(orientation: tuple):
    if (orientation[0] == 0):
        return (-orientation[1], 0)
    else:
        return (0, orientation[0])
    
def turn_right(orientation: tuple):
    if (orientation[0] == 0):
        return (orientation[1], 0)
    else:
        return (0, -orientation[0])
