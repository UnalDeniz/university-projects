import java.util.ArrayList;
import java.util.PriorityQueue;

/**
 * Cities are places that Leyla and Mecnun resides and could go in the honeymoon.
 * Each city has a name, distance to Mecnun's city and the previous city in the path from the Mecnun's city.
 * Roads that starts in a city are held in that city's object.
 * @author Deniz Ünal
 *
 */
public class City implements Comparable<City> {

	final public String name;
	private int distanceToMecnun = Integer.MAX_VALUE;
	public int distanceToPreviousCity = Integer.MAX_VALUE;
	private City previousCity = null;
	private boolean visited = false; 
	/**
	 * List of roads that start in this city.
	 */
	final public ArrayList<Road> outgoingRoads = new ArrayList<Road>();
	
	private static City leylaCity;
	private static City mecnunCity;
	public static String leylaCityName;
	public static String mecnunCityName;
	/**
	 * List of cities in the left side of the country.
	 */
	final public static ArrayList<City> cCities = new ArrayList<City>();
	/**
	 * List of cities in the right side of the country.
	 */
	final public static ArrayList<City> dCities = new ArrayList<City>();
	/**
	 * Queue of cities that will be polled for the Dijkstra's algorithm.
	 */
	final private static PriorityQueue<City> toBeVisitedCCities = new PriorityQueue<City>();
	/**
	 * Queue of cities that will be polled for the Prim's algorithm.
	 */
	final private static PriorityQueue<City> toBeVisitedDCities = new PriorityQueue<City>(new DistanceToPreviousCityComparator());
	
	public City(String name) {
		this.name = name;
		if(name.equals(leylaCityName)) {
			distanceToPreviousCity = 0;
			toBeVisitedDCities.add(this);
			leylaCity = this;
		}
		
		if(name.equals(mecnunCityName)) {
			distanceToMecnun = 0;
			toBeVisitedCCities.add(this);
			mecnunCity = this;
		}
	}
	
	public int compareTo(City other) {
		return this.distanceToMecnun - other.distanceToMecnun;
	}
	/**
	 * Dijkstra's Algorithm.
	 * Starting from Mecnun's city travels through left side of the country while prioritizing the cities 
	 * that are closer to the Mecnun's city and whenever a shortest path from Mecnun is found,
	 *  updates the city and adds it to queue.
	 */
	private static void findShortestPaths() {
		while(!toBeVisitedCCities.isEmpty()) {
			City city = toBeVisitedCCities.poll();
			for(Road r: city.outgoingRoads) {
				City destination;
				if(r.destination.charAt(0) == 'c')
					destination = cCities.get(Integer.parseInt(r.destination.substring(1))-1);
				else 
					destination = dCities.get(Integer.parseInt(r.destination.substring(1))-1);
				
				if(destination.distanceToMecnun > city.distanceToMecnun + r.length) {
					destination.previousCity = city;
					destination.distanceToMecnun = city.distanceToMecnun + r.length;
					if(toBeVisitedCCities.contains(destination)) 
						toBeVisitedCCities.remove(destination);	
					toBeVisitedCCities.add(destination);
				}
			}
		}
	}
	/**
	 * Starts Dijkstra's algorithm and returns the shortest path from Mecnun to Leyla.
	 * If there is no such path returns -1.
	 * @param timeLimit
	 * @return String of cities that are in the path from Mecnun to Leyla.
	 */
	public static String returnRoadToLeyla() {
		findShortestPaths();
		String roadToLeyla = leylaCityName;
		if(leylaCity.previousCity == null)
			return "-1";
		for(City c = leylaCity; c != mecnunCity; c = c.previousCity) {
			roadToLeyla = c.previousCity.name + " " + roadToLeyla;
		}
		return roadToLeyla;
	}
	/**
	 * Prim's Algorithm.
	 * Starting from Leyla's city travels through the right side of the country while prioritizing the cities 
	 * that are closer to their previous cities and whenever a shorter road to a city is found,
	 *  updates that city and adds it to queue.
	 */
	private static void findTheHoneymoonRoute() {
		while(!toBeVisitedDCities.isEmpty()) {
			City city = toBeVisitedDCities.poll();
			city.visited = true;
			for(Road r: city.outgoingRoads) {
				City destination;
				if(r.destination.charAt(0) == 'c')
					destination = cCities.get(Integer.parseInt(r.destination.substring(1))-1);
				else 
					destination = dCities.get(Integer.parseInt(r.destination.substring(1))-1);
				if(!destination.visited) {
					if(destination.distanceToPreviousCity > r.length) {
						destination.previousCity = city;
						destination.distanceToPreviousCity = r.length;
						if(toBeVisitedDCities.contains(destination))
							toBeVisitedDCities.remove(destination);
						toBeVisitedDCities.add(destination);
					}
				}
			}
		}
	}
	/**
	 * Starts Prim's algorithm and returns the total tax cost for the honeymoon.
	 * If Leyla and Mecnun aren't able to get married returns -1, if they cannot 
	 * find a suitable path for the honeymoon returns -2
	 * @param timeLimit the limit that Leyla's father set.
	 * @return total tax cost for the honeymoon.
	 */
	public static int returnHoneymoonCost(int timeLimit) {
		findTheHoneymoonRoute();
		int honeymoonCost = 0;
		if(leylaCity.previousCity == null || leylaCity.distanceToMecnun > timeLimit)
			return -1;
		for(City c:dCities) {
			if(c.previousCity == null)
				return -2;
			honeymoonCost += c.distanceToPreviousCity;
		}
		return 2*honeymoonCost;
	}
}
