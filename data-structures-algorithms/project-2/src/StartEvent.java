/**
 * StartEvent is the process of making a request for a service.
 * Holds information regarding exit such as the player, time and the duration of the session.
 * @author Deniz Ünal
 *
 */
public class StartEvent extends Event {
	
  final private double duration;

  public StartEvent(Player player, double time, double duration, String type){
    super(player, time, type);
    this.duration = duration;
  }
  /**
   * Carries out the processes that should happen when a player makes a request for a service.
   * Checks if the player is in another event or a queue at that time or if the massage limit 
   * will be exceeded in case the mentioned service is a massage service. If not adds the player
   * to the queue for the service and holds the information of entry time for the queue and 
   * the duration of the upcoming session.
   */
  public void initializeEvent(){
	Event.currentTime = time;
	
    if(type.equals("m")) {
    	if(player.getEntryCount("m") == 3) {
    		Player.increaseInvalidAttempts();
    	} else if(player.busy) {
    		Player.increaseCancelledAttempts();
    		return;
    	} else {
    		player.busy = true;
    		player.increaseEntryCount("m");
    		player.queueEntryTime = time;
    		player.nextSessionDuration = duration;
    		Player.getQueue("m").add(player);
    		if(Player.getQueue("m").size() > Player.getMaxLength("m") && Masseur.getMasseurs().isEmpty())
    			Player.increaseMaxLength("m");
    	}
    } else if(player.busy) {
		Player.increaseCancelledAttempts();
	} else if(type.equals("t")) {
    	player.busy = true;
    	player.increaseEntryCount("t");
    	player.queueEntryTime = time;
    	player.nextSessionDuration = duration;
    	Player.getQueue("t").add(player);
    	if(Player.getQueue("t").size() > Player.getMaxLength("t") && TrainingCoach.getTrainingCoaches().isEmpty())
    		Player.increaseMaxLength("t");
    } else if(type.equals("p")) {
    	player.busy = true;
    	player.increaseEntryCount("p");
    	player.queueEntryTime = time;
    	Player.getQueue("p").add(player);
    	if(Player.getQueue("p").size() > Player.getMaxLength("p") && Physiotherapist.getPhysiotherapists().isEmpty())
    			Player.increaseMaxLength("p");
    }
    
    Session.startSessions();
  }
  
}
