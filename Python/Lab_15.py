import numpy as np


def zadanie_1():
    iris = np.genfromtxt(
        "irisP.txt", dtype=None, delimiter=",", names=None, encoding="UTF-8"
    )

    irisplants = set(irisplant[4] for irisplant in iris[1:])
    avgs = {}.fromkeys(irisplants, 0)

    for irisp in irisplants:
        sepl_sum = 0
        sepw_sum = 0
        petl_sum = 0
        petw_sum = 0
        cnt = 0

        for irisplant in iris[1:]:
            if irisplant[4] == irisp:
                sepl_sum += float(irisplant[0])
                sepw_sum += float(irisplant[1])
                petl_sum += float(irisplant[2])
                petw_sum += float(irisplant[3])
                cnt += 1

        irp_avg = [
            round(sepl_sum / cnt, 4),
            round(sepw_sum / cnt, 4),
            round(petl_sum / cnt, 4),
            round(petw_sum / cnt, 4),
        ]

        avgs[irisp] = irp_avg
    print(avgs)

    return avgs


def zadanie_2():
    iris = np.genfromtxt(
        "irisP.txt",
        missing_values="",
        filling_values=0,
        dtype=None,
        delimiter=",",
        names=True,
        encoding="UTF-8",
    )
    # print(iris)
    avgs = zadanie_1()


if __name__ == "__main__":
    zadanie_1()
