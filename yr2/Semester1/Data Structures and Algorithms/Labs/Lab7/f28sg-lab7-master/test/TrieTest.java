import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.Arrays;

import org.junit.Before;
import org.junit.Test;

public class TrieTest {

	/*
	 * Part 1: complete
	 */

	Trie trie;

	@Before
	public void setup() {
		trie = new Trie();
	}
	
	/**
	 * Tests for countAllWords() in the Trie class
	 * 
	 * Implement these tests for the first part of Q1
	 */

	@Test
	public void countAllWordsEmptyTest() {
		// test countAllWords() for an empty trie
		assertEquals(0, trie.countAllWords());;
	}

	@Test
	public void countAllWordsTest() {
		// step 1: add some words to the trie
		trie.insert("hello");
		trie.insert("goodbye");
		// step 2: test countAllWords() for the trie
		assertEquals(2, trie.countAllWords());
	}

	/*
	 * More trie tests
	 */

	@Test
	public void searchTrue() {
		trie.insert("balls");
		trie.insert("a");
		trie.insert("balloon");
		assertTrue(trie.search("balls"));
		assertTrue(trie.search("balloon"));
		assertTrue(trie.search("a"));
	}

	@Test
	public void searchFalse() {
		trie.insert("balls");
		assertFalse(trie.search("bug"));
	}

	@Test
	public void deleteSearch() {
		trie.insert("balls");
		trie.insert("a");
		trie.insert("balloon");
		trie.delete("a");
		assertTrue(trie.search("balls"));
		assertTrue(trie.search("balloon"));
		assertFalse(trie.search("a"));
		trie.delete("balls");
		assertFalse(trie.search("balls"));
		assertTrue(trie.search("balloon"));
		assertFalse(trie.search("a"));
		trie.delete("balloon");
		assertFalse(trie.search("balls"));
		assertFalse(trie.search("balloon"));
		assertFalse(trie.search("a"));
	}
	
	/*
	 * Optional part: uncomment the four tests below if you wish to test your
	 * implementation.
	 */

//	@Test
//	public void  areWordsWithPrefixTestTrue() {
//		trie.insertString("balls");
//		trie.insertString("balloon");
//		trie.insertString("ball");
//		trie.insertString("football");
//		assertTrue(trie.areWordsWithPrefix("ball"));
//	}

//	@Test
//	public void  areWordsWithPrefixTestFalse() {
//		trie.insertString("balls");
//		trie.insertString("balloon");
//		trie.insertString("ball");
//		trie.insertString("football");
//		assertFalse(trie.areWordsWithPrefix("baboon"));
//	}
	
//	@Test
//	public void wordsWithPrefixTestTrue() {
//		trie.insert("balls");
//		trie.insert("balloon");
//		trie.insert("ball");
//		trie.insert("football");
//		String[] strings = {"ball","balloon","balls"};
//		ArrayList<String> expected = new ArrayList<String>(Arrays.asList(strings));
//		assertEquals(expected, trie.wordsWithPrefix("ba"));
//	}
//	
//	@Test
//	public void wordsWithPrefixTestFalse() {
//		trie.insert("balls");
//		trie.insert("balloon");
//		trie.insert("ball");
//		trie.insert("football");
//		String[] strings = {"ball","balloon","balls"};
//		ArrayList<String> expected = new ArrayList<String>(Arrays.asList(strings));
//		assertNotEquals(expected, trie.wordsWithPrefix("foot"));
//	}

}
