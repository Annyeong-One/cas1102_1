class demo:
    def __new__(cls, *args, **kwargs):
        print("__new__")
        obj = super().__new__(cls)
        return obj
    def __init__(self, value):
        print("__init__")
        self.value = value

d=demo(42)
print(d.value)