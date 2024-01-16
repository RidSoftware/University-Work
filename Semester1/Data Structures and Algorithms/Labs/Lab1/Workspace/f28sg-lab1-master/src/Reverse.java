
public class Reverse {

	// Part 2
	//
	// TODO Where N is the length of array 'arr' the complexity is:
	//
	// O(N)
	public static void reverse(String[] arr){ 
		//creates a stack the size of the array
		Stack st = new Stack(arr.length);

		// for every element in the array, starting from the end element, push  each element to the stack
		for (int i = arr.length; i > 0; i--) {
			st.push(arr[i]);
		}

		//the reverse of pushing the array onto the stack, 
		//popping each element beck to the array should produce the reverse
		for (int i = 0; i < arr.length; i++) {
			arr[i] = st.pop();
		}

	}
	
}
