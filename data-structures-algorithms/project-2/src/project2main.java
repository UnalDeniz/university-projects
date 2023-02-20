import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;
/**
 * project2main is the class that includes the main method.
 * Starts the simulation by taking inputs and writes desired outputs at the end of the simulation.
 * @author Deniz Ünal
 *
 */
public class project2main {
	/**
	 * Main method tarts the simulation by taking inputs and writes desired outputs at the end of the simulation.
	 * @param args input file and output file
	 */
  public static void main(String args[]) throws FileNotFoundException{

	File input = new File(args[0]);
	File output = new File(args[1]);
		
	Scanner in = new Scanner(input);
	PrintStream out = new PrintStream(output);
	
	int playerCount = in.nextInt();
	
	for(int i = 0; i < playerCount; i++) {
		int id = in.nextInt();
		int skillLevel = in.nextInt();
		Player.getPlayers().add(new Player(id, skillLevel));
	}
	
	int arrivalCount = in.nextInt();
	
	for(int j = 0; j < arrivalCount; j++) {
		String type = in.next();
		Player player = Player.getPlayers().get(in.nextInt());
		double time = in.nextDouble();
		double duration = in.nextDouble();
		Event.getEvents().add(new StartEvent(player, time, duration, type));
	}
	
	int physiotherapistCount = in.nextInt();
	
	for(int k = 0; k < physiotherapistCount; k++) {
		double serviceTime = in.nextDouble();
		Physiotherapist.getPhysiotherapists().add(new Physiotherapist(k, serviceTime));
	}
	
	int trainingCoachCount = in.nextInt();
	int masseurCount = in.nextInt();
	
	for(int l = 0; l < trainingCoachCount; l++) {
		TrainingCoach.getTrainingCoaches().add(new TrainingCoach(l));
	}
	
	for(int m = 0; m < masseurCount; m++) {
		Masseur.getMasseurs().add(new Masseur(m));
	}
	
	while(!Event.getEvents().isEmpty()) {
		Event.getEvents().poll().initializeEvent();
	}
	
	out.println(Player.getMaxLength("t"));
	out.println(Player.getMaxLength("p"));
	out.println(Player.getMaxLength("m"));

	out.println(String.format("%.3f", Player.getAverageWaitingTime("t")));
	out.println(String.format("%.3f", Player.getAverageWaitingTime("p")));
	out.println(String.format("%.3f", Player.getAverageWaitingTime("m")));
	
	out.println(String.format("%.3f", Session.getAverageSessionTime("t")));
	out.println(String.format("%.3f", Session.getAverageSessionTime("p")));
	out.println(String.format("%.3f", Session.getAverageSessionTime("m")));
	
	out.println(String.format("%.3f", Player.getAverageTurnaroundTime()));
	
	out.println(Player.getMostTimePQ().id + " " + String.format("%.3f", Player.getMostTimePQ().getSpentTime("p")));
	
	if(Player.getLeastTimeMQ() == null)
		out.println("-1 -1");
	else
		out.println(Player.getLeastTimeMQ().id + " " + String.format("%.3f", Player.getLeastTimeMQ().getSpentTime("m")));
	
	out.println(Player.getInvalidAttempts());
	out.println(Player.getCancelledAttempts());
	
	out.println(String.format("%.3f", Event.currentTime));
	
	in.close();
	out.close();
		
  }

}
