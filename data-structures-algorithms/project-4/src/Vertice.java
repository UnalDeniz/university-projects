import java.util.ArrayList;
/**
 * A vertice can be a bag or a transporter.
 * @author Deniz Ünal	
 *
 */
public class Vertice {
	/**
	 * visited is true if the vertice is visited in the current step of the max-flow algorithm.
	 */
	public boolean visited = false;
	/**
	 * This arraylist holds the edges that starts from this vertice.
	 */
	private ArrayList<Edge> outgoingEdges = new ArrayList<Edge>();
	
	public ArrayList<Edge> getOutgoingEdges() {
		return outgoingEdges;
	}
	
}
