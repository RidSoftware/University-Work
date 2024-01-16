# CW2, QUESTION 4

# a. (2 marks) 
# s1 and s2 represent tuple
def threatening(s1, s2):
	# checks Rook moves
	if s1[0] == s2[0] or s1[1] == s2[1]:
		return True


	# list of knight moves
	knight_m = [
		# moves in clockwise order
		(1, 2), (2, 1), (2, -1), (1, -2),
		(-1, -2), (-2, -1), (-2, 1), (-1, 2)
	]
	
	# checks Knight moves
	for m in knight_m:
		if (s1[0] + m[0], s1[1] + m[1]) == s2:
			return True

	return False

# b. (6 marks)
#sqs represent list
def safeConfig(sqs):
    # for each knook
    for i in range(len(sqs)):
        # compare to every other knook
        for ii in range(i+1, len(sqs)):
            # checks if pair is threatened
            if threatening(sqs[i], sqs[ii]):
                return False
    #returns true if there is no pair that is threatened
    return True

# Write the OCaml versions of `threatening` and `safeConfig`
# as Python comments below, and ensure you get the same results
# as in your Python versions.

# let threatening p = (* TODO *)

# let safeConfig sqs = (* TODO *)

# c. (4 marks)
def allKnooks(n):
  pass

# TODO: Explain how your code works as a comment below.

# ----------

# We are not running unit tests on the Python coursework.
# One way to check your work is to run this Python file by
# navigating to it in the terminal and then running
# `python3 question4.py`. You should get the results commented
# next to each line if everything is right.

if __name__ == "__main__":
    print("-----(a)-----")
    print(threatening((0,0),(2,2))) # False
    print(threatening((0,0),(1,2))) # True
    print(threatening((0,0),(4,0))) # True
    print("-----(b)-----")
    print(safeConfig([(0,0),(1,1),(2,2)])) # True
    print(safeConfig([(0,0),(1,2),(4,4)])) # False
    print("-----(c)-----")
    print(allKnooks(2))
    print(len(allKnooks(4))) # 8
    print(len(allKnooks(5))) # 20
    print(len(allKnooks(6))) # 94
