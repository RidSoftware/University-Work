// exception used for Q5
class CalculateException extends RuntimeException{    
	public CalculateException(String err) {
		super(err);
	}
}

public class Calculator {

	/*
	 *  Methods for Part 3
	 */
	public static int calculate(String [] cmds){
		Stack pstack = new Stack(100);

		//reverses the array so that numbers are processed first onto the stack
		String[] reversePolishNotation =Reverse.reverse(cmds);

		//for each given command in the reversed cmds array
		for (String cmd: reversePolishNotation) {
			//if element is a number, add to stack
			if (isNumber(cmd)){
				pstack.push(cmd);
			}
			//if an operand, then take the last to numberss off the stack
			//store the 2 numbers as fst and snd,
			//then push the operand and both numbers back onto the stack in polish notation as strings
			else{
				String snd = pstack.pop();
				String fst = pstack.pop();
		
				pstack.push(String.valueOf(applyOp(fst cmd snd)));
			}
		}
		// returns the remaing value as a integer
		return convert(pstack.pop());
	}	

	public static int convert(String s) throws NumberFormatException{
		//returns value as a number/integer
		return Integer.parseInt(s);
	}

	public static boolean isNumber(String s){
		// checks if s can be converted to a number
		try {
			convert(s);
			return true;
		} catch (NumberFormatException e) {
			return false;
		}
	}

	// apply the operator after converting the numbers
	public static int applyOp(String fst,String op,String snd){
		//converts to integer to be used
		first = convert(fst);	
		second = convert(snd);
		
		//calculates based on oprerator
		switch(op){
			case "+":
				return first + second;
			case "-":
				return first - second;
			case "*":
				return first * second;
			case "/":
				return first / second
		}

	}

	// main operation to calculate using Polish notation directly
	//-not implemented-
    public static int calculatePolish(String [] cmds){
    	return -1; // dummy value
    }
}
