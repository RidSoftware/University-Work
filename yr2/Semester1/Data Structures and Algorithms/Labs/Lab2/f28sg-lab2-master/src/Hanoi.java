class HanoiException extends RuntimeException {
	public HanoiException(String err) {
		super(err);
	}
}

public class Hanoi {
	/*
	 * Part4: Tower of Hanoi
	 */

	// our game will always use 3 Hanoi towers
	private final int TOWERS = 3;
	private Stack[] towers = new Stack[TOWERS];
	private int numRings;

	/**
	 * Initialises the Hanoi towers.
	 * 
	 * @param numRings how many rings to involve in the game.
	 */
	public Hanoi(int numRings) {
		this.numRings = numRings;

		// initialise each tower as a stack, which a capacity matching
		// the number of rings in the game.
		for (int i = 0; i < TOWERS; i++) {
			towers[i] = new Stack(numRings);
		}

		// put all the game's rings on the first tower
		for (int i = 0; i < numRings; i++) {
			towers[0].push(new Ring(numRings - i));
		}
	}

	/**
	 * Question 2A
	 * 
	 * @param from the tower to remove a ring from
	 * @param to   the tower to put the ring onto the top of
	 */
	public void moveOneRing(int from, int to) {
		/* TODO */

		/*
		 * Checks the invariant that a ring can only be placed on a larger ring. Leave
		 * these here.
		 */
		checkTower(to);
		checkTower(from);
	}

	/**
	 * Question 2B
	 * 
	 * Move a pile of rings from one tower to another tower. This is a "big step"
	 * operation. The trick is to use recursion to make sure the execution order of
	 * calls to {@link #moveOneRing(int,int)} with the correct tower index arguments
	 * {@from} and {@to} such that when the game is executed by {@link #playHanoi()}
	 * the game completes without violating the rules checked by
	 * {@link #checkTower(int)} and the JUnit tests in HanoiTest.java.
	 * 
	 * For example, to play with 3 rings, moving them all from tower A to tower B,
	 * the valid execution is:
	 * 
	 * <pre>
	 * moveOneRing(0,1)
	 * moveOneRing(0,2)
	 * moveOneRing(1,2)
	 * moveOneRing(0,1)
	 * moveOneRing(2,0)
	 * moveOneRing(2,1)
	 * moveOneRing(0,1)
	 * </pre>
	 * 
	 * where 0 is tower A, 1 is tower B, 2 is tower C.
	 *
	 * @param n    a counter that, when n==1 means we've removed all rings above the
	 *             bottom ring
	 * @param from the index of the tower to move all rings from
	 * @param to   the index of the tower to move all rings to
	 * @param via  the index of the tower which intermediate rings will be moved to
	 */
	public void movePile(int n, int from, int to, int via) {
		/* TODO */
	}

	/**
	 * @param i the index of the tower, starting indexing at 0.
	 * @return the Hanoi stack.
	 */
	public Stack getTower(int i) {
		return towers[i];
	}

	public void playHanoi() {
		/// move all rings from tower A (0), to tower B (1), via tower C (2)
		movePile(numRings, 0, 1, 2);
	}

	/**
	 * After each ring move, check the invariant that every ring is larger than all
	 * rings stacked higher on the same tower.
	 * 
	 * @param towerIndex the tower to check this invariant.
	 */
	private void checkTower(int towerIndex) {
		Stack ringsCopy = (Stack) towers[towerIndex].clone();
		int ringOnTopSize = -1;
		while (!ringsCopy.isEmpty()) {
			Ring nextRing = (Ring) ringsCopy.pop();
			if (nextRing.getRingSize() < ringOnTopSize) {
				throw new HanoiException("a smaller ring is beneath a larger ring on tower " + towerIndex);
			}
			ringOnTopSize = nextRing.getRingSize();
		}
	}
}

/**
 * Simulates a Hanoi ring moved between Hanoi towers.
 */
class Ring {
	// The size of a ring, where the larger the integer value for 'size',
	// the larger the ring.
	private int size;

	public Ring(int size) {
		this.size = size;
	}

	public int getRingSize() {
		return size;
	}
}