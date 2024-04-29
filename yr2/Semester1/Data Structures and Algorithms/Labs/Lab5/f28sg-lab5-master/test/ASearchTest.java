import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class ASearchTest {

	ASearch as;
	/*
	 * Part 1: complete unit tests
	 */
	@Before
	public void setup(){
		as = new ASearch();
		as.addEntry(new Entry("Andrew",111));
		as.addEntry(new Entry("Ewen",321));
		as.addEntry(new Entry("Peter",123));
		as.addEntry(new Entry("Roger",222));
		
	}
	
	@Test
	public void testLinearSearchOK() {
		// test the linear search method for someone who's in the collection
		assertTrue(as.linearSearch("Ewen") == 321);
	}

	@Test
	public void testLinearSearchFail() {
		// test the linear search method for someone who's not in the collection
		assertTrue(as.linearSearch("Tomas") == -1);
	}
	
	@Test
	public void testBinarySearchOK() {
		// test the binary search method for someone who's in the collection
		;assertTrue(as.binarySearch("Ewen") == 321);
	}
	
	@Test
	public void testBinarySearchFail() {
		// test the binary search method for someone who's not in the collection
		assertTrue(as.binarySearch("Tomas") == -1);
	}

}
