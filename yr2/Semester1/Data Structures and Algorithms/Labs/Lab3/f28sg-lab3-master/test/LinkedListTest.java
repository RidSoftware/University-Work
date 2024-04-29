import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;


public class LinkedListTest {

	LinkedList l;
	
	@Before
	public void setup(){
		l = new LinkedList();
	}
	/*
	 * Part 1: implement these methods
	 */
	@Test
	public void testSizeEmpty() {
		// test l.size() for an empty linked list
		assertEquals(0, l.size());
	}

	@Test
	public void testSizeMany() {
		// test l.size() after adding some numbers to the linked list
		l.addAtHead(1);
		l.addAtHead(2);
		l.addAtHead(3);
		
		assertEquals(3, l.size());
	}
	
	@Test
	public void testSizeTwice() {
		// test l.size() twice after adding some numbers to the linked list
		l.addAtHead(1);
		l.addAtHead(2);
		l.addAtHead(3);
		
		assertEquals(3, l.size());
		assertEquals(3, l.size());
	}

	@Test
	public void testTotalEmpty() {
		// test l.total() for an empty linked list
		assertEquals(0, l.total());
	}

	@Test
	public void testTotalMany() {
		// test l.total() after adding some numbers to the linked list
		l.addAtHead(1);
		l.addAtHead(2);
		l.addAtHead(3);
		
		assertEquals(6, l.total());
	}
	
	@Test
	public void testTotalTwice() {
		// test l.total() twice after adding some numbers to the linked list
		l.addAtHead(1);
		l.addAtHead(2);
		l.addAtHead(3);
		
		assertEquals(6, l.total());
		assertEquals(6, l.total());

	}
	
	/*
	 * Optional part
	 */
	
//	@Test
//	public void testReverse() {
//		l.addAtHead(5);
//		l.addAtHead(2);
//		l.addAtHead(10);
//		l.reverse();
//		assertEquals(5, l.removeAtHead());
//		assertEquals(2, l.removeAtHead());	
//		assertEquals(10, l.removeAtHead());	
//	}

}
