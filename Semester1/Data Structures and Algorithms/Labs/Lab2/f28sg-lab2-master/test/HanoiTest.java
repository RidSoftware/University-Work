import static org.junit.Assert.*;

import org.junit.Test;

public class HanoiTest {

	@Test
	public void playOneRing() {
		playNRings(1);
	}

	@Test
	public void playTwoRings() {
		playNRings(2);
	}

	@Test
	public void playThreeRings() {
		playNRings(3);
	}

	@Test
	public void playFourRings() {
		playNRings(4);
	}

	@Test
	public void playFiveRings() {
		playNRings(5);
	}

	@Test
	public void playSixRings() {
		playNRings(6);
	}

	@Test
	public void playSevenRings() {
		playNRings(7);
	}

	@Test
	public void playEightRings() {
		playNRings(8);
	}

	@Test
	public void playNineRings() {
		playNRings(9);
	}

	@Test
	public void playTenRings() {
		playNRings(10);
	}

	@Test
	public void playTwentyRings() {
		playNRings(20);
	}

	/**
	 * Play the Hanoi tower game with a given number of rings.
	 * 
	 * Tower A has index 0, Tower B has index 1, Tower C has index 2
	 * 
	 * @param rings the number of rings to play in the game.
	 */
	public void playNRings(int rings) {
		Hanoi game = new Hanoi(rings);
		game.playHanoi();

		// ensure tower A is empty
		assertEquals(0, game.getTower(0).size());
		// ensure tower B is full
		assertEquals(rings, game.getTower(1).size());
		// ensure tower C is empty
		assertEquals(0, game.getTower(2).size());
	}
}