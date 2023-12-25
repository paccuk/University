def zadanie_1():
    text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Dolor sed viverra ipsum nunc aliquet bibendum enim. In massa tempor nec feugiat. Nunc aliquet bibendum enim facilisis gravida. Nisl nunc mi ipsum faucibus vitae aliquet nec ullamcorper. Amet luctus venenatis lectus magna fringilla. Volutpat maecenas volutpat blandit aliquam etiam erat velit scelerisque in. Egestas egestas fringilla phasellus faucibus scelerisque eleifend. Sagittis orci a scelerisque purus semper eget duis. Nulla pharetra diam sit amet nisl suscipit. Sed adipiscing diam donec adipiscing tristique risus nec feugiat in. Fusce ut placerat orci nulla. Pharetra vel turpis nunc eget lorem dolor. Tristique senectus et netus et malesuada."

    text = text.lower()
    text = text.replace(",", "")
    text = text.replace(".", "")
    text = text.split(" ")

    unique_words_set = set(text)
    unique_words_count = len(text) - len(unique_words_set)

    print(unique_words_set)
    print(unique_words_count, len(text))


def zadanie_2_and_3():
    A = {2, 4, 6, 8, 10}
    B = {2, 4, 5, 10}

    print(A <= B)
    print(A >= B)
    print(A.intersection(B))
    print(A.union(B))
    print(A.difference(B))
    print(A.symmetric_difference(B))

    cartesian_prod = []

    for numA in A:
        row = []
        for numB in B:
            row.append(numA * numB)
        cartesian_prod.append(row) 

    print(cartesian_prod)

def zadanie_4():
    nums = {
        1: 'one',
        2: 'two',
        3: 'three',
        4: 'four',
        5: 'five',
        6: 'six',
        7: 'seven',
        8: 'eight',
        9: 'nine',
        10: 'ten',
        11: 'eleven',
        12: 'twelve',
        13: 'thirteen',
        14: 'fourteen',
        15: 'fifteen',
        16: 'sixteen',
        17: 'seventeen',
        18: 'eighteen',
        19: 'nineteen',
        20: 'twenty',
        30: 'thirty',
        40: 'forty',
        50: 'fifty',
        60: 'sixty',
        70: 'seventy',
        80: 'eighty',
        90: 'ninety'
    }

    in_num = input("Type number: ")
    int_num = int(in_num)

    if int_num in nums:
        print(nums[int_num])

    else:
        print(nums[int(in_num[0]) * 10], nums[int(in_num[1])])

zadanie_4()
