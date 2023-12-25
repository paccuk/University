def fill_list_with_data(file, iris: list):
    header = file.readline()

    iris.append(list(map(lambda x: x.strip(), header.split(","))))
    data = file.readlines()

    for row in data:
        try:
            elem = []
            for i in row.split(","):
                elem.append(float(i.strip()))

        except ValueError:
            elem.append(i.strip())

        iris.append(elem)
    return iris


def zadanie_2():
    iris = []

    with open("iris.txt", "r") as file:
        iris = fill_list_with_data(file, iris)

    return iris


if __name__ == "__main__":
    iris = zadanie_2()
    print(*iris, sep=",\n")
    # print(iris)
