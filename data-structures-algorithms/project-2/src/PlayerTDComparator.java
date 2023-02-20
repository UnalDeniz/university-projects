import java.util.Comparator;
/**
 * PlayerTDComparator is used to order players that are in the physiotherapy queue.
 * @author Deniz Ünal
 *
 */
public class PlayerTDComparator implements Comparator<Player>{
	/**
	 * Player with the higher last training duration will get the service first.
	 * If the skill levels are equal, the player with the lowest entry time to the queue,
	 * and if the entry times are also equal, the player with the lowest id will 
	 * get the service first.
	 */
	public int compare(Player o1, Player o2) {
		if(Math.abs(o1.lastTrainingDuration - o2.lastTrainingDuration) < 0.0000000001 && Math.abs(o1.queueEntryTime - o2.queueEntryTime) < 0.0000000001)
			return o1.id - o2.id;
		if(Math.abs(o1.lastTrainingDuration - o2.lastTrainingDuration) < 0.0000000001) {
			if(o1.queueEntryTime > o2.queueEntryTime)
				return 1;
			else
				return -1;
		}
		if(o2.lastTrainingDuration > o1.lastTrainingDuration)
			return 1;
		else
			return -1;
	}
	
}
