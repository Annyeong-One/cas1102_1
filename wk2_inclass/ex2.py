class Temperature:
    unit = "Celsius"

    def __init__(self, value):
        self.value = value

    # TODO: Instance method
    def display(self):
        print(f"{self.value} {self.unit}")

    # TODO: Class method with relevant decorator
    @classmethod
    def change_unit(cls, new_unit):
        cls.unit = new_unit

    # TODO: Static method with relevant decorator
    @staticmethod
    def to_fahrenheit(celsius):
        return celsius * 1.8 + 32


t1 = Temperature(100)
t1.display()
print(Temperature.to_fahrenheit(100))
Temperature.change_unit("Kelvin")
t1.display()
# unit is a class attribute, we changed it with change_unit() a class method,
# and therefore upon calling display() afterwards, the printed (displayed) unit
# is "Kelvin"