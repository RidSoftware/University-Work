# Q4a

# s1 and s2 represent tuple
def threatening(s1, s2):
	# checks Rook moves
	if s1[0] == s2[0] or s1[1] == s2[1]:
		return True


	# list of knight moves
	knight_m = [(1, 2), (2, 1), (2, -1), (1, -2),(-1, -2), (-2, -1), (-2, 1), (-1, 2)]

	# checks Knight moves
	for m in knight_m:
		if (s1[0] + m[0], s1[1] + m[1]) == s2:
			return True

	return False


# Q4b

#sqs represent list of squares
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

 
# Q4c

#helper function for genereating every possible combination of knooks on the board
def allKnooksHelper(sqs):
	allCombs = []

	#iterate through the every square
	for i in range(len(sqs)):
		#create a list of all square other than the current square
		sqsMinus_i = sqs[i] + sqs[i+1]
		#recursively calls the helper to iterate through other square
		allCombsMinus_i = allKnooksHelper(sqs)

		#adds the combination onto the new list
		for combs in allCombsMinus_i:
			allCombs += [combs]

	return allCombs


def allKnooks(n): 
	#generates a list of all squares on the board
	sqs = [(x, y) for x in range(n) for y in range(n)]

	#calls the helper to generate possible combinations
	allCombs = allKnooksHelper(sqs)

	#generates a list of all combinations that are safeConfigs
	validCombs = [combs for combs in allCombs if safeConfig(combs)]

	return validCombs


