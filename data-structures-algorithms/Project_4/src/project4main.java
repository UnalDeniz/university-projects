import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;
/**
 * This class is the starting point of the execution of this project.
 * It contains the main class.
 * @author Deniz Ünal
 *
 */
public class project4main {
	/**
	 * This method takes the input, creates the vertices and calls the methods from other classes to generate the output.
	 * @param args input file, output file
	 * @throws FileNotFoundException
	 */
	public static void main(String[] args) throws FileNotFoundException {
		
		File input = new File(args[0]);
		File output = new File(args[1]);
		
		Scanner in = new Scanner(input);
		PrintStream out = new PrintStream(output);
		
		int greenRegionTrainCount = in.nextInt();
		
		for(int i=0; i<greenRegionTrainCount; i++) {
			Transporter greenRegionTrain = new Transporter(in.nextInt());
			Transporter.getGreenRegionTrains().add(greenRegionTrain);
			Transporter.getTransporters().add(greenRegionTrain);
		}
		
		int redRegionTrainCount = in.nextInt();
		
		for(int i=0; i<redRegionTrainCount; i++) {
			Transporter redRegionTrain = new Transporter(in.nextInt());
			Transporter.getRedRegionTrains().add(redRegionTrain);
			Transporter.getTransporters().add(redRegionTrain);
		}
		
		int greenRegionDeerCount = in.nextInt();
		
		for(int i=0; i<greenRegionDeerCount; i++) {
			Transporter greenRegionDeer = new Transporter(in.nextInt());
			Transporter.getGreenRegionDeers().add(greenRegionDeer);
			Transporter.getTransporters().add(greenRegionDeer);
		}
		
		int redRegionDeerCount = in.nextInt();
		
		for(int i=0; i<redRegionDeerCount; i++) {
			Transporter redRegionDeer = new Transporter(in.nextInt());
			Transporter.getRedRegionDeers().add(redRegionDeer);
			Transporter.getTransporters().add(redRegionDeer);
		}
		
		int bagCount = in.nextInt();
		
		for(int i=0; i<bagCount; i++) {
			String type = in.next();
			int giftCount = in.nextInt();
			Bag.getBags().add(new Bag(giftCount, type));
		}
		
		Graph.combineBags();
		Graph.construct();
		
		int totalGiftCount = 0;
		for(Bag b: Bag.getBags()) {
			totalGiftCount += b.giftCount;
		}
		
		out.print(totalGiftCount - Graph.findMaxFlow());
		
		in.close();
		out.close();
		
	}
}
