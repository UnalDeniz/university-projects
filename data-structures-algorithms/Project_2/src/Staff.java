/**
 * Staff are the people that handle the sessions.
 * @author Deniz Ünal
 *
 */
public abstract class Staff implements Comparable<Staff> {
	
	final private int id;
	
	public Staff(int id) {
		this.id = id;
	}
	/**
	 * Staff members are ordered by their id numbers
	 * so that staff member with the lowest id will 
	 * give service first.
	 */
	public int compareTo(Staff other) {
		return this.id - other.id;
	}

}
