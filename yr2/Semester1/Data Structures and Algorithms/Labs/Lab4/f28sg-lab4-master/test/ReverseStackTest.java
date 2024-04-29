import static org.junit.Assert.*;

import org.junit.Test;


public class ReverseStackTest {

	@Test
	public void reverseStackStringsTest() {
		// The <String> syntax uses generics to say:
		//   "This is a stack of String values"
		Stack<String> st = new Stack<String>(5);
		st.push("A");
		st.push("B");
		st.push("C");
		ReverseStack.reverseStack(st);
		assertEquals("A",(String) st.pop());
		assertEquals("B",(String) st.pop());
		assertEquals("C",(String) st.pop());
	}
	
	@Test
	public void reverseStackIntegersTest() {
		// All we changed what the type parameter to <Integer>
		//
		// This generics version of the Stack class
		// is good because it allows code to be reused, there
		// is only a single implementation of Stack for all classes.
		// There is less code to write, test and maintain.
		Stack<Integer> st = new Stack<Integer>(5);
		st.push(1);
		st.push(2);
		st.push(3);
		ReverseStack.reverseStack(st);
		assertEquals(Integer.valueOf(1), st.pop());
		assertEquals(Integer.valueOf(2), st.pop());
		assertEquals(Integer.valueOf(3), st.pop());
	}


}
