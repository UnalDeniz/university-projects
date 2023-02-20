
//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE

package containers;
	/**
	 * The container that can be present on the ports and can be load to ships.
	 * Each container has its own unique ID and weight.
	 * @author deniz ünal
	 *
	 */
public abstract class Container implements Comparable<Container> {
	/**
	 * The container ID.
	 */
	final private int ID;
	/**
	 * The weight of the container.
	 */
	final private int weight;
	/**
	 * Sets the ID and the weight of the container.
	 * @param ID the container ID.
	 * @param weight the weight of the container.
	 */
	public Container(int ID, int weight) {
		this.ID = ID;
		this.weight = weight;
	}
	/**
	 * Returns the amount of consumption the container requires for ship to sail per kilometers.
	 * @return the amount of consumption the container requires.
	 */
	public abstract double consumption();
	/**
	 * compareTo method for container class.
	 * Compares container IDs.
	 */
	public int compareTo(Container other) {
		return this.ID - other.ID;
	}
	/**
	 * Checks if this and the other container in the parameters are equal.
	 * Compares the container IDs, weights and container types. If any of them
	 * are different, returns false.
	 * @param other the other container that will be compared to this.
	 */
	public boolean equals(Container other) {
		if(this.ID == other.ID && this.getWeight() == other.getWeight() && this.getClass() == other.getClass()) {
			return true;
		} else {
			return false;
		}
	}
	/**
	 * Getter method for the weight of the container.
	 * @return the weight of the container
	 */
	public int getWeight() {
		return weight;
	}
	/**
	 * Getter method for the container ID.
	 * @return the container ID.
	 */
	public int getID() {
		return ID;
	}
	
}



//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE

