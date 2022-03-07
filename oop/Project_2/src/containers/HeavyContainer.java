
//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE

package containers;
	/**
	 * A type of container that weight more than 3 metric tons.
	 * @author deniz ünal
	 *
	 */
public class HeavyContainer extends Container {
	/**
	 * Sets the ID and the weight of the container.
	 * @param ID the container ID.
	 * @param weight the weight of the container.
	 */
	public HeavyContainer(int ID, int weight) {
		super(ID, weight);
	}
	/**
	 * Returns the amount of consumption the container requires for ship to sail per kilometers.
	 * @return the amount of consumption the container requires.
	 */
	public double consumption() {
		return getWeight() * 3.00;
	}
	
}



//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE

