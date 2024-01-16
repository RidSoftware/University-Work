

public class Tail {

	public static int factorial(int n) {
		return -1; // TODO use tailFactorial
	}
	
	private static int tailFactorial(int n,int res){
		if (n == 0)
			return res;
		else 
			return tailFactorial(n-1,n*res);
	}
	
	public static int sum(int n) {
		return -1; // TODO use tailSum
	}
	
	// optional part
	private static int tailSum(int n,int sum){
		return -1; // TODO dummy value to be removed.
	}
		
	
	public static int multiply(int m, int n) {
		return -1; // TODO use tailMultiply
	}
	
	// optional part
	private static int tailMultiply(int m,int n,int sum){
		return -1; // TODO dummy value to be removed.
	}

}
