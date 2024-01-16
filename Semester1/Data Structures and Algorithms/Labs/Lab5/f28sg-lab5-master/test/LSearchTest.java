import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class LSearchTest {

	LSearch ls;
	/*
	 * Part 1: complete unit tests
	 */
	
	@Before
	public void setup(){
		ls = new LSearch();
		// doesn't have to be ordered!
		ls.addAtHead(new Entry("Andrew",111));
		ls.addAtHead(new Entry("Ewen",321));
		ls.addAtHead(new Entry("Peter",123));
		ls.addAtHead(new Entry("Roger",222));
		
	}
	
	@Test
	public void testLinearSearchOK() {
		// test the linear search method for someone who's in the collection
		assertTrue(ls.linearSearch("Ewen") == 321);
	}

	@Test
	public void testLinearSearchFail() {
		// test the linear search method for someone who's not in the collection
		assertTrue(ls.linearSearch("Tomas") == -1);
	}

}
