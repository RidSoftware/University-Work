public class ReverseStack {


	/*
	 * 1: complete implementation
	 */
	/** Reverses the order of elements in the given stack
	 * 
	 * TODO Where N is the number of elements in the stack the complexity is:
	 *
	 * O(N)
	 * 
	 * @param st the stack to be reversed
	 */
	public static void reverseStack(Stack st){
		
		Queue q = new Queue();

		//while the stack isnt empty, enqueue via pop until it is empty
		while (st.isEmpty() == false) {
			try {
				q.enqueue(st.pop());
			} catch (StackException e) {
				//prints error message if catches exception from enqueue or pop
				System.out.println(e.getMessage());
			}
		}
		//while the queue isnt empty, push via dequeue until it is empty
		while (q.isEmpty() == false) {
			try {
				st.push(q.dequeue());
			} catch (QueueException e){
				//prints error message if catches exception from dequeue or push
				System.out.println(e.getMessage());
			}
		}

	}
	
	
	
	
}
