from collections import namedtuple, Counter, defaultdict
from random import randint


# Zadanie 1
employee = namedtuple("Employee", ["firstName", "lastName", "company", "wage"])
Employee = employee(firstName="Jeff", lastName="Bezos", company="Amazon", wage=1000000)
print(Employee)
print()


# Zadanie 2
text = """In statistics, naive Bayes classifiers are a family of simple probabilistic classifiers
    based on applying Bayes theorem with strong (naive) independence assumptions between the
    features (see Bayes classifier). They are among the simplest Bayesian network models,
    but coupled with kernel density estimation, they can achieve high accuracy levels."""

text = text.lower()
text = text.replace("\n", " ")
text = text.replace(",", "")
text = text.replace(".", "")
text = text.replace("(", "")
text = text.replace(")", "")

res = Counter(text.split())
# print(res)
print(res.most_common(1)) # `bayes` - 3
print()


# Zadanie 3
d = defaultdict(lambda: randint(0, 9))
print(d[1])
print(d[3])
print(d[7])