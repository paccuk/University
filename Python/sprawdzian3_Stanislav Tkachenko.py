from abc import ABC, abstractmethod


class Computer(ABC):
    @abstractmethod
    def getType(self):
        pass


class Linux(Computer):
    def __init__(self) -> None:
        self.__memory_size = 0

    def getType(self):
        return type(self)

    @property
    def memory_size(self):
        return self.__memory_size

    @memory_size.setter
    def memory_size(self, memory_size):
        if memory_size < 0:
            raise Exception("Rozmiar pamieci nie moze byc ujemny!")

        else:
            self.__memory_size = memory_size


pc = Linux()
pc.memory_size = 16
print(pc.memory_size)
print(pc.getType())

try:
    pc.memory_size = -8
except Exception as err:
    print(err)
