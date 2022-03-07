/**
 * Roads connect two cities to each other.
 * This class holds the length of the road and the destination city.
 * @author Deniz Ünal
 *
 */
public class Road {
	
	final public int length;
	final public String destination;
	
	public Road(String destination, int length) {
		this.length = length;
		this.destination = destination;
	}

}
