class Iterate:
    def __init__(self, a=0):
        self.a = a

    def __call__(self):
        self.a += 1
        return self.a


def example1():
    # Jesli chcemy aby przyjmowala parametry
    # def __call__ (self , * arguments , ** keywords ):
    # (1, 2) --- arguemnts
    # (1, 2, x = 3, y = 4) --- arguments + keywords
    i = Iterate()
    print(i())
    print(i())


class Iterate:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __iter__(self):
        return self

    def __next__(self):
        if self.a > self.b:
            raise StopIteration
        else:
            self.a += 1
        return self.a - 1


def IterateFun(a, b):
    a = a
    while a <= b:
        yield a
        a += 1


def example2():
    for i in Iterate(3, 8):
        print(i)

    for i in IterateFun(3, 8):
        print(i)


class Power:
    def __init__(self, base, power) -> None:
        self.__base = base
        self.__power = power

    def __call__(self):
        self.__power += 1

        return self.__base ** (self.__power - 1)


class PowerRange:
    def __init__(self, num, min_pow, max_pow):
        self.num = num
        self.min_pow = min_pow
        self.max_pow = max_pow

    def __iter__(self):
        return self

    def __next__(self):
        if self.min_pow >= self.max_pow:
            raise StopIteration
        else:
            self.min_pow += 1

        return self.num ** (self.min_pow - 1)


class DList:
    class Element:
        def __init__(self, value, next=None, prev=None):
            self.__value = value
            self.__next = next
            self.__prev = prev

        @property
        def value(self):
            return self.__value

        @property
        def next(self):
            return self.__next

        @property
        def prev(self):
            return self.__prev

        @next.setter
        def next(self, next):
            self.__next = next

        @prev.setter
        def prev(self, prev):
            self.__prev = prev

    def __init__(self, args):
        self.__head = None
        self.__tail = None

        for i in args:
            self.insert(i)

    def insert(self, value):
        if not self.__head and not self.__tail:
            new_element = self.Element(value)

            self.__head = new_element
            self.__tail = new_element

        else:
            current = self.__head

            while current:
                if value < current.value:
                    if current == self.__head:
                        current.prev = self.Element(value, next=current)
                        self.__head = current.prev

                    else:
                        new_element = self.Element(
                            value, prev=current.prev, next=current
                        )
                        current.prev.next = new_element
                        current.prev = new_element

                    break

                if current == self.__tail:
                    current.next = self.Element(value, prev=current)
                    self.__tail = current.next
                    break

                current = current.next

    def __iter__(self):
        current = self.__head

        while current:
            yield current.value
            current = current.next

    def __reversed__(self):
        current = self.__tail

        while current:
            yield current.value
            current = current.prev

    def __contains__(self, value):
        current = self.__head

        while current:
            if value == current.value:
                return True

            elif value < current.value or self.__tail == current:
                return False

            current = current.next


def zadanie_1():
    num = Power(2, 1)
    for i in range(5):
        print(num())


def zadanie_2():
    for i in PowerRange(2, 2, 5):
        print(i)


def zadanie_3():
    dlista = DList([2, 3, 4, 5])

    for i in dlista:
        print(i)
    print("\n--------\n")

    dlista = DList([8, 10, 9, 13])
    dlista.insert(7)
    dlista.insert(12)
    dlista.insert(15)

    for i in reversed(dlista):
        print(i)
        print("\n--------\n")
        print("Contain 8: ", 8 in dlista)
        print("Contain 13: ", 13 in dlista)
        print("Contain 15: ", 15 in dlista)
        print("Contain 6: ", 6 in dlista)
        print("Contain 11: ", 11 in dlista)
        print("Contain 17: ", 17 in dlista)


if __name__ == "__main__":
    zadanie_3()
