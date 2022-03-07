import java.util.Comparator;
/**
 * PlayerSLComparator is used to order players that are in the massage queue.
 * @author Deniz Ünal
 *
 */
public class PlayerSLComparator implements Comparator<Player> {
	/**
	 * Player with the higher skill level will get the service first.
	 * If the skill levels are equal, the player with the lowest entry time to the queue,
	 * and if the entry times are also equal, the player with the lowest id will 
	 * get the service first.
	 */
	public int compare(Player o1, Player o2) {
		if(o1.skillLevel == o2.skillLevel && Math.abs(o1.queueEntryTime - o2.queueEntryTime) < 0.0000000001)
			return o1.id - o2.id;
		if(o1.skillLevel == o2.skillLevel) {
			if(o1.queueEntryTime > o2.queueEntryTime)
				return 1;
			else
				return -1;
		}
		return o2.skillLevel - o1.skillLevel;
	}
	
}
