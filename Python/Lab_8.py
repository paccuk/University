import datetime


class Ulamek:
    def __init__(self, mianownik, licznik) -> None:
        self.__mianownik = mianownik
        self.__licznik = licznik

    def __mul__(self):
        return self.__licznik * self.__mianownik

    def __add__(self):
        return self.__licznik + self.__mianownik

    def __sub__(self):
        return self.__licznik - self.__mianownik

    def __truediv__(self):
        return self.__licznik / self.__mianownik

    def __repr__(self) -> str:
        return f"Ulamek(mianownik: {self.__mianownik}, licznik: {self.__licznik})"

    def __str__(self) -> str:
        return f"__mul__: {self.__mul__()}\n__add__: {self.__add__()}\n__sub__: {self.__sub__()}\n __truediv__: {self.__truediv__()}"


class Osoba:
    __liczba_osob = 0

    def __init__(
        self,
        pesel: str,
        imie: str,
        nazwisko: str,
        wzrost: float = 0.0,
        waga: float = 0.0,
    ) -> None:
        """
        :param wzrost: meters
        :param waga: kilograms
        """
        self.__pesel = pesel
        self.__imie = imie
        self.__nazwisko = nazwisko
        self.__wzrost = wzrost
        self.__waga = waga
        self.__rok_urodzenia = self.__calculate_birthday()
        Osoba.__liczba_osob += 1

    def set_weight(self, waga):
        self.__waga = waga

    def set_height(self, wzrost):
        self.__wzrost = wzrost

    def get_weight(self):
        return self.__waga

    def get_height(self):
        return self.__wzrost

    def get_age(self):
        return self.__calc_age()

    def __calc_age(self):
        return datetime.datetime.now().year - int(self.__rok_urodzenia)

    def __calculate_birthday(self):
        pesel_str = str(self.__pesel)
        century = pesel_str[2]

        true_century = str(19)

        if int(century) > 1:
            true_century = str(20)

        return true_century + pesel_str[:2]

    @staticmethod
    def get_instances_count():
        return Osoba.__liczba_osob

    @classmethod
    def create_person(
        cls, pesel: str, imie: str, nazwisko: str, wzrost: float, waga: float
    ):
        """
        :param wzrost: meters
        :param waga: kilograms
        """
        cls.__pesel = pesel
        cls.__imie = imie
        cls.__nazwisko = nazwisko
        cls.__wzrost = wzrost
        cls.__waga = waga
        cls.__rok_urodzenia = cls.__calculate_birthday(cls)
        Osoba.__liczba_osob += 1

    def __hash__(self) -> int:
        return int(self.__pesel)

    def __str__(self) -> str:
        return f"{self.__pesel}, {self.__imie} {self.__nazwisko}"

    def __repr__(self) -> str:
        return f"Osoba({self.__pesel!r}, {self.__imie!r}, {self.__nazwisko!r}, {self.__wzrost!r}, {self.__waga!r})"

    def __del__(self) -> None:
        Osoba.__liczba_osob -= 1


def zadanie_1():
    ulamek = Ulamek(mianownik=15, licznik=3)
    print(ulamek)
    print(ulamek.__repr__())


def zadanie_2():
    osoba = Osoba("81010200141", "Oleg", "Napas", 1.80, 70.4)
    print(osoba)


def zadanie_3():
    osoby = [
        Osoba("81010200141", "Oleg", "Napas", 1.80, 70.4),
        Osoba("81010200141", "Taras", "Napas", 1.80, 70.4),
        Osoba("81010200141", "Napas", "Oleg", 1.80, 70.4),
        Osoba("81010200141", "Napas", "Taras", 1.80, 70.4),
        Osoba("81010200141", "Oras", "Toleg", 1.80, 70.4),
    ]
    print(osoby)
    print(osoby[4]._Osoba__liczba_osob)


def zadanie_4():
    osoba = Osoba("81010200141", "Oleg", "Napas", 1.80, 70.4)
    print(osoba)
    print(repr(osoba))
    eval(repr(osoba))


def zadanie_5():
    osoba = Osoba("81010200141", "Oleg", "Napas")
    print(osoba.get_age())
    print(osoba.get_weight())
    print(osoba.get_height())

    osoba.set_height(1.5)
    osoba.set_weight(67.2)
    print(osoba.get_height())
    print(osoba.get_weight())

    print(osoba.get_instances_count())

    osoba2 = Osoba.create_person("81010200141", "Oleg", "Napas", 1.80, 70.4)
    print(osoba2.get_age())
    print(osoba2.get_weight())
    print(osoba2.get_height())

    print(Osoba.get_instances_count())

