import java.util.PriorityQueue;
/**
 * Training coaches are the staff members that handle the training sessions.
 * @author Deniz Ünal
 *
 */
public class TrainingCoach extends Staff {

  private static PriorityQueue<TrainingCoach> trainingCoaches = new PriorityQueue<TrainingCoach>();

  public TrainingCoach(int id){
    super(id);
  }
  
  public static PriorityQueue<TrainingCoach> getTrainingCoaches(){
	  return trainingCoaches;
  }

}
