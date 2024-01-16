import java.util.ArrayList;
import java.util.Iterator;

public class Trie implements TrieADT {

	private TrieNode rootNode = null;
	static private final char ROOT_NODE_CHAR = '*'; // A dummy char to represent the Root Node

	private class TrieNode { // This is the class that represents a node in the trie
		private char value; // the character contained at this node
		private TrieNode[] subnodes; // the subtrees that stem from this node
		private boolean isValidEnd = false; // We need to know if this node represents the end point of a a valid word

		/**
		 * Constructor for a trie node. It initialises 26 children for A-Z child nodes.
		 * 
		 * @param c the character to exist inside the node
		 */
		public TrieNode(char c) {
			value = c;
			isValidEnd = false;
			subnodes = new TrieNode[26];
			for (int i = 0; i < 26; i++) { // initialise each node to null. 26 nodes for 26 letters
				subnodes[i] = null;
			}
		}

		/**
		 * Inserts a word into a trie
		 * 
		 * @param s the word being inserted into the trie
		 */
		public void insert(String s) {
			int positionOfNextNode = ((int) s.codePointAt(0)) - 97; // 97 is 'a' in ASCII //Where is this character
			// based in the array
			if (subnodes[positionOfNextNode] == null) { // add a new node for this value
				subnodes[positionOfNextNode] = new TrieNode(s.charAt(0));
			}
			if (s.length() == 1) // if this is the last character, and we don't need to add a node, then set the
				// end point to be valid
				subnodes[positionOfNextNode].isValidEnd = true;
			else
				subnodes[positionOfNextNode].insert(s.substring(1)); // add the substring from 1 on to that node
		}

		/**
		 * Removes a word from a trie
		 * 
		 * @param s the word to remove
		 * @return a trie node to return to a parent caller of this method
		 */
		public TrieNode delete(String s) {
			// similar to deleting a linked list, we rebuild the Trie as we return.
			if (s.length() == 0) { // this is the last char
				isValidEnd = false;
			} else {
				int positionOfNextNode = ((int) s.codePointAt(0)) - 97; // 97 is 'a' in ASCII
				if (subnodes[positionOfNextNode] == null) {
					return this; // we don't have the word at all
				} else { // there are still more characters
					subnodes[positionOfNextNode] = subnodes[positionOfNextNode].delete(s.substring(1));
				}
			}
			// As a final step. can we delete the nodes
			// remember. we can only delete a node at this point if it is not a valid end
			// point and it has no subtrees
			// otherwise we need to leave it alone.
			if (!isValidEnd) {
				boolean canDeleteNode = true;
				for (int i = 0; i < subnodes.length; i++) {
					if (subnodes[i] != null)
						canDeleteNode = false;
				}

				// if we can remove this node then return false
				if (canDeleteNode)
					return null;
				else
					return this;
			}
			return this;
		}

		/**
		 * Searches for a word in a trie
		 * 
		 * @param s the word being searched for
		 * @return true if the word is in the trie, false otherwise
		 */
		public boolean search(String s) {
			int positionOfNextNode = ((int) s.codePointAt(0)) - 97; // 97 is 'a' in ASCII
			if (subnodes[positionOfNextNode] == null) {
				return false; // we don't have the word
			} else { // there are still more characters
				if (s.length() == 1) {
					return subnodes[positionOfNextNode].isValidEnd;
				} else {
					return subnodes[positionOfNextNode].search(s.substring(1));
				}
			}
		}
		
		// Optional challenge
		//
		// "b" is a prefix of "boxed"
		// "bo" is a prefix of "boxed"
		// "box" is a prefix of "boxed"
		// "ba" is not a prefix of "boxed"
		// "a" is not a prefix of "boxed"
		public ArrayList<String> wordsWithPrefix(String s) {
			// 97 is 'a' in ASCII
			int positionOfNextNode = ((int) s.toLowerCase().codePointAt(0)) - 97;
			/* TODO */
			return null;
		}
		
