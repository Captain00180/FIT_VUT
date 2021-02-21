

data = [i for i in range(10)]

def foo(num):
    global data
    data [num] = "Hit"
    return data

