import java.util.Comparator;
/**
 * Compares cities by their distances to their previous cities.
 * This is used to sort the Prim's algorithm's queue.
 * @author Deniz Ünal
 *
 */
public class DistanceToPreviousCityComparator implements Comparator<City>{
	
	public int compare(City o1, City o2) {
		return o1.distanceToPreviousCity - o2.distanceToPreviousCity;
	}

}