		/**
		 * Optional challenge.
		 */
		public boolean areWordsWithPrefix(String s){
			int positionOfNextNode = ((int)s.codePointAt(0)) - 97; //97 is 'a' in ASCII
			/* TODO */
			return false;
		}

		/**
		 * Extracts the words from the trie
		 * 
		 * @return a list of words (Strings)
		 */
		public ArrayList<String> returnAllWords() {
			ArrayList<String> al = new ArrayList<>();
			// if this is the root node, then we don't want to add that character on
			String prefixString = "";
			if (value == ROOT_NODE_CHAR) {
				prefixString = "";
			} else {
				prefixString = "" + value;
			}
			if (isValidEnd) { // if this is a valid end point we need to add the char we store as a string
				al.add(prefixString);
			}

			// Find all the substrings and add them on
			for (int i = 0; i < subnodes.length; i++) {
				if (subnodes[i] != null) {
					// there be substrings
					ArrayList<String> tempAL = subnodes[i].returnAllWords();
					Iterator<String> it = tempAL.iterator();
					while (it.hasNext()) {
						al.add(prefixString + it.next()); // add our prefix onto each suffix
					}
				}
			}
			return al;
		}

		/**
		 * Counts all the words in the trie
		 * 
		 * Implement this for Q1
		 * 
		 * @return the number of words in the trie
		 */
		public int countAllWords() {
			int numberOfWords = 0;

			//checks if it has found a leaf and increments numberOfWords counted
			if(isValidEnd){
				numberOfWords++;
			}

			//recursive call
			for (int i = 0; i < subnodes.length; i++) {
				if (subnodes[i] != null) {
					numberOfWords += subnodes[i].countAllWords();
				}	
			}
			return numberOfWords;
		}
	}

	/**
	 * Prints all of the words in the Trie to the console
	 */
	public void printAllWords() {
		if (rootNode == null) {
			return;
		} else {
			ArrayList<String> al = rootNode.returnAllWords();

			Iterator<String> it = al.iterator();
			while (it.hasNext()) {
				System.out.println(it.next());
			}
		}
	}

	/**
	 * inserts a word into the trie
	 * 
	 * @param s the word to be inserted
	 */
	public void insert(String s) {
		if (rootNode == null) {
			rootNode = new TrieNode(ROOT_NODE_CHAR);
		}
		rootNode.insert(s.toLowerCase());
	}

	/**
	 * search for a word in the trie
	 * 
	 * @param s the word being searched for
	 * @return true if word is in thrie, false otherwise
	 */
	public boolean search(String s) {
		return rootNode.search(s.toLowerCase());
	}

	/**
	 * delete a word from the trie
	 * 
	 * @param s the word to be deleted
	 */
	public void delete(String s) {
		rootNode.delete(s.toLowerCase());
	}

	/**
	 * Count all the words in a trie
	 * 
	 * This is part of Question 1
	 * 
	 * @return the count of words in the trie
	 */
	public int countAllWords() {
		if (rootNode == null) {
			return 0;
		} else {
			return rootNode.countAllWords();
		}
	}
	
	/**
	 * Find all words in a trie that have the given prefix
	 * 
	 * Optional challenge.
	 * 
	 * For a Trie containing "boxed"
	 * 
	 *     wordsWithPrefix("bo") should return ["boxed"]
	 *     wordsWithPrefix("boxe") should return ["boxed"]
	 * 
	 * @param str the prefix to search for
	 * @return the list of words that have str as its prefix
	 */
	public ArrayList<String> wordsWithPrefix(String str) {
		if (rootNode == null) {
			return new ArrayList<>();
		}
		else {
			return rootNode.wordsWithPrefix(str);
		}
	}

	/**
	 * Find if a given string is a prefix of a word in a trie
	 * 
	 * Optional challenge.
	 * 
	 * @param str the prefix to search for
	 * @return true if str is a prefix of at least one word in the true, false
	 *         otherwise
	 */
	public boolean areWordsWithPrefix(String str) {
		return false;
	}

	public static void main(String[] args) {
		Trie t = new Trie();
		t.insert("hello");
		t.insert("hell");
		t.insert("zebra");
		t.printAllWords();
	}
}
