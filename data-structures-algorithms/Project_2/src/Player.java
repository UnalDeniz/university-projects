import java.util.ArrayList;
import java.util.PriorityQueue;
/**
 * Players are the people come to the facility to get various services.
 * Holds the information regarding each player such as id, skill level, spent time in queues,
 * and how many time that each player waited in a queue.
 * Also holds more generic information such as the total invalid and cancelled attempts, maximum length of the queues.
 * @author Deniz Ünal
 *
 */
public class Player {

  final public int id;

  final public int skillLevel;
  
  public double queueEntryTime;
  
  public double lastTrainingDuration;
  
  public double nextSessionDuration;
  /**
   * Spent time in the training queue.
   */
  private double spentTimeTQ = 0;
  /**
   * The number of entry to the training queue.
   */
  private int entryCountTQ = 0;
  /**
   * Spent time in the physiotherapy queue.
   */
  private double spentTimePQ = 0;
  /**
   * The number of entry to the physiotherapy queue.
   */
  private int entryCountPQ = 0;
  /**
   * Spent time in the massage queue.
   */
  private double spentTimeMQ = 0;
  /**
   * The number of entry to the massage queue.
   */
  private int entryCountMQ = 0;
  
  public boolean busy = false;

  private static ArrayList<Player> players = new ArrayList<Player>();
  /**
   * Players in the training queue are  ordered by the rules in the PlayerETComparator class.
   */
  private static PriorityQueue<Player> trainingQueue = new PriorityQueue<Player>(new PlayerETComparator());
  /**
   * Max length of the training queue.
   */
  private static int maxLengthTQ = 0;
  /**
   * Players in the massage queue are  ordered by the rules in the PlayerSLComparator class.
   */
  private static PriorityQueue<Player> massageQueue = new PriorityQueue<Player>(new PlayerSLComparator());
  /**
   * Max length of the massage queue.
   */
  private static int maxLengthMQ = 0;
  /**
   * Players in the physiotherapy queue are  ordered by the rules in the PlayerTDComparator class.
   */
  private static PriorityQueue<Player> physiotherapyQueue = new PriorityQueue<Player>(new PlayerTDComparator());
  /**
   * Max length of the physiotherapy queue.
   */
  private static int maxLengthPQ = 0;
  
  private static int invalidAttempts = 0;

  private static int cancelledAttempts = 0;

  public Player(int id, int skillLevel){
    this.id = id;
    this.skillLevel = skillLevel;
  }
  
  public static void increaseMaxLength(String type) {
	  if(type.equals("t"))
		  maxLengthTQ++;
	  else if(type.equals("p"))
		  maxLengthPQ++;
	  else if(type.equals("m"))
		  maxLengthMQ++;
  }
  
  public static int getMaxLength(String type) {
	  if(type.equals("t"))
		  return maxLengthTQ;
	  if(type.equals("p"))
		  return maxLengthPQ;
	  else
		  return maxLengthMQ;
  }

  public static PriorityQueue<Player> getQueue(String type) {
	  if(type.equals("t")) 
		return trainingQueue;
	  if(type.equals("p"))
		return physiotherapyQueue;
	  else
		return massageQueue;
  }
  
  public static ArrayList<Player> getPlayers() {
	return players;
  }

  public double getSpentTime(String type) {
	  if(type.equals("t"))
		  return spentTimeTQ;
	  if(type.equals("p"))
		  return spentTimePQ;
	  else
		  return spentTimeMQ;
  }
  
  public void increaseSpentTime(double spentTime, String type) {
	  if(type.equals("t"))
		  spentTimeTQ += spentTime;
	  if(type.equals("p"))
		  spentTimePQ += spentTime;
	  else if(type.equals("m"))
		  spentTimeMQ += spentTime;
  }
  
  public int getEntryCount(String type) {
	  if(type.equals("t"))
		  return entryCountTQ;
	  if(type.equals("p"))
		  return entryCountPQ;
	  else
		  return entryCountMQ;
  }
  
  public void increaseEntryCount(String type) {
	  if(type.equals("t"))
		  entryCountTQ++;
	  if(type.equals("p"))
		  entryCountPQ++;
	  else if(type.equals("m"))
		  entryCountMQ++;
  }

  public static int getInvalidAttempts() {
	return invalidAttempts;
  }

  public static void increaseInvalidAttempts() {
	Player.invalidAttempts++;
  }

  public static int getCancelledAttempts() {
	return cancelledAttempts;
  }

  public static void increaseCancelledAttempts() {
	Player.cancelledAttempts++;
  }
  /**
   * Average waiting time is calculated by summing all waiting times and entry counts for each player 
   * in the facility and dividing the waiting time with entry count.
   * @param type shows if the waiting time is for the massage, training or the physiotherapy queue
   * @return average waiting time in a particular queue
   */
  public static double getAverageWaitingTime(String type) {
	  double totalSpentTime = 0;
	  int totalEntryTime = 0;
	  
	  if(type.equals("t")) {
		  for(Player p: players) {
			  totalSpentTime += p.spentTimeTQ;
			  totalEntryTime += p.entryCountTQ;
		  }
	  } else if(type.equals("p")) {
		  for(Player p: players) {
			  totalSpentTime += p.spentTimePQ;
			  totalEntryTime += p.entryCountPQ;
		  }
	  } else if(type.equals("m")) {
		  for(Player p: players) {
			  totalSpentTime += p.spentTimeMQ;
			  totalEntryTime += p.entryCountMQ;
		  }
	  }
	  if(totalEntryTime == 0)
		  return 0;
	  return totalSpentTime / totalEntryTime;
  }
  /**
   * Average turnaround time is calculated by summing average waiting time
   *  in training and physiotherapy queues and  average session time of
   *   training and physiotherapy sessions.
   * @return average turnaround time
   */
  public static double getAverageTurnaroundTime() {
	  double time = 0;
	  time += getAverageWaitingTime("t");
	  time += Session.getAverageSessionTime("t");
	  time += getAverageWaitingTime("p");
	  time += Session.getAverageSessionTime("p");
	  return time;
  }
  /**
   * @return the player that waited most in the physiotherapy queue
   */
  public static Player getMostTimePQ() {
	   Player mostTimePQ = players.get(0);
	   for(Player p: players) {
		   if(Math.abs(p.getSpentTime("p") - mostTimePQ.getSpentTime("p")) < 0.0000000001) {
				if(p.id < mostTimePQ.id)
					mostTimePQ = p;
			} else if(p.getSpentTime("p") > mostTimePQ.getSpentTime("p"))
				mostTimePQ = p;
	   }
	   return mostTimePQ;
  }
  /**  
   * @return the player that waited least in the massage queue among the players that took the massage service 3 times.
   */
  public static Player getLeastTimeMQ() {
	   Player leastTimeMQ = null;
	   for(Player p:players) {
		   if(p.getEntryCount("m") == 3) {
				if(leastTimeMQ == null)
					leastTimeMQ = p;
				else if(Math.abs(p.getSpentTime("m") - leastTimeMQ.getSpentTime("m")) < 0.0000000001) {
					if(p.id < leastTimeMQ.id)
						leastTimeMQ = p;
				} else if(p.getSpentTime("m") < leastTimeMQ.getSpentTime("m"))
					leastTimeMQ = p;
			}
	   }
	   return leastTimeMQ;
   }

}
