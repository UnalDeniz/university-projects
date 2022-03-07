import java.util.ArrayList;
/**
 * The houses that students will be located to.
 * @author Deniz Ünal
 *
 */
public class House implements Comparable<House>{
	/**
	 * Id of the house.
	 */
	private final int id;
	/**
	 * The remaining duration until the house is empty.
	 */
	private int duration;
	/**
	 * Rating of the house.
	 */
	final double rating;
	/**
	 * The state of the house being empty or not.
	 */
	private boolean isEmpty;
    /**
     * ArrayList that contains the houses.
     */
	private static ArrayList<House> houses = new ArrayList<House>();
	/**
	 * Constructor method for the house.
	 * @param id the id of the house
	 * @param duration the remaining duration until the house is empty.
	 * @param rating the rating of the house.
	 */
	public House(int id, int duration, double rating, boolean isEmpty) {
		this.id = id;
		this.duration = duration;
		this.rating = rating;
		this.isEmpty = isEmpty;
	}
	/**
	 * Sets the house as empty.
	 */
	public void emptyHouse() {
		isEmpty = true;
	}
	/**
	 * Sets the house as not empty.
	 * Also set the duration to the duration of the student.
	 * @param student the student who will be allocated to this house.
	 */
	public void fillHouse(Student student) {
		isEmpty = false;
		this.duration = student.getDuration();
	}
	/**
	 * Decreases the duration by 1.
	 */
	public void endTerm() {
		duration = getDuration() - 1;
	}
	/**
	 * compareTo method for the House class.
	 * Compares houses by their ids.
	 */
	public int compareTo(House other) {
		return this.id - other.id;
	}
	/**
	 * Getter method for the houses ArrayList.
	 * @return the houses ArrayList.
	 */
	public static ArrayList<House> getHouses() {
		return houses;
	}
	/**
	 * Getter method for the duration
	 * @return the duration.
	 */
	public int getDuration() {
		return duration;
	}
	/**
	 * Getter method for the isEmpty variable.
	 * @return isEmpty variable.
	 */
	public boolean isEmpty() {
		return isEmpty;
	}
}
