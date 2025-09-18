class A:
    def hello(self):
        print("Hello from A")

class B(A):
    def hello(self):
        print("Hello from B")
        super().hello()

class C(A):
    def hello(self):
        print("Hello from C")
        super().hello()

class D(B, C):
    def hello(self):
        print("Hello from D")
        super().hello()

class E(C): # Task 1
    def hello(self):
        print("Hello from E")
        super().hello()

class F(B,E): # Task 2
    def hello(self):
        print("Hello from F")
        super().hello()

Task1 = E()
Task1.hello()
print("-----")
Task2 = F()
Task2.hello()
print(F.mro())
"""
The order is F-B-E-C-A(-object) as...
- C has order C-A,
- and therefore E has order E-C-A,
- B has order B-A,
- F merges B-A and E-C-A and therefore has order F-B-E-C-A
"""
print("-----")
class G(C,B):
    def hello(self):
        print("Hello from G")
        super().hello()

class H(G,D):
    def hello(self):
        print("Hello from H")
        super().hello()

Task3 = H()
Task3.hello()
print(H.mro())
"""
MRO conflict error:
- D has D-B-C-A but G has G-C-B-A
"""
