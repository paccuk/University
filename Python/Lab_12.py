import struct

from Lab_11 import zadanie_2 as zd2


def examples():
    a = 7
    b = struct.pack("i", a)
    print(b)
    print(struct.unpack("i", b))

    a = 10123**16
    print(a)
    b = a.to_bytes(30, "big")
    print(b)
    c = int.from_bytes(b, "big")
    print(c)

    s = "informatyka"
    p = bytes(s, "raw_unicode_escape")
    print(p)
    s2 = p.decode("raw_unicode_escape")
    print(s2)


def zadanie_1():
    iris = zd2()
    # print(*iris, sep=",\n")

    with open("zad1.bin", "wb") as file:
        header = ",".join(iris[0]) + "\n"
        file.write(bytes(header, "raw_unicode_escape"))

        for row in iris[1:]:
            file.writelines(
                map(
                    lambda x: struct.pack("f", x)
                    if isinstance(x, float)
                    else bytes(x + "\n", "raw_unicode_escape"),
                    row,
                )
            )

if __name__ == "__main__":
    zadanie_2()
