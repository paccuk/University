from collections import (
    Counter,
    OrderedDict,
    defaultdict,
    deque,
)


def zadanie_1():
    text = """Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt
    ut labore et dolore magna aliqua. Dolor sed viverra ipsum nunc aliquet bibendum enim.
    In massa tempor nec feugiat. Nunc aliquet bibendum enim facilisis gravida. Nisl nunc mi
    ipsum faucibus vitae aliquet nec ullamcorper. Amet luctus venenatis lectus magna fringilla.
    Volutpat maecenas volutpat blandit aliquam etiam erat velit scelerisque in. Egestas egestas
    fringilla phasellus faucibus scelerisque eleifend. Sagittis orci a scelerisque purus semper eget
    duis. Nulla pharetra diam sit amet nisl suscipit. Sed adipiscing diam donec adipiscing tristique
    risus nec feugiat in. Fusce ut placerat orci nulla. Pharetra vel turpis nunc eget lorem
    dolor. Tristique senectus et netus et malesuada."""

    text = text.lower()
    text = text.replace(",", "")
    text = text.replace(".", "")

    res = Counter(text.split())

    print(res)


def zadanie_2():
    table = [
        ["sunny", 85, 85, False, "no"],
        ["sunny", 80, 90, True, "no"],
        ["overcast", 83, 86, False, "yes"],
        ["rainy", 70, 96, False, "yes"],
        ["rainy", 68, 80, False, "yes"],
        ["rainy", 65, 70, True, "no"],
        ["overcast", 64, 65, True, "yes"],
        ["sunny", 72, 95, False, "no"],
        ["sunny", 69, 70, False, "yes"],
        ["rainy", 75, 80, False, "yes"],
        ["sunny", 75, 70, True, "yes"],
        ["overcast", 72, 90, True, "yes"],
        ["overcast", 81, 75, False, "yes"],
        ["rainy", 71, 91, True, "no"],
    ]
    num_rows = len(table)

    probs = {}
    for col in range(len(table[0])):
        col_values = [row[col] for row in table]
        c = Counter(col_values)

        value_probabilities = {value: count / num_rows for value, count in c.items()}

        probs[col] = value_probabilities

    for k, v in probs.items():
        print(f"\nColumn {k + 1} probabilities:")
        for value, prob in v.items():
            print(f"{value}: {prob:.3f}")

    return probs


def zadanie_3(probs: dict):
    sorted_probs = OrderedDict()

    for k, v in probs.items():
        sorted_column = OrderedDict(sorted(v.items(), key=lambda d: d[1], reverse=True))

        sorted_probs[k] = sorted_column

    for k, v in sorted_probs.items():
        print(f"\nColumn {k + 1} probabilities:")
        for value, prob in v.items():
            print(f"{value}: {prob:.3f}")


def zadanie_5():
    word = deque(input("Type word: "))

    flag = True
    for i in range(len(word) // 2):
        if word.popleft() != word.pop():
            flag = False
            break

    if flag:
        print("Slowo jest polindromem!")
    else:
        print("Slowo nie jest polindromem!")


zadanie_1()
probs = zadanie_2()
zadanie_3(probs)
zadanie_5()
