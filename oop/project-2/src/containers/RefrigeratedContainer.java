
//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE

package containers;
	/**
	 * A special type of heavy container that has its own consumption calculation.
	 * Not limited to any weight restriction.
	 * @author deniz ünal
	 *
	 */
public class RefrigeratedContainer extends HeavyContainer{
	/**
	 * Sets the ID and the weight of the container.
	 * @param ID the container ID.
	 * @param weight the weight of the container.
	 */
	public RefrigeratedContainer(int ID, int weight) {
		super(ID, weight);
	}
	/**
	 * Returns the amount of consumption the container requires for ship to sail per kilometers.
	 * @return the amount of consumption the container requires.
	 */
	public double consumption() {
		return getWeight() * 5.00;
	}

}



//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE

