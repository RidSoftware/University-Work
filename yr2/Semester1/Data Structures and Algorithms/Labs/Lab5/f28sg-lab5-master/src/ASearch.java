public class ASearch {


	private Entry[] catalogue;
	private int current;
	
	/*
	 * Assume 10 entries
	 */
	public ASearch(){
		catalogue = new Entry[10];
		current = 0;
	}
	
	/*
	 * Ignores adding if full (should really be handled by exception...)
	 */
	public void addEntry(Entry e){
		if(current < 10){
			catalogue[current++] = e;
		}
	}
	
	/*
	 * Part 2: complete implementation
	 */
	/**
	 * Uses linear search to look up a given name in the catalogue and returns the
	 * number if the name is in the catalogue. Otherwise it returns -1.
	 * 
	 * TODO Where N is the number of entries in the catalogue the (worst case) complexity is:
	 *
	 * O(N)
	 *  
	 * @param name is the person name to look for in the catalogue
	 * @return the number of that person, otherwise -1 to indicate an error
	 */
	public int linearSearch(String name){
		// loops through each entry in the catalogue
		// if the name matches, then returns the number, w/ getName() and getNumber() 
		for (int i = 0; i < current ; i++){
			if(catalogue[i].getName() == name){
				return catalogue[i].getNumber();
			}
		}
		
		return -1;
	}

	/*
	 * Part 4: complete implementation
	 */
	/**
	 * Uses binary search to look up a given name in the catalogue and returns the
	 * number if the name is in the catalogue. Otherwise it returns -1.
	 * 
	 * TODO Where N is the number of entries in the catalogue the (worst case) complexity is:
	 *
	 * O(log n)
	 *  
	 * @param first the array index of the start of search space
	 * @param last the array index of the end of the search space
	 * @param name the person name being searched for
	 * @return the persons phone number if their name is found or -1 otherwise
	 */

	private int binarySearch(int first,int last,String name){
		
		while(first <= last){
			//instansiate variables
			int middle = first + (last - first) / 2;
			String midName = catalogue[middle].getName();

			//if statement
			if(midName.compareTo(name) == 0){
				// if the names match, return the number
				return catalogue[middle].getNumber();

			} else if (midName.compareTo(name) < 0) {
				// if the middle name is smaller than target name, 
				// then changes the search space to the riggt half
				first = middle + 1;

			} else if (midName.compareTo(name) > 0){
				// if the middle name is larger than target name, 
				// then changes the search space to the left half
				last = middle - 1;

			}

		}

		return -1;
	}

	// helper method exposed to the programmer
	public int binarySearch(String name){
		return binarySearch(0,current-1,name);
	}
	
	
}
