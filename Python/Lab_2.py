WHITE_ENDLINE = "\x1b[0m"


def zadanie_1():
    array = [0, -2, 1, 7, 3, 4]
    print(array[::-1])


def zadanie_2():
    x = int(input("Wpisz pierwsza liczbe: "))
    y = int(input("Wpisz druga liczbe: "))
    z = int(input("Wpisz trzecia liczbe: "))
    c = int(input("[1] Suma\n[2] Roznica\n[3] Iloczyn\n[Inne] Iloraz\nWybierz: "))

    match c:
        case 1:
            return x + y + z
        case 2:
            return x - y - z
        case 3:
            return x * y * z
        case _:
            try:
                return x / y / z
            except ZeroDivisionError as err:
                print(err)


def zadanie_3():
    wzrost_m = float(input("Wpisz wzrost w centymetrach: ")) / 100
    waga_kg = float(input("Wpisz wage w gramach: ")) / 1000

    bmi = round(waga_kg / wzrost_m**2, 1)

    print(f"\nWzrost:, {wzrost_m} m\nWaga: {waga_kg} kg")

    if bmi < 18.5:
        print(
            "\x1b[0;30;43m" + f"Waga ponizej normy: {bmi}(BMI) < 18.5" + WHITE_ENDLINE
        )
    elif 18.5 <= bmi and bmi < 25:
        print(
            "\x1b[0;30;42m" + f"Waga normalna: 18.5 <= {bmi}(BMI) < 25" + WHITE_ENDLINE
        )
    elif 25 <= bmi and bmi < 30:
        print(
            "\x1b[0;30;41m"
            + f"Waga ponadnormowa: 25 <= {bmi}(BMI) < 30"
            + WHITE_ENDLINE
        )


def zadanie_4():
    height = int(input("Wpisz wysokosc: "))

    for i in range(height):
        print("X" * (i + 1))


def zadanie_5():
    array = [21, 2, 221, 122, 321, 241, 3421, 4231]
    num = 21

    for i in array:
        if str(num) in str(i):
            print(i)


def zadanie_6():
    catalana = 1
    even_numbers = 0
    i = 0
    while catalana < 1000000:
        print(catalana)
        catalana = ((4 * i + 2) / (i + 2)) * catalana

        if catalana % 2 == 0:
            even_numbers += 1

        i += 1
    print("Ilosc liczb parzystych:", even_numbers - 1)


def zadanie_7():
    print([i for i in range(1, 8, 3)] * 3)


def zadanie_8():
    ilosc_pierwszych_liczb = int(input("Wpisz ilosc pierwszych do wyswietlenia: "))
    cnt = 0
    i = 0
    flag = False

    while cnt < ilosc_pierwszych_liczb:
        if i > 1:
            for j in range(2, int(i / 2) + 1):
                if i % j == 0:
                    flag = True
                    break

            if not flag:
                print(i, end=" ")
                cnt += 1

            flag = False
        i += 1


def zadanie_9():
    from math import factorial

    row_amount = int(input("Wpisz ilosc wierszy do wyswietlenia: "))

    if row_amount > 0:
        for i in range(row_amount):
            print(" " * (row_amount - i), end=" ")
            for j in range(i + 1):
                print(factorial(i) // (factorial(j) * factorial(i - j)), end=" ")
            print()
    else:
        raise Exception("Liczba musi byc nieujemna!")


# zadanie_1()
# zadanie_2()
# zadanie_3()
# zadanie_4()
# zadanie_5()
# zadanie_6()
# zadanie_7()
# zadanie_8()
zadanie_9()
