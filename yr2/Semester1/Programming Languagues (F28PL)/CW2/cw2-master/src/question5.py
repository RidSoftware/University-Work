# CW2, QUESTION 5

# a. (5 marks) 
def toDecimal(n):
  pass

# TODO: explain your code in a comment below.

# b. (3 marks)
def toFrac(nonrep,rep):
  pass

# TODO: explain your code in a comment below.

# ----------

# We are not running unit tests on the Python coursework.
# One way to check your work is to run this Python file by
# navigating to it in the terminal and then running
# `python3 question5.py`. You should get the results commented
# next to each line if everything is right.

if __name__ == "__main__":
    print("-----(a)-----")
    print(toDecimal(4))  # ([2,5],[])
    print(toDecimal(12)) # ([0,8],[3])
    print(toDecimal(7))  # ([],[1,4,2,8,5,7])
    print("-----(b)-----")
    print(toFrac([2,5],[]))  # (1,4)
    print(toFrac([0,8],[3])) # (1,12)
    print(toFrac([1],[3]))   # (2,15)
