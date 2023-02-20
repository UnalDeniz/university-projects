import java.util.Comparator;
/**
 * PlayerETComparator is used to order players that are in the training queue.
 * @author Deniz Ünal
 *
 */
public class PlayerETComparator implements Comparator<Player> {
	/**
	 * Player with the lowest entry time to the queue will get the service first.
	 * If the entry times are equal, the player with the lowest id will get the service first.
	 */
	public int compare(Player o1, Player o2) {
		if(Math.abs(o1.queueEntryTime - o2.queueEntryTime) < 0.0000000001)
			return o1.id - o2.id;
		if(o1.queueEntryTime > o2.queueEntryTime)
			return 1;
		else
	        return -1;
		}
	
}