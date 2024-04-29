import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;


public class StackTest {

	Stack st;
	@Before
	public void setup()
	{
		st = new Stack(2);
	}
	
	/*
	 * Part1: complete the following test methods as specified. 
	 * Note that you will need to add new methods in order to test that exceptions are thrown
	 */
	
	@Test
	public void testPushEmptySize() {
		//assertEquals method comparing the result of the st.size() method *which should be empty* to 0
		assertEquals(0, st.size());
	}
	
@Test
	public void testPushNonEmptySize() {
		st.push("A");
		st.push("B");
		// AssertEquals method similar to empty push size, but instead checking that it is the right size, 2(as there are 2 elements A & B)
		assertEquals(2, st.size());
	}
	
	@Test
	public void testPopTwo() {
		st.push("A");
		st.push("B");
		// Check that st.pop() pops the correct element, "B" as it was the last to be pushed 
		assertEquals("B", st.pop());
		// Check that the seccond element popped is "A", as "B" should be popped already
		assertEquals("A", st.pop());
	}
	
	@Test
	public void testTopTwo() {
		st.push("A");
		// checks that A is at the top of the stack
		assertEquals("A", st.top());
		// checks that st.top(), returns the same value after being called twice, as st.top() should change the contents of the stack
		assertEquals("A",st.top());
	}
	
	
	@Test(expected = StackException.class)
	public void testEmptyPop() {
		// try popping from an empty stack, which should through the expected StackException
		st.pop(); //exception should be thrown here
	}

	@Test(expected = StackException.class)
	public void testFullPush() {
		// try pushing too many elements to the stack
		st.push("A");
		st.push("B");
		st.push("C"); // this should throw the expected exception as the stack is only of size 2
	}

}
