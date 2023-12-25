import datetime

from math import pi

from abc import ABC, abstractmethod


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
        self.wzrost = wzrost
        self.waga = waga
        self.__rok_urodzenia = self.__calculate_birthday()
        Osoba.__liczba_osob += 1

    @property
    def pesel(self):
        return self.__pesel

    @property
    def imie(self):
        return self.__imie

    @property
    def nazwisko(self):
        return self.__nazwisko

    @property
    def waga(self):
        return self.__waga

    @property
    def wzrost(self):
        return self.__wzrost

    @property
    def rok_urodzenia(self):
        return self.__rok_urodzenia

    @property
    def wiek(self):
        return self.__calc_age()

    @waga.setter
    def waga(self, waga):
        if waga < 0:
            self.__waga = 0
        else:
            self.__waga = waga

    @wzrost.setter
    def wzrost(self, wzrost):
        if wzrost < 0:
            self.__wzrost = 0
        else:
            self.__wzrost = wzrost

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
        return f"{self.__class__.__name__}({self.__pesel!r}, {self.__imie!r}, {self.__nazwisko!r}, {self.__wzrost!r}, {self.__waga!r})"

    def __del__(self) -> None:
        Osoba.__liczba_osob -= 1


class Pracownik(Osoba):
    def __init__(
        self,
        pesel: str,
        imie: str,
        nazwisko: str,
        mz: str,
        pensja: float = 0,
        wzrost: float = 0,
        waga: float = 0,
    ) -> None:
        """
        mz : Miejsce Zatrudnienia
        """
        super().__init__(pesel, imie, nazwisko, wzrost, waga)
        self.__mz = mz
        self.pensja = pensja

    @property
    def mz(self):
        return self.__mz

    @property
    def pensja(self):
        return self.__pensja

    @mz.setter
    def mz(self, mz: str):
        self.__mz = mz

    @pensja.setter
    def pensja(self, pensja: float):
        if pensja < 0:
            self.__pensja = 0
        else:
            self.__pensja = pensja

    def __str__(self):
        return f"{super().__str__()}, {self.__mz}"

    def __repr__(self):
        return f"{self.__class__.__name__}({super().pesel!r}, {super().imie!r}, {super().nazwisko!r}, {self.__mz!r}, {self.__pensja!r}, {super().wzrost!r}, {super().waga!r})"


def zad_1_3():
    baza = {
        Osoba("81010200141", "Oleg", "Napas", 1.80, 70.4),
        Osoba("81010200141", "Napas", "Oleg", 1.80, 70.4),
        Osoba("81010200141", "Noleg", "Onapas", 1.80, 70.4),
        Pracownik("81010200141", "Oleg", "Napas", "Szczecin", 5120, 1.80, 70.4),
        Pracownik("81010200141", "Napas", "Oleg", "Szczecin", 5120, 1.80, 70.4),
    }
    for person in baza:
        print(repr(person))


class Figura(ABC):
    @abstractmethod
    def oblicz_pole(self):
        pass

    @abstractmethod
    def typ_figury(self):
        pass

    def print(self):
        print("Figura: ", self.typ_figury(), ", Pole: ", self.oblicz_pole())


class Kolo(Figura):
    def __init__(self, r) -> None:
        self.r = r

    def oblicz_pole(self):
        return 2 * pi * self.r

    def typ_figury(self):
        return "Kolo"


class Trojkat(Figura):
    def __init__(self, a, h) -> None:
        self.a = a
        self.h = h

    def oblicz_pole(self):
        return self.a * self.h / 2

    def typ_figury(self):
        return "Trojkat"


def zad_4():
    a = 6
    b = 3
    c = 4

    if isinstance(a, (int, float)):
        kolo = Kolo(a)
    else:
        raise TypeError

    if isinstance(b, (int, float)) and isinstance(c, (int, float)):
        trojkat = Trojkat(b, c)
    else:
        raise TypeError
    
    kolo.print()
    trojkat.print()

zad_4()
