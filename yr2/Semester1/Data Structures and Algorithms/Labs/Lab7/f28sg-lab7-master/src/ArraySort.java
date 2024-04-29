import java.util.ArrayList;
import java.util.Iterator;

public class ArraySort {

	/** Insertion sort of an array
	 * @param arr the array to be sorted in-place
	 */
	public static void insertionSort(int[] arr) {
		for (int i = 1; i < arr.length; i++) {
			int cur = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j] > cur) {
				arr[j + 1] = arr[j--];
				arr[j + 1] = cur;
			}
		}
	}

	/** Bubble sort of an array
	 * 
	 * This is Question 3
	 * 
	 * TODO Where N is the number of elements in the array 'arr' the complexity is:
	 *
	 * O(N^2)
	 * 
	 * @param arr the array to be sorted in-place
	 */
	public static void bubbleSort(int[] arr) {

		boolean swaps = true;

		//swaps is used to flag if a swap took place during the iteration
		//as if no swaps to place then it should be ordered
		while (swaps) {
			swaps = false;
		
			//iterates through the array, -1 length as swapping is impossible on the last element
			for (int i = 0; i < arr.length-1; i++){

				if (arr[i] > arr[i+1]) {
					//uses a temporary integer to swap elements if
					int temp = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = temp;

					swaps = true;
				}

			}

		}

	}

	/** Quick sort of an array. This method creates a new array with
	 * its values sorted, based on the values in the unsorted input array S.
	 * 
	 * This is Question 5
	 * 
	 * TODO Where N is the number of elements in the array 'S' the complexity is:
	 *
	 * O(NlogN)
	 * 
	 * @param S the unsorted input array
	 * @return the sorted output array
	 */
	public static ArrayList<Integer> quickSort(ArrayList<Integer> S) {
		//handles cases of empty and 1 element list
		//as they are already "sorted"
		if (S.size() <= 1) {
			return S;
		}

		//sets the pivot to the middle of the array list
		//size/2 should be fine for cases of odd numbers as it is of type int
		int pivot = S.get(S.size()/2);

		//creates the 3 array lists 
		ArrayList<Integer> L = new ArrayList<>();
		ArrayList<Integer> E = new ArrayList<>();
		ArrayList<Integer> G = new ArrayList<>();

		//assigns all values to the subarrays,relative to their value with pivot
		while (S.size() > 0) {
			int current = S.get(0);

			if (current< pivot) {
				L.add(current);
			} else if (current == pivot){
				E.add(current);
			} else {
				G.add(current);
			}

			S.remove(0);
		}

		//recursively sorts L and G
		ArrayList<Integer> sortedL = quickSort(L);
		ArrayList<Integer> sortedG = quickSort(G);


		ArrayList<Integer> sortedS = new ArrayList<>();

		//adds sorted lists into the new arraw list in sorted order
		sortedS.addAll(sortedL);
		sortedS.addAll(E);
		sortedS.addAll(sortedG);

		//returns new sorted list
		return sortedS;
	}

	
	/** predicate to check if array is sorted
	 * @param arr the array to be checked
	 * @return true if the array is sorted, false otherwise
	 */
	public static boolean isSorted(int[] arr) {
		for (int i = 0; i < arr.length - 1; i++)
			if (arr[i] > arr[i + 1])
				return false;
		return true;
	}

	
	/** predicate to check if arrayList is sorted.
	 *  Useful for checking ArrayList<Integer> lists returned
	 *  from Quick Sort.
	 * 
	 * @param arr the array to be checked
	 * @return true is the aray is sorted, flalse otherwise
	 */
	public static boolean isSorted(ArrayList<Integer> arr) {
		Iterator i = arr.iterator();
		int val;
		if (i.hasNext())
			val = (int) i.next();
		else
			return true;
		while (i.hasNext()) {
			int nv = (int) i.next();
			if (val > nv)
				return false;
			val = nv;
		}
		return true;
	}

	
	/** Helper printing methods for testing
	 * @param arr the array to print
	 */
	private static void printIntArray(int[] arr) {
		System.out.print("[ ");
		for (Integer i : arr) {
			System.out.print(i + " ");
		}
		System.out.println(" ]");
	}

	private static void printIntArrayList(ArrayList<Integer> arr) {
		System.out.print("[ ");
		for (Integer i : arr) {
			System.out.print(i + " ");
		}
		System.out.println(" ]");
	}

	public static void main(String[] args) {
		// testing part1
		int[] arr1 = { 5, 4, 3, 2, 1 };
		bubbleSort(arr1);
		printIntArray(arr1);

		// testing part2
		ArrayList<Integer> arr2 = new ArrayList<Integer>();
		arr2.add(3);
		arr2.add(1);
		arr2.add(6);
		arr2.add(5);
		ArrayList<Integer> arr2_sorted = quickSort(arr2);
		printIntArrayList(arr2_sorted);
		// {5,4,3,5,1};

	}

}
