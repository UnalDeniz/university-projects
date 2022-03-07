import java.util.ArrayList;
/**
 * The students who will be located to houses.
 * @author Deniz Ünal
 *
 */
public class Student implements Comparable<Student>{
	/**
	 * The id of the student.
	 */
	private final int id;
	/**
	 * The name of the student.
	 */
	final String name;
	/**
	 * The remaining duration until the graduation of the student.
	 */
	private int duration;
	/**
	 * The minimum rating of the houses that student will accept being located to.
	 */
	final double rating;
	/**
	 * The ArrayList that contains students that is currently unsettled.
	 */
	private static ArrayList<Student> unsettledStudents = new ArrayList<Student>();
	/**
	 * The ArrayList that contains students that are currently located.
	 */
	private static ArrayList<Student> locatedStudents = new ArrayList<Student>();
	/**
	 * The ArrayList that contains graduates who never located to houses. 
	 */
	private static ArrayList<Student> unsettledGraduates = new ArrayList<Student>();
	/**
	 * The constructor method for the Student class.
	 * @param id the id of the student.
	 * @param name the name of the student.
	 * @param duration the remaining duration until graduation.
	 * @param rating the minimum preffered rating for the house.
	 */
	public Student(int id, String name, int duration, double rating){
		this.id = id;
		this.name = name;
		this.duration = duration;
		this.rating = rating;
	}
	/**
	 * Adds the student to the PriorityQueue of graduates.
	 */
	public void graduate() {
		getUnsettledGraduates().add(this);
	}
	/**
	 * Decreases the duration by 1.
	 */
	public void endTerm() {
		duration = getDuration() - 1;
	}
	/**
	 * The compareTo method for the Student class.
	 */
	public int compareTo(Student other) {
		return this.id - other.id;
	}
	/**
	 * The getter method for the PriorityQueue of unsettled students.
	 * @return PriorityQueue of unsettled students.
	 */
	public static ArrayList<Student> getUnsettledStudents() {
		return unsettledStudents;
	}
	/**
	 * The getter method for the PriorityQueue of unsettled graduates.
	 * @return
	 */
	public static ArrayList<Student> getUnsettledGraduates() {
		return unsettledGraduates;
	}
	/**
	 * The getter method for the duration.
	 * @return
	 */
	public int getDuration() {
		return duration;
	}
	/**
	 * Getter method for the located students ArrayList.
	 * @return located students ArrayList.
	 */
	public static ArrayList<Student> getLocatedStudents() {
		return locatedStudents;
	}
}
